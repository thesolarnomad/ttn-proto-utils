#!/usr/bin/env bash
set -eu

echo "--> Pulling docker images"
docker pull wala/platformio-node-proto

echo "--> Generating arduino lib files from proto"
./gen-c.sh \
    `pwd`/example/proto/test.proto \
    `pwd`/example/arduino/lib/proto

echo "--> Building arduino project"
docker \
    run -it \
    -v `pwd`:`pwd` \
    -w `pwd` \
    wala/platformio-node-proto \
        platformio run -d `pwd`/example/arduino

echo "--> Generating TTN console files"
yarn ttn-proto-generator -- \
  -p example/proto/test.proto \
  -m com.example.MyMessage \
  -o example/ttn-console