//
// Created by victor on 26/02/22.
//
#include <gtest/gtest.h>
#include "../src/lib/classes/plant_raw.h"
#include "../src/lib/services/lazy_connection_pool.h"
#include <memory>
#include <vector>

TEST(testClasses, plantRaw) {
    auto plant =
            std::make_unique<plant_raw>(1, 1, 4, "rose");
    ASSERT_EQ(plant->get_rack(), 1);
}

TEST(testClasses, racks) {
    auto db = gardener_db();
    auto racks = db.get_racks();
    std::for_each(racks.begin(), racks.end(), [](rack r){
       std::cout <<  r.get_id() << std::endl;
    });
}