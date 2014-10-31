SOURCE_DIR := java/lang/

SOURCE := $(foreach d, $(SOURCE_DIR), $(abspath $(wildcard $(d)/*.java)))
JAVA_SRC := $(foreach d, $(SOURCE_DIR), $(wildcard $(d)/*.java))
CLASS := $(foreach cls, $(JAVA_SRC), $(patsubst %.java, %.class, $(cls)))
JAVA_LIB_OUT  := $(addprefix $(OUT_DIR), javalib/)
TARGET := $(addprefix $(JAVA_LIB_OUT), libcore.dex)

all :
	@echo Compiler java files...
	@$(JAVAC) $(SOURCE)
	@$(DX) --dex --core-library --output=$(TARGET) $(CLASS)
	@rm -rf $(CLASS)
	@echo Install: $(TARGET)

clean:
	rm -rf $(TARGET) 
