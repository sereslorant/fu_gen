#ifndef DRAW_MODEL_H
#define DRAW_MODEL_H

#include <iostream>

#include <Data/TreeHypergraph.h>
#include <Data/MultiMesh.h>

#include <Const.h>

#include <Utils/GeneralizedCylinder.h>
#include <Utils/Quickhull.h>

void DrawSpline(const ICurve &curve,float t_begin,float t_end,float dt);

constexpr unsigned int CYLINDER_ARRAY_WIDTH = 6;
constexpr unsigned int CYLINDER_ARRAY_HEIGHT = 6;

void DrawGeneralizedCylinder(const GeneralizedCylinder &cylinder,float t0,float t_fin);

void DrawHalfedgeMesh(MyMesh &mesh);
void DrawHalfedgeVertices(MyMesh &mesh);

void DrawTexturedHalfedgeMesh(MyMesh &mesh);

extern bool DRAW_SPLINE;
extern bool DRAW_MODEL;
extern bool DRAW_SPLINE_FRONT_TO_BACK;
extern bool DRAW_CSO;
extern bool DRAW_JUNCTION;

extern bool DrawBranch;

void DrawHypergraph(TreeHypergraph *hypergraph);
void DrawMultiMesh(MultiMesh &Mesh);

#endif // DRAW_MODEL_H
