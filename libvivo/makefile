SOURCE_DIR := .\
	  util\
	  ../

SOURCE := $(foreach d, $(SOURCE_DIR), $(abspath $(wildcard $(d)/*.cpp)))

LOCAL_INCLUDE := $(SOURCE_DIR) 

LOCAL_CFLAGS := -shared -fPIC

CFLAGS += $(LOCAL_CFLAGS)

INCLUDE_ += $(LOCAL_INCLUDE)

INCLUDE = $(foreach n, $(INCLUDE_), $(addprefix -I , $(abspath $(n))))


LOCAL_OUT := $(addprefix $(OUT_DIR), lib/)
TARGET := $(addprefix $(LOCAL_OUT), libvivo.so)

all : 
	@echo Compiler libvivo...
	@$(CC)  $(CFLAGS) $(SOURCE) $(INCLUDE) -o $(TARGET) 
	@echo Install: $(TARGET)

clean:
	rm -rf $(TARGET) 
