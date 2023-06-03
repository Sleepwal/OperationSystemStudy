#include "../head/thread.h"
#include "../head/thread-sync.h"

#define LENGTH(arr) (sizeof(arr) / sizeof(arr[0]))

enum { A = 1, B, C, D, E, F, };

struct rule {
  int from, ch, to;
} rules[] = {
  { A, '<', B },
  { B, '>', C },
  { C, '<', D },
  { A, '>', E },
  { E, '<', F },
  { F, '>', D },
  { D, '_', A },
};

int current = A, quota = 1;

mutex_t lk = MUTEX_INIT();
cond_t cv = COND_INIT();

int next(char ch) {
  for(int i = 0; i < LENGTH(rules); i++) {
    struct rule *rule = &rules[i];
    if(rule->from == current && rule->ch == ch) //满足状态机 转移到 下一个状态的条件
      return rule->to; //下一个状态
  }
  return 0;
}

static int can_print(char ch) { //能打印
  return next(ch) != 0 && quota > 0; //满足条件且有配额
}

void fish_before(char ch) { //打印前
  mutex_lock(&lk);
  while(!can_print(ch)) {
    cond_wait(&cv, &lk);
  }
  quota--;
  mutex_unlock(&lk);
}

void fish_after(char ch) {
  mutex_lock(&lk);
  quota++;
  current = next(ch);
  assert(current);
  cond_broadcast(&cv);
  mutex_unlock(&lk);
}

const char roles[] = ".<<<<<>>>>___";

void fish_thread(int id) {
  char role = roles[id];
  while(1) {
    fish_before(role); //此时醒来的线程都是合法的
    putchar(role); //没有锁
    fish_after(role); 
  }
}

int main() {
  setbuf(stdout, NULL);
  for(int i = 0; i < strlen(roles); i++) {
    create(fish_thread);
  }
}