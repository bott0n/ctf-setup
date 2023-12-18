#!/bin/bash

check_name=`docker ps -a | grep ctf2204`

if [[ -z $check_name ]]; then
    echo "==> Creating a new container!"
    sudo docker run -v $(pwd):/ctf --cap-add=SYS_PTRACE --security-opt seccomp=unconfined --privileged --entrypoint /bin/bash -it --rm --name=ctf2204 ctf:22.04 
else
    echo "==> Container already Exist!"
    echo "==> Entry now!"
    sudo docker exec -it ctf2204 /bin/tmux
fi
