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
	void AddProduction(char predecessor,const Production_T &production)
	{
		Productions[predecessor] = production;
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
