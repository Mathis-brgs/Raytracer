#include <catch2/catch_test_macros.hpp>

#include "vector.hpp"

TEST_CASE("add sums each component", "[vector]") {
    Vector a(1.0, 2.0, 3.0);
    Vector b(4.0, 5.0, 6.0);

    Vector result = a.add(b);

    REQUIRE(result.getX() == 5.0);
    REQUIRE(result.getY() == 7.0);
    REQUIRE(result.getZ() == 9.0);
}

TEST_CASE("subtract subtracts each component", "[vector]") {
    Vector a(-1.0, 4.0, 0.0);
    Vector b(-5.0, 2.0, 1.0);

    Vector result = a.subtract(b);

    REQUIRE(result.getX() == 4.0);
    REQUIRE(result.getY() == 2.0);
    REQUIRE(result.getZ() == -1.0);
}
