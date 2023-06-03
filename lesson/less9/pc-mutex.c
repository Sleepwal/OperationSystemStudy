#include "../head/thread.h"
#include "../head/thread-sync.h"

int n, count = 0; //左括号的数量
mutex_t lk = MUTEX_INIT();

#define CAN_PRODUCE (count < n) //生产者，括号嵌套的深度不超过n
#define CAN_CONSUME (count > 0) //消费者，有生产者资源才能消费

void Tproduce() {
    while(1) {
    retry:
        mutex_lock(&lk);
        if(!CAN_PRODUCE) { //不符合条件
            mutex_unlock(&lk); //解锁
            goto retry; //循环判断
        }

        count++;  //入栈
        printf("(");
        mutex_unlock(&lk);
    }
}

void Tconsume() {
    while(1) {
    retry:
        mutex_lock(&lk);
        if(!CAN_CONSUME) {
            mutex_unlock(&lk);
            goto retry;
        }

        count--; //出栈
        printf(")"); 
        mutex_unlock(&lk);
    }
}

int main(int argc, char *argv[]) {
    assert(argc == 2);

    n = atoi(argv[1]);
    setbuf(stdout, NULL);

    for(int i = 0; i < 8; i++) {
        create(Tproduce);
        create(Tconsume);
    }
}