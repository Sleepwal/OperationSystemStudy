#include<assert.h>
#include <cstdio>

typedef struct {
  int pc, n;
  char type;
} Frame;

#define call(...) ({ *(++top) = (Frame) { .pc = 0, __VA_ARGS__ }; })
#define ret()     ({ top--; })
#define goto(loc) ({ f->pc = (loc) - 1; })

int fg_os(int n, char type) {
  int sum = 0;
  Frame stk[64], *top = stk - 1;
  call(n, type);
  for(Frame *f; (f = top) >= stk; f->pc++) {
    n = f->n; type = f->type;
    switch (f->pc) {
      case 0: if(n <= 1) { sum++; goto(2); } break;
      case 1:
        if(type == 'f') {
          call(n - 1, type);
          call(n - 2, 'g');
        } else {
          call(n - 1, type);
          call(n + 1, 'f');
        }
        break;
      case 2: ret(); break;
      default: assert(0);
    }
  }

  return sum;
}