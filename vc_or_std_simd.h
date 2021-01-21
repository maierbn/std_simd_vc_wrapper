
#pragma once
// This header files either includes <Vc/Vc> or it includes <experimental/simd> and defines a compatibility namespace Vc.
// In either way, the including code can access Vc functions.

#if __cplusplus >= 201703L
#define HAVE_STDSIMD
#endif

#ifdef HAVE_STDSIMD
// if there is c++17, we use std::experimental::simd

// define compatibility layer such that std::simd appears like Vc
#include <experimental/simd>
namespace Vc
{
  // define types
  using double_v = std::experimental::native_simd<double>;
  using int_v = std::experimental::native_simd<int>;
  
  // import math functions
  using std::experimental::abs;
  using std::experimental::exp;
  using std::experimental::log;
  using std::experimental::where;
  using std::experimental::any_of;
  using std::experimental::all_of;
  
  // define constants
  const std::experimental::native_simd<double> One(1);
  const std::experimental::native_simd<double> Zero(0);
  
  // define inline if functions
  template<typename T>
  constexpr T iif(const typename T::mask_type& mask, const T& trueValue, const T& falseValue)
  {
    T result(falseValue);
    where(mask, result) = trueValue;
    return result;
  }
  
  template<typename T> 
  constexpr T iif (bool condition, const T &trueValue, const T &falseValue)
  {
    return condition ? trueValue : falseValue;
  }

  template<typename T>
  typename T::mask_type isnegative(const T &x)
  {
    return x < 0;
  }

  template<typename T>
  typename T::mask_type isfinite(const T &x)
  {
    typename T::mask_type mask;
    for (int i = 0; i < T::mask_type::size(); i++)
      mask[i] = std::isfinite(x[i]);
    return mask;
  }
  
  // define reduction functions
  template<typename Mask>
  int count(const Mask &mask)
  {
    int result(0);
    for (int i = 0; i < Mask::size(); i++)
      result += (int)(mask[i]);
    return result;
  }
  
  template<typename T>
  typename T::value_type min(const T &x)
  {
    typename T::value_type result(x[0]);
    for (int i = 1; i < T::size(); i++)
      result = std::min(result, x[i]);
    return result;
  }
  
  template<typename T>
  typename T::value_type max(const T &x)
  {
    typename T::value_type result(x[0]);
    for (int i = 1; i < T::size(); i++)
      result = std::max(result, x[i]);
    return result;
  }
}
#else
// if there is no c++17, we are use Vc

#include <Vc/Vc>

namespace Vc_1
{
  // define reduction functions
  template<typename Mask>
  int count(const Mask &mask)
  {
    return mask.count();
  }
  
  template<typename T>
  typename T::value_type min(const T &x)
  {
    return x.min();
  }
  
  template<typename T>
  typename T::value_type max(const T &x)
  {
    return x.max();
  }
}
#endif

