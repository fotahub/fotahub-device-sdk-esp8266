@echo off
docker run --rm ^
  -v %~dp0..\..\..:/workspace ^
  -w /workspace/examples/huzzah/thingshadow ^
  fotahub/esp8266-nonos-sdk:3.0.4-1 ^
  make %* HOST=Windows
