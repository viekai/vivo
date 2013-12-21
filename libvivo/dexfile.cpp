#include "dexfile.h"
#include "util.h"
#include "common.h"
#include "leb.h"

#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <ostream>
#include <memory.h>
#include <errno.h>

namespace vivo
{
    const ubyte_t DexFile::kDefaultMagic[8] = {0x64, 0x65, 0x78, 0x0a, 0x30, 0x33, 0x35, 0x00};

    DexFile::~DexFile()
    {
        if(fd)
            close(fd);

        munmap(startAddr_, size_);
    }

    void* DexFile::dexOpen()
    {
        struct stat st;
        DECHECKNE(name_.size(), 0);
        fd = open(name_.c_str(), O_RDONLY);
        DECHECKNE(fd, 0);
        stat(name_.c_str(), &st);
        size_ = st.st_size;

        startAddr_ = mmap(NULL, size_, PROT_READ, MAP_PRIVATE, fd, 0);

        if((reinterpret_cast<long>(startAddr_) == -1))
        {
            std::cout<< strerror(errno)<<std::endl;
            abort();
        }

        return startAddr_;
    }

    bool DexFile::dexParse()
    {
        head_ = reinterpret_cast<DexFile::DexHead*>(startAddr_);
        std::cout<<"Dex Head is" << " " << head_->magic_ << " " << head_->headerSize_ << std::endl;
        stringData_ = reinterpret_cast<StringIdItem*>(static_cast<ubyte_t*>(startAddr_) + head_->stringIdsOff_);

        return true;
    }
    
    const char* DexFile::StringDataById(uint32_t id)
    {
        if(kNoIdx == id)
            return "";
        const StringIdItem& idItem = stringData_[id];
        ubyte_t* stringData = static_cast<ubyte_t*>(startAddr_) + idItem.offset_;
        return reinterpret_cast<const char*>(stringData + Leb128::uleb128Length(stringData));
    }



}
