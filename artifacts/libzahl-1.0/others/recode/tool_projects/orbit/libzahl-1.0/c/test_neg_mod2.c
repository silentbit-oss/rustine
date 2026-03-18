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
    
    // Test zmodpow: (-3)^5 % 13
    zseti(b, -3);
    zseti(c, 5);
    zseti(d, 13);
    
    zmodpow(a, b, c, d);
    
    printf("(-3)^5 mod 13 = %s\n", zstr(a, buf));
    
    // Test zmodpowu: (-3)^5 % 13
    zseti(b, -3);
    zseti(d, 13);
    
    zmodpowu(a, b, 5, d);
    
    printf("(-3)^5 mod 13 (zmodpowu) = %s\n", zstr(a, buf));
    
    zfree(a);
    zfree(b);
    zfree(c);
    zfree(d);
    
    zunsetup();
    
    return 0;
}
