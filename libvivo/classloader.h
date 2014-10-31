#ifndef VIVO_CLASS_LOADER_H_
#define VIVO_CLASS_LOADER_H_

#include "class.h"
#include "dexfile.h"

namespace vivo {
class ClassLoader {
public:
    ClassLoader(const char* class_loader);
    
    Class* ResovleClass(uint32_t cld);

    Class* FindClass(const char* classname);
   
private:
    DexCache* dex_cache_;
};
}

#endif
