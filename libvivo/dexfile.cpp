#include "dexfile.h"
#include "util.h"
#include "common.h"
#include "leb.h"

#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <ostream>
#include <memory.h>
#include <errno.h>

namespace vivo
{
    const ubyte_t DexFile::kDefaultMagic[8] = {0x64, 0x65, 0x78, 0x0a, 0x30, 0x33, 0x35, 0x00};

    DexFile::~DexFile() {
    }

    DexFile::DexFile(void* startAddr) : startAddr_(startAddr) {
    }

    DexFile* DexFile::Open(const string& name) {
        struct stat st;
        DECHECKNE(name.size(), 0);
        int fd = open(name.c_str(), O_RDONLY);
        DECHECKNE(fd, 0);
        stat(name.c_str(), &st);
        int size_ = st.st_size;

        void* startAddr = mmap(NULL, size_, PROT_READ, MAP_PRIVATE, fd, 0);

        if ((reinterpret_cast<long>(startAddr) == -1)) {
            std::cout<< strerror(errno)<<std::endl;
            ABORT();
        }

        DexFile* dexFile = new DexFile(startAddr);
        if (dexFile == NULL) {
            std::cout<< strerror(errno)<<std::endl;
            ABORT();
        }

        dexFile->Parse();
        return dexFile;
    }

    bool DexFile::Parse() {
        head_ = reinterpret_cast<DexFile::DexHead*>(startAddr_);

        stringItem_ = reinterpret_cast<StringIdItem*>(static_cast<ubyte_t*>(startAddr_) + head_->stringIdsOff_);
        typeItem_ = reinterpret_cast<TypeIdItem*>(static_cast<ubyte_t*>(startAddr_) + head_->typeIdsOff_);
        protoIdItem_ = reinterpret_cast<ProtoIdItem*>(static_cast<ubyte_t*>(startAddr_) + head_->protoIdsOff_);
        classDefItem_ = reinterpret_cast<ClassDefItem*>(static_cast<ubyte_t*>(startAddr_) + head_->classDefOff_);

        return true;
    }


    const char* DexFile::StringDataById(uint32_t id) {
        if(kNoIdx == id)
            return "";
        const StringIdItem& idItem = stringItem_[id];
        ubyte_t* stringData = static_cast<ubyte_t*>(startAddr_) + idItem.offset_;
        return reinterpret_cast<const char*>(stringData + Leb128::uleb128Length(stringData));
    }

    const char* DexFile::TypeDataById(uint32_t idx) {
        if(kNoIdx == idx)
            return "";
        const TypeIdItem& idItem = typeItem_[idx];
        return StringDataById(idItem.descript_idx_);
    }

    const DexFile::ProtoIdItem& DexFile::GetProtoItemById(uint32_t idx) {
        return protoIdItem_[idx];
    }

    const DexFile::ClassDefItem& DexFile::GetClassDefItemById(uint32_t idx) {
        return classDefItem_[idx];
    }

    const DexFile::ClassDefItem* DexFile::LoadClassFromDex(const char* classDesc) {
        const ClassDefItem* item = NULL;
        uint32_t class_def_size = head_->classDefSize_;
        /*TODO use iteroter*/
        for (uint32_t i = 0; i < class_def_size; i++) {
            item = &classDefItem_[i];
            if (0 == strcmp(classDesc, TypeDataById(item->class_idx_))) {
                    return item;
            }
        }

        return NULL;
    }
}
