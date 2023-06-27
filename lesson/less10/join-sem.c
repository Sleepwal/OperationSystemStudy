/**
 * 信号量实现线程 join
*/

#include "../head/thread.h"
#include "../head/thread-sync.h"

#define T 4
#define N 10000000

sem_t done; //计数型的同步
long sum = 0;

void atomic_inc(long *ptr) {
    asm volatile(
        "lock incq %0"
        : "+m"(*ptr) : : "memory"
    );
}

void Tsum() {
    for(int i = 0; i < N; i++) {
        atomic_inc(&sum); //sum++;
    }
    V(&done); //放一个球
}

void Tprint() {
    for(int i = 0; i < T; i++) { //拿到T个球才继续
        P(&done);
    }
    printf("sum = %ld\n", sum);
}

int main() {
    SEM_INIT(&done, 0);
    // T个Tsum
    for(int i = 0; i < T; i++) {
        create(Tsum);
    }
    create(Tprint); //1个Tprint
}