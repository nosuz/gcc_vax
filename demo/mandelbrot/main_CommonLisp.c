/* Mandelbrot ASCII renderer using putc(char c) */

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

/* Map terminal size and view window as needed
https://codegolf.stackexchange.com/a/3735
*/

/* 固定小数点演算用の定数 */
#define FIXED_SHIFT 12              /* 12bit小数部 */
#define FIXED_ONE (1 << FIXED_SHIFT) /* 1.0 = 4096 */

/* 固定小数点の乗算: (a * b) >> FIXED_SHIFT */
int multiply_fixed(int a, int b) {
    return (a * b) >> FIXED_SHIFT;
}

/* 整数を固定小数点に変換 */
int int_to_fixed(int i) {
    return i << FIXED_SHIFT;
}

/* 固定小数点の平方根（abs計算用） */
int sqrt_fixed(int x) {
    if (x <= 0) return 0;

    int result = 0;
    int bit = 1 << 30;  /* 最上位ビットから開始 */

    while (bit > x) {
        bit >>= 2;
    }

    while (bit != 0) {
        if (x >= result + bit) {
            x -= result + bit;
            result = (result >> 1) + bit;
        } else {
            result >>= 1;
        }
        bit >>= 2;
    }

    return result;
}

/* Common Lisp版Mandelbrot集合の計算 */
int main(void) {
    /* ループの定数を固定小数点で計算 */
    /* y: -1 to 1 by 1/15 → -4096 to 4096 by 273 */
    /* x: -2 to 1 by 0.04 → -8192 to 4096 by 164 */
    int y_start = int_to_fixed(-1);   /* -1.0 */
    int y_end = int_to_fixed(1);      /*  1.0 */
    int y_step = FIXED_ONE / 15;      /*  1/15 ≈ 273 */

    int x_start = int_to_fixed(-2);   /* -2.0 */
    int x_end = int_to_fixed(1);      /*  1.0 */
    int x_step = (FIXED_ONE * 4) / 100; /* 0.04 ≈ 164 */

    int threshold = int_to_fixed(2);  /* abs threshold = 2.0 */

    /* (loop for y from -1 to 1 by 1/15 do */
    for (int y = y_start; y <= y_end; y += y_step) {

        /* (loop for x from -2 to 1 by .04 do */
        for (int x = x_start; x <= x_end; x += x_step) {

            /* (let*((c 126) (z (complex x y)) (a z)) */
            int c = 126;
            int z_real = x;    /* z = complex(x, y) */
            int z_imag = y;
            int a_real = x;    /* a = z */
            int a_imag = y;

            /* (loop while (< (abs (setq z (+ (* z z) a))) 2) */
            /*       while (> (decf c) 32)) */
            while (c > 32) {
                /* z = z * z + a */
                int z_real_new = multiply_fixed(z_real, z_real) - multiply_fixed(z_imag, z_imag) + a_real;
                int z_imag_new = 2 * multiply_fixed(z_real, z_imag) + a_imag;

                z_real = z_real_new;
                z_imag = z_imag_new;

                /* abs(z) = sqrt(z_real^2 + z_imag^2) */
                int z_real_squared = multiply_fixed(z_real, z_real);
                int z_imag_squared = multiply_fixed(z_imag, z_imag);
                int abs_z_squared = z_real_squared + z_imag_squared;

                /* abs(z) < 2.0 の判定は abs(z)^2 < 4.0 で代用 */
                if (abs_z_squared >= multiply_fixed(threshold, threshold)) {
                    break;
                }

                c--;
            }

            /* (princ (code-char c)) */
            putc((char)c);
        }

        /* (terpri) */
        puts("\n");
    }

    return 0;
}
