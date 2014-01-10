#ifndef __BASIC_H
#define __BASIC_H

#include <iostream>

class point
{
public:
	inline point(const float _x = 0, const float _y = 0, const float _z = 0);
	inline void setX(const float v) {_x = v;}
	inline void setY(const float v) {_y = v;}
	inline void setZ(const float v) {_z = v;}
	inline void set(const float _x = 0, const float _y = 0, \
			const float _z = 0);
	inline float x(void) const {return _x;}
	inline float y(void) const {return _y;}
	inline float z(void) const {return _z;}
	inline class point& operator+=(const class point& p);
	inline class point& operator-=(const class point& p);

private:
	float _x, _y, _z;
};

inline point::point(const float _x, const float _y, const float _z)
{
	set(_x, _y, _z);
}

inline void point::set(const float _x, const float _y, const float _z)
{
	this->_x = _x;
	this->_y = _y;
	this->_z = _z;
}

inline class point& point::operator+=(const class point& p)
{
	set(_x + p.x(), _y + p.y(), _z + p.z());
	return *this;
}

inline class point& point::operator-=(const class point& p)
{
	set(_x - p.x(), _y - p.y(), _z - p.z());
	return *this;
}

static inline class point operator+(const class point& a, const class point& b)
{
	class point p(a);
	p += b;
	return p;
}

static inline class point operator-(const class point& a, const class point& b)
{
	class point p(a);
	p -= b;
	return p;
}

static inline std::ostream& operator<<(std::ostream &out, const class point& p)
{
	out << "Point: <" << p.x() << ", " << p.y() << ", " << p.z() << '>' << std::endl;
	return out;
}

class angle
{
public:
	inline angle(const float _x = 0, const float _y = 0, \
			const float _z = 0);
	inline void setX(const float v) {_x = v;}
	inline void setY(const float v) {_y = v;}
	inline void setZ(const float v) {_z = v;}
	inline void set(const float _x = 0, const float _y = 0, \
			const float _z = 0);
	inline float x(void) const {return _x;}
	inline float y(void) const {return _y;}
	inline float z(void) const {return _z;}

private:
	float _x, _y, _z;
};

inline angle::angle(const float _x, const float _y, const float _z)
{
	set(_x, _y, _z);
}

inline void angle::set(const float _x, const float _y, \
		const float _z)
{
	this->_x = _x;
	this->_y = _y;
	this->_z = _z;
}

#endif
