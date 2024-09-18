#pragma once
#include "includeHeader.h"

namespace Won
{
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

