FROM ubuntu:latest

RUN apt-get update \
    && apt-get install -y git \
    && apt-get clean \
    && rm -rf /var/lib/apt-get/lists/*

ARG USERNAME=vscode
ARG UID=10000
ARG GID=$UID

# Create new user or rename username if already exist.
RUN set -eux; \
    # modify group
    if getent group "${GID}" > /dev/null; then \
        EXISTING_GROUP=$(getent group "${GID}" | cut -d: -f1); \
        echo "GID ${GID} already exists as group '${EXISTING_GROUP}'"; \
    else \
        groupadd --gid "${GID}" "${USERNAME}"; \
    fi; \
    \
    # modify uid
    if getent passwd "${UID}" > /dev/null; then \
        EXISTING_USER=$(getent passwd "${UID}" | cut -d: -f1); \
        echo "UID ${UID} already exists as user '${EXISTING_USER}'"; \
        usermod -l "${USERNAME}" -d /home/${USERNAME} -m "${EXISTING_USER}"; \
        groupmod -n "${USERNAME}" $(id -gn "${USERNAME}"); \
    else \
        useradd --uid "${UID}" --gid "${GID}" -m "${USERNAME}"; \
    fi

# RUN apt-get update \
#     && apt-get install -y sudo \
#     && rm -rf /var/lib/apt-get/lists/* \
#     && echo $USERNAME ALL=\(root\) NOPASSWD:ALL > /etc/sudoers.d/$USERNAME \
#     && chmod 0440 /etc/sudoers.d/$USERNAME

# Default user
USER vscode
