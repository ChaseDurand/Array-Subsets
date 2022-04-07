#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../src/arraySubsets.cpp"
#include "tests.h"

namespace tests{
    TEST_CASE ("Case 1") {
        REQUIRE (subsetA(in1) == out1);
    }

    TEST_CASE ("Case 2") {
        REQUIRE (subsetA(in2) == out2);
    }

    TEST_CASE ("Case 3") {
        REQUIRE (subsetA(in3) == out3);
    }

    // TODO
    // TEST_CASE ("Case 4") {
    //     REQUIRE (subsetA(in4) == out4);
    // }

    TEST_CASE ("Case 5") {
        REQUIRE (subsetA(in5) == out5);
    }

    TEST_CASE ("Case 6") {
        REQUIRE (subsetA(in6) == out6);
    }

    TEST_CASE ("Case 7") {
        REQUIRE (subsetA(in7) == out7);
    }

    TEST_CASE ("Case 8") {
        REQUIRE (subsetA(in8) == out8);
    }
}