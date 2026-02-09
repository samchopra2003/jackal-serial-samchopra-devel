#!/bin/bash

#xhost +
docker run -it --rm \
    --network=host \
    --ipc=host \
    --privileged \
    --entrypoint="" \
    -v "/dev:/dev" \
    -v "/tmp/.X11-unix:/tmp/.X11-unix" \
    -e DISPLAY=$DISPLAY \
    -e QT_X11_NO_MITSHM=1 \
    -e XAUTHORITY=$XAUTH \
    -e RMW_IMPLEMENTATION=rmw_fastrtps_cpp \
    --group-add=$(getent group input | cut -d: -f3) \
    --name dcist-jackal-`hostname`-base-service \
    dcist-jackal-`hostname`:service \
    bash
#xhost -
