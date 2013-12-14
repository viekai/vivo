#include "dexfile.h"
#include "util.h"
#include "common.h"

#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <ostream>

namespace vivo
{
    void* DexFile::dexOpen()
    {
        struct stat st;
        std::cout<<name_.length()<<std::endl;
        DECHECKNE(name_.size(), 0);
        int fd = open(name_.c_str(), O_RDONLY);
        DECHECKNE(fd, 0);
        stat(name_.c_str(), &st);

        startaddr_ = mmap(NULL, st.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
        DECHECK(startaddr_);

        return startaddr_;
    }

    bool DexFile::dexParse()
    {
        return true;
    }
}
