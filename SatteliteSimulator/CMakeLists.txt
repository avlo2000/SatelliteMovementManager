cmake_minimum_required(VERSION 3.0.0)
project(satelite VERSION 0.1)
set(CMAKE_CXX_STANDART 14)

if(DEBUG_OPTION)
    set(BUILD_TYPE "DEBUG")
else()
    set(BUILD_TYPE "RELEASE")
endif()

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/third_party/eigen)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/third_party/MiniDNN/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}r/third_party/tiny-dnn-master)

message(../${CMAKE_CURRENT_SOURCE_DIR}/third_party/eigen)

SET(GCC_COVERAGE_COMPILE_FLAGS "-fexceptions")

SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}" )

set(CMAKE_CXX_COMPILER "g++")

#include_dir
set (SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set (SRC_CONTROLLER_DIR ${SRC_DIR}/Controller)
set (SRC_FINAL ${SRC_DIR}/SatteliteSimulator)
set (SRC_CONTROLLER_CONTRACTS_DIR ${SRC_DIR}/Controller.Contracts)
set (SRC_SATELITE_SIMULATOR_DIR ${SRC_DIR})
set (SRC_SIMULATION_DIR ${SRC_DIR}/Simulation)
set (SRC_SIMULATION_CONTRACTS_DIR ${SRC_DIR}/Simulation.Contracts)
set (SRC_SIMULATION_Entry ${SRC_DIR}/Entry)

include_directories(${SRC_DIR})
include_directories(${SRC_FINAL})
include_directories(${SRC_CONTROLLER_DIR})
include_directories(${SRC_CONTROLLER_CONTRACTS_DIR})
include_directories(${SRC_SATELITE_SIMULATOR_DIR})
include_directories(${SRC_SIMULATION_DIR})
include_directories(${SRC_SIMULATION_CONTRACTS_DIR})
include_directories(${SRC_SIMULATION_Entry})

FILE(GLOB SRCFILES
    ${SRC_DIR}/*.cpp
    ${SRC_DIR}/*.h
    ${SRC_FINAL}/*.h
    ${SRC_FINAL}/*.cpp
    ${SRC_CONTROLLER_DIR}/*.cpp
    ${SRC_CONTROLLER_DIR}/*.h
    ${SRC_CONTROLLER_CONTRACTS_DIR}/*.cpp
    ${SRC_CONTROLLER_CONTRACTS_DIR}/*.h
    ${SRC_SATELITE_SIMULATOR_DIR}/*.cpp
    ${SRC_SATELITE_SIMULATOR_DIR}/*.h
    ${SRC_SIMULATION_DIR}/*.cpp
    ${SRC_SIMULATION_DIR}/*.h
    ${SRC_SIMULATION_CONTRACTS_DIR}/*.cpp
    ${SRC_SIMULATION_CONTRACTS_DIR}/*.h
    ${SRC_SIMULATION_Entry}/*.h
    ${SRC_SIMULATION_Entry}/*.cpp)

list(REMOVE_ITEM SRCFILES ${SRC_SATELITE_SIMULATOR_DIR}/Entry/main.cpp)
message(${SRC_DIR} "SOUCRE ")

add_library (satelite_lib OBJECT ${SRCFILES})
ADD_EXECUTABLE(${PROJECT_NAME} $<TARGET_OBJECTS:satelite_lib> ${SRC_SATELITE_SIMULATOR_DIR}/Entry/main.cpp)
LINK_DIRECTORIES(/usr/local/lib)
LINK_DIRECTORIES(/usr/lib)
set(LINKLIBS)

target_link_libraries(${PROJECT_NAME} ${LINKLIBS})
