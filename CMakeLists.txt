cmake_minimum_required(VERSION 2.8)
project(DataFormatsTest)
set(CMAKE_CXX_FLAGS "-g -O0 -std=c++11")
message(STATUS "Build folder: ${CMAKE_BINARY_DIR}")

include_directories("${ROOT_ROOT}/include")
include_directories("${FLATBUFFERS_ROOT}/include")
include_directories("${MSGPACK_ROOT}/include")
include_directories("${THRIFT_ROOT}/include")
include_directories("${BOOST_ROOT}/include")
include_directories("${PROJECT_BINARY_DIR}")
include_directories("${PROJECT_BINARY_DIR}/gen-cpp")
link_directories("${ROOT_ROOT}/lib")
link_directories("${FLATBUFFERS_ROOT}/lib")
link_directories("${THRIFT_ROOT}/lib")
link_directories("${BOOST_ROOT}/lib")

add_custom_command(OUTPUT DictOutput.cxx DictOutput.h
  COMMAND ${ROOT_ROOT}/bin/rootcint
  ARGS -f DictOutput.cxx -c ${CMAKE_SOURCE_DIR}/simple.h ${CMAKE_SOURCE_DIR}/LinkDef.h
  DEPENDS ${CMAKE_SOURCE_DIR}/simple.h ${CMAKE_SOURCE_DIR}/LinkDef.h
)
add_custom_command(OUTPUT hits_generated.h
  COMMAND ${FLATBUFFERS_ROOT}/bin/flatc
  ARGS -c ${CMAKE_SOURCE_DIR}/hits.fbs
  DEPENDS ${CMAKE_SOURCE_DIR}/hits.fbs
)
add_custom_command(OUTPUT digis_generated.h
  COMMAND ${FLATBUFFERS_ROOT}/bin/flatc
  ARGS -c ${CMAKE_SOURCE_DIR}/digis.fbs
  DEPENDS ${CMAKE_SOURCE_DIR}/digis.fbs
)
add_custom_command(OUTPUT ${CMAKE_BINARY_DIR}/gen-cpp/event_types.cpp
  COMMAND ${THRIFT_ROOT}/bin/thrift
  ARGS --gen cpp ${CMAKE_SOURCE_DIR}/event.thrift
  DEPENDS ${CMAKE_SOURCE_DIR}/event.thrift
)

add_executable(benchmark
               benchmark.cxx 
               ${CMAKE_BINARY_DIR}/DictOutput.cxx
               ${CMAKE_BINARY_DIR}/digis_generated.h
               ${CMAKE_BINARY_DIR}/hits_generated.h
               ${CMAKE_BINARY_DIR}/gen-cpp/event_types.cpp)

target_link_libraries(benchmark Core Net Hist RIO Cint libthrift.a)
