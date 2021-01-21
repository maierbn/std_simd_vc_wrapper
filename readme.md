This is a wrapper to [std::experimental::simd](https://github.com/VcDevel/std-simd) that makes it useable (almost) like [Vc 1.4.1](https://github.com/VcDevel/Vc).
It consists of one header file ([vc_or_std_simd.h](https://github.com/maierbn/std_simd_vc_wrapper/blob/main/vc_or_std_simd.h)), which includes either Vc or std-simd, depending if compiled with c++17 support.

Thus, it is possible to include this header in code that uses Vc and actually use std::simd with its AVX-512 support.

The support is not completely perfect as some high-level functions of Vc such as reductions are not implemented in std::experimental::simd. Have a look at the header file to learn the exact usage.
