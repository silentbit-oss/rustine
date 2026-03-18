#include "zahl.h"
#include <stdio.h>
#include <string.h>
#include <setjmp.h>

int main() {
    jmp_buf env;
    z_t a, b, c, d;
    char buf[1024];
    
    if (setjmp(env)) {
        fprintf(stderr, "Error occurred\n");
        return 1;
    }
    
    zsetup(env);
    
    zinit(a);
    zinit(b);
    zinit(c);
    zinit(d);
    
    // Test: (-10 * 7) % 13
    zseti(b, -10);
    zseti(c, 7);
    zseti(d, 13);
    
    zmodmul(a, b, c, d);
    
    printf("(-10 * 7) mod 13 = %s\n", zstr(a, buf));
    
    zfree(a);
    zfree(b);
    zfree(c);
    zfree(d);
    
    zunsetup();
    
    return 0;
}
