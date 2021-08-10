#!/bin/bash
# Build and install on Unix based systems like macOS or Linux
echo -e "\033[32mBuilding BASM ...\033[0m";
./build.py build clean;
echo -e "\033[32mBuilding succesful\033[0m";
echo -e "\033[32mInstalling binary ...\033[0m";
mv bin/basm /usr/local/bin;
echo -e "\033[32mInstall succesful\033[0m";
