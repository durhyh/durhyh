#include"acutest.h"

void test_answer_zero() {
    void init() {
        for (int x = 0; x < width; ++x) {
            for (int y = 0; y < height; ++y) {
                u[x][y] = 0.0;
                v[x][y] = 0.0;
            }
        }
    }

    main(5, new char* [5] {"0.14", "0.07", "0.03", "0.0648", "0.1"});

    int countAboveThreshold = countElementsAboveThreshold();
    TEST_CHECK(countAboveThreshold == 0);
}

TEST_LIST = {
    {"test_answer_zero", test_answer_zero},
    {NULL, NULL}
};