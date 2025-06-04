FROM ubuntu:latest

ARG USERNAME=vscode
ARG UID=10000
ARG GID=$UID

# Remove users and create new user before installing packages
# because new users may created by installing package.
RUN for i in $(awk -F: '$3 >= 1000 && $3 <= 60000 { print $1 }' /etc/passwd); \
    do userdel $i; done; \
    for i in $(awk -F: '$3 >= 1000 && $3 <= 60000 { print $1 }' /etc/passwd); \
    do groupdel $i; done; \
    groupadd --gid "${GID}" "${USERNAME}"; \
    useradd --uid "${UID}" --gid "${GID}" -s /bin/bash -m "${USERNAME}"

# install packages
ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update \
    && apt-get install --no-install-recommends -y \
    # ssh is required to handle GitHub in the container
    git ssh \
    && apt-get clean \
    && rm -rf /var/lib/apt-get/lists/*

# enable sudo command
# RUN apt-get update \
#     && apt-get install -y sudo \
#     && apt-get clean \
#     && rm -rf /var/lib/apt-get/lists/* \
#     && echo $USERNAME ALL=\(root\) NOPASSWD:ALL > /etc/sudoers.d/$USERNAME \
#     && chmod 0440 /etc/sudoers.d/$USERNAME

# Default user
USER vscode
