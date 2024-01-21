docker buildx build -f Dockerfile --load -t sieve .
mkdir -p build
docker container run -v "./build:/sieve/build" sieve:latest
