#include "runtime.h"
namespace vivo {

Runtime::Runtime(const char* boot_class_path,
        const char* class_path) 
    : boot_class_path_(boot_class_path),
    class_path_(class_path) {
}

void Runtime::Initilize() {
    class_loader_ = new ClassLoader(boot_class_path_);
}

}
