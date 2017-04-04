#ifndef TURTLE_BASE_H
#define TURTLE_BASE_H

template<class Scalar_T,class TurtleState_T>
class TurtleBase
{
protected:
	Scalar_T dDist;
	Scalar_T dAngle;
	//
	TurtleState_T InitialState;
	//
public:
	//
	void Set_dAngle(Scalar_T d_angle)
	{
		dAngle = d_angle;
	}
	//
	void Set_dDist(Scalar_T d_dist)
	{
		dDist = d_dist;
	}
	//
	TurtleBase(Scalar_T d_dist,Scalar_T d_angle,const TurtleState_T &initial_state)
		:dDist(d_dist),dAngle(d_angle),InitialState(initial_state)
	{
		/*
		 * Üres függvénytörzs
		 */
	}
	//
	~TurtleBase()
	{
		/*
		 * Üres függvénytörzs
		 */
	}
	//
	/*
	 * Class vége
	 */
};

#endif // TURTLE_BASE_H