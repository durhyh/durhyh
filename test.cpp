#include "acutest.h"
#define TESTING
#include "gs.cpp"

// 第一个测试：检查模型参数类型（F和K）与u和v向量的元素类型是否匹配
void test_parameter_type_matching(void) {
    // 检查 F 和 u[0][0] 的类型是否匹配
    TEST_CHECK(typeid(F) == typeid(u[0][0]));
    TEST_MSG("The type of F does not match with the type of elements in u");

    // 检查 K 和 v[0][0] 的类型是否匹配
    TEST_CHECK(typeid(k) == typeid(v[0][0]));
    TEST_MSG("The type of k does not match with the type of elements in v");
}

// 第二个测试：确保u和v大小相同
void test_vectors_size_matching(void) {
    // 检查 u 和 v 的大小是否匹配
    TEST_CHECK(u.size() == v.size());
    TEST_MSG("The size of u and v does not match: u.size() = %zu, v.size() = %zu", u.size(), v.size());
}

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

// 测试列表
TEST_LIST = {
    { "parameter_type_matching", test_parameter_type_matching },
    { "vectors_size_matching", test_vectors_size_matching },
    { "simulation_with_zero_initial_values", test_simulation_with_zero_initial_values },
    { NULL, NULL } // 测试列表结束
};