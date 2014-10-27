#ifndef VIVO_DEX_CLASS_
#define VIVO_DEX_CLASS_
#include "common.h"
#include "dexfile.h"
#include "array.h"

namespace vivo
{
class Field;
class Method;
class Class;

class DexCache {
public:
    DexCache(const char* dex_path) {
        dex_file_ = DexFile::Open(dex_path); 
        dex_file_->Parse();
    }

    inline const Method* GetResolvedMethod(uint32_t idx) {
        return resolvedMethod.at(idx);
    }

    inline const Field*  GetResolvedField(uint32_t idx) {
        return resolvedField.at(idx);
    }

    inline const Class*  GetFesolvedClass(uint32_t idx){
        return resolvedClass.at(idx);
    }

    inline void SetResolvedMethod(uint32_t idx, Method* method) {
        resolvedMethod.set(idx, method);
    }

    inline void  SetResolvedField(uint32_t idx, Field* field) {
        resolvedField.set(idx, field);
    }

    inline void SetFesolvedClass(uint32_t idx, Class* vclass){
        resolvedClass.set(idx, vclass);
    }

private:
    ObjectArray<Method*> resolvedMethod;
    ObjectArray<Field*>  resolvedField;
    ObjectArray<Class*>  resolvedClass;
    DexFile* dex_file_;
};

class Field {
};

class Method {
private:
};

class Class {
public:
    const char* GetClassName();
    void SetClassName(const char* name);

    void SetField(uint32_t idx, Field* field);
    Field* GetField(uint32_t idx);

    void SetMethod(uint32_t idx, Method* method);
    Method* GetMethod(uint32_t idx);

    Class* Alloc();
private:
    const char*             name_;
    DexFile::AccessFlag     access_;
    uint32_t                staticFieldSize_;
    uint32_t                instancFieldSize_;

    uint32_t                virtualMethodSize_;
    uint32_t                directMethodSize_;

    Method* methods_;
    Field*  fields_;
};
}

#endif
