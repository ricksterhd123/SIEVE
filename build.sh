docker build -f Dockerfile -t sieve .
mkdir -p build
docker container run -v "./build:/sieve/build" sieve:latest
clear
docker container run -v "$PWD/build":/usr/src/app -w /usr/src/app node:latest node SIEVE.js
