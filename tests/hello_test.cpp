#include <catch2/catch_test_macros.hpp>

#include "hello.hpp"

TEST_CASE("greet says hello to the given name") {
    REQUIRE(greet("world") == "Hello, world!");
}
