#include "httpd.h"

int main(void) {
    httpd server = httpd(2333);
    server.start();

    return 0;
}