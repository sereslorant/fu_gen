#ifndef GLMATH_H
#define GLMATH_H

#include <cmath>

template<class Scalar_T>
struct mat4_t {
	Scalar_T m[4][4];
public:
	mat4_t() {}
	mat4_t(Scalar_T m00, Scalar_T m01, Scalar_T m02, Scalar_T m03,
		Scalar_T m10, Scalar_T m11, Scalar_T m12, Scalar_T m13,
		Scalar_T m20, Scalar_T m21, Scalar_T m22, Scalar_T m23,
		Scalar_T m30, Scalar_T m31, Scalar_T m32, Scalar_T m33) {
		m[0][0] = m00; m[0][1] = m01; m[0][2] = m02; m[0][3] = m03;
		m[1][0] = m10; m[1][1] = m11; m[1][2] = m12; m[1][3] = m13;
		m[2][0] = m20; m[2][1] = m21; m[2][2] = m22; m[2][3] = m23;
		m[3][0] = m30; m[3][1] = m31; m[3][2] = m32; m[3][3] = m33;
	}
	//
	mat4_t operator*(const mat4_t& right)
	{
		mat4_t result;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				result.m[i][j] = 0;
				for (int k = 0; k < 4; k++)
				{
					result.m[i][j] += m[i][k] * right.m[k][j];
				}
			}
		}
		return result;
	}
	operator Scalar_T*() { return &m[0][0]; }
};

template<class Scalar_T>
struct vec4_t
{
	Scalar_T v[4];

	template<class OtherScalar_T>
	vec4_t(const vec4_t<OtherScalar_T> &other)
	{
		v[0] = other[0]; v[1] = other[1]; v[2] = other[2]; v[3] = other[3];
	}
	
	vec4_t(Scalar_T x = 0, Scalar_T y = 0, Scalar_T z = 0, Scalar_T w = 1)
	{
		v[0] = x; v[1] = y; v[2] = z; v[3] = w;
	}
	
	Scalar_T &operator[](unsigned int i)
	{
		return v[i];
	}
	
	const Scalar_T &operator[](unsigned int i) const
	{
		return v[i];
	}

	vec4_t<Scalar_T> operator*(const mat4_t<Scalar_T> &mat) const
	{
		vec4_t<Scalar_T> result;
		for (int j = 0; j < 4; j++)
		{
			result.v[j] = 0;
			for (int i = 0; i < 4; i++)
			{
				result.v[j] += v[i] * mat.m[i][j];
			}
		}
		return result;
	}

	vec4_t<Scalar_T> operator+(const vec4_t<Scalar_T> rhs) const
	{
		vec4_t<Scalar_T> tmp;
		tmp.v[0] = v[0] + rhs.v[0];
		tmp.v[1] = v[1] + rhs.v[1];
		tmp.v[2] = v[2] + rhs.v[2];
		return tmp;
	}
	
	vec4_t<Scalar_T> operator-(const vec4_t<Scalar_T> rhs) const
	{
		vec4_t<Scalar_T> tmp;
		tmp.v[0] = v[0] - rhs.v[0];
		tmp.v[1] = v[1] - rhs.v[1];
		tmp.v[2] = v[2] - rhs.v[2];
		return tmp;
	}
	
	template<class OtherScalar_T>
	vec4_t<Scalar_T> operator*(OtherScalar_T rhs) const
	{
		vec4_t<Scalar_T> tmp;
		tmp.v[0] = v[0] * rhs;
		tmp.v[1] = v[1] * rhs;
		tmp.v[2] = v[2] * rhs;
		return tmp;
	}
	
	template<class OtherScalar_T>
	vec4_t<Scalar_T> operator/(OtherScalar_T rhs) const
	{
		vec4_t<Scalar_T> tmp;
		tmp.v[0] = v[0] / rhs;
		tmp.v[1] = v[1] / rhs;
		tmp.v[2] = v[2] / rhs;
		return tmp;
	}

	vec4_t<Scalar_T> &operator+=(const vec4_t<Scalar_T> rhs)
	{
		
		v[0] += rhs.v[0];
		v[1] += rhs.v[1];
		v[2] += rhs.v[2];
		return *this;
	}
	
	vec4_t<Scalar_T> &operator-=(const vec4_t<Scalar_T> rhs)
	{
		vec4_t<Scalar_T> tmp;
		v[0] -= rhs.v[0];
		v[1] -= rhs.v[1];
		v[2] -= rhs.v[2];
		return *this;
	}
	
	template<class OtherScalar_T>
	vec4_t<Scalar_T> &operator*=(OtherScalar_T rhs)
	{
		v[0] *= rhs;
		v[1] *= rhs;
		v[2] *= rhs;
		return *this;
	}
	
	template<class OtherScalar_T>
	vec4_t<Scalar_T> &operator/=(OtherScalar_T rhs)
	{
		v[0] /= rhs;
		v[1] /= rhs;
		v[2] /= rhs;
		return *this;
	}
	
	template<class OtherScalar_T>
	vec4_t<Scalar_T> &operator=(const vec4_t<OtherScalar_T> &other)
	{
		v[0] = other[0];
		v[1] = other[1];
		v[2] = other[2];
		return *this;
	}
};

template<class Scalar_T,class OtherScalar_T>
vec4_t<Scalar_T> operator*(OtherScalar_T lhs,const vec4_t<Scalar_T> &rhs)
{
	return rhs * lhs;
}

template<class Scalar_T>
Scalar_T dot(const vec4_t<Scalar_T> lhs,const vec4_t<Scalar_T> rhs)
{
	return lhs[0]*rhs[0] + lhs[1]*rhs[1] + lhs[2]*rhs[2];
}

template<class Scalar_T>
Scalar_T length(const vec4_t<Scalar_T> &v)
{
	return std::sqrt(dot(v,v));
}

template<class Scalar_T>
vec4_t<Scalar_T> normalize(const vec4_t<Scalar_T> &v)
{
	Scalar_T len = length(v);
	vec4_t<Scalar_T> retval = v;
	if(len > 0.0)
	{
		retval[0] /= len;
		retval[1] /= len;
		retval[2] /= len;
	}
	return retval;
}

template<class Scalar_T>
vec4_t<Scalar_T> cross(const vec4_t<Scalar_T> &a,const vec4_t<Scalar_T> &b)
{
	vec4_t<Scalar_T> retval;  
	retval[0] = a[1]*b[2] - a[2]*b[1];
	retval[1] = a[2]*b[0] - a[0]*b[2];
	retval[2] = a[0]*b[1] - a[1]*b[0];
	retval[3] = 1.0;
	return retval;
}

template<class Scalar_T>
vec4_t<Scalar_T> rotate(const vec4_t<Scalar_T> &axis,Scalar_T angle,const vec4_t<Scalar_T> &rotated_vector)
{
	Scalar_T cos_angle = std::cos(angle);
	Scalar_T sin_angle = std::sin(angle);
	return	rotated_vector * cos_angle +
			cross(axis,rotated_vector) * sin_angle +
			axis * dot(axis,rotated_vector) * (1.0 - cos_angle);
}

typedef mat4_t<float> mat4;
typedef vec4_t<float> vec4;

typedef mat4_t<double> dmat4;
typedef vec4_t<double> dvec4;

#endif // GLMATH_H
