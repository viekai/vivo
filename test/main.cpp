#include "log.h"
#include "common.h"
#include "dexfile.h"
#include <string>
#include <ostream>

using std::string;

int main()
{
    string str = "/home/work/vivo/main.dex";

    vivo::DexFile dexFile(str);
    dexFile.dexOpen();
    dexFile.dexParse();

    return 0;
}
