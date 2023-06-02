#include "thread.h"

unsigned long balance = 100;

void ali_pay(int amt) {
    if(balance >= amt) {
        usleep(1);
        balance -= amt;
    }
}

void tail_pay(int id) {
    ali_pay(100);
}

int main() {
    create(tail_pay);
    create(tail_pay);
    join();
    printf("balance = %lu\n", balance);

    return 0;
}