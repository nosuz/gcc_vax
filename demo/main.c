/* hello_nostdlib.c */
typedef unsigned int uint32_t;

/* 出力先アドレスは仮の値（エミュレータやハード依存） */
#define UART_BASE   0x20000000
volatile char *const UART_TX = (volatile char *)UART_BASE;

/* 文字送信 */
static void putch(char c) {
    *UART_TX = c;
}

/* 文字列送信 */
static int puts(const char *s) {
    while (*s) {
        putch(*s++);
    }

    return 0;
}

void main(void) {
    puts("Hello from VAX-11 bare-metal!\n");

    /* 無限ループで停止 */
    // for (;;);
}
