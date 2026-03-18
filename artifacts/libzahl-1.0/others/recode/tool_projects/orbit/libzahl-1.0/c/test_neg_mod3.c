#include "zahl.h"
#include <stdio.h>
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
    
    // Test zmodpow: (-3)^3 % 10
    zseti(b, -3);
    zseti(c, 3);
    zseti(d, 10);
    
    zmodpow(a, b, c, d);
    
    printf("(-3)^3 mod 10 = %s\n", zstr(a, buf));
    
    zfree(a);
    zfree(b);
    zfree(c);
    zfree(d);
    
    zunsetup();
    
    return 0;
}
