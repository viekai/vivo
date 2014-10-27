#include"class.h"
#include <malloc.h>
#include <string.h>

namespace vivo {
    Class* Class::Alloc() {
        Class* cls = (Class*)malloc(sizeof(Class));
        DECHECK(cls);
        memset(cls, 0, sizeof(Class));
        return cls;
    }
}
