//
// Created by manson on 2023/5/25.
//
#include <cstdio>
#include "fgFun.h"
#include "fgFun_non_recursive.h"
#include "fgFun_os.h"

int main() {
    int n = 5;
    int f_res = f(n);
    int g_res = g(n);
    printf("f = %d, g = %d\n", f_res, g_res);

    fg_no_re(n, 'f');
    printf("f_no_re = %d, ", sum);
    fg_no_re(n, 'g');
    printf("g_no_re = %d\n", sum);

    int f_os_res = fg_os(n, 'f');
    int g_os_res = fg_os(n, 'g');
    printf("f_os_res = %d, ", f_os_res);
    printf("g_os_res = %d\n", g_os_res);

    return 0;
}