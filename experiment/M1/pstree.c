#include<stdio.h>

void readFile() {
    FILE *fp = NULL;
    char buff[255];

    fp = fopen("/proc/cpuinfo", "r");
    while(fp) {
        fscanf(fp, "%s", buff);
        printf("%s\n", buff);
        
        fclose(fp);
    }

}

int main() {
    readFile();

    return 0;
}