# Use Ubuntu 20.04
FROM ubuntu:22.04

ENV DEBIAN_FRONTEND=noninteractive

# system
RUN apt update -y && \
    apt install -y git gcc g++ cmake  \
    libjsoncpp-dev uuid-dev openssl libssl-dev zlib1g-dev curl zip unzip  \
    tar pkg-config bison libx11-dev libxft-dev libxext-dev libboost-all-dev \
    libdbus-1-dev libxtst-dev libxrandr-dev autoconf-archive libxcursor-dev \
    libxdamage-dev libxinerama-dev

RUN git clone https://github.com/an-tao/drogon && \
  cd drogon && \
  git submodule update --init && \
  mkdir build && \
  cd build && \
  cmake .. && \
  make && make install

RUN rm -r drogon

#vcpkg
RUN git clone https://github.com/Microsoft/vcpkg.git

RUN ./vcpkg/bootstrap-vcpkg.sh

COPY . /lvif

WORKDIR /lvif

RUN cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_TOOLCHAIN_FILE=/vcpkg/scripts/buildsystems/vcpkg.cmake -S . -B build/ && \
    cd build/ && make

#port to expose
EXPOSE 3005

#command
CMD ["./build/lvif"]