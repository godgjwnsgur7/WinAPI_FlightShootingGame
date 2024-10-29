#pragma once

struct Vector2
{
	float x;
	float y;

public:
	bool IsZero()
	{
		if (x == 0.f && y == 0.f)
			return true;
		return false;
	}

	float Length() { return sqrt(x * x + y * y); }

	Vector2& Normalize()
	{
		float fLen = Length();
		
		assert(fLen != 0.f);

		x /= fLen;
		y /= fLen;

		return *this;
	}

public:
	Vector2 operator - ()
	{
		return Vector2(-x, -y);
	}

	Vector2 operator = (POINT _pt)
	{
		x = (float)_pt.x;
		y = (float)_pt.y;
		return *this;
	}

	Vector2 operator + (Vector2 _vOther)
	{
		return Vector2(x + _vOther.x, y + _vOther.y);
	}

	void operator += (Vector2 _vOther)
	{
		x += _vOther.x;
		y += _vOther.y;
	}

	void operator += (float _f)
	{
		x += _f;
		y += _f;
	}

	Vector2 operator - (Vector2 _vOther)
	{
		return Vector2(x - _vOther.x, y - _vOther.y);
	}

	void operator -= (Vector2 _vOther)
	{
		x -= _vOther.x;
		y -= _vOther.y;
	}

	void operator -= (float _f)
	{
		x -= _f;
		y -= _f;
	}

	Vector2 operator * (Vector2 _vOther)
	{
		return Vector2(x * _vOther.x, y * _vOther.y);
	}

	Vector2 operator * (int _i)
	{
		return Vector2(x * (float)_i, y * (float)_i);
	}

	Vector2 operator * (float _f)
	{
		return Vector2(x * _f, y * _f);
	}

	void operator *= (float _f)
	{
		x *= _f;
		y *= _f;
	}

	Vector2 operator / (Vector2 _vOther)
	{
		assert(!(_vOther.x == 0.f || _vOther.y == 0.f));
		return Vector2(x / _vOther.x, y / _vOther.y);
	}

	Vector2 operator / (float _f)
	{
		assert(!(0.f == _f));
		return Vector2(x / _f, y / _f);
	}

	void operator /= (Vector2 _vOther)
	{
		x /= _vOther.x;
		y /= _vOther.y;
	}

	bool operator == (Vector2 _vOther)
	{
		return (x == _vOther.x) && (y == _vOther.y);
	}

	bool operator != (Vector2 _vOther)
	{
		return (x != _vOther.x) || (y != _vOther.y);
	}

public:
	Vector2() : x(0.f), y(0.f) {}
	Vector2(float _x, float _y) : x(_x), y(_y) {}
	Vector2(int _x, int _y) : x((float)_x), y((float)_y) {}
	Vector2(POINT _pt) : x((float)_pt.x), y((float)_pt.y) {}
};