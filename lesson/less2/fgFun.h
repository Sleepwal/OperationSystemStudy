//
// Created by manson on 2023/5/25.
//

#ifndef OSSTUDY_FGFUN_H
#define OSSTUDY_FGFUN_H

#endif //OSSTUDY_FGFUN_H

int g(int);
int f(int);

int f(int n) {
    if (n <= 1) return 1;
    return f(n - 1) + g(n - 2);
}

int g(int n) {
    if (n <= 1) return 1;
    return f(n + 1) + g(n - 1);
}