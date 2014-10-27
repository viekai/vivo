#include "log.h"
#include "common.h"
#include "dexfile.h"
#include <string>
#include <ostream>
#include "test_common.h"

using namespace std;

bool DexFileOpenTest_() {
    string str = "main.dex";
    string except = "Switch.java";
    vivo::DexFile* dexFile = vivo::DexFile::Open(str);
    dexFile->Parse();

    const vivo::DexFile::ClassDefItem& classItem = dexFile->GetClassDefItemById(0);
    std::string output = dexFile->StringDataById(classItem.soure_file_idx_);

    return (output == except);
}

bool DexFileLoadClassItem_() {
    string str = "main.dex";
    vivo::DexFile* dexFile = vivo::DexFile::Open(str);
    dexFile->Parse();

    const vivo::DexFile::ClassDefItem* item =  dexFile->LoadClassFromDex("LSwitch;");
    if (NULL == item) {
        return false;
    }

    const char* classDef = dexFile->TypeDataById(item->class_idx_);
    return (0 == strcmp(classDef, "LSwitch;"));
}

TEST_F(FooTest, DexFileOpenTest) {
  EXPECT_EQ(true, DexFileOpenTest_());
}

TEST_F(FooTest, DexFileLoad) {
  EXPECT_EQ(true, DexFileLoadClassItem_());
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
