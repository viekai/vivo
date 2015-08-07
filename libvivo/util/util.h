#ifndef VIVO_UTIL_H_
#define VIVO_UTIL_H_
namespace util {
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
}
#endif
