#include "dexfile.h"
#include "class.h"
#include "classloader.h"
#include "util.h"
namespace vivo {
    ClassLoader::ClassLoader(const char* boot_class_path) {
        std::string str(boot_class_path);
        OpenDexFile(str);
    }

    ClassLoader::ClassLoader(std::string& boot_class_path) {
        OpenDexFile(boot_class_path);
    }

    void ClassLoader::OpenDexFile(std::string& dex_path) {
        DexFile* dex_file = NULL;
        dex_file = DexFile::Open(dex_path.c_str());
        if (dex_file) {
            dex_file->Parse();
            dex_files_.push_back(dex_file);
        }
    }

    Class* ClassLoader::FindClass(const char* name) {
        util::ClassName clsName(name);
        Class* cls = DefineClass(clsName.Get());
        return cls;
    }

    Class* ClassLoader::ResovleClass(uint32_t cld) {
        return NULL;
    }

    /*
     * load class from dex
     * load method from dex
     * load field from dex
     * */
    Class* ClassLoader::LoadClass(DexFile* dex_file, const DexFile::ClassDefItem* cls_item) {

        return NULL;
    }

    /*
     *1. Load class from dex file
         1.

     *2. Link class:
            a. Load and link the super
            b. link methods:
                 1. direct methods
                    a. MethodArrays? or use hash set

                 2. virtual methods
                    a. use MethodArrays
                    b. copy the father's virtual methods to this array

                 TODO
                 3. interface

            c. link fiedls
     * */
    Class* ClassLoader::DefineClass(std::string& className) {
        const DexFile::ClassDefItem* cls_def_ = NULL;
        DexFile* cls_dex_file_ = NULL;
        Class* ret = NULL;

        // iterator over all the dex files to find the className
        for (std::vector<DexFile*>::iterator it = dex_files_.begin();
                it != dex_files_.end(); ++it) {
            DexFile* dex_file = *it;
            cls_def_ = dex_file->LoadClassFromDex(className.c_str()); 

            if (cls_def_ != NULL) {
                cls_dex_file_ = dex_file;
                break;
            }
        }

        /*Find the class, if not find , throw no class find exception*/
        if (cls_def_ == NULL) {
            printf("ERROR: class not found for %s", className.c_str());
        }
        
        ret = LoadClass(cls_dex_file_, cls_def_);
        return ret;
    }
}
