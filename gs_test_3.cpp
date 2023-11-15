#include "acutest.h"
#define TESTING
#include "gs.cpp"

// 第三个测试：当u=0和v=0时，检查模拟产生的数学上的正确答案
void test_simulation_with_zero_initial_values(void) {
    // 将 u 和 v 初始化为 0
    for (auto& row : u) std::fill(row.begin(), row.end(), 0.0);
    for (auto& row : v) std::fill(row.begin(), row.end(), 0.0);

    // 运行模拟
    for (int iteration = 0; iteration < numIterations; ++iteration) {
        simulateStep();
    }

    // 检查 u 中是否有元素大于 0
    bool uHasPositive = false;
    for (const auto& row : u) {
        if (std::any_of(row.begin(), row.end(), [](double val) { return val > 0.0; })) {
            uHasPositive = true;
            break;
        }
    }

    // 检查 v 是否仍然全为 0
    bool vAllZero = std::all_of(v.begin(), v.end(), [](const std::vector<double>& row) {
        return std::all_of(row.begin(), row.end(), [](double val) { return val == 0.0; });
    });

    TEST_CHECK(uHasPositive && vAllZero);
    TEST_MSG("Simulation result is not as expected when u and v are initialized to zero.");
}

TEST_LIST = {
    { "simulation_with_zero_initial_values", test_simulation_with_zero_initial_values },
    { NULL, NULL } // 测试列表结束
};