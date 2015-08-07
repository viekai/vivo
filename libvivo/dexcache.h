#ifndef VIVO_DEXCACHE_H
#define VIVO_DEXCACHE_H
#include <vector>
#include "array.h"
#include "class.h"
#include "dexfile.h"
namespace vivo {
class DexCache {
public:
    DexCache(std::string& dex_path) {
    }

    inline const Method* GetResolvedMethod(uint32_t idx) {
        return resolvedMethod.at(idx);
    }

    inline const Field*  GetResolvedField(uint32_t idx) {
        return resolvedField.at(idx);
    }

    inline const Class*  GetResolvedClass(uint32_t idx){
        return resolvedClass.at(idx);
    }

    inline void SetResolvedMethod(uint32_t idx, Method* method) {
        resolvedMethod.set(idx, method);
    }

    inline void  SetResolvedField(uint32_t idx, Field* field) {
        resolvedField.set(idx, field);
    }

    inline void SetResolvedClass(uint32_t idx, Class* vclass) {
        resolvedClass.set(idx, vclass);
    }

private:
    ObjectArray<Method*> resolvedMethod;
    ObjectArray<Field*>  resolvedField;
    ObjectArray<Class*>  resolvedClass;

};
}
#endif
