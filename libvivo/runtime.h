#ifndef  VIVO_RUNTIME_H
#define VIVO_RUNTIME_H
#include "classloader.h"
#include <string>
namespace vivo {
class Runtime {
public:
    Runtime(const char* boot_class_path, 
            const char* class_path_);

    void Initilize();
    void RunMain();

private:
    std::string boot_class_path_;
    std::string class_path_;
    ClassLoader* class_loader_;
};
}

#endif
