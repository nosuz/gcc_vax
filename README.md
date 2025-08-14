# GCC C compiler for VAX-11

VAX-11用のGCC C compilerのDev Containerです。

ただし`libc`などの標準ライブラリがないため、`-nostdlib`オプションが必須です。

## Demos

サンプルプログラムが`demo`ディレクトリーにあります。

```bash
cd demo
make
vax780 demo.ini

# expected output
VAX780 simulator V3.8-1
Logging to file "demo.log"
Hello
Hello from VAX-11 bare-metal!

HALT instruction, PC: 00001026 (BRB 1025)
sim> [Ctrl-C]
```

### compile example

```bash
vax-unknown-netbsdelf-gcc -nostdlib -Ttext=0x1000 test/test.c
vax-unknown-netbsdelf-objdump -d a.out  > test/test.s
```

## Git

editor が設定されていないため、コマンドラインから`git commit --amend`など編集が必要な操作ができません。そこで、`.git/config`に`editor`の設定を加えます。

```
[core]
 editor = code --wait
```

ローカルの`~/.gitconfig`に設定がある場合は、デフォルト設定ではこのファイルがコピーされるのでコンテナ毎の設定は不要です。
