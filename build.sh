docker build -f Dockerfile -t sieve .
mkdir -p build
docker container run -it -v "./build:/sieve/build" sieve:latest
clear
docker container run -it -v "$PWD/build":/usr/src/app -w /usr/src/app node:latest node SIEVE.js
