#ifndef VIVO_DEXFILE_H_
#define VIVO_DEXFILE_H_
#include <stdio.h>
#include <string>
#include "common.h"

using std::string;
namespace vivo
{
class DexFile
{
    public:
    static const ubyte_t        kDefaultMagic[8];
    static const uint32_t       kEndianConst = 0x12345678;
    static const uint32_t       kReversEndianConst = 0x78563412;
    static const uint32_t       kNoIdx = 0xffffffff;


    DexFile(const string& name) :
        name_(name),
        startAddr_(NULL)
    {
    }

    ~DexFile();

    void* dexOpen();
    bool dexParse();

    /*
     * Head for dex
     */
    struct DexHead
    {
       ubyte_t      magic_[8];
       uint32_t     checksum;
       ubyte_t      signature_[20];  //SHA-1 signature(hash) of the rest of the file
       uint32_t     fileSize_;
       uint32_t     headerSize_;
       uint32_t     endianTag_;
       uint32_t     linkSize_;
       uint32_t     linkOff_;
       uint32_t     mapOff_;
       uint32_t     stringIdsSize_;
       uint32_t     stringIdsOff_;
       uint32_t     typeIdsSize_;
       uint32_t     typeIdsOff_;
       uint32_t     protoIdsSize;
       uint32_t     protoIdsOff_;
       uint32_t     fieldIdsSize_;
       uint32_t     fieldIdsOff_;
       uint32_t     methodIdsSize_;
       uint32_t     methodIdsOff_;
       uint32_t     classDefSize_;
       uint32_t     classDefOff_;
       uint32_t     dataSize_;
       uint32_t     dataOff_;

    private:
        DISALLOW_COPY_AND_ASSIGN(DexHead);
    };

    struct MapItem
    {
        uint16_t    type_;
        uint16_t    unused_;
        uint32_t    size_;               //count of number of items to be found in the offset
        uint32_t    offset_;

    private:
        DISALLOW_COPY_AND_ASSIGN(MapItem);
    };

    /*
     *Map List
     *{
     *   uint32_t size;
     *   MapItem mapItem[size];
     *}
     * */
    struct DexField
    {
    };

    struct StringIdItem
    {
        uint32_t offset_;

    private:
        DISALLOW_COPY_AND_ASSIGN(StringIdItem);
    };

    const char* StringDataById(uint32_t idx);

    private:
        const string&        name_;
        uint32_t             size_;
        int                  fd;
        void*                startAddr_;
        DexHead*             head_;
        StringIdItem*        stringData_;
};
}
#endif
