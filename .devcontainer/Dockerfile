FROM ubuntu:latest

RUN apt-get update \
    && apt-get install -y git \
    && apt-get clean \
    && rm -rf /var/lib/apt-get/lists/*

# Create the user
# ARG USERNAME=vscode
# ARG USER_UID=10000
# ARG USER_GID=$USER_UID

# RUN groupadd --gid $USER_GID $USERNAME \
#     && useradd --uid $USER_UID --gid $USER_GID -m $USERNAME

# RUN apt-get update \
#     && apt-get install -y sudo \
#     && rm -rf /var/lib/apt-get/lists/* \
#     && echo $USERNAME ALL=\(root\) NOPASSWD:ALL > /etc/sudoers.d/$USERNAME \
#     && chmod 0440 /etc/sudoers.d/$USERNAME

# Default UID 1000 user
USER ubuntu
