#ifndef VIVO_DEXFILE_H_
#define VIVO_DEXFILE_H_
#include <stdio.h>

namespace Dex
{
class DexFile
{
    public:
    DexFile(char* name) : 
        name_(name),
        startaddr_(NULL)
    {
    }

    void* open(char *name);

    private:
        char* name_;
        void* startaddr_;
};
}
#endif
