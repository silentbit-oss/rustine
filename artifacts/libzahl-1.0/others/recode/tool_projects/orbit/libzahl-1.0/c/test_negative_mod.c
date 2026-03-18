/* Quick test for negative modulus behavior */
#include "zahl.h"
#include <stdio.h>
#include <setjmp.h>

int main() {
    jmp_buf jmp;
    if (setjmp(jmp)) {
        printf("Error occurred\n");
        return 1;
    }
    zsetup(jmp);

    z_t a, b, c;
    zinit(a); zinit(b); zinit(c);

    zseti(b, 7);
    zseti(c, -10);

    zmodsqr(a, b, c);

    char result[100];
    zstr(a, result);
    printf("Result of (7*7) %% -10 = %s\n", result);

    zfree(a); zfree(b); zfree(c);
    zunsetup();
    return 0;
}
