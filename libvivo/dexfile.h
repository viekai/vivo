#ifndef VIVO_DEXFILE_H_
#define VIVO_DEXFILE_H_
#include <stdio.h>
#include <string>
#include "common.h"

using std::string;
namespace vivo {
class DexFile {
    public:
    static const ubyte_t        kDefaultMagic[8];
    static const uint32_t       kEndianConst = 0x12345678;
    static const uint32_t       kReversEndianConst = 0x78563412;
    static const uint32_t       kNoIdx = 0xffffffff;


    DexFile(void* startAddr);

    ~DexFile();

    static DexFile* Open(const string& name);
    bool Parse();

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
        void*                      startAddr_;
        const DexHead*             head_;
        const StringIdItem*        stringItem_;
        const TypeIdItem*          typeItem_;
        const ProtoIdItem*         protoIdItem_;
        const ClassDefItem*        classDefItem_;
};

/*
 * Def the class Data 
 *  
 * */
class ClassDataIterator {
 public:
  ClassDataIterator(const DexFile& dex_file, const ubyte_t* raw_class_data_item)
      : dex_file_(dex_file), pos_(0), ptr_pos_(raw_class_data_item), last_idx_(0) {
    ReadClassDataHeader();
    if (EndOfInstanceFieldsPos() > 0) {
      ReadClassDataField();
    } else if (EndOfVirtualMethodsPos() > 0) {
      ReadClassDataMethod();
    }
  }
  uint32_t NumStaticFields() const {
    return header_.static_fields_size_;
  }
  uint32_t NumInstanceFields() const {
    return header_.instance_fields_size_;
  }
  uint32_t NumDirectMethods() const {
    return header_.direct_methods_size_;
  }
  uint32_t NumVirtualMethods() const {
    return header_.virtual_methods_size_;
  }
  bool HasNextStaticField() const {
    return pos_ < EndOfStaticFieldsPos();
  }
  bool HasNextInstanceField() const {
    return pos_ >= EndOfStaticFieldsPos() && pos_ < EndOfInstanceFieldsPos();
  }
  bool HasNextDirectMethod() const {
    return pos_ >= EndOfInstanceFieldsPos() && pos_ < EndOfDirectMethodsPos();
  }
  bool HasNextVirtualMethod() const {
    return pos_ >= EndOfDirectMethodsPos() && pos_ < EndOfVirtualMethodsPos();
  }
  bool HasNext() const {
    return pos_ < EndOfVirtualMethodsPos();
  }
  inline void Next() {
    pos_++;
    if (pos_ < EndOfStaticFieldsPos()) {
      last_idx_ = GetMemberIndex();
      ReadClassDataField();
    } else if (pos_ == EndOfStaticFieldsPos() && NumInstanceFields() > 0) {
      last_idx_ = 0;  // transition to next array, reset last index
      ReadClassDataField();
    } else if (pos_ < EndOfInstanceFieldsPos()) {
      last_idx_ = GetMemberIndex();
      ReadClassDataField();
    } else if (pos_ == EndOfInstanceFieldsPos() && NumDirectMethods() > 0) {
      last_idx_ = 0;  // transition to next array, reset last index
      ReadClassDataMethod();
    } else if (pos_ < EndOfDirectMethodsPos()) {
      last_idx_ = GetMemberIndex();
      ReadClassDataMethod();
    } else if (pos_ == EndOfDirectMethodsPos() && NumVirtualMethods() > 0) {
      last_idx_ = 0;  // transition to next array, reset last index
      ReadClassDataMethod();
    } else if (pos_ < EndOfVirtualMethodsPos()) {
      last_idx_ = GetMemberIndex();
      ReadClassDataMethod();
    } else {
      // DCHECK(!HasNext());
    }
  }
  uint32_t GetMemberIndex() const {
    if (pos_ < EndOfInstanceFieldsPos()) {
      return last_idx_ + field_.field_idx_delta_;
    } else {
      // DCHECK_LT(pos_, EndOfVirtualMethodsPos());
      return last_idx_ + method_.method_idx_delta_;
    }
  }
  uint32_t GetRawMemberAccessFlags() const {
    if (pos_ < EndOfInstanceFieldsPos()) {
      return field_.access_flags_;
    } else {
      // DCHECK_LT(pos_, EndOfVirtualMethodsPos());
      return method_.access_flags_;
    }
  }

/*
  uint32_t GetFieldAccessFlags() const {
    return GetRawMemberAccessFlags() & kAccValidFieldFlags;
  }
  uint32_t GetMethodAccessFlags() const {
    return GetRawMemberAccessFlags() & kAccValidMethodFlags;
  }
  bool MemberIsNative() const {
    return GetRawMemberAccessFlags() & kAccNative;
  }
  bool MemberIsFinal() const {
    return GetRawMemberAccessFlags() & kAccFinal;
  }
  InvokeType GetMethodInvokeType(const DexFile::ClassDef& class_def) const {
    if (HasNextDirectMethod()) {
      if ((GetRawMemberAccessFlags() & kAccStatic) != 0) {
        return kStatic;
      } else {
        return kDirect;
      }
    } else {
      DCHECK_EQ(GetRawMemberAccessFlags() & kAccStatic, 0U);
      if ((class_def.access_flags_ & kAccInterface) != 0) {
        return kInterface;
      } else if ((GetRawMemberAccessFlags() & kAccConstructor) != 0) {
        return kSuper;
      } else {
        return kVirtual;
      }
    }
  }
  const DexFile::CodeItem* GetMethodCodeItem() const {
    return dex_file_.GetCodeItem(method_.code_off_);
  }
  */
  uint32_t GetMethodCodeItemOffset() const {
    return method_.code_off_;
  }
  const ubyte_t* EndDataPointer() const {
    // CHECK(!HasNext());
    return ptr_pos_;
  }

 private:
  // A dex file's class_data_item is leb128 encoded, this structure holds a decoded form of the
  // header for a class_data_item
  struct ClassDataHeader {
    uint32_t static_fields_size_;  // the number of static fields
    uint32_t instance_fields_size_;  // the number of instance fields
    uint32_t direct_methods_size_;  // the number of direct methods
    uint32_t virtual_methods_size_;  // the number of virtual methods
  } header_;

  // Read and decode header from a class_data_item stream into header
  void ReadClassDataHeader();

  uint32_t EndOfStaticFieldsPos() const {
    return header_.static_fields_size_;
  }
  uint32_t EndOfInstanceFieldsPos() const {
    return EndOfStaticFieldsPos() + header_.instance_fields_size_;
  }
  uint32_t EndOfDirectMethodsPos() const {
    return EndOfInstanceFieldsPos() + header_.direct_methods_size_;
  }
  uint32_t EndOfVirtualMethodsPos() const {
    return EndOfDirectMethodsPos() + header_.virtual_methods_size_;
  }

  // A decoded version of the field of a class_data_item
  struct ClassDataField {
    uint32_t field_idx_delta_;  // delta of index into the field_ids array for FieldId
    uint32_t access_flags_;  // access flags for the field
    ClassDataField() :  field_idx_delta_(0), access_flags_(0) {}

   private:
    DISALLOW_COPY_AND_ASSIGN(ClassDataField);
  };
  ClassDataField field_;

  // Read and decode a field from a class_data_item stream into field
  void ReadClassDataField();

  // A decoded version of the method of a class_data_item
  struct ClassDataMethod {
    uint32_t method_idx_delta_;  // delta of index into the method_ids array for MethodId
    uint32_t access_flags_;
    uint32_t code_off_;
    ClassDataMethod() : method_idx_delta_(0), access_flags_(0), code_off_(0) {}

   private:
    DISALLOW_COPY_AND_ASSIGN(ClassDataMethod);
  };
  ClassDataMethod method_;

  // Read and decode a method from a class_data_item stream into method
  void ReadClassDataMethod();

  const DexFile& dex_file_;
  size_t pos_;  // integral number of items passed
  const ubyte_t* ptr_pos_;  // pointer into stream of class_data_item
  uint32_t last_idx_;  // last read field or method index to apply delta to
  // DISALLOW_IMPLICIT_CONSTRUCTORS(ClassDataItemIterator);
};
}
#endif
