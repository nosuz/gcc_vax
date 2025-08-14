/* putc function - outputs character and waits */
void putc(int c) {
    int txcs;

    /* while (!(TXCS & RDY)) {} */
    do {
        asm volatile ("mfpr $34, %0" : "=g" (txcs));  /* mfpr $34, %r0 */
    } while ((txcs & 0x80) == 0);                     /* bitb $0x80, %r0; beql 1b */

    asm volatile ("mtpr %0, $35" : : "g" (c));        /* mtpr %r0, $35 */
    /* ret */
}

/* puts() function - outputs null-terminated string */
int puts(const char *str) {
    if (!str) return -1;

    const char *p = str;
    while (*p) {
        if (*p == '\n') {
            putc('\r');  /* 先にCRを出力 */
            putc('\n');  /* 次にLFを出力 */
        } else {
            putc(*p);
        }
        p++;
    }

    return 1;
}

/* Mandelbrot ASCII renderer using putc(char c) */

/* Map terminal size and view window as needed
https://www.retrobrewcomputers.org/forum/index.php?t=msg&th=201&goto=4704&#msg_4704
*/
int main(void) {
    for (int Y = -12; Y <= 12; ++Y) {           /* 10 FOR Y=-12 TO 12 */
        for (int X = -39; X <= 39; ++X) {       /* 20 FOR X=-39 TO 39 */

            double CA = X * 0.0458;             /* 30 CA=X*0.0458  */
            double CB = Y * 0.08333;            /* 40 CB=Y*0.08333 */
            double A  = CA;                      /* 50 A=CA         */
            double B  = CB;                      /* 60 B=CB         */

            int escaped = 0;                     /* 収束しない=0（内部）/発散=1 */
            int I;
            for (I = 0; I <= 15; ++I) {          /* 70 FOR I=0 TO 15 */
                double T = A*A - B*B + CA;       /* 80 T=A*A-B*B+CA  */
                B = 2.0*A*B + CB;                /* 90 B=2*A*B+CB    */
                A = T;                            /* 100 A=T          */
                if (A*A + B*B > 4.0) {            /* 110 IF ... > 4 THEN GOTO 200 */
                    escaped = 1;
                    break;
                }
            }

            if (!escaped) {
                putc(' ');                        /* 130 PRINT " " */
            } else {
                int idx = I;                      /* 200 IF I>9 THEN I=I+7 */
                if (idx > 9) idx += 7;            /* 205 PRINT CHR$(48+I); */
                char ch = (char)(48 + idx);       /* 0..9,A..F に対応 */
                putc(ch);
            }
        }
        puts("\n");                               /* 220 PRINT */
    }
    return 0;                                     /* 230 NEXT Y */
}
