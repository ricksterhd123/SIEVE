#!/usr/bin/env bash

set -e

mkdir -p build
docker buildx build -f Dockerfile --load -t sieve .
docker container run -v "./build:/sieve/build" sieve:latest
