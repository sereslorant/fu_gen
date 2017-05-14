
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)

include_directories(${CMAKE_CURRENT_BINARY_DIR})

set(GL_TEST_SRCS	"GLViewTest.cpp"
					"../View/EdgeVisualizer/FuGenGLView.cpp"
					"../View/EdgeVisualizer/GL/GLExt.cpp"
					"../View/EdgeVisualizer/GL/GLEdgeVisualizer.cpp"
					)

add_executable(GLViewTest ${GL_TEST_SRCS})
target_link_libraries(GLViewTest ${Qt5Core_LIBRARIES} ${Qt5OpenGL_LIBRARIES} ${OPENGL_LIBRARIES} FuGenPresenter FuGenLib)

set(PIPELINE_VISUALIZATION_TEST_SRCS	"PipelineVisualizationTest.cpp"
                                        "../View/PipelineEditor/FuGenPipelineEdge.cpp"
                                        "../View/PipelineEditor/FuGenPipelineEditor.cpp"
                                        "../View/PipelineEditor/FuGenPipelineNode.cpp"
                                        "../View/EdgeVisualizer/FuGenGLView.cpp"
                                        "../View/EdgeVisualizer/GL/GLExt.cpp"
                                        "../View/EdgeVisualizer/GL/GLEdgeVisualizer.cpp"
                                        )

add_executable(PipelineVisualizationTest ${PIPELINE_VISUALIZATION_TEST_SRCS})
target_link_libraries(PipelineVisualizationTest ${Qt5Core_LIBRARIES} ${Qt5OpenGL_LIBRARIES} ${OPENGL_LIBRARIES} FuGenPresenter FuGenLib)

set(NODE_EDITOR_TEST_SRCS	"NodeEditorTest.cpp"
							"../View/NodeEditor/TurtleNodeEditor.cpp"
							"../View/NodeEditor/HypergraphNodeEditor.cpp"
							"../View/NodeEditor/MeshNodeEditor.cpp"
							"../View/PipelineEditor/FuGenPipelineEdge.cpp"
							"../View/PipelineEditor/FuGenPipelineEditor.cpp"
							"../View/PipelineEditor/FuGenPipelineNode.cpp"
							"../View/EdgeVisualizer/FuGenGLView.cpp"
							"../View/EdgeVisualizer/GL/GLExt.cpp"
							"../View/EdgeVisualizer/GL/GLEdgeVisualizer.cpp"
							)

add_executable(NodeEditorTest ${NODE_EDITOR_TEST_SRCS})
target_link_libraries(NodeEditorTest ${Qt5Core_LIBRARIES} ${Qt5OpenGL_LIBRARIES} ${OPENGL_LIBRARIES} FuGenPresenter FuGenLib)

set(NODE_EDITOR_AND_PIPELINE_TEST_SRCS	"NodeEditorAndPipelineTest.cpp"
                                        "../View/NodeEditor/TurtleNodeEditor.cpp"
                                        "../View/NodeEditor/HypergraphNodeEditor.cpp"
                                        "../View/NodeEditor/MeshNodeEditor.cpp"
                                        "../View/NodeEditor/FuGenNodeEditor.cpp"
                                        "../View/PipelineEditor/FuGenPipelineEdge.cpp"
                                        "../View/PipelineEditor/FuGenPipelineEditor.cpp"
                                        "../View/PipelineEditor/FuGenPipelineNode.cpp"
                                        "../View/EdgeVisualizer/FuGenGLView.cpp"
                                        "../View/EdgeVisualizer/GL/GLExt.cpp"
                                        "../View/EdgeVisualizer/GL/GLEdgeVisualizer.cpp"
                                        )

add_executable(NodeEditorAndPipelineTest ${NODE_EDITOR_AND_PIPELINE_TEST_SRCS})
target_link_libraries(NodeEditorAndPipelineTest ${Qt5Core_LIBRARIES} ${Qt5OpenGL_LIBRARIES} ${OPENGL_LIBRARIES} FuGenPresenter FuGenLib)
