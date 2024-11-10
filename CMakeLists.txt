cmake_minimum_required(VERSION 3.16)
project(jack_audio_examples)

set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH}" "${PROJECT_SOURCE_DIR}/cmake")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

find_package(Jack REQUIRED)

set(VOPM_STANDALONE_SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/src/vopm_standalone.cpp
)

set(LFO_SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/include/lfo.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/lfo.cpp
)

set(OP_SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/include/op.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/op.cpp
)

set(OPM_SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/include/opm.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/opm.cpp
)

add_library(fm_synth_model)
target_sources(fm_synth_model
 PRIVATE
 ${OP_SOURCES}
 ${OPM_SOURCES}
 ${LFO_SOURCES}
)
target_include_directories(fm_synth_model
 PRIVATE
)
target_link_libraries(fm_synth_model
)

add_executable(vopm_standalone)
target_sources(vopm_standalone
 PRIVATE
  ${VOPM_STANDALONE_SOURCES}
)
target_include_directories(vopm_standalone
 PRIVATE
)
target_link_libraries(vopm_standalone
)
