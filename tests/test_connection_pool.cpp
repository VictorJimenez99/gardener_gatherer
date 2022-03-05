//
// Created by victor on 01/03/22.
//

#include <gtest/gtest.h>
#include "../src/lib/constants/constants.h"
#include "../src/lib/services/lazy_connection_pool.h"


TEST(connectionPoolTest, drop) {
    auto conn = db_connection().get();
    ASSERT_TRUE(conn->schema_is_complete());
}

TEST(connectionPOolTest, saturate) {
    std::array<db_connection, CONNECTION_POOL_SIZE> saturation;
    auto con = saturation.back();
    ASSERT_FALSE(con.get_ownership());
    db_connection extra;
    ASSERT_TRUE(extra.get_ownership());


}