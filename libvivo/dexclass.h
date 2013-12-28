#ifndef VIVO_DEX_CLASS_
#define VIVO_DEX_CLASS_
#include "common.h"
#include "dexfile.h"
#include "array.h"

namespace vivo
{

class VivoField;
class VivoMethod;
class VivoClass;

class DexCache
{
public:
    inline const VivoMethod* GetResolvedMethod(uint32_t idx) {
        return resolvedMethod.at(idx);
    }

    inline const VivoField*  GetResolvedField(uint32_t idx) {
        return resolvedField.at(idx); 
    }

    inline const VivoClass*  GetFesolvedClass(uint32_t idx){
        return resolvedClass.at(idx);
    }

    inline void SetResolvedMethod(uint32_t idx, VivoMethod* method) {
        resolvedMethod.set(idx, method);
    }

    inline void  SetResolvedField(uint32_t idx, VivoField* field) {
        resolvedField.set(idx, field); 
    }

    inline void SetFesolvedClass(uint32_t idx, VivoClass* vclass){
        resolvedClass.set(idx, vclass);
    }
private:
    ObjectArray<VivoMethod*> resolvedMethod;
    ObjectArray<VivoField*>  resolvedField;
    ObjectArray<VivoClass*>  resolvedClass;
};

class VivoField
{
};

class VivoMethod
{
private:
};

class VivoClass
{
public:
    const char* GetClassName();
    void SetClassName();

    void SetField(uint32_t idx, VivoField* field);
    VivoField* GetField(uint32_t idx);

    void SetMethod(uint32_t idx, VivoMethod* method);
    VivoMethod* GetMethod(uint32_t idx);

    void SetClassName(const char* name);

    DexCache* dexCache_;

private:
    const char*             name_;
    DexFile::AccessFlag     access_;
    uint32_t                staticFieldSize_;
    uint32_t                instancFieldSize_;

    uint32_t                virtualMethodSize_;
    uint32_t                directMethodSize_;

    VivoMethod* methods_;
    VivoField*  fields_;
};
}

#endif
