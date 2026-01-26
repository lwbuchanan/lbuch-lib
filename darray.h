/*
 * Flexible Dynamic Array Implementation
 * This library allows you to define dynamic arrays for custom types with by
 * calling one macro. Add #define LBUCH_DARRAY_IMPLEMENTATION below the include
 * to also include common darray implementations for types like int and float.
 * These arn't defined by default to avoid cluttering the namespace when
 * unneeded.
 *
 * To define a darray for a custom type, call the macro
 * `IMPLEMENT_DARRAY(<TYPE>, <DA_TYPE_NAME>)`. This includes a typedef for the
 * name you provide. If you use this method, you can expand the macro to get the
 * full implementation in your code, nice and free of icky macros. You can also
 * use the underlying macros to define your own darray methods for operations
 * like init, append, delete, etc.
 *
 * To get and set value at a particular index, use the underlying data buffer.
 * YOU are reponsible for bounds checking in this particular case. Always make
 * sure to grow the buffer if it doesn't have capacity to store a value at the
 * index you want to access.
 *
 * Author: Luke Buchanan
 * License: MIT License
 */

#ifndef LBUCH_DARRAY_INCLUDE
#define LBUCH_DARRAY_INCLUDE

#include <stdlib.h>

#include <lbuch/defs.h>

#define DARRAY(T)                                                              \
  /* Declare a new darray that store type T */                                 \
  struct {                                                                     \
    T *data;                                                                   \
    usize size;                                                                \
    usize capacity;                                                            \
  }

#define INIT_DARRAY(T, da_type, da, cap)                                       \
  /* Dyanamically allocates da as a `da_type<T>`                               \
   * with a data buffer of size `cap` */                                       \
  do {                                                                         \
    da = (da_type *)malloc(sizeof(da_type));                                   \
    T *data = (T *)malloc(sizeof(T) * cap);                                    \
    da->data = data;                                                           \
    da->size = 0;                                                              \
    da->capacity = cap;                                                        \
  } while (0)

#define DESTROY_DARRAY(da)                                                     \
  /* Frees `da` and its underlying data buffer */                              \
  do {                                                                         \
    free(da->data);                                                            \
    free(da);                                                                  \
  } while (0)

#define DARRAY_GROW(T, da)                                                     \
  /* Grow the data buffer by 2x its current capacity */                        \
  do {                                                                         \
    da->capacity *= 2;                                                         \
    da->data = (T *)realloc(da->data, da->capacity * sizeof(T));               \
  } while (0)

#define DARRAY_APPEND(T, da, val)                                              \
  /* Push `val` of type T to the back of `da`.                                 \
   * Grow the data buffer if needed */                                         \
  do {                                                                         \
    if (da->size >= da->capacity) {                                            \
      DARRAY_GROW(T, da);                                                      \
    }                                                                          \
    da->data[da->size++] = val;                                                \
  } while (0)

#define IMPLEMENT_DARRAY(T, name)                                              \
  /* Define a new darray type `name<T>`                                        \
   * Declares and implements all common dynamic array methods */               \
  typedef DARRAY(T) name;                                                      \
  name *init_##name() {                                                        \
    name *da;                                                                  \
    INIT_DARRAY(T, name, da, 256);                                             \
    return da;                                                                 \
  }                                                                            \
  void delete_##name(name *da) { DESTROY_DARRAY(da); }                         \
  void name##_grow(name *da) { DARRAY_GROW(T, da); }                           \
  void name##_append(name *da, T val) { DARRAY_APPEND(T, da, val); }

#define DECLARE_DARRAY(T, name)                                                \
  /* Define a new darray type `name<T>`                                        \
   * Declares and implements all common dynamic array methods */               \
  typedef DARRAY(T) name;                                                      \
  name *init_##name();                                                         \
  void delete_##name(name *da);                                                \
  void name##_grow(name *da);                                                  \
  void name##_append(name *da, T val);

#ifdef LBUCH_DARRAY_IMPLEMENTATION
IMPLEMENT_DARRAY(int, da_int)
IMPLEMENT_DARRAY(long, da_long)
IMPLEMENT_DARRAY(float, da_float)
IMPLEMENT_DARRAY(double, da_double)
IMPLEMENT_DARRAY(char *, da_string)
#endif

#endif
