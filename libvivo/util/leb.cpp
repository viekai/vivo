#include "leb.h"
#include "common.h"

namespace vivo {
uint32_t Leb128::readUleb128(ubyte_t* start) {
    uint32_t    size = 0;
    uint32_t    data = 0;
    ubyte_t     b = 0;

    while((b = *(start++)) & 0x80)
    {
        data |= (b & 0x7f) << ((size++) << 3);
    }

    data |= (b & 0x7f) << ((size++) << 3);

    return data;
}

uint32_t Leb128::uleb128Length(ubyte_t* addr) {
    uint32_t size = 1;
    while((*(addr++)) & 0x80)
        size++;

    return size;
}

}
