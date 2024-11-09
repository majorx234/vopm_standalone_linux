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
