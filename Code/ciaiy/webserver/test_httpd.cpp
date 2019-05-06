#include "httpd.h"

int main(void) {
    httpd server = httpd(8888);
    server.start();

    return 0;
}