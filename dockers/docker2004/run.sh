#!/bin/bash

check_name=`docker ps -a | grep ctf2004`

if [[ -z $check_name ]]; then
    echo "==> Creating a new container!"
    sudo docker run -v $(pwd):/ctf --cap-add=SYS_PTRACE --security-opt seccomp=unconfined --privileged --entrypoint /bin/bash -it --rm --name=ctf2004 ctf:20.04 
else
    echo "==> Container already Exist!"
    echo "==> Entry now!"
    sudo docker exec -it ctf2004 /bin/tmux
fi