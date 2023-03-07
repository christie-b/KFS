#!/bin/bash

# docker build -t kfs .
# docker run -d --rm --name kfs kfs
xhost +local:docker
export NO_AT_BRIDGE=1

docker build -t my_kernel_image . 
docker run -it --rm -v /tmp/.X11-unix:/tmp/.X11-unix -e DISPLAY=$DISPLAY my_kernel_image