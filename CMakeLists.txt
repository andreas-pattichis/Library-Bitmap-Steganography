cmake_minimum_required(VERSION 3.17)
project(Homework4 C)

set(CMAKE_C_STANDARD 99)

add_executable(Homework4  Waterproof.c bmp.h bmp.c stringToImage.c grayscale.h grayscale.c encodeStegano.c encodeStegano.h decodeStegano.c decodeStegano.h encodeText.c encodeText.h decodeText.c decodeText.h stringToImage.h imageToString.h imageToString.c)