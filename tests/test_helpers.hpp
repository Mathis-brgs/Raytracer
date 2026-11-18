#pragma once

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include "colour/colour.hpp"
#include "math/vector.hpp"

using Catch::Matchers::WithinAbs;

const double tolerance = 1e-9;

static void requireVectorsEqual(const Vector& actual, const Vector& expected) {
    REQUIRE_THAT(actual.x(), WithinAbs(expected.x(), tolerance));
    REQUIRE_THAT(actual.y(), WithinAbs(expected.y(), tolerance));
    REQUIRE_THAT(actual.z(), WithinAbs(expected.z(), tolerance));
}

static void requireColourEqual(const Colour& actual, double r, double g, double b) {
    REQUIRE_THAT(actual.r(), WithinAbs(r, tolerance));
    REQUIRE_THAT(actual.g(), WithinAbs(g, tolerance));
    REQUIRE_THAT(actual.b(), WithinAbs(b, tolerance));
}
