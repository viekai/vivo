#include"dexclass.h"
#include <malloc.h>
#include <string.h>

namespace vivo {
    VivoClass* VivoClass::Alloc() {
        VivoClass* cls = (VivoClass*)malloc(sizeof(VivoClass));
        DECHECK(cls);
        memset(cls, 0, sizeof(VivoClass));
        return cls;
    }
}
