#pragma once
#include "includeHeader.h"

namespace Won
{
	struct FVector2
	{
		float X;
		float Y;

		FVector2()
		{
			X = 0.0f;
			Y = 0.0f;
		}
		FVector2(float NewX, float NewY)
		{
			X = NewX;
			Y = NewY;
		}

		FVector2 operator-(FVector2 other)
		{
			return FVector2(X - other.X, Y - other.Y);
		}
		FVector2 operator+(FVector2 other)
		{
			return FVector2(X + other.X, Y + other.Y);
		}
		FVector2 operator/(float Value)
		{
			return FVector2(X / Value, Y / Value);
		}

	};

	struct CVector3
	{
		int8_t X;
		int8_t Y;
		int8_t Z;

		static CVector3 Zero;

		CVector3()
		{
			X = 0;
			Y = 0;
			Z = 0;
		}
		CVector3(int8_t NewX, int8_t NewY, int8_t NewZ)
		{
			X = NewX;
			Y = NewY;
			Z = NewZ;
		}

		bool operator==(CVector3 other)
		{
			if(X == other.X && Y == other.Y && Z == other.Z)
			{
				return true;
			}

			return false;
		}
	};
}

