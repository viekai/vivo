SOURCE_DIR := .\
	  ../libvivo/util\
      ../libvivo

SOURCE := $(foreach d, $(SOURCE_DIR), $(wildcard $(abspath $(d))/*.cpp))
LOCAL_INCLUDE := $(SOURCE_DIR) 
LOCAL_INCLUDE += ../ gtest/include/

CFLAGS += $(LOCAL_CFLAGS)
INCLUDE_ += $(LOCAL_INCLUDE)
INCLUDE = $(foreach n, $(INCLUDE_), $(addprefix -I , $(abspath $(n))))

OUT_DIR_ := $(addprefix $(OUT_DIR), bin/)
TARGET := $(addprefix $(OUT_DIR_), main)
LIBPATH = -L $(LIBDIR)
LIB = -lvivo -lgtest -lpthread


all : Main

Main : Gtest 
	@$(CC)  $(CFLAGS) $(SOURCE) $(INCLUDE) $(LIBPATH) $(LIB) -o $(TARGET) 
	@echo Install: $(TARGET)

Gtest:
	@echo Make: make gtest
	@cd gtest && make
	@echo Install: libgtest.a
	@cp gtest/lib/.libs/libgtest.a $(LIBDIR)

clean:
	rm -rf $(TARGET) 

