#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>

// Floating-point numbers are not exact: compare them with a margin.
TEST_CASE("0.1 + 0.2 is close to 0.3", "[float]") {
    float sum = 0.1f + 0.2f;
    REQUIRE(sum == Catch::Approx(0.3f).epsilon(1e-5));
}
