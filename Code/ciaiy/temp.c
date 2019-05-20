#include <stdio.h>

int main(void) {
    FILE *fp;
    fp = fopen("./test", "a+");
    fprintf(fp, "testtest");
    fclose(fp);
        fp = fopen("./test", "a+");
    char msg[1024] = {0};
    fscanf(fp, "%s", msg);
    printf("%s\n", msg);
    return 0;
}