//
// Created by victor on 01/03/22.
//

#include <gtest/gtest.h>
#include "../src/lib/services/connection_pool.h"
#include "../src/lib/constants/constants.h"

TEST(testConnPool, regrow) {
    auto saturation = std::vector<connection_handler>();
    ASSERT_EQ(saturation.size(), 0);
    for(int i = 0; i < CONNECTION_POOL_START_SIZE; i++) {
        saturation.emplace_back();
        auto size = saturation.size();

        //it  should be full at this point
        ASSERT_EQ(size, i+1);

    }
    auto ptr = connection_pool_inner::instance();
    auto size = ptr->get_pool().size();

    //it  should be full at this point
    ASSERT_EQ(size, CONNECTION_POOL_START_SIZE);

    /*
    auto conn = connection_handler();

    ptr = connection_pool_inner::instance();
    size = ptr->get_pool().size();

    ASSERT_EQ(size, CONNECTION_POOL_START_SIZE + 1);
*/

}