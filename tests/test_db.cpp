#include <gtest/gtest.h>
#include "../src/lib/services/GardenerDB.h"

TEST(TestDB, completeSchema) {
    GardenerDB g;
    ASSERT_TRUE(g.schema_is_complete());
}

TEST(TestDB, basic) {
    ASSERT_EQ(2, 1+1);
}