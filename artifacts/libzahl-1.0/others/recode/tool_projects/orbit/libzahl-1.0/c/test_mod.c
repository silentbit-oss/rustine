#include "zahl.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    z_t a, b, c;
    jmp_buf env;
    
    if (setjmp(env)) {
        zperror(0);
        return 2;
    }
    
    zsetup(env);
    zinit(a), zinit(b), zinit(c);
    
    // Test -7 % 3
    zseti(a, -7);
    zseti(b, 3);
    zmod(c, a, b);
    
    char buf[100];
    printf("-7 %% 3 = %s\n", zstr(c, buf));
    printf("zsignum(c) = %d\n", zsignum(c));
    
    // Test 7 % -3
    zseti(a, 7);
    zseti(b, -3);
    zmod(c, a, b);
    printf("7 %% -3 = %s\n", zstr(c, buf));
    printf("zsignum(c) = %d\n", zsignum(c));
    
    zfree(a), zfree(b), zfree(c);
    zunsetup();
    return 0;
}
