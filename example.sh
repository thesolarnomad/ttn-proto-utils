#!/usr/bin/env bash
set -eu

echo "--> Generating arduino lib files from proto"
./gen-c.sh \
    `pwd`/example/proto/test.proto \
    `pwd`/example/arduino/lib/proto

echo "--> Building arduino project"
docker \
    run -it \
    -v `pwd`:`pwd` \
    -w `pwd` \
    wala/platformio-sodaqsamd-node \
        platformio run -d `pwd`/example/arduino

docker \
    run -it \
    -v `pwd`:`pwd` \
    -w `pwd` \
    golang:latest \
    go get -v github.com/robertkrimen/otto/otto