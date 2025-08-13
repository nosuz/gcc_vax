        .text
        .globl  _start
        .globl  main          # C 側の main を呼ぶなら

        .align  1
_start:
        # スタック初期化（リンカスクリプトで定義した _stack_top を使用）
        movab   _stack_top, %sp

        # BSS クリア
        movab   __bss_start, %r0
        movab   __bss_end,   %r1
1:      cmpl    %r0, %r1
        bgeq    2f
        clrb    (%r0)+
        brb     1b
2:
        # C の main() を呼ぶ（不要なら削除）
        calls   $0, main

halt:   halt
        brb     halt
