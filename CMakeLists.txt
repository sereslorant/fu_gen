cmake_minimum_required(VERSION 2.8)
project(FuGen)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")

#The source of OpenMesh, SOIL and GLM should be placed into the Dependencies folder.
#For more info see the ./Dependencies/CMakeLists.txt file
set(DEPENDENCY_DIR			"./Dependencies")

set(FU_GEN_LIB_DIR "./FuGenLib")

#Setting up dependencies
set(OPEN_MESH_SRC_DIR "./Dependencies/OpenMesh/src/")
add_subdirectory(Dependencies)

include_directories(${DEPENDENCY_DIR} ${FU_GEN_LIB_DIR} ${OPEN_MESH_SRC_DIR})

add_subdirectory(FuGenLib)
add_subdirectory(FuGenEditor)
add_subdirectory(FuGenDemo)
