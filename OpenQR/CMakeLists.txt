cmake_minimum_required(VERSION 3.7)
project(OpenQR)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        Application.cpp
        BMPImageIO.hpp
        core.h
        IImageIn.hpp
        IImageIO.hpp
        IImageOut.hpp
        bmp.cpp
        bmp.h
        ImageIO.hpp
        SupFunction.h
        Matrix.hpp)

add_executable(OpenQR ${SOURCE_FILES})