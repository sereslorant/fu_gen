
#include "CatmullRom.h"

vec4 Hermite(const vec4 &p0,const vec4 &p1,const vec4 &v0,const vec4 &v1,float t0,float t1,float t)
{
	vec4 a0 = p0;
	vec4 a1 = v0;
	vec4 a2 = (3.0f*(p1-p0)/((float)pow(t1-t0,2))) - ((v1+2.0f*v0)/((float)(t1-t0)));
	vec4 a3 = (2.0f*(p0-p1)/((float)pow(t1-t0,3))) + ((v1+v0)/((float)pow(t1-t0,2)));

	return a0 + a1*(t-t0) + a2*((float)pow(t-t0,2)) + a3*((float)pow(t-t0,3));
}

vec4 HermiteDerivative(const vec4 &p0,const vec4 &p1,const vec4 &v0,const vec4 &v1,float t0,float t1,float t)
{
	vec4 a1 = v0;
	vec4 a2 = (3.0f*(p1-p0)/((float)pow(t1-t0,2))) - ((v1+2.0f*v0)/((float)(t1-t0)));
	vec4 a3 = (2.0f*(p0-p1)/((float)pow(t1-t0,3))) + ((v1+v0)/((float)pow(t1-t0,2)));

	return a1 + 2.0f*a2*(t-t0) + 3.0f*a3*((float)pow(t-t0,2));
}

vec4 HermiteSecondDerivative(const vec4 &p0,const vec4 &p1,const vec4 &v0,const vec4 &v1,float t0,float t1,float t)
{
	vec4 a2 = (3.0f*(p1-p0)/((float)pow(t1-t0,2))) - ((v1+2.0f*v0)/((float)(t1-t0)));
	vec4 a3 = (2.0f*(p0-p1)/((float)pow(t1-t0,3))) + ((v1+v0)/((float)pow(t1-t0,2)));

	return 2.0f*a2 + 6.0f*a3*(t-t0);
}

vec4 AverageVelocity(const vec4 &p0,const vec4 &p1,float t0,float t1)
{
	return (p1-p0)/(t1-t0);
}

int sgn(float p)
{
	if(p > 0.0)
		{return  1;}

	if(p < 0.0)
		{return -1;}

	return 0;
}

bool BisectionMethod(const ICurve &curve,float t_begin,float t_end,float dt_min,const IScalarField &scalar_field,std::list<float> &roots)
{
	vec4 p0 = curve.GetPoint(t_begin);
	vec4 p1 = curve.GetPoint(t_end);

	float s_p0 = scalar_field.GetValue(p0);
	float s_p1 = scalar_field.GetValue(p1);

	int s_p0_sgn = sgn(s_p0);
	int s_p1_sgn = sgn(s_p1);

	if((t_end - t_begin) < dt_min)
	{
		if(s_p0_sgn == s_p1_sgn)
		{
			return false;
		}
		else
		{
			roots.push_back((t_begin + t_end) / 2.0);
			return true;
		}
	}

	bool RootFound = false;

	if(s_p0_sgn != s_p1_sgn)
	{
		float t_mid = (t_begin + t_end) / 2.0;
		vec4 p_mid = curve.GetPoint(t_mid);

		float s_p_mid = scalar_field.GetValue(p_mid);
		int s_p_mid_sgn = sgn(s_p_mid);

		int Szercsy	= s_p0_sgn * s_p_mid;

		if(Szercsy == 0)
		{
			roots.push_back(t_mid);

			RootFound = true;
		}

		if(Szercsy < 0)
		{
			bool Ret = BisectionMethod(curve,t_begin,t_mid,dt_min,scalar_field,roots);
			if(Ret == true)
			{
				RootFound = true;
			}
		}

		if(Szercsy > 0)
		{
			bool Ret = BisectionMethod(curve,t_mid,t_end,dt_min,scalar_field,roots);
			if(Ret == true)
			{
				RootFound = true;
			}
		}
	}
	/*
	 * Mivel most elég speciális esetekben használjuk, ezért az else ágat nem kezeljük.
	 */

	return RootFound;
}
