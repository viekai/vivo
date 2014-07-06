#include "array.h"
#include "heap.h"
#include "array-inl.h"

namespace vivo
{
Array* Array::Alloc(uint32_t compontLength, uint32_t compontSize)
{
    size_t size = compontSize * compontLength + sizeof(Array);

    Array* array = reinterpret_cast<Array*>(Heap::allocObject(size));
    array->setLength(compontLength);

    if(!array)
        return NULL;
    else
        return array;
}
}
