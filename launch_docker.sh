#!/bin/bash

xhost +local:docker

docker build -t my_kernel_image . 
docker run -it --rm -v /tmp/.X11-unix:/tmp/.X11-unix -e DISPLAY=$DISPLAY my_kernel_image