cmake_minimum_required(VERSION 3.7)
project(OpenQR)
set(CMAKE_CXX_STANDARD 11)

#file(GLOB_RECURSE rw_module_source_list . "*.cpp" "*.c" "*.h" "*.hpp" "*.inl")
#aux_source_directory(. rw_module_source_list)
set(rw_module_source_list
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
        Matrix.hpp FFTCore.h FFTCore.cpp
        DataEncoder.cpp DataEncoder.h Examples.cpp Examples.h
        poly.hpp QRCode.cpp QRCode.h rs.hpp gf.hpp)

add_executable(OpenQR ${rw_module_source_list})