#ifndef VIVO_DEXFILE_H_
#define VIVO_DEXFILE_H_
#include <stdio.h>
#include <string>

using std::string;
namespace vivo
{
class DexFile
{
    public:
    DexFile(const string& name) :
        name_(name),
        startaddr_(NULL)
    {
    }
    void* dexOpen();
    bool dexParse();

    private:
        const string& name_;
        void* startaddr_;
};
}
#endif
