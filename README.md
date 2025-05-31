# Boilertemplate for VSCode Dev Container

VSCodeのでdev containerを使用するための雛形です。

このレポジトリをコピーして、VSCodeのコマンドパレット(Ctrl + Shift + P)でDev Containers: Rebuild containerを実行すると、コンテナイメージが作成されて接続されます。

```
git clone https://github.com/nosuz/dev_container.git
cd dev_container
rm -r .git
git init
git -m main # if needed

code .
# Edit .devcontainer/Dockerfile to install required APT packages before rebuilding this container.
```

### When the UID is not 1000

このコンテナは、UID 1000のユーザでの実行を想定しています。そのためUIDが1000以外のユーザが実行した場合は、コンテナのworkspaceをプロジェクト・ディレクトリにbind mountするためownershipの問題を生じます。

その場合には、`.devcontainer/Dockerfile`を編集して実行するユーザと同じUIDのユーザを作成します。また、`.devcontainer/devcontainer.json`で作成したユーザ名を指定します。

```
# Dockerfile
ARG USERNAME=<NEW_USER_NAME>
ARG USER_UID=<YOUR_UID>
ARG USER_GID=$USER_UID

RUN groupadd --gid $USER_GID $USERNAME \
    && useradd --uid $USER_UID --gid $USER_GID -m $USERNAME

```

```
// devcontainer.json
{
  "remoteUser": "<NEW_USER_NAME>"
}
```

#### more smart way

設定ファイルを書き換えなくて済むようなスマートな方法があるような気がしますが、これまで見つけられていません。

## VSCode settings and extensions

Dev containerでは、VSCodeの設定と機能拡張がリセットされます。そこで、必要な設定と機能拡張を`.devcontainer/devcontainer.json`の`customizations`に記載します。

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

editorが設定されていないため、コマンドラインから`git commit --amend`など編集が必要な操作ができません。そこで、`.bit/config`に`editor`の設定を加えます。

```
[core]
	editor = code --wait
```

### GitHub access

GitHubは、特別な設定無く使用できると思います。次のコマンドでGitHubへの接続を確認できます。

```
$ ssh -T git@github.com
Hi nosuz! You've successfully authenticated, but GitHub does not provide shell access.
```
