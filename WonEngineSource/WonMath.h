#pragma once
#include "includeHeader.h"

namespace Won
{
#define PI 3.141592f

	template<typename T>
	struct mVector2
	{
		T X;
		T Y;

		mVector2()
		{
			X = 0;
			Y = 0;
		}
		mVector2(T NewX, T NewY)
		{
			X = NewX;
			Y = NewY;
		}

		static float Dot(mVector2& v)
		{
			return X * v.X + Y * v.Y;

		}

		static float Cross(mVector2& v)
		{
			return X * v.Y + Y * v.X;
		}

		mVector2 operator-(mVector2 other)
		{
			return mVector2(X - other.X, Y - other.Y);
		}
		mVector2 operator+(mVector2 other)
		{
			return mVector2(X + other.X, Y + other.Y);
		}
		mVector2 operator/(float Value)
		{
			return mVector2(X / Value, Y / Value);
		}
		mVector2 operator*(float Value)
		{
			return mVector2(X * Value, Y * Value);
		}
		mVector2 operator+=(mVector2 Other)
		{
			return mVector2(X += Other.X, Y += Other.Y);
		}

		float Lenth()
		{
			return sqrtf(X * X + Y * Y);
		}

		mVector2 Nomalize()
		{
			float lenth = Lenth();
			X /= lenth;
			Y /= lenth;

			return *(this);
		}

		mVector2 Rotate(float Degree)
		{
			float radian = (Degree / 180.f) * PI;
		}

	};

	template<typename T>
	struct mVector3
	{
		T X;
		T Y;
		T Z;

		mVector3()
		{
			X = 0;
			Y = 0;
			Z = 0;
		}
		mVector3(T NewX, T NewY, T NewZ)
		{
			X = NewX;
			Y = NewY;
			Z = NewZ;
		}

		bool operator==(mVector3 other)
		{
			if(X == other.X && Y == other.Y && Z == other.Z)
			{
				return true;
			}

			return false;
		}
	};
}

