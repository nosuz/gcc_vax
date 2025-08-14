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
        putc(*p);
        p++;
    }

    /* Add newline */
    putc('\n');
    return 1;
}

void main(void) {
    putc('H');
    putc('e');
    putc('l');
    putc('l');
    putc('o');
    putc('\r');
    putc('\n');

    puts("Hello from VAX-11 bare-metal!\n");

    /* 無限ループで停止 */
    // for (;;);
}
