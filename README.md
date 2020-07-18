# Simple AVX examples

There are 5 simple examples showing how to use AVX intrinsics to accelerate your program. However, please remember that I am a beginner in the use of CPU vector instructions. I'm not claiming this code is exemplary.

To build this respository, make sure your computer support AVX2, to find out, run the command

`cat /proc/cpuinfo | grep avx2`

## References

1. https://software.intel.com/en-us/articles/introduction-to-intel-advanced-vector-extensions/
2. https://software.intel.com/en-us/articles/benefits-of-intel-avx-for-small-matrices/
3. https://www.codeproject.com/Articles/874396/Crunching-Numbers-with-AVX-and-AVX
4. https://software.intel.com/en-us/node/523876
5. http://sci.tuomastonteri.fi/programming/sse
6. http://stackoverflow.com/questions/13577226/intel-sse-and-avx-examples-and-tutorials
7. http://supercomputingblog.com/optimization/getting-started-with-sse-programming/
8. https://felix.abecassis.me/2011/09/cpp-getting-started-with-sse/
9. http://www.walkingrandomly.com/?p=3378
10. https://software.intel.com/sites/landingpage/IntrinsicsGuide/

## Problem 1: add two (properly aligned) arrays of floats

Not only will we assume the input is correctly aligned, but also that
their lengths are multiples of 256 bits.

## Problem 2: add two arbitrary arrays of floats

Are there necessary restrictions on alignment with respect to each
other, or can we take any two arrays of float anywhere in memory?

## Problem 3: dot product

Let's calcuate dot product of two vectors.

## Problem 4: linear search through an array

I have seen it asserted online that brute force linear search can beat
binary search for arrays of size up to 10K. The calculations people
give to support this claim involve vector instructions. Let's try
writing a vectorized linear search.

## Problem 5: aligned issue for AVX accelerated class

When the object is created dynamically, its address is determined at runtime.
However, C++ Runtime Library does not concern the alignment statement,
so we need to overload the new function.

In addition, if we want to create a class with aligned class dynamically,
C++ Runtime Library will not call the overload new function,
which will cause memory disalignment.
The solution is relatively tricky, which requires users to use a Macro in their code.
See the code for detail.

Reference 
http://eigen.tuxfamily.org/dox-devel/group__DenseMatrixManipulation__Alignement.html
