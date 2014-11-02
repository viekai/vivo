#ifndef VIVO_DEX_CLASS_
#define VIVO_DEX_CLASS_
#include <string>
#include "common.h"
#include "array.h"
#include "dexfile.h"

namespace vivo {
class Field;
class Method;
class Class;


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
