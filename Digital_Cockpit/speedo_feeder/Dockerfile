FROM ubuntu:24.04


RUN apt update &&\
    apt install build-essential software-properties-common -y &&\
    add-apt-repository ppa:lely/ppa -y &&\
    apt update &&\
    apt install make net-tools iproute2 can-utils liblely-coapp-dev liblely-co-tools libncurses5-dev libncursesw5-dev ncurses-term -y

# ADD /scripting/speed_feeder.sh .
ADD . /speed_feeder

WORKDIR /speed_feeder
RUN chmod +x /speed_feeder/scripting/speed_feeder.sh

ENV TERM=xterm


ENTRYPOINT [ "sh", "/speed_feeder/scripting/speed_feeder.sh" ]