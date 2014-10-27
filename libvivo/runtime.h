#ifndef  VIVO_RUNTIME_H
#define VIVO_RUNTIME_H
#include "classloader.h"
namespace vivo {
class Runtime {
public:
    Runtime(const char* classPath);

    void Initilize();
    void RunMain();

private:
    const char* class_path_;
    ClassLoader* class_loader_;
};
}

#endif
