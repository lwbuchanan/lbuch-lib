#include <stdio.h>

#define LBUCH_DARRAY_IMPLEMENTATION
#include "../darray.h"
#include "../defs.h"

#define RED  "\x1B[31m"
#define YEL  "\x1B[33m"
#define NRM  "\x1B[0m"

typedef struct {
  u32 total;
  u32 failed;
} test_ctx;

int test_eq(test_ctx *ctx, int exp, int act) {
  ctx->total++;
  if (exp != act) {
    ctx->failed++;
    printf("%sTest %d failed:\n\tExpected: %d\n\tActual: %d\n", RED, ctx->total, exp, act);
    return 1;
  }
  return 0;
}


void test_darray(test_ctx *ctx) {
    printf("%s\n== Testing darray.h ==\n", NRM);

    // Test append
    da_int *da = init_da_int();
    da_int_append(da, 1);
    test_eq(ctx, 1, da->data[0]);
    da_int_append(da, 2);
    test_eq(ctx, 2, da->data[1]);
    da_int_append(da, 3);
    test_eq(ctx, 3, da->data[2]);
    delete_da_int(da);

    // Test grow
    da = init_da_int();
    test_eq(ctx, 256, da->capacity);
    da_int_grow(da);
    test_eq(ctx, 512, da->capacity);
    delete_da_int(da);

    // Append a bunch
    da = init_da_int();
    for (int i = 0; i < 2047; i++) {
        da_int_append(da, i);
    }
    test_eq(ctx, 2048, da->capacity);
    test_eq(ctx, 2047, da->size);
    test_eq(ctx, 1111, da->data[1111]);
    delete_da_int(da);
}

int main(int argc, char **argv) {
  test_ctx ctx = {0, 0};

  test_darray(&ctx);

  printf("%s\n== Results ==\n", NRM);
  if (ctx.failed == 0) {
    printf("%sAll tests passed\n%s", YEL, NRM);
  } else {
    printf("%s%d tests failed\n%s", RED, ctx.failed, NRM);
  }
  
  return 0;
}
