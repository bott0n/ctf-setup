#!/bin/bash

check_name=`docker ps -a | grep pwn_docker2304`

if [[ -z $check_name ]]; then
    echo "==> Creating a new container!"
    sudo docker run -v "$(pwd):/ctf" --cap-add=SYS_PTRACE --security-opt seccomp=unconfined --privileged --entrypoint /bin/bash -it --rm --name=pwn_docker2304 pwn_docker2304
else
    echo "==> Container already Exist!"
    echo "==> Entry now!"
    sudo docker exec -it pwn_docker2304 /bin/tmux
fi
