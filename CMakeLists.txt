cmake_minimum_required(VERSION 3.14)
project(gardener)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
FetchContent_Declare(
        googletest
        # Specify the commit you depend on and update it regularly.
        URL https://github.com/google/googletest/archive/e2239ee6043f73722e7aa812a459f54a28552929.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Now simply link against gtest or gtest_main as needed. Eg

add_executable(gardener
        src/main.cpp
        src/lib/constants/constants.h
        src/lib/classes/plant_raw.cpp src/lib/classes/plant_raw.h
        src/lib/services/db_handler.cpp src/lib/services/db_handler.h
        src/lib/services/gardener_db.cpp src/lib/services/gardener_db.h
        src/lib/services/connection_pool.cpp src/lib/services/connection_pool.h)


target_link_libraries(gardener sqlite3)

# TESTS ------------------------
enable_testing()
add_executable(test_suit
        tests/test_db.cpp
        tests/test_classes.cpp
        src/lib/constants/constants.h
        src/lib/classes/plant_raw.cpp src/lib/classes/plant_raw.h
        src/lib/services/db_handler.cpp src/lib/services/db_handler.h
        src/lib/services/gardener_db.cpp src/lib/services/gardener_db.h
        src/lib/services/connection_pool.cpp src/lib/services/connection_pool.h tests/test_connection_pool.cpp)
target_link_libraries(test_suit gtest_main sqlite3)

include(GoogleTest)
gtest_discover_tests(test_suit)