docker build -f Dockerfile -t sieve .
mkdir -p build
docker container run -v "./build:/sieve/build" sieve:latest
