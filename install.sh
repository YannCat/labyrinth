#!/bin/bash

mkdir /usr/local/lib/fmod
cp lib-ext/fmodstudioapi11004linux/api/lowlevel/lib/x86_64/* /usr/local/lib/fmod
mkdir /usr/local/include/fmod
cp lib-ext/fmodstudioapi11004linux/api/lowlevel/inc/* /usr/local/include/fmod
echo  "LD_LIBRARY_PATH=\"/usr/local/lib/fmod\"" >> /etc/environment
echo  "LD_LIBRARY_PATH=\"/usr/local/lib/fmod\"" >> ~/.bashrc
source ~/.bashrc
