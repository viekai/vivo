#include "log.h"
#include "common.h"
#include "dexfile.h"
#include <string>
#include <ostream>
#include "test_common.h"

using namespace std;

bool fun1() {
    string str = "main.dex";
    string except = "Switch.java";
    vivo::DexFile dexFile(str);

    const vivo::DexFile::ClassDefItem& classItem = dexFile.GetClassDefItemById(0);
    std::string output = dexFile.StringDataById(classItem.soure_file_idx_);

    return (output == except);
}

TEST_F(FooTest, DexFileTest) {
  EXPECT_EQ(true, fun1());
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
