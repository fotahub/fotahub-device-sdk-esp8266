#!/bin/bash
docker run --rm \
  -v $PWD/../../..:/workspace \
  -w /workspace/examples/huzzah/rollbackable \
  fotahub/esp8266-nonos-sdk:3.0.4-1 \
  make $@
