#include <immintrin.h>
#include <iostream>

int main() {
    
    float a[8]{ 1,1,1,1,1,1,1,1 };
    float b[8]{ 1,2,3,4,5,6,7,8 };
    float c[8];

    __m256 x = _mm256_loadu_ps(a);
    __m256 y = _mm256_loadu_ps(b);
    __m256 z = _mm256_add_ps(x, y);

    _mm256_storeu_ps(c, z);

    std::cout << c[0] << " " << c[1] << " " << c[2] << " " << c[3] << " " 
        << c[4] << " " << c[5] << " " << c[6] << " " << c[7] << "\n";
    
    return 0;

}
