FROM quay.io/school21/alpine:3.16

RUN apk --no-cache --upgrade add \
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

RUN mkdir /test 

COPY . /project
COPY materials_tests/build/scripts /project/ci-scripts
COPY materials_tests/build/grep /project/grep
COPY materials_tests/build/scripts /project/tests
COPY materials_tests/linters /project/tests/linters
COPY ../../src/grep/s21_grep.c /project/tests

WORKDIR "/project"

ENTRYPOINT ["/bin/bash","grep/test_dir/test_grep/test_4_valgrind.sh"]
