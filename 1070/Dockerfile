FROM ubuntu:20.04

# FROM ubuntu:latest

LABEL maintainer="tsheke_shele.johnny@uqam.ca"


EXPOSE 80 8080 443 4280
EXPOSE 22
# SuiteCRM sera accessible sur le port 4280
EXPOSE 8069 8071

ENV LANG=fr_CA.UTF-8  
ENV LANGUAGE=fr_CA:fr  
ENV LC_ALL=fr_CA.UTF-8


RUN apt-get update &&  apt-get install -y\
 sed locales dpkg \
 man manpages-fr apt-utils coreutils lsb-release

# Do not exclude man pages. Needed for the INF1070 course


RUN cp /etc/dpkg/dpkg.cfg.d/excludes \
      /etc/dpkg/dpkg.cfg.d/excludes.old && \
    sed -e 's/path-exclude/# path-exclude/' \
    /etc/dpkg/dpkg.cfg.d/excludes >\
    /etc/dpkg/dpkg.cfg.d/excludes.tmp && \
    mv /etc/dpkg/dpkg.cfg.d/excludes.tmp \
     /etc/dpkg/dpkg.cfg.d/excludes

# Set locale: french Canada

RUN sed -i -e 's/# fr_CA.UTF-8 UTF-8/fr_CA.UTF-8 UTF-8/' /etc/locale.gen && \
    locale-gen fr_CA && update-locale LANG=fr_CA
 

# reinstall man pages
# Install man pages in french -- required for UQAM students

RUN apt-get update && apt-get install --reinstall -y\
  man manpages-fr manpages-fr-extra manpages-fr-dev \
  manpages-posix coreutils

# Install fr language

RUN apt-get update && apt-get install --reinstall -y \
    language-pack-fr language-pack-fr-base

# default timezone
ENV DEBIAN_FRONTEND=noninteractive
RUN apt-get update &&  apt-get install -y\
    tzdata
ENV TZ=America/Montreal
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone
RUN dpkg-reconfigure --frontend noninteractive tzdata

# install vim et autre utilitaire

RUN apt-get update && apt-get install -y\
    vim vim-common unzip 

# create user 'admincrm' with the password 'INF1070pass'

RUN apt-get update && apt-get install -y\
    sudo openssl

RUN useradd -m -g adm -G sudo -d /home/admincrm -s /bin/bash -p `(echo "INF1070pass" |openssl passwd -1 -stdin)` admincrm
