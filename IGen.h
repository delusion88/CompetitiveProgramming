#ifndef _IGen
#define _IGen

#include <random>
#include <chrono>
#include <type_traits>

namespace IGen {
  std::mt19937 mtrand (std::chrono::steady_clock::now ().time_since_epoch ().count ());

  template <
    typename T,
    typename = typename std::enable_if<std::is_integral<T>::value, T>
  >
  T nextInt (T l, T r) {
    std::uniform_int_distribution<T> uid (l, r);
    return uid (mtrand);
  }

  template <
    typename T,
    typename = typename std::enable_if<std::is_integral<T>::value, T>
  >
  T nextInt (T r) {
    return next (1, r);
  }

  template <
    typename T,
    typename = typename std::enable_if<std::is_floating_point<T>::value, T>
  >
  T nextFloat (T l, T r) {
    std::uniform_real_distribution<T> urd (l, r);
    return urd (mtrand);
  }

  template <
    typename T,
    typename = typename std::enable_if<std::is_floating_point<T>::value, T>  
  >
  T nextFloat (T r) {
    return next (0., r);
  }
};

#endif
