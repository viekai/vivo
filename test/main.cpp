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

    const vivo::DexFile::ClassDefItem& classItem = dexFile.GetClassDefItemById(0);
    std::cout << dexFile.StringDataById(classItem.soure_file_idx_) << std::endl; 

    return 0;
}
