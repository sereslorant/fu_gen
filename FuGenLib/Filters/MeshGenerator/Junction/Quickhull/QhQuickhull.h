#ifndef QH_QUICKHULL_H
#define QH_QUICKHULL_H

#include "glmath.hpp"

#include "QhMesh.h"

extern unsigned int MaxIterations;

void QhQuickhull(vec4 vertices[],unsigned int num_vertices,QhMesh &result);

#endif // QH_QUICKHULL_H
