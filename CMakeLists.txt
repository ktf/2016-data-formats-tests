cmake_minimum_required(VERSION 2.8)
set(CMAKE_CXX_FLAGS "-g -O0 -std=c++11")

include_directories("${ROOT_ROOT}/include")
include_directories("${FLATBUFFERS_ROOT}/include")
include_directories("${MSGPACK_ROOT}/include")
link_directories("${ROOT_ROOT}/lib")
link_directories("${FLATBUFFERS_ROOT}/lib")
add_custom_command(OUTPUT DictOutput.cxx DictOutput.h
  COMMAND rootcint
  ARGS -f DictOutput.cxx -c simple.h LinkDef.h
  DEPENDS simple.h LinkDef.h
)
add_custom_command(OUTPUT hits_generated.h
  COMMAND flatc
  ARGS -c hits.fbs
  DEPENDS hits.fbs
)
add_custom_command(OUTPUT digis_generated.h
  COMMAND flatc
  ARGS -c digis.fbs
  DEPENDS digis.fbs
)
add_executable(benchmark
               benchmark.cxx DictOutput.cxx digis_generated.h hits_generated.h)

target_link_libraries(benchmark Core Net Hist RIO Cint)
