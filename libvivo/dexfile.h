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


    DexFile(const string& name);

    ~DexFile();

    void* dexOpen(const string& name);
    bool dexParse();

    enum AccessFlag {
        ACC_PUBLIC          = 0x1,
        ACC_PRIVATE         = 0x2,
        ACC_PROTECTED       = 0x4,
        ACC_STATIC          = 0x8,
        ACC_FINAL           = 0x10,
        ACC_SYNCHRONIZED    = 0x20,
        ACC_VOLATIVE        = 0x40,
        ACC_BRIDGE          = 0x40,
        ACC_TRANSINET       = 0x80,
        ACC_VARARGS         = 0x80,
        ACC_NATIVE          = 0x100,
        ACC_INTERFACE       = 0x200,
        ACC_ABSTRACT        = 0x400,
        ACC_STRICT          = 0x800,
        ACC_SYNTHETIC       = 0x1000,
        ACC_ANNOTATION      = 0x2000,
        ACC_ENUM            = 0x4000,
        ACC_CONSTRUCTOR     = 0x10000,
        ACC_DECLARED_SYNCHRONIZED = 0x20000,
    };
    /*
     * Head for dex
     */
    struct DexHead {
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

    struct MapItem {
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
    struct DexField {
    };

    struct StringIdItem {
        uint32_t offset_;

    private:
        DISALLOW_COPY_AND_ASSIGN(StringIdItem);
    };

    struct TypeIdItem {
        uint32_t descript_idx_;

    private:
        DISALLOW_COPY_AND_ASSIGN(TypeIdItem);
    };

    struct ProtoIdItem {
       uint32_t  shorty_idx_;
       uint32_t  return_type_idx_;
       uint32_t  parameters_off_;

    private:
        DISALLOW_COPY_AND_ASSIGN(ProtoIdItem);
    };

    struct ClassDefItem  {
       uint32_t  class_idx_;            //type_ids
       uint32_t  access_flags_;         //access flags
       uint32_t  superclass_idx_;       //type_ids
       uint32_t  interfaces_off_;       //0 or type_ids
       uint32_t  soure_file_idx_;       //string_ids
       uint32_t  annotations_off_;      //0 or annotations_dircetor_item
       uint32_t  class_data_off_;       //0 or offset to class_data_item
       uint32_t  static_values_off_;    //0 or encoded_array_item
    private:
       DISALLOW_COPY_AND_ASSIGN(ClassDefItem);
    };

    const char* StringDataById(uint32_t idx);
    const char* TypeDataById(uint32_t   idx);
    const ProtoIdItem& GetProtoItemById(uint32_t idx);
    const ClassDefItem& GetClassDefItemById(uint32_t idx);

    const ClassDefItem* LoadClassFromDex(const char* classDesc);

    const ClassDefItem* LoadClassFromDex(uint32_t typeIdx) {
        const char* classDesc = TypeDataById(typeIdx);
        return LoadClassFromDex(classDesc);
    }

    private:
        void*                startAddr_;
        const DexHead*             head_;
        const StringIdItem*        stringData_;
        const TypeIdItem*          typeData_;
        const ProtoIdItem*         protoIdItem_;
        const ClassDefItem*        classDefItem_;
};
}
#endif
