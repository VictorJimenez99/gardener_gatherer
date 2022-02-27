#include <gtest/gtest.h>
#include "../src/lib/services/gardener_db.h"

TEST(TestDB, completeSchema) {
    gardener_db g;
    ASSERT_TRUE(g.schema_is_complete());
}

TEST(TestDB, basic) {
    ASSERT_EQ(2, 1 + 1);
}