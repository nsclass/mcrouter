#!/usr/bin/env bash
# Copyright (c) Meta Platforms, Inc. and affiliates.
#
# This source code is licensed under the MIT license found in the
# LICENSE file in the root directory of this source tree.

set -ex

BASE_DIR="$1"
TARGET="${2:-all}"

[ -n "$BASE_DIR" ] || ( echo "Base dir missing"; exit 1 )

sudo apt-get update

sudo apt-get install -y \
    autoconf \
    binutils-dev \
    bison \
    cmake \
    flex \
    g++ \
    gcc \
    git \
    libboost1.83-all-dev \
    libbz2-dev \
    libdouble-conversion-dev \
    libevent-dev \
    libgflags-dev \
    libgoogle-glog-dev \
    libgmock-dev \
    libgtest-dev \
    libjemalloc-dev \
    liblz4-dev \
    liblzma-dev \
    liblzma5 \
    libsnappy-dev \
    libsodium-dev \
    libssl-dev \
    libtool \
    libunwind8-dev \
    libxxhash-dev \
    libzstd-dev \
    make \
    ninja-build \
    pkg-config \
    python3-dev \
    ragel \
    sudo

cd "$(dirname "$0")" || ( echo "cd fail"; exit 1 )

./get_and_build_by_make.sh "Makefile_ubuntu-24.04" "$TARGET" "$BASE_DIR"
