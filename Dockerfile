FROM ubuntu:18.04
RUN apt-get update \
	&& apt-get install -y build-essential \
	&& apt-get install -y g++ \
	&& apt-get install -y libboost-all-dev \
	&& apt-get install -y libjsoncpp-dev \
	&& apt-get install -y libcurl4-gnutls-dev \
	&& apt-get install -y libssl-dev
WORKDIR /Source

