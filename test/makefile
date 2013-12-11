SOURCE_DIR := .\
	  ../libvivo/util

SOURCE := $(foreach d, $(SOURCE_DIR), $(wildcard $(d)/*.cpp))

LOCAL_INCLUDE := $(SOURCE_DIR) 
LOCAL_INCLUDE += ../

#LOCAL_CFLAGS := 

CFLAGS += $(LOCAL_CFLAGS)

INCLUDE_ += $(LOCAL_INCLUDE)
INCLUDE = $(foreach n, $(INCLUDE_), $(addprefix -I , $(n)))


OUT_DIR_ := $(addprefix $(OUT_DIR), bin/)
TARGET := $(addprefix $(OUT_DIR_), main)

all : $(FILE)
	$(CC)  $(CFLAGS) $(SOURCE) $(INCLUDE) -o $(TARGET) 
	@echo Install: $(TARGET)

clean:
	rm -rf $(TARGET) 
