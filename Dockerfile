FROM ubuntu:20.04

# Install required packages
ENV DEBIAN_FRONTEND=noninteractive
ENV TERM xterm


RUN apt-get update && \
    apt-get install -y \
    build-essential \
    nasm \
    xorriso \
    grub-pc-bin \
    qemu-system-x86 \
    && rm -rf /var/lib/apt/lists/*
	
# RUN apt-get install -y at-spi2-core
# RUN /usr/lib/at-spi2-core/at-spi-bus-launcher --launch-immediately


# Copy your kernel source code to the container
COPY . /usr/src/mykernel

# Set the working directory to your kernel source code
WORKDIR /usr/src/mykernel

# Build your kernel
RUN make fclean
RUN make iso

# Set the command to run when the container starts
CMD ["qemu-system-i386", "-cdrom", "build/our_kfs.iso"]
# CMD while true; do sleep infinity; done

