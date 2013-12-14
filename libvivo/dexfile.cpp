#include "dexfile.h"
#include "util.h"
#include "common.h"

#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <ostream>
#include <memory.h>

namespace vivo
{
    const ubyte_t DexFile::kDefaultMagic[8] = {0x64, 0x65, 0x78, 0x0a, 0x30, 0x33, 0x35, 0x00};

    void* DexFile::dexOpen()
    {
        struct stat st;
        DECHECKNE(name_.size(), 0);
        int fd = open(name_.c_str(), O_RDONLY);
        DECHECKNE(fd, 0);
        stat(name_.c_str(), &st);

        startAddr_ = mmap(NULL, st.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
        DECHECK(startAddr_);

        return startAddr_;
    }

    bool DexFile::dexParse()
    {
        ubyte_t* ptr = reinterpret_cast<ubyte_t*>(startAddr_);
        memcpy(&head_, ptr, sizeof(DexFile::DexHead));
        std::cout<<"Dex Head is" << " " << head_.magic_ << " " << head_.headerSize_ << std::endl;

        return true;
    }
}
