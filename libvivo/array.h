#ifndef VIVO_ARRAY_H
#define VIVO_ARRAY_H

#include "common.h"

namespace vivo {
class MANAGED Array {
public:
    static Array* Alloc(uint32_t compontLength, uint32_t compontSize);
    bool IsValid(uint32_t idx);
    void setLength(uint32_t length);

private:
    uint32_t    size_;
    ubyte_t*   first_element_;
};


template <class T>
class ObjectArray : Array {
public:
    T at(uint32_t idx);
    void set(uint32_t idx, T data);

};

}
#endif
