//
// Created by victor on 01/03/22.
//

#include <gtest/gtest.h>
#include "../src/lib/services/connection_pool.h"
#include "../src/lib/constants/constants.h"


TEST(connectionPool, poolElemTest) {
    pool_elem e;
    auto f = e.get_is_busy_ref().load();
    ASSERT_EQ(f, false);
}


TEST(connectioPool, poolConn) {
    auto& handler = connection_pool_inner::get_instance();
    int size = handler.unsafe_get_pool().unsafe_get_size();

    ASSERT_EQ(size, CONNECTION_POOL_START_SIZE);

    auto saturation = std::vector<std::shared_ptr<connection_pool>>();

    ASSERT_EQ(saturation.size(), 0);
    for (int i = 0; i < CONNECTION_POOL_START_SIZE; i++) {
        saturation.emplace_back(std::make_shared<connection_pool>());
    }
    long saturation_size = saturation.size();
    ASSERT_EQ(saturation_size, CONNECTION_POOL_START_SIZE);
    size = handler.unsafe_get_pool().unsafe_get_size();
    ASSERT_EQ(size, CONNECTION_POOL_START_SIZE);

    auto connection = connection_pool();
    size = handler.unsafe_get_pool().unsafe_get_size();
    saturation.size();
    ASSERT_EQ(size, CONNECTION_POOL_START_SIZE + 1);
}