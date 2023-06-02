#include "thread.h"

#define N 100000000
#define M 10

long sum = 0; //和

int xchg(int volatile *ptr, int newval)
{
    int result;
    asm volatile(
        "lock xchgl %0, %1"
        : "+m"(*ptr), "=a"(result)
        : "1"(newval)
        : "memory");
    return result;
}

int locked = 0; //锁

void lock() { //上锁
    while(xchg(&locked, 1));
}

void unlock() { //解锁
    xchg(&locked, 0);
}

void Tsum() {
    long nround = N / M; //分为M份
    for (int i = 0; i < nround; i++) { 
        lock(); 
        for(int j = 0; j < M; j++) { 
            sum++; // 非原子指令，sum是一个普通的变量
        }
        unlock();
    }   
}

int main() {
    assert(N % M == 0);
    create(Tsum);
    create(Tsum);
    join();
    printf("sum = %ld\n", sum);
}