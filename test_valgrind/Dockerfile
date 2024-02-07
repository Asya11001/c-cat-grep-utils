FROM quay.io/school21/alpine:3.16

RUN apk --no-cache --upgrade \
    add \
    git \
    git-lfs \
    curl \
    jq \
    bash \
    build-base \
    python3 \
    valgrind \
    cppcheck \
    alpine-sdk \
    pcre-dev \
    clang-extra-tools

COPY . /project

WORKDIR "/project"

# Keep the container running
#CMD ["tail", "-f", "/dev/null"]
ENTRYPOINT ["/bin/bash", "tests/test_grep/test_4_valgrind.sh"]