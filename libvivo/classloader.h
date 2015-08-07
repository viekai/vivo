#ifndef VIVO_CLASS_LOADER_H_
#define VIVO_CLASS_LOADER_H_

#include "class.h"
#include "dexfile.h"
#include "dexcache.h"
#include <unordered_map>
#include <string.h>

namespace vivo {
class ClassLoader {
public:
    ClassLoader(std::string& boot_class_path);
    ClassLoader(const char* boot_class_path);

    Class* ResovleClass(uint32_t cld);

    Class* FindClass(const char* className);

    Class* DefineClass(std::string& className);

    void OpenDexFile(std::string& dex_path);

    Class* LoadClass(DexFile* dex_file, const DexFile::ClassDefItem* cls_item);

private:
    uint32_t num_dex_files_;
    /*use to record the dex files open in this classLinker*/
    std::vector<DexFile*> dex_files_;

};
}

#endif
