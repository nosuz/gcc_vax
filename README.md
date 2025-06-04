# Boilerplate for VSCode Dev Container

VSCode の dev container を使用するための雛形です。

### pre-required packages

```
sudo apt install docker.io docker-buildx docker-compose-v2
```

### clone boilerplate files

1. このレポジトリを次のコマンドでクローンしてください。

```
git clone https://github.com/nosuz/dev_container.git
cd dev_container
rm -r .git
git init
git -m main # if needed

code .
# Edit .devcontainer/Dockerfile to install required APT packages before rebuilding this container.
```

2. 必要なパッケージをインストールするように Dockerfile を編集してください。
3. このディレクトリを VSCode で開き、コマンドパレット(Ctrl + Shift + P)で Dev Containers: Rebuild container を実行すると、コンテナイメージが作成されて接続されます。

### user name and id

このコンテナは、コンテナを開いたユーザと同じIDで実行されます。そのため権限の問題なしにディレクトリを共有できます。ただしコンテナ内のユーザ名は、`vscode`となり、`ls -l`で共有ディレクトリを見るとユーザ名が元と変わって`vscode`になります。

また、`.devcontainer/devcontainer.json`の`remoteUser`で`root`を指定した場合には、root権限で実行されます。

## VSCode settings and extensions

Dev container では、VSCode の設定と機能拡張がリセットされます。そこで、必要な設定と機能拡張を`.devcontainer/devcontainer.json`の`customizations`に記載します。

```
// devcontainer.json
{
  "customizations": {
    "vscode": {
      "settings": {},
      "extensions": ["mhutchie.git-graph", "streetsidesoftware.code-spell-checker"]
    }
  }
}
```

初期設定では、[Code Spell Checker](https://marketplace.visualstudio.com/items?itemName=streetsidesoftware.code-spell-checker)と[Git Graph](https://marketplace.visualstudio.com/items?itemName=mhutchie.git-graph)がインストールされます。

## Git

editor が設定されていないため、コマンドラインから`git commit --amend`など編集が必要な操作ができません。そこで、`.git/config`に`editor`の設定を加えます。

```
[core]
	editor = code --wait
```

ローカルの`~/.gitconfig`に設定がある場合は、デフォルト設定ではこのファイルがコピーされるのでコンテナ毎の設定は不要です。

### GitHub access

GitHub は、`ssh`パッケージをインストールしてあれば他に特別な設定無く使用できると思います。次のコマンドで GitHub への接続を確認できます。

```
$ ssh -T git@github.com
Hi nosuz! You've successfully authenticated, but GitHub does not provide shell access.
```

## Docker Images

古いイメージは、次のコマンドで一括削除できます。

```bash
for i in $(docker image ls | awk '$1 == "<none>" && $2 == "<none>" { print $3 }'); do echo $i; docker image rm $i; done
```
