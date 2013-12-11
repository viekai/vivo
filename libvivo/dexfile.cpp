#include "dexfile.h"
#include "util.h"

#include <unistd.h>
#include <sys/mman.h> 
#include <sys/stat.h>


namespace Dex
{
    void* DexFile::open(char* name)  
    {
        struct stat st;
        name_ = name; 
        stat(name, &st);
//        void* add = mmap(NULL, );
        return NULL;
    }
}
