#include "dexfile.h"
#include "class.h"
#include "classloader.h"
namespace vivo {
    ClassLoader::ClassLoader(const char* class_path) {
        dex_cache_ = new DexCache(class_path);
    }
    
    Class* FindClass(const char* name) {
        return NULL;
    }
    
    Class* ResovleClass(uint32_t cld) {
        return NULL;
    }
}
