#include "../head/thread.h"
#include "../head/thread-sync.h"

sem_t fill, empty; //两个信号量，一个打印 ) ，一个打印 (

void Tproduce() {
    while(1) {
        P(&empty); //-1，少一个 能打印左括号的数量
        printf("(");
        V(&fill); //+1 多一个 能打印右括号的数量
    }
}

void Tconsume() {
    while(1) {
        P(&fill);
        printf(")");
        V(&empty);
    }
}

int main(int argc, char *argv[]) {
    assert(argc == 2);
    SEM_INIT(&fill, 0); //0
    SEM_INIT(&empty, atoi(argv[1])); //括号深度

    for(int i = 0; i < 8; i++) {
        create(Tproduce);
        create(Tconsume);
    }
}