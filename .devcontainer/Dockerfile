# syntax=docker/dockerfile:1.4
# enable here documents.
# RUN cat <<EOF >> /home/vscode/.bashrc
#
# EOF

FROM ubuntu:latest

# Set locale and timezone
ENV LANG=ja_JP.UTF-8
ENV LC_ALL=ja_JP.UTF-8
ENV LC_CTYPE=ja_JP.UTF-8
ENV TZ=Asia/Tokyo

ARG USERNAME=vscode
ARG UID=10000
ARG GID=$UID

# Setup user and group id
# Remove all general users and create a new user for USER direction.
RUN set -eux; \
    for i in $(awk -F: '$3 >= 1000 && $3 <= 60000 { print $1 }' /etc/passwd); do \
        userdel $i; \
    done; \
    for i in $(awk -F: '$3 >= 1000 && $3 <= 60000 { print $1 }' /etc/passwd); do \
        groupdel $i; \
    done; \
    groupadd --gid "${GID}" "${USERNAME}"; \
    useradd --uid "${UID}" --gid "${GID}" -s /bin/bash -m "${USERNAME}"

# Enable sudo
# RUN apt-get update \
#     && apt-get install -y sudo \
#     && apt-get clean \
#     && rm -rf /var/lib/apt-get/lists/* \
#     && echo $USERNAME ALL=\(root\) NOPASSWD:ALL > /etc/sudoers.d/$USERNAME \
#     && chmod 0440 /etc/sudoers.d/$USERNAME

# Install packages
ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update \
    && apt-get install --no-install-recommends -y \
    # Basic tools
    # ssh is required to handle GitHub in the container
    git ssh \
    # System tools
    locales tzdata \
    # Clean up
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/* \
    # Configure locale
    && locale-gen ja_JP.UTF-8 \
    && update-locale LANG=ja_JP.UTF-8 \
    # Configure timezone
    && ln -fs /usr/share/zoneinfo/Asia/Tokyo /etc/localtime \
    && dpkg-reconfigure -f noninteractive tzdata

# Default user
USER vscode
