
#include "SOL_System.h"

#include <random>

const std::string &SOL_Production::GetSuccessor(double sample)
{
	for(SuccessorType &Successor : Successors)
	{
		Interval &SuccessorInterval = Successor.first;
		if(sample >= SuccessorInterval.LowerBound && sample <= SuccessorInterval.UpperBound)
		{
			return Successor.second;
		}
	}
	//
	return Successors.back().second;
}

void SOL_Production::AddNextSuccessor(double upper_bound,const std::string &next_successor)
{
	double LowerBound = 0.0;
	if(Successors.size() != 0)
	{
		LowerBound = Successors.back().first.UpperBound;
	}
	double UpperBound = upper_bound;
	if(UpperBound >= 1.0)
	{
		UpperBound = 1.0;
	}
	Interval SuccessorInterval = {LowerBound,UpperBound};
	Successors.push_back({SuccessorInterval,next_successor});
}

void SOL_System::ApplyProductions(const std::string &str,unsigned int random_seed,std::string &dest)
{
	std::default_random_engine RandomEngine(random_seed);
	std::uniform_real_distribution<double> UniformDistribution(0.0,1.0);
	dest.clear();
	//
	for(unsigned int i=0;i < str.size();i++)
	{
		char CurrentChar = str[i];
		//
		auto I = Productions.find(CurrentChar);
		//
		if(I != Productions.end())
		{
			float sample = UniformDistribution(RandomEngine);
			dest += I->second.GetSuccessor(sample);
		}
		else
		{
			dest += CurrentChar;
		}
	}
}
