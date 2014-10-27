#include "runtime.h"
namespace vivo {

Runtime::Runtime(const char* class_path) : class_path_(class_path) {
}

void Runtime::Initilize() {
    class_loader_ = new ClassLoader(class_path_); 
}

}
