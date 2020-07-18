#include <immintrin.h>
#include <string>
#include <iostream>

#define QY_ALIGNED_OPERATOR_NEW \
    void* operator new (std::size_t count) { \
        void* original = ::operator new(count + 32); \
        void* aligned = reinterpret_cast<void*>((reinterpret_cast<size_t>(original) & ~size_t(32 - 1)) + 32); \
        *(reinterpret_cast<void**>(aligned) - 1) = original; \
        return aligned;\
    } \
    void operator delete (void* ptr) { \
        ::operator delete(*(reinterpret_cast<void**>(ptr) - 1)); \
    }

class Vector4f {
public:
    Vector4f() {}
    Vector4f(float a, float b, float c, float d) {
        data[0] = a;
        data[1] = b;
        data[2] = c;
        data[3] = d;
    }

    Vector4f operator+ (const Vector4f& v) {
        __m256 data1 = _mm256_load_ps(data);
        __m256 data2 = _mm256_load_ps(v.data);
        __m256 data3 = _mm256_add_ps(data1, data2);
        Vector4f result;
        _mm256_store_ps(result.data, data3);
        return result;
    }

    void* operator new (std::size_t count) {
        void* original = ::operator new(count + 32);
        void* aligned = reinterpret_cast<void*>((reinterpret_cast<size_t>(original) & ~size_t(32 - 1)) + 32);
        *(reinterpret_cast<void**>(aligned) - 1) = original;
        return aligned;
    }

    void operator delete (void* ptr) {
        ::operator delete(*(reinterpret_cast<void**>(ptr) - 1));
    }

    void printAddress(const std::string& s) const {
        std::cout << s << data << std::endl;
    }

    friend std::ostream& operator<<(std::ostream& o, const Vector4f& v);

private:
    using aligned_float4 = __attribute__((aligned(32))) float[4];
    aligned_float4 data;
};

std::ostream& operator<<(std::ostream& o, const Vector4f& v) {
    o << "(" << v.data[0] << ", " << v.data[1] << ", " << v.data[2] << ", " << v.data[3] << ")";
    return o;
}

class Point {
public:
    Point() {}
    Point(const Vector4f& v) : pos(v) {}

    void printAddress(const std::string& s) const {
        pos.printAddress(s);
    }
    QY_ALIGNED_OPERATOR_NEW;
    Vector4f pos;
    
};

int main() {
    Vector4f* input1 = new Vector4f(1, 1, 1, 1);
    Vector4f* input2 = new Vector4f(1, 2, 3, 4);

    Point* point1 = new Point(*input1);
    Point* point2 = new Point(*input2);

    point1->printAddress("address of point1: ");
    point2->printAddress("address of point2: ");

    Vector4f result = point1->pos + point2->pos;

    std::cout << result << std::endl;

    delete input1;
    delete input2;
    delete point1;
    delete point2;
    return 0;
}
