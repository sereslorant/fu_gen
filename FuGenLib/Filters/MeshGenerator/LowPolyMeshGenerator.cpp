
#include "LowPolyMeshGenerator.h"

#include <iostream>

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
	virtual void Execute() override
	{
		//auto Before = std::chrono::steady_clock::now();
		segmentGenerator.SampleSegment();
		Finished = true;
		//auto After = std::chrono::steady_clock::now();
		//auto Difference = After - Before;
		//{
		//	std::lock_guard<Spinlock> Guard(cout_lock);
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

#include "Junction/OMJunctionGenerator.h"
#include "Junction/QhJunctionGenerator.h"

template<class JunctionGeneratorStrategy_T>
class SampleJunctionJob : public Job
{
private:
	JunctionGeneratorStrategy_T junctionGenerator;
	bool Finished = false;
	//
public:
	//
	virtual bool IsFinished() override
	{
		return Finished;
	}
	//
	virtual void Execute() override
	{
		//auto Before = std::chrono::steady_clock::now();
		junctionGenerator.SampleJunction();
		Finished = true;
		//auto After = std::chrono::steady_clock::now();
		//auto Difference = After - Before;
		//{
		//	std::lock_guard<Spinlock> Guard(cout_lock);
		//	std::cout << "Junction sampling time: " << std::chrono::duration<double,std::milli>(Difference).count() << std::endl;
		//}
	}
	//
	SampleJunctionJob(unsigned int num_dependencies,Job *dependencies[],const JunctionGeneratorStrategy_T &junction_generator)
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
	virtual void Execute() override
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
	virtual void Execute() override
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
	virtual void Execute() override
	{
		//auto Before = std::chrono::steady_clock::now();
		junctionMeshGenerator.ParametrizeHalfedge();
		Finished = true;
		//auto After = std::chrono::steady_clock::now();
		//auto Difference = After - Before;
		//{
		//	std::lock_guard<Spinlock> Guard(cout_lock);
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

//#define USE_OPEN_MESH_QUICKHULL

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
#ifdef USE_OPEN_MESH_QUICKHULL
		OMJunctionGenerator junctionGenerator(JunctionMesh,*J,SegmentWidth,SegmentHeight);
#else
		QhJunctionGenerator junctionGenerator(JunctionMesh,*J,SegmentWidth,SegmentHeight);
#endif
		//
		//SampleJunction(*J,result,&JunctionMesh);
		//junctionGenerator.SampleJunction();
		//
#ifdef USE_OPEN_MESH_QUICKHULL
		Job *sampleJunctionJob = job_queue.CreateJob<SampleJunctionJob<OMJunctionGenerator> >(0,nullptr,junctionGenerator);
#else
		Job *sampleJunctionJob = job_queue.CreateJob<SampleJunctionJob<QhJunctionGenerator> >(0,nullptr,junctionGenerator);
#endif
		//
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

void LowPolyMeshGenerator::GenerateSingleThreaded(TreeHypergraph *tree_hypergraph,MultiMesh &result)
{
	auto Before = std::chrono::steady_clock::now();
	//
	result.Segments.clear();
	result.Segments.resize(tree_hypergraph->Branches.size());
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
		//auto Before = std::chrono::steady_clock::now();
		segmentGenerator.SampleSegment();
		//auto After = std::chrono::steady_clock::now();
		//auto Difference = After - Before;
		//std::cout << "Segment generation time: " << std::chrono::duration<double,std::milli>(Difference).count() << std::endl;
	}
	//
	auto After = std::chrono::steady_clock::now();
	auto Difference = After - Before;
	std::cout << "Branch generation time: " << std::chrono::duration<double,std::milli>(Difference).count() << std::endl;
	//
	Before = std::chrono::steady_clock::now();
	//
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
#ifdef USE_OPEN_MESH_QUICKHULL
		OMJunctionGenerator junctionGenerator(JunctionMesh,*J,SegmentWidth,SegmentHeight);
#else
		QhJunctionGenerator junctionGenerator(JunctionMesh,*J,SegmentWidth,SegmentHeight);
#endif
		//
		junctionGenerator.SampleJunction();
		//
		JunctionOperations junctionOperations(JunctionMesh);
		//
		junctionOperations.DeleteTriangles();
		junctionOperations.CollapseEdges();
		//
		SegmentAdjuster segmentAdjuster(JunctionMesh,result);
		//
		segmentAdjuster.AdjustSegments();
		//
		JunctionMeshGenerator junctionMeshGenerator(JunctionMesh,DELTA_UV);
		//
		junctionMeshGenerator.ParametrizeHalfedge();
	}
	//
	After = std::chrono::steady_clock::now();
	Difference = After - Before;
	std::cout << "Junction generation time: " << std::chrono::duration<double,std::milli>(Difference).count() << std::endl;
}

void LowPolyMeshGenerator::GenerateMultiThreaded(TreeHypergraph *tree_hypergraph,MultiMesh &result)
{
	JobQueue jobQueue;
	//
	Worker firstWorker(jobQueue);
	Worker secondWorker(jobQueue);
	Worker thirdWorker(jobQueue);
	Worker fourthWorker(jobQueue);
	//
	std::thread Threads[4];
	Threads[0] = std::thread(Worker::RunWorker,&firstWorker);
	Threads[1] = std::thread(Worker::RunWorker,&secondWorker);
	Threads[2] = std::thread(Worker::RunWorker,&thirdWorker);
	Threads[3] = std::thread(Worker::RunWorker,&fourthWorker);
	//
	std::vector<Job *> GenerateSegmentJobs;
	GenerateSegments(GenerateSegmentJobs,jobQueue,tree_hypergraph,result);
	//
	GenerateJunctions(GenerateSegmentJobs,jobQueue,tree_hypergraph,result);
	//
	firstWorker.AllowToStop();
	secondWorker.AllowToStop();
	thirdWorker.AllowToStop();
	fourthWorker.AllowToStop();
	//
	for(int i=0;i < 4;i++)
	{
		Threads[i].join();
	}
}

//#define SINGLE_THREADED

void LowPolyMeshGenerator::Generate(TreeHypergraph *tree_hypergraph,MultiMesh* &result)
{
	result = new MultiMesh;
	//
	std::cout << "Number of branches: " << tree_hypergraph->Branches.size() << "\n";
	std::cout << "Number of junctions: " << tree_hypergraph->Junctions.size() << std::endl;
	//
	auto Before = std::chrono::steady_clock::now();
	//
#ifdef SINGLE_THREADED
	GenerateSingleThreaded(tree_hypergraph,*result);
#else
	GenerateMultiThreaded(tree_hypergraph,*result);
#endif
	//
	auto After = std::chrono::steady_clock::now();
	auto Difference = After - Before;
	std::cout << "Mesh generation time: " << std::chrono::duration<double,std::milli>(Difference).count() << std::endl;
}
