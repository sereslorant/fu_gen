#ifndef I_CURVE_H
#define I_CURVE_H

#include <glmath.hpp>

class ICurve
{
public:

	virtual vec4 GetPoint(float t) const = 0;
	virtual vec4 GetDerivative(float t) const = 0;
	virtual vec4 GetSecondDerivative(float t) const = 0;

	virtual vec4 GetSegment(float t,float dt) const = 0;

	static void GetFrenetFrame(const ICurve &curve,float t,vec4 *i,vec4 *j,vec4 *k,bool normalize_vectors = false)
	{
		if(normalize_vectors)
		{
			vec4 SecondDerivative = curve.GetSecondDerivative(t);

			*j = normalize(curve.GetDerivative(t));
			*i = normalize(cross(SecondDerivative,*j));
			*k = normalize(cross(*i,*j));
		}
		else
		{
			vec4 SecondDerivative = curve.GetSecondDerivative(t);

			*j = curve.GetDerivative(t);
			*i = cross(SecondDerivative,*j);
			*k = cross(*i,*j);
		}
	}

	static void GetExplicitUpFrame(const ICurve &curve,const vec4 &up,float t,float dt,vec4 *i,vec4 *j,vec4 *k,bool normalize_vectors = false)
	{
		if(normalize_vectors)
		{
			*j = normalize(curve.GetDerivative(t));
			if(length(*j) < 1e-2)
			{
				*j = normalize(curve.GetSegment(t,dt));
			}
			*i = normalize(cross(up,*j));
			*k = normalize(cross(*i,*j));
		}
		else
		{
			*j = curve.GetDerivative(t);
			*i = cross(up,*j);
			*k = cross(*i,*j);
		}
	}

	ICurve(){}
	virtual ~ICurve(){}
};

#endif // I_CURVE_H