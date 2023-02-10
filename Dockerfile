FROM debian:buster

COPY . /KFS


RUN apt-get update\
	&& apt-get install build-essential -y \
	&& apt-get install clang -y \
	&& apt-get install gcc -y \
	&& apt-get install sudo -y \
	&& apt-get install make -y \
	&& apt-get install valgrind -y \
	&& apt-get install vim -y \
	&& apt-get install bison -y \
	&& apt-get install flex -y \
	&& apt-get install libgmp3-dev -y \
	&& apt-get install libmpc-dev -y \
	&& apt-get install libmpfr-dev -y \
	&& apt-get install texinfo -y \
	&& apt-get install nasm -y \
	&& apt-get install qemu-system-i386 -y

RUN docker pull joshwyant/gcc-cross
# To keep the container running:
CMD while true; do sleep infinity; done