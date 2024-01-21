FROM ubuntu:latest
SHELL ["/bin/bash", "-c"]

RUN apt update
RUN apt install -y build-essential cmake git curl wget
RUN git clone https://github.com/emscripten-core/emsdk.git
RUN wget https://gmplib.org/download/gmp/gmp-6.3.0.tar.xz
RUN tar -xf gmp-6.3.0.tar.xz

WORKDIR /nodejs
RUN curl -fsSL https://deb.nodesource.com/setup_21.x >> setup_21.sh
RUN bash setup_21.sh
RUN apt-get install -y nodejs

WORKDIR /emsdk
RUN ./emsdk install latest
RUN ./emsdk activate latest

WORKDIR /gmp-6.3.0
RUN source /emsdk/emsdk_env.sh && emconfigure ./configure --disable-assembly --host none --enable-cxx --prefix=${HOME}/opt
RUN make
RUN make install

WORKDIR /sieve
COPY SIEVE.cpp .
COPY CMakeLists.txt .

WORKDIR /sieve/build
ENTRYPOINT source /emsdk/emsdk_env.sh && emcmake cmake .. && emmake make
