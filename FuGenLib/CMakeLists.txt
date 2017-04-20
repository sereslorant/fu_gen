
set(FU_GEN_SRC_DIR "./")

set(FU_GEN_SRC	"${FU_GEN_SRC_DIR}/Filters/L_Systems/SOL_System.cpp"
				"${FU_GEN_SRC_DIR}/Filters/Turtles/Turtle2D.cpp"
				"${FU_GEN_SRC_DIR}/Filters/Turtles/Turtle3D.cpp"
				"${FU_GEN_SRC_DIR}/Filters/MeshGenerator/SegmentGenerator.cpp"
				"${FU_GEN_SRC_DIR}/Filters/MeshGenerator/Junction/Quickhull/OMQuickhull.cpp"
				"${FU_GEN_SRC_DIR}/Filters/MeshGenerator/Junction/Quickhull/QhMesh.cpp"
				"${FU_GEN_SRC_DIR}/Filters/MeshGenerator/Junction/Quickhull/QhQuickhull.cpp"
				"${FU_GEN_SRC_DIR}/Filters/MeshGenerator/Junction/OMJunctionGenerator.cpp"
				"${FU_GEN_SRC_DIR}/Filters/MeshGenerator/Junction/JunctionOperations.cpp"
				"${FU_GEN_SRC_DIR}/Filters/MeshGenerator/Junction/JunctionMeshGenerator.cpp"
				"${FU_GEN_SRC_DIR}/Filters/MeshGenerator/LowPolyMeshGenerator.cpp"
				"${FU_GEN_SRC_DIR}/Multithreading/Job.cpp"
				"${FU_GEN_SRC_DIR}/Multithreading/JobQueue.cpp"
				"${FU_GEN_SRC_DIR}/Utils/CatmullRom.cpp"
				)

find_package(Threads)

add_library(FuGenLib ${FU_GEN_SRC})
#target_link_libraries(FuGenLib ${CMAKE_THREAD_LIBS_INIT} OpenMeshCoreStatic)
target_link_libraries(FuGenLib ${CMAKE_THREAD_LIBS_INIT} OpenMeshCore)
