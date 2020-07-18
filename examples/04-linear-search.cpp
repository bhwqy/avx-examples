#include <random>
#include <cmath>
#include <immintrin.h>
#include <iostream>

const int N = 1234;

int slow_linear_search(const float* a, float target) {
    for (int i = 0; i < N; ++i) 
        if (a[i] == target)
            return i;
    return -1;
}

int fast_linear_search(const float* a, float target) {
    __m256 target_vector = _mm256_set1_ps(target);
    for (int i = 0; i < N / 8; ++i) {
        __m256 x = _mm256_load_ps(a + 8 * i);
        __m256 ans = _mm256_cmp_ps(x, target_vector, _CMP_EQ_OQ);

        // TODO is there any way better then this?
        int* tmp = (int*)(&ans);
        for (int j = 0; j < 8; ++j)
            if (tmp[j] != 0)
                return i * 8 + j; 
    }
    for (int i = N - N % 4; i < N; ++i) {
        if (a[i] == target)
            return i;
    }
    return -1;
}

int main() {
    __attribute__((aligned(32))) float a[N];
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<float> urd(-100, 100);
    for (int i = 0; i < N; ++i)
        a[i] = urd(mt);
    std::uniform_int_distribution<int> uid(0, 1234);
    int target = uid(mt);
    std::cout << slow_linear_search(a, a[target]) << " " << fast_linear_search(a, a[target]) << "\n";
    return 0;
}
