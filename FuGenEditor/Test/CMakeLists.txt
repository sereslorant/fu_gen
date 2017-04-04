
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)

include_directories(${CMAKE_CURRENT_BINARY_DIR})

set(GL_TEST_SRCS "GLViewTest.cpp" "../View/EdgeVisualizer/FuGenGLView.cpp")

add_executable(GLViewTest ${GL_TEST_SRCS})
target_link_libraries(GLViewTest ${Qt5Core_LIBRARIES} ${Qt5OpenGL_LIBRARIES} ${OPENGL_LIBRARIES})
