#ifndef VIVO_CLASS_LINKER_H_
#define VIVO_CLASS_LINKER_H_
#include "class.h"
#include "dexfile.h"
#include "classloader.h"

namespace vivo {
class ClassLinker {
public:
    class HashClasses {
    public:
        Class* find(std::string& str) {
            std::unordered_map<std::string, Class*>::iterator it = hash_.find(str);
            return it->second;
        }

    private:
        struct HashFunc {
            std::size_t operator()(std::string k) const {
                return std::hash<std::string>()(k);
            }
        };

        struct HashCompare {
            bool operator()(std::string name1, std::string name2) const {
                return strcmp(name1.c_str(), name1.c_str()) == 0;
            }
        };

        std::unordered_map<std::string, Class*, HashFunc, HashCompare> hash_;
    };

private:
    ClassLoader* boot_class_loader_;
    HashClasses hash_;
};
}
#endif
