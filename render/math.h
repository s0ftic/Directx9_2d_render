#pragma once

#define M_PI 3.14159265

enum typeZero {
	ZERO
};

//to do finish all operator
template <typename F> struct Vec2_tpl
{
	F x, y;
	Vec2_tpl(typeZero) : x(0), y(0) { }
	explicit Vec2_tpl(F f) : x(f), y(f) { }

	Vec2_tpl() { Vec2_tpl<F>(0, 0); }
	Vec2_tpl(F xt, F yt) { x = xt; y = yt; }

	void SetPos(F xt, F yt) { this->x = xt; this->y = yt; }

	__forceinline Vec2_tpl& operator+=(Vec2_tpl vt) { this->x += vt.x; this->y += vt.y; return *this; }
	__forceinline Vec2_tpl& operator-=(Vec2_tpl vt) { this->x += vt.x; this->y += vt.y; return *this; }

	__forceinline Vec2_tpl& operator *= (F f) { x *= f; y *= f; return *this; }
	__forceinline Vec2_tpl& operator /= (F f) { x /= f; y /= f; return *this; }

	__forceinline Vec2_tpl& operator=(Vec2_tpl vt) { this->x = vt.x; this->y = vt.y; return *this; }
	__forceinline bool operator==(Vec2_tpl vt) { return this->x == vt.x && this->y == vt.y; }
};

typedef Vec2_tpl<float> fVec2;
typedef Vec2_tpl<int> iVec2;