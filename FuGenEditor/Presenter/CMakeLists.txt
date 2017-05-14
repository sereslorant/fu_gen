
set(DATA_SRC	Data/TreeSkeletonPresenter.cpp
				Data/TreeHypergraphPresenter.cpp
				Data/TreeMeshPresenter.cpp
				)

set(ELEMENTS_SRC	Elements/Nodes/TurtleNodePresenter.cpp
					Elements/Nodes/HypergraphNodePresenter.cpp
					Elements/Nodes/MeshNodePresenter.cpp
					)

add_library(FuGenPresenter PipelinePresenter.cpp ${DATA_SRC} ${ELEMENTS_SRC})
target_link_libraries(FuGenPresenter FuGenLib)
