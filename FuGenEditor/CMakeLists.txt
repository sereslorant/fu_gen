
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
find_package(Qt5 REQUIRED COMPONENTS Core Widgets OpenGL)
find_package(OpenGL REQUIRED)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_POSITION_INDEPENDENT_CODE True)

include_directories("./")
include_directories(${Qt5Core_INCLUDE_DIRS} ${Qt5Widgets_INCLUDE_DIRS} ${Qt5OpenGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS} ${CMAKE_CURRENT_BINARY_DIR})

set(FuGenEdgeVisualizer_SRC	View/EdgeVisualizer/FuGenGLView.cpp
							View/EdgeVisualizer/GL/GLExt.cpp
							View/EdgeVisualizer/GL/GLEdgeVisualizer.cpp
							)

set(FuGenPipelineEditor_SRC	View/PipelineEditor/FuGenPipelineNode.cpp
							View/PipelineEditor/FuGenPipelineEdge.cpp
							View/PipelineEditor/FuGenPipelineEditor.cpp
							)

set(FuGenNodeEditor_SRC	View/NodeEditor/FuGenNodeEditor.cpp
						View/NodeEditor/TurtleNodeEditor.cpp
						View/NodeEditor/HypergraphNodeEditor.cpp
						View/NodeEditor/MeshNodeEditor.cpp
						)

set(FuGenEditor_SRCS	View/FuGenWindow.cpp
						${FuGenEdgeVisualizer_SRC}
						${FuGenPipelineEditor_SRC}
						${FuGenNodeEditor_SRC}
						)


add_executable(FuGenEditor ${FuGenEditor_SRCS} View/FuGenMain.cpp)
target_link_libraries(FuGenEditor ${Qt5Core_LIBRARIES} ${Qt5OpenGL_LIBRARIES} ${OPENGL_LIBRARIES} FuGenPresenter)

add_subdirectory(Presenter)



add_subdirectory(Test)
