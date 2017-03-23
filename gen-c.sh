#!/usr/bin/env bash
set -eu

function main() {
    local protofile="$1"
    local outdir="$2"
    local dir
    dir=$(dirname "${protofile}")

    docker run \
        -it \
        -v `pwd`:`pwd` \
        -w `pwd` \
        wala/platformio-sodaqsamd-node \
            protoc \
                --plugin=protoc-gen-nanopb=/nanopb/generator/protoc-gen-nanopb \
                --nanopb_out="${outdir}" \
                -I /nanopb/generator/proto/ \
                -I "${dir}" \
                "${protofile}"
}

main "$@"