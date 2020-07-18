#include <immintrin.h>
#include <iostream>

const int N = 123;

float slow_dot_product(const float *a, const float *b) {
    float answer = 0.0;
    for (int i = 0; i < N; ++i)
        answer += a[i] * b[i];
    return answer;
}

float reduce_vector(__m256 input) {
    __m256 temp = _mm256_hadd_ps(input, input);
    return ((float*)&temp)[0] + ((float*)&temp)[1] + ((float*)&temp)[4] + ((float*)&temp)[5];
}

float dot_product(const float *a, const float *b) {
    __m256 sum_vec = _mm256_set1_ps(0.0);

    /* Add up partial dot-products in blocks of 256 bits */
    for(int i = 0; i < N / 8; ++i) {
        __m256 x = _mm256_load_ps(a + 8 * i);
        __m256 y = _mm256_load_ps(b + 8 * i);
        __m256 z = _mm256_mul_ps(x, y);
        sum_vec = _mm256_add_ps(sum_vec, z);
    }
    float final = 0.0;
    for(int i = N - N % 8; i < N; ++i)
        final += a[i] * b[i];
    return reduce_vector(sum_vec) + final;
}

int main() {
    __attribute__ ((aligned (32))) float a[N], b[N];

    for(int i = 0; i < N; ++i)
        a[i] = b[i] = i;

    std::cout << dot_product(a, b) << "\n"
        << slow_dot_product(a, b) << "\n";

    return 0;
}
