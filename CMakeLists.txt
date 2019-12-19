cmake_minimum_required(VERSION 3.9)
project(bmsty_aia_dz2_master)

set(CMAKE_CXX_STANDARD 11)

add_executable(bmsty_aia_dz2_master
        dz-2.cpp
        Game.cpp
        Grid.cpp
        Grid.h
        Tile.cpp
        Tile.h)
