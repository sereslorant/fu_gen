#ifndef DOL_SYSTEM_H
#define DOL_SYSTEM_H

#include "OL_System.h"

#include <string>

class DOL_Production
{
private:
	std::string Successor;
	//
public:
	//
	const std::string &GetSuccessor() const
	{
		return Successor;
	}
	//
	void SetSuccessor(const std::string &successor)
	{
		Successor = successor;
	}
	//
	DOL_Production()
	{}
	//
	DOL_Production(const std::string &successor)
		:Successor(successor)
	{}
	//
	~DOL_Production()
	{}
};

class DOL_System : public OL_System<DOL_Production>
{
public:
	//
	void ApplyProductions(const std::string &str,std::string &dest)
	{
		dest.clear();

		for(unsigned int i=0;i < str.size();i++)
		{
			char CurrentChar = str[i];

			auto I = Productions.find(CurrentChar);

			if(I != Productions.end())
			{
				dest += I->second.GetSuccessor();
			}
			else
			{
				dest += CurrentChar;
			}
		}
	}
	//
	DOL_System()
	{
		/*
		 * Üres függvénytörzs
		 */
	}
	//
	virtual ~DOL_System() override
	{
		/*
		 * Üres függvénytörzs
		 */
	}
};

#endif // DOL_SYSTEM_H
