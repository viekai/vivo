#include "log.h"
#include "common.h"
#include "dexfile.h"
#include <string>
#include <ostream>
#include "test_common.h"
#include "classloader.h"

using namespace std;

bool DexFileOpenTest_() {
    string str = "main.dex";
    string except = "Switch.java";
    vivo::DexFile* dexFile = vivo::DexFile::Open(str);

    const vivo::DexFile::ClassDefItem& classItem = dexFile->GetClassDefItemById(0);
    std::string output = dexFile->StringDataById(classItem.soure_file_idx_);

    return (output == except);
}

bool DexFileLoadClassItem_() {
    string str = "main.dex";
    vivo::DexFile* dexFile = vivo::DexFile::Open(str);

    const vivo::DexFile::ClassDefItem* item =  dexFile->LoadClassFromDex("LSwitch;");
    if (NULL == item) {
        return false;
    }

    const char* classDef = dexFile->TypeDataById(item->class_idx_);
    return (0 == strcmp(classDef, "LSwitch;"));
}

bool ClassHashTableTest_() {
    return true;
}

const std::string ClassTestname_(std::string caseName) {
    vivo::ClassLoader::ClassName case1Name(caseName.c_str());
    return case1Name.Get().c_str();
}

/*
testing::AssertionResult AssertFoo(const char* m_expr, const char* n_expr, const char* k_expr, int m, int n, int k) {
    if (10 == k)
        return testing::AssertionSuccess();
    testing::Message msg;
    return testing::AssertionFailure(msg);
}

TEST(AssertFooTest, HandleFail)
{
    ASSERT_PRED_FORMAT3(AssertFoo, 3, 6, 2);
}
*/

TEST_F(FooTest, DexFileOpenTest) {
  EXPECT_EQ(true, DexFileOpenTest_());
}

TEST_F(FooTest, DexFileLoad) {
  EXPECT_EQ(true, DexFileLoadClassItem_());
}

TEST_F(FooTest, ClassNameTest) {
    EXPECT_EQ(std::string("Ljava/lang/object;"), ClassTestname_(std::string("java.lang.object")));
    EXPECT_EQ(std::string("LSwitch;"), ClassTestname_(std::string("Switch")));
    EXPECT_EQ(std::string(""), ClassTestname_(std::string("")));
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
