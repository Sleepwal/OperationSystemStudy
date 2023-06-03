#include "../head/thread.h"
#include "../head/thread-sync.h"

int n, count = 0;
mutex_t lk = MUTEX_INIT();
cond_t cv = COND_INIT(); //条件变量

#define CAN_PRODUCE (count < n) //生产者，括号嵌套的深度不超过n
#define CAN_CONSUME (count > 0) //消费者，有生产者资源才能消费

// 被唤醒的时候，条件未必成立
void Tproduce() {
    while(1) {
        mutex_lock(&lk);
        if(!CAN_PRODUCE)  //不符合条件
            cond_wait(&cv, &lk); //睡眠，释放锁

        count++; printf("("); //入栈
        cond_signal(&cv); //唤醒另一个线程
        mutex_unlock(&lk);
    }
}

void Tconsume() {
    while(1) {
        mutex_lock(&lk);
        if(!CAN_CONSUME) 
            cond_wait(&cv, &lk); //睡眠，释放锁

        count--; printf(")"); //出栈
        cond_signal(&cv); //唤醒另一个线程
        mutex_unlock(&lk);
    }
}

int main(int argc, char *argv[]) {
  assert(argc == 3);
  n = atoi(argv[1]); //括号深度
  int T = atoi(argv[2]); //生产者或消费者线程数
  setbuf(stdout, NULL);

  for (int i = 0; i < T; i++) {
    create(Tproduce);
    create(Tconsume);
  }
}