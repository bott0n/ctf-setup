# OS version
FROM ubuntu:23.04

ENV DEBIAN_FRONTEND=noninteractive
ENV LANG en_US.UTF-8  
ENV LANGUAGE en_US:en  
ENV LC_ALL en_US.UTF-8  

RUN apt-get update -y
RUN apt-get install -y binutils file
RUN apt-get install -y sudo locales python3 python3-pip python3-dev git gcc gcc-multilib gdb vim ruby gem tmux wget nmap xinetd socat 

RUN python3 -m pip install -U pip  --break-system-packages
RUN python3 -m pip install --no-cache-dir  --break-system-packages\
    ropgadget \
    pwntools==4.8.0 \
    z3-solver \
    ropper \
    unicorn \
    keystone-engine \
    capstone \
    angr 

# Install one_gadget
RUN gem install one_gadget 

# Install gef
RUN wget -O ~/.gdbinit-gef.py -q http://gef.blah.cat/py
RUN echo source ~/.gdbinit-gef.py >> ~/.gdbinit

RUN sed -i '/en_US.UTF-8/s/^# //g' /etc/locale.gen && \
    locale-gen

RUN mkdir -p /ctf

ENTRYPOINT ["/bin/bash"]
