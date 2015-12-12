// =============================================================================
// PROJECT CHRONO - http://projectchrono.org
//
// Copyright (c) 2014 projectchrono.org
// All right reserved.
//
// Use of this source code is governed by a BSD-style license that can be found
// in the LICENSE file at the top level of the distribution and at
// http://projectchrono.org/license-chrono.txt.
//
// =============================================================================
// Authors: Hammad Mazhar
// =============================================================================
//
// Description: definition of a real number which can be defined as a float
// (increased speed on some architectures) or a double (increased precision)
// =============================================================================

#pragma once

#include "chrono_parallel/ChParallelDefines.h"
#include <cmath>
#include <float.h>

namespace chrono {
// Check if SSE was found in CMake
#ifdef CHRONO_PARALLEL_HAS_SSE
// Depending on the SSE variable in CMake include the proper header file for that
// version of sse
#ifdef CHRONO_PARALLEL_SSE_1_0
#include <xmmintrin.h>
#elif defined CHRONO_PARALLEL_SSE_2_0
#include <emmintrin.h>
#elif defined CHRONO_PARALLEL_SSE_3_0
#include <pmmintrin.h>
#elif defined CHRONO_PARALLEL_SSE_4_1
#include <smmintrin.h>
#elif defined CHRONO_PARALLEL_SSE_4_2
#include <nmmintrin.h>
#endif
#ifndef ENABLE_SSE
#define ENABLE_SSE
#endif
#else
#undef ENABLE_SSE
#endif

// If the user specified using doubles in CMake make sure that SSE is disabled
#ifdef CHRONO_PARALLEL_USE_DOUBLE
#undef ENABLE_SSE
#endif
// If the user specified using doubles, define the real type as double
// Also set some constants. The same is done if floats were specified.
#ifdef CHRONO_PARALLEL_USE_DOUBLE
typedef double real;
#define C_LARGE_REAL DBL_MAX
#define C_EPSILON DBL_EPSILON
#else
typedef float real;
#define C_LARGE_REAL FLT_MAX
#define C_EPSILON FLT_EPSILON
#endif

//#define C_Pi 4 * ATan(real(1.0))
//#define C_2Pi real(2.0) * C_Pi
//#define C_InvPi real(1.0) / C_Pi
//#define C_Inv2Pi real(0.5) / C_Pi
//
//#define C_DegToRad C_Pi / real(180.0)
//#define C_RadToDeg real(180.0 / C_Pi

#ifdef CHRONO_PARALLEL_USE_DOUBLE

// Trig Functions
// ========================================================================================
static inline real Sin(const real theta) {
  return sin(theta);
}
static inline real Cos(const real theta) {
  return cos(theta);
}
static inline real Tan(const real theta) {
  return tan(theta);
}
static inline real ASin(const real theta) {
  return asin(theta);
}
static inline real ACos(const real theta) {
  return acos(theta);
}
static inline real ATan(const real theta) {
  return atan(theta);
}
static inline real ATan2(const real x, const real y) {
  return atan2(x, y);
}
// Geometric Functions
// ========================================================================================
static inline real Sqr(const real x) {
  return x * x;
}
static inline real Cube(const real x) {
  return x * x * x;
}
static inline real Sqrt(const real x) {
  return sqrt(x);
}
static inline real InvSqrt(const real x) {
  return 1.0 / sqrt(x);  // could also use rsqrtf(x) here and avoid division
}
static inline real Abs(const real x) {
  return fabs(x);
}
static inline real Pow(const real b, const real e) {
  return pow(b, e);
}
static inline real Mod(const real x, const real y) {
  return fmod(x, y);
}
static inline real Exp(const real x) {
  return exp(x);
}
static inline real Min(const real a, const real b) {
  return fmin(a, b);
}
static inline real Max(const real a, const real b) {
  return fmax(a, b);
}
static inline real Floor(const real a) {
  return floor(a);
}
static inline real Ceil(const real a) {
  return ceil(a);
}
static inline real Round(const real a) {
  return round(a);
}
static inline real Log(const real a) {
  return log(a);
}
#else

// Trig Functions
// ========================================================================================
static inline real Sin(const real theta) {
  return sinf(theta);
}
static inline real Cos(const real theta) {
  return cosf(theta);
}
static inline real Tan(const real theta) {
  return tanf(theta);
}
static inline real ASin(const real theta) {
  return asinf(theta);
}
static inline real ACos(const real theta) {
  return acosf(theta);
}
static inline real ATan(const real theta) {
  return atanf(theta);
}
static inline real ATan2(const real x, const real y) {
  return atan2f(x, y);
}
static inline real DegToRad(const real t) {
  return t * C_DegToRad;
}
static inline real RadToDeg(const real t) {
  return t * C_RadToDeg;
}

// Geometric Functions
// ========================================================================================
static inline real Sqr(const real x) {
  return x * x;
}
static inline real Cube(const real x) {
  return x * x * x;
}
static inline real Sqrt(const real x) {
  return sqrtf(x);
}
static inline real InvSqrt(const real x) {
  return 1.0f / sqrtf(x);  // could also use rsqrtf(x) here and avoid division
}
static inline real Abs(const real x) {
  return fabsf(x);
}
static inline real Pow(const real b, const real e) {
  return powf(b, e);
}
static inline real Mod(const real x, const real y) {
  return fmod(x, y);
}
static inline real Exp(const real x) {
  return expf(x);
}
static inline real Min(const real a, const real b) {
  return fminf(a, b);
}
static inline real Max(const real a, const real b) {
  return fmaxf(a, b);
}
static inline real Floor(const real a) {
  return floorf(a);
}
static inline real Ceil(const real a) {
  return ceilf(a);
}
static inline real Round(const real a) {
  return roundf(a);
}
static inline real Log(const real a) {
  return logf(a);
}
#endif

// static inline real DegToRad(real t) {
//    return t * C_DegToRad;
//}
// static inline real RadToDeg(real t) {
//    return t * C_RadToDeg;
//}

//static inline real Sign(const real x) {
//  return x < 0.0f ? -1.0f : 1.0f;
//}
// Returns a -1 if the value is negative
// Returns a +1 if the value is positive
// Otherwise returns zero, this should only happen if the given value is zero
static inline real Sign(const real& x) {
  if (x < 0) {
    return -1;
  } else if (x > 0) {
    return 1;
  } else {
    return 0;
  }
}

// Checks if the value is zero to within a certain epsilon
// in this case ZERO_EPSILON is defined based on what the base type of real is
static inline bool IsZero(const real x) {
  return Abs(x) < C_EPSILON;
}

// template <typename T>
// inline T Min(T a, T b) {
//    return a < b ? a : b;
//}
//
// template <typename T>
// inline T Max(T a, T b) {
//    return a > b ? a : b;
//}

// Check if two values are equal using a small delta/epsilon value.
// Essentially a fuzzy comparison operator
// template <typename T>
// inline bool IsEqual(const T& x, const T& y) {
//    return IsZero(x - y);
//}

// Check if two values are equal using a small delta/epsilon value.
// Essentially a fuzzy comparison operator
template <typename T>
static inline bool IsEqual(const T& _a, const T& _b) {
  real ab;
  ab = Abs(_a - _b);
  if (Abs(ab) < C_EPSILON)
    return 1;
  real a, b;
  a = Abs(_a);
  b = Abs(_b);
  if (b > a) {
    return ab < C_EPSILON * b;
  } else {
    return ab < C_EPSILON * a;
  }
}

template <typename T>
inline real LengthSq(const T v) {
  return Dot(v);
}

template <typename T>
inline real Length(const T& v) {
  return Sqrt(LengthSq(v));
}

template <typename T>
inline real SafeLength(const T& v) {
  real len_sq = LengthSq(v);
  if (len_sq) {
    return Sqrt(len_sq);
  } else {
    return 0.0f;
  }
}

template <typename T>
inline T Normalize(const T& v) {
  return v / Length(v);
}

template <typename T>
inline T SafeNormalize(const T& v, const T& safe = T()) {
  real len_sq = LengthSq(v);
  if (len_sq > 0.0f) {
    return v * InvSqrt(len_sq);
  } else {
    return safe;
  }
}

template <typename T, typename U>
inline T Lerp(const T& start, const T& end, const U& t) {
  return start + (end - start) * t;
}

template <typename T>
inline void Swap(T& a, T& b) {
  T temp = a;
  a = b;
  b = temp;
}
// Clamps a given value a between user specified minimum and maximum values
template <typename T>
inline T Clamp(T x, T low, T high) {
  if (low > high) {
    Swap(low, high);
  }
  return Max(low, Min(x, high));
}

template <typename T, typename U>
inline T ClampMin(T x, U low) {
  return Max(low, x);
}

template <typename T, typename U>
inline T ClampMax(T x, U high) {
  return Min(x, high);
}
}
//=========MACROS
#define OPERATOR_EQUALS(op, tin, tout)     \
  inline tout& operator op##=(tin scale) { \
    *this = *this op scale;                \
    return *this;                          \
  }
