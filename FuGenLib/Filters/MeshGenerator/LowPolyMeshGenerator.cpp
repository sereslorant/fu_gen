
#include "LowPolyMeshGenerator.h"

#include <iostream>
/*
void GenerateLowPolyMesh::SampleSegment(const GeneralizedCylinder &cylinder,float t_begin,float t_end,Mesh<glm::vec3> *mesh)
{
	float dt = (t_end - t_begin)/(SegmentHeight - 1);
	float dAngle = 2.0*PI/SegmentWidth;

	*mesh = Mesh<glm::vec3>(SegmentWidth*SegmentHeight,(SegmentWidth+1)*SegmentHeight);
	for(unsigned int i=0;i < SegmentHeight;i++)
	{
		unsigned int j;
		for(j=0;j < SegmentWidth;j++)
		{
			float x = t_begin + i*dt;
			float y = j*dAngle;
			mesh->Vertices[i*SegmentWidth + j] = cylinder.GetPoint(x,y);
			//
			x /= (t_end - t_begin);
			y /= 2.0*PI;
			mesh->TexCoords[i*(SegmentWidth + 1) + j] = glm::vec2(y,x);
		}

		float x = t_begin + i*dt;
		float y = j*dAngle;
		//
		x /= (t_end - t_begin);
		y /= 2.0*PI;
		mesh->TexCoords[i*(SegmentWidth + 1) + j] = glm::vec2(y,x);
	}

	for(unsigned int i=0;i < SegmentHeight - 1;i++)
	{
		for(unsigned int j=0;j < SegmentWidth;j++)
		{
			unsigned int I = (i+1);
			unsigned int J = (j+1) % SegmentWidth;

			unsigned int V1_Id = i*SegmentWidth + j;
			unsigned int V2_Id = i*SegmentWidth + J;
			unsigned int V3_Id = I*SegmentWidth + j;
			unsigned int V4_Id = I*SegmentWidth + J;

			unsigned int V1_TexCoord = i*(SegmentWidth + 1) + j;
			unsigned int V2_TexCoord = i*(SegmentWidth + 1) + (j+1);
			unsigned int V3_TexCoord = I*(SegmentWidth + 1) + j;
			unsigned int V4_TexCoord = I*(SegmentWidth + 1) + (j+1);

			Triangle T1;
			T1.VertexId[2] = V1_Id;
			T1.VertexId[1] = V2_Id;
			T1.VertexId[0] = V3_Id;

			T1.TexCoordId[2] = V1_TexCoord;
			T1.TexCoordId[1] = V2_TexCoord;
			T1.TexCoordId[0] = V3_TexCoord;

			Triangle T2;
			T2.VertexId[2] = V3_Id;
			T2.VertexId[1] = V2_Id;
			T2.VertexId[0] = V4_Id;

			T2.TexCoordId[2] = V3_TexCoord;
			T2.TexCoordId[1] = V2_TexCoord;
			T2.TexCoordId[0] = V4_TexCoord;

			mesh->Triangles.push_back(T1);
			mesh->Triangles.push_back(T2);
		}
	}
}
*/
/*
void LowPolyMeshGenerator::SampleJunction(const TreeHypergraph::Junction &J,MultiMesh &multi_mesh,MyMesh *junction_mesh)
{
	unsigned int NumVertices = J.Children.size()*SegmentWidth;

	if(J.Root != nullptr)
		{NumVertices += SegmentWidth;}
	//else
	//	{continue;}
	std::vector<VertexData> Vertices(NumVertices);

	unsigned int j=0;
	if(J.Root != nullptr)
	{
		for(unsigned int i=0;i < SegmentWidth;i++)
		{
			unsigned int VertexId = (SegmentHeight - 1)*SegmentWidth + i;
			Vertices[j].Vertex = multi_mesh.Segments[J.Root->Id].Vertices[VertexId];
			Vertices[j].SegmentId = J.Root->Id;
			Vertices[j].SampleId = VertexId;
			j++;
		}
	}

	for(TreeHypergraph::Branch *B : J.Children)
	{
		for(unsigned int i=0;i < SegmentWidth;i++)
		{
			unsigned int VertexId = i;
			Vertices[j].Vertex = multi_mesh.Segments[B->Id].Vertices[VertexId];
			Vertices[j].SegmentId = B->Id;
			Vertices[j].SampleId = VertexId;
			j++;
		}
	}

	//for(auto v : Vertices)
	//{
		//std::cout << v.SegmentId << " ";
	//}

	//std::cout << std::endl;

	Quickhull(&Vertices[0],Vertices.size(),*junction_mesh);
}
*/
/*
void LowPolyMeshGenerator::DeleteTriangles(MyMesh &half_edge)
{
	std::list<MyMesh::FaceIter> DeletableTriangles;

	for(MyMesh::FaceIter F = half_edge.faces_begin();F != half_edge.faces_end();F++)
	{
		bool VertexFound = false;

		for(MyMesh::FaceVertexIter V_I = half_edge.fv_iter(*F);V_I.is_valid();V_I++)
		{
			auto Data_I = half_edge.data(V_I);
			MyMesh::FaceVertexIter V_J = V_I;
			V_J++;
			for(/*MyMesh::FaceVertexIter V_J = half_edge.fv_iter(*F)* /;V_J.is_valid();V_J++)
			{
				auto Data_J = half_edge.data(V_J);
				if(Data_I.SegmentId != Data_J.SegmentId)
				{
					VertexFound = true;
					break;
				}
			}

			if(VertexFound)
			{
				break;
			}
		}

		if(!VertexFound)
		{
			DeletableTriangles.push_back(F);
		}
	}

	for(auto I : DeletableTriangles)
	{
		half_edge.delete_face(I,true);
	}

	half_edge.garbage_collection();
}
*/
/*
void LowPolyMeshGenerator::CollapseEdges(MyMesh &half_edge)
{
	for(MyMesh::VertexIter I = half_edge.vertices_begin();I != half_edge.vertices_end();I++)
	{
		auto &I_Data = half_edge.data(I);
		I_Data.Collapsed = false;
	}
	//
	std::list<MyMesh::VertexOHalfedgeIter> EdgesToCollapse;
	unsigned int i=0;
	//
	for(MyMesh::VertexIter I = half_edge.vertices_begin();I != half_edge.vertices_end();I++)
	{
		auto &I_Data = half_edge.data(I);
		if(I_Data.Collapsed)
			{continue;}
		//if(i == Anyad){break;}
		//
		bool FoundOne = false;
		MyMesh::VertexOHalfedgeIter MinIter;
		float MinLength;
		//
		for(MyMesh::VertexOHalfedgeIter J = half_edge.voh_iter(I);J.is_valid();J++)
		{
			MyMesh::VertexHandle J_V = half_edge.to_vertex_handle(J);
			auto &J_Data = half_edge.data(J_V);
			//
			if(J_Data.Collapsed)
				{continue;}
			//
			if(I_Data.SegmentId != J_Data.SegmentId)
			{
				MyMesh::Point I_Point = half_edge.point(*I);
				MyMesh::Point J_Point = half_edge.point(J_V);
				//
				glm::vec3 I_Vec(I_Point[0],I_Point[1],I_Point[2]);
				glm::vec3 J_Vec(J_Point[0],J_Point[1],J_Point[2]);
				//
				float Length = glm::length(I_Vec - J_Vec);
				//
				if(FoundOne)
				{
					if(Length < MinLength)
					{
						//
						MinIter = J;
						MinLength = Length;
					}
				}
				else
				{
					//
					MinIter = J;
					MinLength = Length;
					//
					FoundOne = true;
				}
			}
		}
		//
		if(FoundOne)
		{
			MyMesh::VertexHandle J_V = half_edge.to_vertex_handle(MinIter);
			auto &J_Data = half_edge.data(J_V);
			//
			I_Data.OtherSegmentId	= J_Data.SegmentId;
			I_Data.OtherSampleId	= J_Data.SampleId;
			//
			I_Data.Collapsed = true;
			//
			J_Data.OtherSegmentId	= I_Data.SegmentId;
			J_Data.OtherSampleId	= I_Data.SampleId;
			//
			J_Data.Collapsed = true;
			//
			MyMesh::Point I_Point = half_edge.point(*I);
			MyMesh::Point J_Point = half_edge.point(J_V);
			MyMesh::Point Average = (1.0/2.0)*(I_Point + J_Point);
			//
			half_edge.set_point(*I,	Average);
			half_edge.set_point(J_V,Average);
			//
			EdgesToCollapse.push_back(MinIter);
			i++;
		}
	}

	for(auto &Edge : EdgesToCollapse)
	{
		half_edge.collapse(*Edge);
	}

	half_edge.garbage_collection();
}
*/
/*
void LowPolyMeshGenerator::AdjustSegments(MyMesh &half_edge,MultiMesh &multi_mesh)
{
	for(MyMesh::VertexIter I = half_edge.vertices_begin();I != half_edge.vertices_end();I++)
	{
		auto &I_Data = half_edge.data(I);
		if(!I_Data.Collapsed)
			{continue;}

		if(I_Data.OtherSegmentId != -1)
		{
			MyMesh::Point I_Point = half_edge.point(*I);
			multi_mesh.Segments[I_Data.SegmentId].Vertices[I_Data.SampleId] = glm::vec3(I_Point[0],I_Point[1],I_Point[2]);
			multi_mesh.Segments[I_Data.OtherSegmentId].Vertices[I_Data.OtherSampleId] = glm::vec3(I_Point[0],I_Point[1],I_Point[2]);
		}
	}
}
*/
/*
void SetTexCoord(MyMesh &half_edge,MyMesh::FaceHalfedgeIter E,bool from_other,bool to_other,float delta_uv)
{
	auto &FromData	= half_edge.data(half_edge.from_vertex_handle(E));
	auto &ToData	= half_edge.data(half_edge.to_vertex_handle(E));
	//
	glm::vec2 FromTexCoord = from_other? FromData.OtherTexCoord : FromData.TexCoord;
	glm::vec2 ToTexCoord = to_other? ToData.OtherTexCoord : ToData.TexCoord;
	//
	E++;
	auto &ThirdData = half_edge.data(half_edge.to_vertex_handle(E));
	ThirdData.TexCoord	= (FromTexCoord + ToTexCoord)*(1.0f/2.0f) + glm::vec2(delta_uv,delta_uv);
}

void LowPolyMeshGenerator::ParametrizeHalfedge(MyMesh &half_edge)
{
	for(MyMesh::FaceIter F = half_edge.faces_begin();F != half_edge.faces_end();F++)
	{
		bool Found = false;
		//
		for(MyMesh::FaceHalfedgeIter E = half_edge.fh_iter(F);E.is_valid();E++)
		{
			auto &FromData	= half_edge.data(half_edge.from_vertex_handle(E));
			auto &ToData	= half_edge.data(half_edge.to_vertex_handle(E));
			//
			/*
			 * TODO Csúnya kódduplikálást ki kéne irtani.
			 * /
			if(FromData.SegmentId == ToData.SegmentId)
			{
				SetTexCoord(half_edge,E,false,false,DELTA_UV);
				//
				Found = true;
				break;
			}
			else if(FromData.OtherSegmentId == ToData.SegmentId)
			{
				SetTexCoord(half_edge,E,true,false,DELTA_UV);
				//
				Found = true;
				break;
			}
			else if(FromData.SegmentId == ToData.OtherSegmentId)
			{
				SetTexCoord(half_edge,E,false,true,DELTA_UV);
				//
				Found = true;
				break;
			}
			else if(FromData.OtherSegmentId == ToData.OtherSegmentId)
			{
				SetTexCoord(half_edge,E,true,true,DELTA_UV);
				//
				Found = true;
				break;
			}
		}
		//
		if(!Found)
		{
			//std::cout << "Epic bug" << std::endl;
			std::cout << "Epic bug\n";
			//
			for(MyMesh::FaceHalfedgeIter E = half_edge.fh_iter(F);E.is_valid();E++)
			{
				auto &FromData	= half_edge.data(half_edge.from_vertex_handle(E));
				//
				std::cout << FromData.SegmentId << " ";
			}
			//
			std::cout << std::endl;
			//
			for(MyMesh::FaceHalfedgeIter E = half_edge.fh_iter(F);E.is_valid();E++)
			{
				auto &FromData	= half_edge.data(half_edge.from_vertex_handle(E));
				//
				std::cout << FromData.OtherSegmentId << " ";
			}
		}
	}
}
*/
#include "SegmentGenerator.h"

Spinlock cout_lock;

class SampleSegmentJob : public Job
{
private:
	SegmentGenerator segmentGenerator;
	bool Finished = false;
	//
public:
	//
	virtual bool IsFinished() override
	{
		return Finished;
	}
	//
	void Execute()
	{
		//auto Before = std::chrono::steady_clock::now();
		segmentGenerator.SampleSegment();
		Finished = true;
		//auto After = std::chrono::steady_clock::now();
		//auto Difference = After - Before;
		//{
		//	std::lock_guard<SpinLock> Guard(cout_lock);
		//	std::cout << "Branch generation time: " << std::chrono::duration<double,std::milli>(Difference).count() << std::endl;
		//}
	}
	//
	SampleSegmentJob(unsigned int num_dependencies,Job *dependencies[],const SegmentGenerator &segment_generator)
		:Job(num_dependencies,dependencies),segmentGenerator(segment_generator)
	{
		//
	}
	//
	virtual ~SampleSegmentJob() override
	{
		//
	}
	/*
	 * End of class
	 */
};

void LowPolyMeshGenerator::GenerateSegments(std::vector<Job *> &generate_segment_jobs,JobQueue &job_queue,TreeHypergraph *tree_hypergraph,MultiMesh &result)
{
	result.Segments.clear();
	result.Segments.resize(tree_hypergraph->Branches.size());
	generate_segment_jobs.resize(tree_hypergraph->Branches.size());
	//
	int i=0;
	for(TreeHypergraph::Branch *B : tree_hypergraph->Branches)
	{
		SegmentGenerator segmentGenerator(
						GeneralizedCylinder(*B->Curve,B->Up,B->Width),
						B->t_Begin,
						B->t_End,
						SegmentWidth,
						SegmentHeight,
						result.Segments[B->Id]
						);
		//
		generate_segment_jobs[i] = job_queue.CreateJob<SampleSegmentJob>(0,nullptr,segmentGenerator);
		i++;
		//segmentGenerator.SampleSegment();
	}
}

#include "Junction/JunctionGenerator.h"

class SampleJunctionJob : public Job
{
private:
	JunctionGenerator junctionGenerator;
	bool Finished = false;
	//
public:
	//
	virtual bool IsFinished() override
	{
		return Finished;
	}
	//
	void Execute()
	{
		//auto Before = std::chrono::steady_clock::now();
		junctionGenerator.SampleJunction();
		Finished = true;
		//auto After = std::chrono::steady_clock::now();
		//auto Difference = After - Before;
		//{
		//	std::lock_guard<SpinLock> Guard(cout_lock);
		//	std::cout << "Junction sampling time: " << std::chrono::duration<double,std::milli>(Difference).count() << std::endl;
		//}
	}
	//
	SampleJunctionJob(unsigned int num_dependencies,Job *dependencies[],const JunctionGenerator &junction_generator)
		:Job(num_dependencies,dependencies),junctionGenerator(junction_generator)
	{
		//
	}
	//
	virtual ~SampleJunctionJob() override
	{
		//
	}
	/*
	 * End of class
	 */
};

#include "Junction/JunctionOperations.h"

class ProcessJunctionJob : public Job
{
private:
	JunctionOperations junctionOperations;
	bool Finished = false;
	//
public:
	//
	virtual bool IsFinished() override
	{
		return Finished;
	}
	//
	void Execute()
	{
		//auto Before = std::chrono::steady_clock::now();
		junctionOperations.DeleteTriangles();
		junctionOperations.CollapseEdges();
		Finished = true;
		//auto After = std::chrono::steady_clock::now();
		//auto Difference = After - Before;
		//{
		//	std::lock_guard<SpinLock> Guard(cout_lock);
		//	std::cout << "Junction processing time: " << std::chrono::duration<double,std::milli>(Difference).count() << std::endl;
		//}
	}
	//
	ProcessJunctionJob(unsigned int num_dependencies,Job *dependencies[],const JunctionOperations &junction_operations)
		:Job(num_dependencies,dependencies),junctionOperations(junction_operations)
	{
		//
	}
	//
	virtual ~ProcessJunctionJob() override
	{
		//
	}
	/*
	 * End of class
	 */
};

#include "SegmentAdjuster.h"

class AdjustSegmentJob : public Job
{
private:
	SegmentAdjuster segmentAdjuster;
	bool Finished = false;
	//
public:
	//
	virtual bool IsFinished() override
	{
		return Finished;
	}
	//
	void Execute()
	{
		//auto Before = std::chrono::steady_clock::now();
		segmentAdjuster.AdjustSegments();
		Finished = true;
		//auto After = std::chrono::steady_clock::now();
		//auto Difference = After - Before;
		//{
		//	std::lock_guard<SpinLock> Guard(cout_lock);
		//	std::cout << "Segment adjusting time: " << std::chrono::duration<double,std::milli>(Difference).count() << std::endl;
		//}
	}
	//
	AdjustSegmentJob(unsigned int num_dependencies,Job *dependencies[],const SegmentAdjuster &segment_adjuster)
		:Job(num_dependencies,dependencies),segmentAdjuster(segment_adjuster)
	{
		//
	}
	//
	virtual ~AdjustSegmentJob() override
	{
		//
	}
	/*
	 * End of class
	 */
};

#include "Junction/JunctionMeshGenerator.h"

class GenerateJunctionMeshJob : public Job
{
private:
	JunctionMeshGenerator junctionMeshGenerator;
	bool Finished = false;
	//
public:
	//
	virtual bool IsFinished() override
	{
		return Finished;
	}
	//
	void Execute()
	{
		//auto Before = std::chrono::steady_clock::now();
		junctionMeshGenerator.ParametrizeHalfedge();
		Finished = true;
		//auto After = std::chrono::steady_clock::now();
		//auto Difference = After - Before;
		//{
		//	std::lock_guard<SpinLock> Guard(cout_lock);
		//	std::cout << "Halfedge parametrization time: " << std::chrono::duration<double,std::milli>(Difference).count() << std::endl;
		//}
	}
	//
	GenerateJunctionMeshJob(unsigned int num_dependencies,Job *dependencies[],const JunctionMeshGenerator &junction_mesh_generator)
		:Job(num_dependencies,dependencies),junctionMeshGenerator(junction_mesh_generator)
	{
		//
	}
	//
	virtual ~GenerateJunctionMeshJob() override
	{
		//
	}
	/*
	 * End of class
	 */
};

void LowPolyMeshGenerator::GenerateJunctions(std::vector<Job *> &generate_segment_jobs,JobQueue &job_queue,TreeHypergraph *tree_hypergraph,MultiMesh &result)
{
	result.JunctionMeshes.clear();
	//
	for(TreeHypergraph::Junction *J : tree_hypergraph->Junctions)
	{
		if(J->Root == nullptr)
		{continue;}
		//
		result.JunctionMeshes.emplace_back();
		MyMesh &JunctionMesh = result.JunctionMeshes.back();
		//
		JunctionGenerator junctionGenerator(JunctionMesh,*J,SegmentWidth,SegmentHeight);
		//SampleJunction(*J,result,&JunctionMesh);
		//junctionGenerator.SampleJunction();
		Job *sampleJunctionJob = job_queue.CreateJob<SampleJunctionJob>(0,nullptr,junctionGenerator);
		//sampleJunctionJob.Execute();
		//
		JunctionOperations junctionOperations(JunctionMesh);
		//DeleteTriangles(JunctionMesh);
		//junctionOperations.DeleteTriangles();
		//CollapseEdges(JunctionMesh);
		//junctionOperations.CollapseEdges();
		//Job *processParent = &sampleJunctionJob;
		Job *processJunctionJob = job_queue.CreateJob<ProcessJunctionJob>(1,&sampleJunctionJob,junctionOperations);
		//processJunctionJob.Execute();
		//
		SegmentAdjuster segmentAdjuster(JunctionMesh,result);
		//AdjustSegments(JunctionMesh,result);
		//segmentAdjuster.AdjustSegments();
		std::vector<Job *>adjustSegmentParents(J->Children.size() + 2);
		int i=0;
		for(auto Child : J->Children)
		{
			adjustSegmentParents[i] = generate_segment_jobs[Child->Id];
			i++;
		}
		adjustSegmentParents[adjustSegmentParents.size() - 2] = generate_segment_jobs[J->Root->Id];
		adjustSegmentParents[adjustSegmentParents.size() - 1] = processJunctionJob;
		Job *adjustSegmentJob = job_queue.CreateJob<AdjustSegmentJob>(adjustSegmentParents.size(),&adjustSegmentParents[0],segmentAdjuster);
		//adjustSegmentJob.Execute();
		//
		JunctionMeshGenerator junctionMeshGenerator(JunctionMesh,DELTA_UV);
		//ParametrizeHalfedge(JunctionMesh);
		//junctionMeshGenerator.ParametrizeHalfedge();
		//Job *generateMeshParent = &processJunctionJob;
		Job *generateJunctionMeshJob = job_queue.CreateJob<GenerateJunctionMeshJob>(1,&processJunctionJob,junctionMeshGenerator);
		//generateJunctionMeshJob.Execute();
	}
}

#include <chrono>
#include <iostream>

#include <thread>

void LowPolyMeshGenerator::Generate(TreeHypergraph *tree_hypergraph,MultiMesh &result)
{
	std::cout << "Number of branches: " << tree_hypergraph->Branches.size() << "\n";
	std::cout << "Number of junctions: " << tree_hypergraph->Junctions.size() << std::endl;
	//
	JobQueue jobQueue;
	//
	Worker firstWorker(jobQueue);
#ifndef SINGLE_THREADED
	Worker secondWorker(jobQueue);
	Worker thirdWorker(jobQueue);
	Worker fourthWorker(jobQueue);
#endif
	//
	auto Before = std::chrono::steady_clock::now();
	//
	std::thread Threads[4];
	Threads[0] = std::thread(Worker::RunWorker,&firstWorker);
#ifndef SINGLE_THREADED
	Threads[1] = std::thread(Worker::RunWorker,&secondWorker);
	Threads[2] = std::thread(Worker::RunWorker,&thirdWorker);
	Threads[3] = std::thread(Worker::RunWorker,&fourthWorker);
#endif
	//
	std::vector<Job *> GenerateSegmentJobs;
	GenerateSegments(GenerateSegmentJobs,jobQueue,tree_hypergraph,result);
	//
	GenerateJunctions(GenerateSegmentJobs,jobQueue,tree_hypergraph,result);
	//
	firstWorker.AllowToStop();
#ifndef SINGLE_THREADED
	secondWorker.AllowToStop();
	thirdWorker.AllowToStop();
	fourthWorker.AllowToStop();
#endif
	//
#ifndef SINGLE_THREADED
	for(int i=0;i < 4;i++)
	{
		Threads[i].join();
	}
#else
	Threads[0].join();
#endif
	//
	auto After = std::chrono::steady_clock::now();
	auto Difference = After - Before;
	std::cout << "Mesh generation time: " << std::chrono::duration<double,std::milli>(Difference).count() << std::endl;
}
