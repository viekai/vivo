#ifndef VIVO_HEAP_H
#define VIVO_HEAP_H

#include<memory.h>
#include<stdio.h>

namespace vivo
{
class Heap
{
public:
    static void* allocObject(uint32_t size) 
    {
        return operator new(size);
    }
};
}

#endif
