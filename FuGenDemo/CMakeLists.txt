
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

include_directories(${OPENGL_INCLUDE_DIRS})
include_directories(${GLUT_INCLUDE_DIRS})

set(FU_GEN_DEMO_SRC_DIR	".")

set(FU_GEN_DEMO_SRC "${FU_GEN_DEMO_SRC_DIR}/Main.cpp"
					"${FU_GEN_DEMO_SRC_DIR}/Demo/DrawModel.cpp"
					)

add_executable(FuGenDemo ${FU_GEN_DEMO_SRC})
target_link_libraries(FuGenDemo FuGenLib SOIL ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES})