#include "solve_eq.h"
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <vector>

#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators_all.hpp>

constexpr double I = 1.0;
constexpr double EPS0 = 1;
constexpr double EPS2 = 1e-2;

template <class T1, class T2>
bool RoughEq(T1 lhs, T2 rhs, T2 epsilon) { 
    return std::fabs(lhs - rhs) < epsilon;
}

template <class T1, class T2>
bool RoughLT(T1 lhs, T2 rhs, T2 epsilon) {
    return rhs - lhs >= epsilon;
}

template <class T1, class T2>
bool RoughtLTE(T1 lhs, T2 rhs, T2 epsilon) {
    return rhs - lhs > -epsilon;
}

void GeneratRightPart(int64_t n, std::vector<double>& right_part) {
    assert(right_part.size() == static_cast<size_t>(n));
    const double step = I / (n * n);
    for (int i = 1; i < n; ++i) {
        right_part[i] = 2 * ((i * step + I) * (i * step + I) - 4 * i * i * step * (i * step + I)) / ((i * step + I) * (i * step + I) * (i * step + I) * (i * step + I));
    }
}

static void Test(const int64_t n) {
    std::vector<double> x(n);
    std::vector<double> right_part(n);
    GeneratRightPart(n, right_part);
    Solve(n, right_part, x);
    double val, l2_norm = 0, c_norm = 0;
    for(int64_t i = 1; i < n; i++) {
        val = std::abs(x[i] - I / (i + 1));
        l2_norm += val * val;
        c_norm = std::max(c_norm, val);
    }
    l2_norm = std::sqrt(l2_norm) / n;
    REQUIRE(RoughEq<double, double>(l2_norm, 0, EPS2));
    REQUIRE(RoughEq<double, double>(c_norm, 0, EPS0));
}

TEST_CASE("Size 100") {
    Test(100);
}

TEST_CASE("Size 1000") {
    Test(1000);
}

TEST_CASE("Size 10000") {
    Test(10000);
}

TEST_CASE("Size 100000") {
    Test(100000);
}