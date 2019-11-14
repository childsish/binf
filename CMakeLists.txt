cmake_minimum_required(VERSION 3.14)
project(binf)

set(CMAKE_CXX_STANDARD 17)

add_library(zstr INTERFACE)
target_include_directories(zstr INTERFACE lib/zstr/src)
target_link_libraries(zstr INTERFACE
  z)

add_library(binf
  src/Interval.cpp include/binf/Interval.h
  src/algorithms/bitap.cpp
  src/io/fastq/FastqEntry.cpp
  src/io/fastq/FastqFile.cpp
  src/os/path.cpp include/binf/os/path.h)
target_include_directories(binf PRIVATE
  include)
target_link_libraries(binf
  zstr)

add_executable(fastq
  src/fastq.cpp)
target_include_directories(fastq PRIVATE
  include)
target_link_libraries(fastq
  binf)

add_executable(binf-bin
  src/binf.cpp)
target_include_directories(binf-bin PRIVATE
  include)
target_link_libraries(binf-bin
  binf)
set_target_properties(binf-bin PROPERTIES OUTPUT_NAME binf)
