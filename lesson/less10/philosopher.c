/**
 * 哲学家问题
*/

#include "../head/thread.h"
#include "../head/thread-sync.h"

#define N 5

sem_t table, avail[N];

void Tphilosopher(int id) {
    int lhs = (id + N - 1) % N; //左叉子
    int rhs = id % N; //右叉子

    
    P(&table); // 进入桌子

    P(&avail[lhs]);
    printf("拿 %d by T%d\n", lhs, id);
    P(&avail[rhs]);
    printf("拿 %d by T%d\n", rhs, id);

    //吃
    //放回叉子
    printf("放 %d by T%d\n", lhs, id);
    printf("放 %d by T%d\n", rhs, id);
    V(&avail[lhs]);
    V(&avail[rhs]);


    V(&table); // 离开桌子
}

int main() {
    SEM_INIT(&table, N - 1);

    for (int i = 0; i < N; i++) {
        SEM_INIT(&avail[i], 1);
    }
    for (int i = 0; i < N; i++) {
        create(Tphilosopher);
    }
}
