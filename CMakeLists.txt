cmake_minimum_required(VERSION 3.22)
project(othello)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20")
file(GLOB GAME_SRC "src/*")

include_directories(./dxlib)
link_directories(./dxlib)

add_executable(othello ${GAME_SRC}
        src/main.cpp
        src/board.cpp
        src/board.h
        src/stone.cpp
        src/stone.h
        src/input_manager.cpp
        src/game.cpp
        src/game.h
        src/othello.cpp
        src/othello.h
        src/othello_ai.cpp
        src/othello_ai.h
        src/othello_player.cpp
        src/othello_player.h
        src/stone_type.h
        src/title.cpp
        src/title.h
        src/highlightable_text.cpp
        src/highlightable_text.h
)

add_custom_command(
        TARGET othello POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${PROJECT_SOURCE_DIR}/resources"
        "${PROJECT_BINARY_DIR}/resources"
        COMMENT "Copying over resource files to build"
)

target_link_libraries(
        othello
        DxLib
        DxUseCLib
        DxDrawFunc
        jpeg
        png
        zlib
        tiff
        theora_static
        vorbis_static
        vorbisfile_static
        ogg_static
        bulletdynamics
        bulletcollision
        bulletmath
        opusfile
        opus
        silk_common
        celt
)