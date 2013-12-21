#ifndef VIVO_LEB_H
#define VIVO_LEB_H
#include "common.h"

namespace vivo
{

struct LebItem
{
    uint32_t size_;

    union
    {
        uint32_t  udata_;
        int32_t   sdata_;
    };
};

class Leb128
{
    public:
        static uint32_t readUleb128(ubyte_t* addr);
        static uint32_t uleb128Length(ubyte_t* addr);
};

}
#endif
