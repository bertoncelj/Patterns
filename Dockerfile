FROM ubuntu:22.04 as base

ARG ARM_ARCH=x86_64
ARG TOOLS_PATH=/opt/gcc-arm-none-eabi
ARG ARM_VERSION=12.3.rel1
ARG CMAKE_VERSION=3.26.0-rc6


RUN echo "I am running on potatoe"

# Update ubuntu 
RUN apt-get update
RUN apt-get install -y --no-install-recommends apt-utils
RUN apt-get -y upgrade

# Install 
RUN apt-get install -y 
RUN apt-get install -y nano sudo ca-certificates git make
RUN apt-get install -y ninja-build
RUN apt-get install -y build-essential curl checkinstall zlib1g-dev libssl-dev
RUN apt-get install -y wget

RUN  wget -O cmake-${CMAKE_VERSION}.tar.gz https://github.com/Kitware/CMake/releases/download/v${CMAKE_VERSION}/cmake-${CMAKE_VERSION}.tar.gz \
  && ls -lat \
  && mkdir /opt/cmake \
  && tar -zxvf cmake-${CMAKE_VERSION}.tar.gz -C . \
  && ls -lat \
  && cd cmake-3.26.0-rc6 \
  && sudo ./bootstrap \
  # && cd /opt/cmake/cmake-${CMAKE_VERSION}-linux-x86_64 \
  # && cd /opt/cmake/ \
  # && cd cmake-3.26.0-rc6-linux-x86_64 \
  && ls -lat \
  && make \
  && sudo make install 


 RUN echo "Downloading ARM GNU GCC for Platform: $ARM_ARCH" \
	&& sudo mkdir ${TOOLS_PATH} \
	&& curl -Lo gcc-arm-none-eabi.tar.xz "https://developer.arm.com/-/media/Files/downloads/gnu/${ARM_VERSION}/binrel/arm-gnu-toolchain-${ARM_VERSION}-${ARM_ARCH}-arm-none-eabi.tar.xz" \
	&& sudo tar xf gcc-arm-none-eabi.tar.xz --strip-components=1 -C ${TOOLS_PATH} \
	&& sudo rm gcc-arm-none-eabi.tar.xz \
	&& sudo rm ${TOOLS_PATH}/*.txt \
	&& sudo rm -rf ${TOOLS_PATH}/share/doc \
	&& echo "https://developer.arm.com/-/media/Files/downloads/gnu/${ARM_VERSION}/binrel/arm-gnu-toolchain-${ARM_VERSION}-${ARM_ARCH}-arm-none-eabi.tar.xz"


# Get static analysis tools: clang-format clang-tidy, Lizard, cpplint
RUN apt-get install -y clang-format clang-tidy 
RUN	apt-get clean

# Set the working directory inside the container
WORKDIR /app
