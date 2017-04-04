#To compile SOIL and OpenMesh with this CMake file, copy the following directories:
#Contents of <OpenMesh path> folder should be copied into ./OpenMesh
#Contents of <SOIL path>/src should be copied into ./SOIL
#
#The other libraries require you to copy the source of glm into this folder as well.

#Setting up SOIL
set(SOIL_SRC_DIR			"./SOIL")

set(SOIL_SRC	"${SOIL_SRC_DIR}/image_helper.c"
				"${SOIL_SRC_DIR}/image_DXT.c"
				"${SOIL_SRC_DIR}/stb_image_aug.c"
				"${SOIL_SRC_DIR}/SOIL.c"
				)

#Adding libraries
add_library(SOIL  ${SOIL_SRC})

set(BUILD_APPS OFF)
add_subdirectory(OpenMesh)
