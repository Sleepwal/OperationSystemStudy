#include "thread.h"

int x;

void Thello(int id) {
    x++;
    printf("%d ", x);
}

int main() {
    for(int i = 0; i < 30; i++) {
        create(Thello);
    }
    return 0;
}
