#ifndef SOL_SYSTEM_H
#define SOL_SYSTEM_H

#include "OL_System.h"

#include <string>
#include <list>

class SOL_Production
{
private:
	struct Interval
	{
		double LowerBound;
		double UpperBound;
	};
	//
	typedef std::pair<Interval,std::string> SuccessorType;
	std::list<SuccessorType> Successors;
	//
public:
	//
	const std::string &GetSuccessor(double sample);
	//
	void AddNextSuccessor(double upper_bound,const std::string &next_successor);
	//
	SOL_Production()
	{}
	//
	~SOL_Production()
	{}
};

class SOL_System : public OL_System<SOL_Production>
{
public:
	//
	void ApplyProductions(const std::string &str,unsigned int random_seed,std::string &dest);
	//
	SOL_System()
	{
		/*
		 * Üres függvénytörzs
		 */
	}
	//
	virtual ~SOL_System() override
	{
		/*
		 * Üres függvénytörzs
		 */
	}
};

#endif // SOL_SYSTEM_H
