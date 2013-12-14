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
TARGET := $(addprefix $(OUT_DIR_), main)
LIB := -L ../out/lib/libvivo

all : $(FILE)
	$(CC)  $(CFLAGS) $(SOURCE) $(INCLUDE) $(LIB) -o $(TARGET) 
	@echo Install: $(TARGET)

clean:
	rm -rf $(TARGET) 
