cmake_minimum_required(VERSION 3.14)
project(binf)

set(CMAKE_CXX_STANDARD 17)

add_library(binflib
  src/algorithms/bitap.cpp
  src/io/fastq/FastqEntry.cpp
  src/io/fastq/FastqFile.cpp
  src/os/path.cpp include/binf/os/path.h)
target_include_directories(binflib PRIVATE
  include
  lib/zstr/src)

add_executable(fastq
  src/fastq.cpp)
target_include_directories(fastq PRIVATE
  include)
target_link_libraries(fastq
  binflib)

#add_executable(binf
#  src/main.cpp)
#target_include_directories(binf PRIVATE
#  include)
#target_link_libraries(binf
#  binflib)
