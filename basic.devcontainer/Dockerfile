# syntax=docker/dockerfile:1.4
# enable here documents.
# RUN cat <<EOF >> /home/vscode/.bashrc
#
# EOF

FROM ubuntu:latest

ENV LANG=ja_JP.UTF-8
#ENV LC_ALL=ja_JP.UTF-8
#ENV LC_CTYPE=ja_JP.UTF-8

ARG USERNAME=vscode
ARG UID=1000
ARG GID=$UID

# Remove user if already exist and create new user.
RUN set -eux; \
    if getent passwd "${UID}" > /dev/null; then \
        echo "UID ${UID} already exists. Deleting..."; \
        userdel -f $(getent passwd "${UID}" | cut -d: -f1) || true; \
    fi; \
    if getent group "${GID}" > /dev/null; then \
        echo "GID ${GID} already exists. Deleting..."; \
        groupdel $(getent group "${GID}" | cut -d: -f1) || true; \
    fi; \
    groupadd --gid "${GID}" "${USERNAME}"; \
    useradd --uid "${UID}" --gid "${GID}" -s /bin/bash -m "${USERNAME}"

# enable sudo command
# RUN apt-get update \
#     && apt-get install -y sudo \
#     && apt-get clean \
#     && rm -rf /var/lib/apt-get/lists/* \
#     && echo $USERNAME ALL=\(root\) NOPASSWD:ALL > /etc/sudoers.d/$USERNAME \
#     && chmod 0440 /etc/sudoers.d/$USERNAME

# install packages
ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update \
    && apt-get install --no-install-recommends -y \
    # ssh is required to handle GitHub in the container
    git ssh \
    && apt-get clean \
    && rm -rf /var/lib/apt-get/lists/*

# Default user
USER vscode
