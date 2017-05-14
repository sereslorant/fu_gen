#ifndef OL_SYSTEM_H
#define OL_SYSTEM_H

#include <map>

template<class Production_T>
class OL_System
{
protected:
	std::map<char,Production_T> Productions;
	//
public:
	//
	Production_T &GetProduction(char predecessor)
	{
		return Productions[predecessor];
	}
	//
	void AddProduction(char predecessor,const Production_T &production)
	{
		Productions[predecessor] = production;
	}
	//
	bool HasProduction(char predecessor)
	{
		return Productions.find(predecessor) != Productions.end();
	}
	//
	void DeleteProduction(char predecessor)
	{
		Productions.erase(predecessor);
	}
	//
	const std::map<char,Production_T> &GetProductions() const
	{
		return Productions;
	}
	//
	OL_System()
	{
		/*
		 * Üres függvénytörzs
		 */
	}
	//
	virtual ~OL_System()
	{
		/*
		 * Üres függvénytörzs
		 */
	}
};

#endif // OL_SYSTEM_H
