#!/bin/sh

set -x

gcc -Wall -Werror -Wextra -o bin/main src/main.c
bin/main
ppmtojpeg output.ppm > output.jpeg
mpv output.jpeg

