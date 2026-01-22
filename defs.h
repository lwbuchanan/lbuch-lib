/*
 * Common typedefs. Can be used in place of stddef.h, stdint.h, etc
 *
 * Author: Luke Buchanan
 * License: MIT License
 */

#ifndef LBUCH_DEFS_INCLUDE
#define LBUCH_DEFS_INCLUDE

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Rust-style primatives because I like them better. Sue me.
typedef uint64_t u64;
typedef int64_t i64;
typedef uint32_t u32;
typedef int32_t i32;
typedef uint16_t u16;
typedef int16_t i16;
typedef uint8_t u8;
typedef int8_t i8;

typedef float f32;
typedef double f64;

typedef size_t usize;

// Some convenient vectors
typedef struct {
  float x, y, z;
} vec3_f32;

typedef struct {
  int32_t x, y, z;
} vec3_i32;

typedef struct {
  uint32_t x, y, z;
} vec3_u32;

#endif
