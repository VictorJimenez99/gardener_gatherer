//
// Created by victor on 26/02/22.
//
#include <gtest/gtest.h>
#include "../src/lib/classes/plant_raw.h"
#include <memory>

TEST(testClasses, plantRaw) {
    auto plant =
            std::make_unique<plant_raw>(1, 1, 4, "rose", 4);
    ASSERT_EQ(plant->get_rack(), 1);
}