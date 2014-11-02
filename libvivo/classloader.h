#ifndef VIVO_CLASS_LOADER_H_
#define VIVO_CLASS_LOADER_H_

#include "class.h"
#include "dexfile.h"
#include "dexcache.h"
#include <unordered_map>
#include <string.h>

namespace vivo {
class ClassLoader {
public:
    ClassLoader(std::string& boot_class_path);

    Class* ResovleClass(uint32_t cld);

    Class* FindClass(const char* className);

    Class* DefineClass(std::string& className);

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

    class ClassName {
        public:
            ClassName(const char* name) : 
                source_name_(name),
                value_(name) {
                    if (value_.size() != 0) {
                        for (std::string::size_type i = 0; i < value_.size(); i++) {
                            if (value_[i] == '.')
                                value_[i] = '/';
                        }
                        value_ = "L" + value_ + ";";
                    }
            }

            std::string& Get() {
                return value_;
            }

        private:
            const char* source_name_;
            std::string value_;
    };

private:
    DexCache* dex_cache_;
    HashClasses hash_;
};
}

#endif
