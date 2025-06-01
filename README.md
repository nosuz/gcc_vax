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
3. VSCode を起動してこのディレクトリを開き、のコマンドパレット(Ctrl + Shift + P)で Dev Containers: Rebuild container を実行すると、コンテナイメージが作成されて接続されます。

### When the UID is not 1000

このコンテナは、UID が 1000、GID が 1000 のユーザでの実行を想定しています。

UID と GID のいずれか、または両方が異なる場合は、UID と GID を`.devcontainer/.env`に設定してください。UID と GID は、`id`コマンドで確認できます。

```
UID=1001
GID=1001
```

また、`.devcontainer/generate_env.sh`または`.devcontainer/generate_env.py`を実行することで、`.env`を作成することができます。

_UID (GID)の変更対応については、[Docker や VSCode + Remote-Container のパーミッション問題に立ち向かう](https://zenn.dev/forrep/articles/8c0304ad420c8e)を参考にしました。_

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

editor が設定されていないため、コマンドラインから`git commit --amend`など編集が必要な操作ができません。そこで、`.bit/config`に`editor`の設定を加えます。

```
[core]
	editor = code --wait
```

### GitHub access

GitHub は、特別な設定無く使用できると思います。次のコマンドで GitHub への接続を確認できます。

```
$ ssh -T git@github.com
Hi nosuz! You've successfully authenticated, but GitHub does not provide shell access.
```
