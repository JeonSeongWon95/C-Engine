#pragma once
#include "includeHeader.h"

namespace Won
{
#define PI 3.141592f

	template<typename T>
	struct sVector2
	{
		T X;
		T Y;

		sVector2()
		{
			X = 0;
			Y = 0;
		}
		sVector2(T NewX, T NewY)
		{
			X = NewX;
			Y = NewY;
		}

		static float Dot(sVector2& v)
		{
			return X * v.X + Y * v.Y;

		}

		static float Cross(sVector2& v)
		{
			return X * v.Y + Y * v.X;
		}
		sVector2 operator-()
		{
			return sVector2(-X,-Y);
		}
		bool operator<=(sVector2 other)
		{
			return (X <= other.X && Y <= other.Y);
		}
		sVector2 operator-(sVector2 other)
		{
			return sVector2(X - other.X, Y - other.Y);
		}
		sVector2 operator+(sVector2 other)
		{
			return sVector2(X + other.X, Y + other.Y);
		}
		sVector2 operator/(float Value)
		{
			return sVector2(X / Value, Y / Value);
		}
		sVector2 operator*(float Value)
		{
			return sVector2(X * Value, Y * Value);
		}
		sVector2 operator+=(sVector2 Other)
		{
			return sVector2(X += Other.X, Y += Other.Y);
		}

		float Lenth()
		{
			return sqrtf(X * X + Y * Y);
		}
		sVector2 Nomalize()
		{
			float lenth = Lenth();
			X /= lenth;
			Y /= lenth;

			return *(this);
		}
		sVector2 Rotate(float Degree)
		{
			float radian = (Degree / 180.f) * PI;
		}

	};

	template<typename T>
	struct sVector3
	{
		T X;
		T Y;
		T Z;

		sVector3()
		{
			X = 0;
			Y = 0;
			Z = 0;
		}
		sVector3(T NewX, T NewY, T NewZ)
		{
			X = NewX;
			Y = NewY;
			Z = NewZ;
		}

		bool operator==(sVector3 other)
		{
			if(X == other.X && Y == other.Y && Z == other.Z)
			{
				return true;
			}

			return false;
		}
	};
}

