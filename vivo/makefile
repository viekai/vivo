SOURCE_DIR := .\
	  ../libvivo/util\
      ../libvivo

SOURCE := $(foreach d, $(SOURCE_DIR), $(wildcard $(abspath $(d))/*.cpp))
LOCAL_INCLUDE := $(SOURCE_DIR) 
LOCAL_INCLUDE += ../

CFLAGS += $(LOCAL_CFLAGS)
INCLUDE_ += $(LOCAL_INCLUDE)
INCLUDE = $(foreach n, $(INCLUDE_), $(addprefix -I , $(abspath $(n))))

OUT_DIR_ := $(addprefix $(OUT_DIR), bin/)
TARGET := $(addprefix $(OUT_DIR_), vivo)
LIBPATH = -L $(LIBDIR)
LIB = -lvivo  -lpthread


all : Main

Main :
	@$(CC)  $(CFLAGS) $(SOURCE) $(INCLUDE) $(LIBPATH) $(LIB) -o $(TARGET) 
	@echo Install: $(TARGET)

clean:
	rm -rf $(TARGET) 

