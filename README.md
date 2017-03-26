# TTN Utilities for protobuf

[![Build Status](https://travis-ci.org/thesolarnomad/ttn-proto-utils.svg?branch=master)](https://travis-ci.org/thesolarnomad/ttn-proto-utils)

Toolbox for using protobuf-defined messages with The Things Network.
This repository contains examples about how to use a message defined in the [protobuf format](https://github.com/google/protobuf) with an arduino sketch via [nanopb](https://jpa.kapsi.fi/nanopb/).
It leverages [a docker file that comes with all necessary tools](https://hub.docker.com/r/wala/platformio-sodaqsamd-node/) installed and the [ttn-proto-generator](https://github.com/thesolarnomad/ttn-proto-generator) that can take a proto file and generate a `Converter`, `Decoder`, `Encoder` and `Validator` for The Things Network Console via [protobuf.js](https://github.com/dcodeIO/protobuf.js).

## How? What?

Install [Docker](https://www.docker.com/) - on Mac you can just run `brew bundle` in the root of a checkout of this project and then run

```bash
./example.sh
```

to end up with a buildable Arduino project with a sample usage of `example/proto/test.proto` in `example/arduino` and the TTN console functions in `example/ttn-console`.

## Generate Arduino-compatible definition files
Run:

```bash
./gen-c.sh \
    `pwd`/path/to/your.proto \
    `pwd`/path/to/your/arduino/project
```

The headers, etc. will be generated in `/path/to/your/arduino/project`.
_Please note the absolute paths_

## Generate TTN console functions
Run:

```bash
yarn global ttn-proto-generator
ttn-proto-generator \
  -p example/proto/test.proto \
  -m com.example.MyMessage \
  -o example/ttn-console
```
to generate the TTN functions in `example/ttn-console`.

Head over to https://github.com/thesolarnomad/ttn-proto-generator for details.