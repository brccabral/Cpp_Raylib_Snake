#!/bin/bash

source $EMSDK/emsdk_env.sh

emcc -o snake.html main.cpp -Os -Wall $RAYLIB_INSTALL_PATH/lib/libraylib.a -I. -I$RAYLIB_INSTALL_PATH/include -L. -L$RAYLIB_INSTALL_PATH/lib -s USE_GLFW=3 -s ASYNCIFY --shell-file $RAYLIB_SRC_PATH/shell.html -DPLATFORM_WEB

# python -m http.server 8080
