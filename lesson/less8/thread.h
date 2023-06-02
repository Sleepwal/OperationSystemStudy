#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdatomic.h>
#include <assert.h>
#include <unistd.h>
#include <pthread.h>
#include <stdint.h>

#define NTHREAD 64

enum { 
    T_FREE = 0, T_LIVE, T_DEAD, 
};

struct thread {
    int id, status;
    pthread_t thread;
    void (*entry)(int);
};

struct thread tpool[NTHREAD], *tptr = tpool;

void* wrapper(void* arg) {
    struct thread *thread = (struct thread *)arg;
    thread->entry(thread->id);
    return NULL;
}

// 创建线程并执行
void create(void *fn) {
    assert(tptr - tpool < NTHREAD);
    *tptr = (struct thread) {
        .id = tptr - tpool + 1,
        .status = T_LIVE,
        .entry = fn,
    };

    pthread_create(&(tptr->thread), NULL, wrapper, tptr);
    ++tptr;
}

// 等待线程执行完毕
void join() {
    for(int i = 0; i < NTHREAD; i++) {
        struct thread * t = &tpool[i];
        //线程存活，执行后死亡
        if(t->status == T_LIVE) {
            pthread_join(t->thread, NULL);
            t->status = T_DEAD;
        }
    }
}

//析构函数
__attribute__((destructor)) void cleanup() {
  join();
}