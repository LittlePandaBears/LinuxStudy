#include <stdio.h>
#include <string.h>

#define PATH_MAX 256
#define PARAM_MAX 16

enum STATUS {
    SPACE, PATH, PARAMETER, ERROR
};

#define FALSE 0
#define TRUE !FALSE

#define NO_PARAM 0
#define HAVE_a 1 << 0
#define HAVE_l 1 << 1
#define HAVE_R 1 << 2


char path[PATH_MAX];
int pathIndex;
int param;

int analysis_param(char ch);

int analysis_param(char ch) {
    int retValue = TRUE;

    switch (ch) {
        case 'R' : param |= HAVE_R; break;
        case 'l' : param |= HAVE_l; break;
        case 'a' : param |= HAVE_a; break;
        default : retValue = FALSE;
    }

    return retValue;
}

int main(int argc, char *argv[]) {
    int status = SPACE;
    char *str = "pathtest -l          -aR";
        for(int i = 0; i < strlen(str); i++) {
            char ch = str[i];
            if(status == ERROR) {
                fprintf(stderr, "参数有误\n");
                continue;
            }

            if(status == SPACE) {   // 空格状态
                if(ch == '-') {
                    status = PARAMETER;
                    continue;
                }else if (ch == ' ') {
                    continue;
                }else {
                    path[pathIndex++] = ch;
                    path[pathIndex] = '\0';
                    status = PATH;
                    continue;
                }
            }

            if(status == PARAMETER) {   // 参数状态
                if(ch == '-') {
                    status = ERROR;
                    continue;
                }else if(ch == ' ') {
                    status = SPACE;
                    continue;
                }else if(analysis_param(ch)) {
                    continue;
                }else {
                    status = ERROR;
                    continue;
                }
            }

            if(status == PATH) {    // 路径状态
                if(ch == ' ') {
                    status = SPACE;
                    continue;
                }else {
                    path[pathIndex++] = ch;
                    path[pathIndex] = '\0';
                    continue;
                }
            }
        
    }

    printf("path : \"%s\"\n", path);
    printf("param : \"%d\"\n", param);

    return 0;
}