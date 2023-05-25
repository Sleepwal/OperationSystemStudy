//
// Created by manson on 2023/5/25.
//
#include <cstdio>
#include "fgFun.h"
#include "fgFun_non_recursive.h"

int main() {
    int n = 5;
    int f_res = f(n);
    int g_res = g(n);
    printf("f = %d, g = %d\n", f_res, g_res);

    fg_no_re(n, 'f');
    printf("f_no_re = %d, ", sum);
    fg_no_re(n, 'g');
    printf("g_no_re = %d", sum);

    return 0;
}