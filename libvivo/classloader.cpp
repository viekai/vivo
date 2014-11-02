#include "dexfile.h"
#include "class.h"
#include "classloader.h"
namespace vivo {
    ClassLoader::ClassLoader(std::string& boot_class_path) {
        dex_cache_ = new DexCache(boot_class_path);
    }

    Class* ClassLoader::FindClass(const char* name) {
        ClassLoader::ClassName clsName(name);
        Class* cls = hash_.find(clsName.Get());
        if (NULL != cls)
            return cls;

        return NULL;
    }

    Class* ClassLoader::ResovleClass(uint32_t cld) {
        return NULL;
    }

    Class* ClassLoader::DefineClass(std::string& className ) {
        return NULL;
    }
}
