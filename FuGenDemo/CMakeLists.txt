
find_package(SDL2 REQUIRED)
find_package(OpenGL REQUIRED)

string(STRIP ${SDL2_INCLUDE_DIRS} SDL2_INCLUDE_DIRS)
string(STRIP ${SDL2_LIBRARIES} SDL2_LIBRARIES)

include_directories(${OPENGL_INCLUDE_DIRS})
include_directories(${SDL2_INCLUDE_DIRS})

include_directories(".")

set(FU_GEN_DEMO_SRC_DIR	".")

#find_package(GLUT REQUIRED)
#include_directories(${GLUT_INCLUDE_DIRS})

#set(FU_GEN_DEMO_SRC ${FU_GEN_DEMO_SRC_DIR}/LegacyMain.cpp
#					${FU_GEN_DEMO_SRC_DIR}/DemoUtils/DrawModel.cpp
#					${FU_GEN_DEMO_SRC_DIR}/DemoUtils/DemoTexture.cpp
#					
#					${FU_GEN_DEMO_SRC_DIR}/Demo/Demo2D/QuadraticKochCurve.cpp
#					${FU_GEN_DEMO_SRC_DIR}/Demo/Demo2D/DragonCurve.cpp
#					${FU_GEN_DEMO_SRC_DIR}/Demo/Demo2D/StochasticTree2D.cpp
#					${FU_GEN_DEMO_SRC_DIR}/Demo/Demo2D/CordateLeaf.cpp
#					
#					${FU_GEN_DEMO_SRC_DIR}/Demo/Demo3D/HilbertCurve.cpp
#					${FU_GEN_DEMO_SRC_DIR}/Demo/Demo3D/TreeDemo.cpp
#					${FU_GEN_DEMO_SRC_DIR}/Demo/Demo3D/DeterministicTree.cpp
#					${FU_GEN_DEMO_SRC_DIR}/Demo/Demo3D/StochasticTree3D.cpp
#					)

#add_executable(FuGenDemo ${FU_GEN_DEMO_SRC})
#target_link_libraries(FuGenDemo FuGenLib SOIL ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES})

set(SDL2_DEMO_FRAMEWORK_SRC SDL2DemoFramework.cpp ${FU_GEN_DEMO_SRC_DIR}/DemoUtils/DrawModel.cpp)

add_executable(Fractal2D	MainFractal2D.cpp
							${SDL2_DEMO_FRAMEWORK_SRC}
							${FU_GEN_DEMO_SRC_DIR}/Demo/Demo2D/QuadraticKochCurve.cpp
							${FU_GEN_DEMO_SRC_DIR}/Demo/Demo2D/DragonCurve.cpp
							${FU_GEN_DEMO_SRC_DIR}/Demo/Demo2D/CordateLeaf.cpp
							)
target_link_libraries(Fractal2D FuGenLib ${OPENGL_LIBRARIES} ${SDL2_LIBRARIES})

add_executable(StochasticTree2D	MainStochasticTree2D.cpp
								${SDL2_DEMO_FRAMEWORK_SRC}
								${FU_GEN_DEMO_SRC_DIR}/Demo/Demo2D/StochasticTree2D.cpp
								)
target_link_libraries(StochasticTree2D FuGenLib ${OPENGL_LIBRARIES} ${SDL2_LIBRARIES})

add_executable(Fractal3D	MainFractal3D.cpp
							${SDL2_DEMO_FRAMEWORK_SRC}
							${FU_GEN_DEMO_SRC_DIR}/Demo/Demo3D/HilbertCurve.cpp
							)
target_link_libraries(Fractal3D FuGenLib ${OPENGL_LIBRARIES} ${SDL2_LIBRARIES})

add_executable(DeterministicTree3D	MainDeterministicTree3D.cpp
									${SDL2_DEMO_FRAMEWORK_SRC}
									${FU_GEN_DEMO_SRC_DIR}/DemoUtils/DemoTexture.cpp
									${FU_GEN_DEMO_SRC_DIR}/Demo/Demo3D/TreeDemo.cpp
									${FU_GEN_DEMO_SRC_DIR}/Demo/Demo3D/DeterministicTree.cpp
									)
target_link_libraries(DeterministicTree3D FuGenLib SOIL ${OPENGL_LIBRARIES} ${SDL2_LIBRARIES})

add_executable(StochasticTree3D		MainStochasticTree3D.cpp
									${SDL2_DEMO_FRAMEWORK_SRC}
									${FU_GEN_DEMO_SRC_DIR}/DemoUtils/DemoTexture.cpp
									${FU_GEN_DEMO_SRC_DIR}/Demo/Demo3D/TreeDemo.cpp
									${FU_GEN_DEMO_SRC_DIR}/Demo/Demo3D/StochasticTree3D.cpp
									)
target_link_libraries(StochasticTree3D FuGenLib SOIL ${OPENGL_LIBRARIES} ${SDL2_LIBRARIES})
