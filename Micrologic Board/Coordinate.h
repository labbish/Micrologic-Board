#pragma once

#include "Utils.h"

template<typename T>
class TemplateCoordinate {
public:
	T x, y;
	inline TemplateCoordinate() :x(0), y(0) {}
	inline TemplateCoordinate(T x, T y) : x(x), y(y) {}
	TemplateCoordinate(const TemplateCoordinate&) = default;
	inline friend bool operator==(TemplateCoordinate c1, TemplateCoordinate c2) {
		return c1.x == c2.x && c1.y == c2.y;
	}
	inline TemplateCoordinate operator=(TemplateCoordinate c) {
		x = c.x;
		y = c.y;
		return *this;
	}
	inline friend TemplateCoordinate operator+(TemplateCoordinate c1, TemplateCoordinate c2) {
		return TemplateCoordinate(c1.x + c2.x, c1.y + c2.y);
	}
	inline friend TemplateCoordinate operator+=(TemplateCoordinate& c1, TemplateCoordinate c2) {
		c1 = c1 + c2;
		return c1;
	}
	inline friend TemplateCoordinate operator-(TemplateCoordinate c) {
		return TemplateCoordinate(-c.x, -c.y);
	}
	inline friend TemplateCoordinate operator-(TemplateCoordinate c1, TemplateCoordinate c2) {
		return TemplateCoordinate(c1.x - c2.x, c1.y - c2.y);
	}
	inline friend TemplateCoordinate operator-=(TemplateCoordinate& c1, TemplateCoordinate c2) {
		c1 = c1 - c2;
		return c1;
	}
	template <typename numT>
	inline friend TemplateCoordinate operator*(TemplateCoordinate c, numT d) {
		return TemplateCoordinate(c.x * d, c.y * d);
	}
	template <typename numT>
	inline friend TemplateCoordinate operator*(numT d, TemplateCoordinate c) {
		return TemplateCoordinate(c.x * d, c.y * d);
	}
	template <typename numT>
	inline friend TemplateCoordinate operator*=(TemplateCoordinate& c1, numT d) {
		c1 = c1 * d;
		return c1;
	}
	template <typename numT>
	inline friend TemplateCoordinate operator/(TemplateCoordinate c, numT d) {
		return TemplateCoordinate(c.x / d, c.y / d);
	}
	template <typename numT>
	inline friend TemplateCoordinate operator/=(TemplateCoordinate& c1, numT d) {
		c1 = c1 / d;
		return c1;
	}
	inline friend TemplateCoordinate xSymmetry(TemplateCoordinate c) {
		return TemplateCoordinate(-c.x, c.y);
	}
	inline friend TemplateCoordinate ySymmetry(TemplateCoordinate c) {
		return TemplateCoordinate(c.x, -c.y);
	}
	inline void print() const {
#ifdef BOARD_DEBUG
		printf("(%lf,%lf)", (double)x, (double)y);
#endif
	}
};

namespace std {
	template <typename T>
	struct hash<TemplateCoordinate<T>> {
		size_t operator()(const TemplateCoordinate<T>& coordinate) const {
			return hash<T>()(coordinate.x) ^ hash<T>()(coordinate.y);
		}
	};
}

using Coordinate = TemplateCoordinate<double>;
using TrueCoordinate = TemplateCoordinate<double>;
using GridCoordinate = TemplateCoordinate<int>;
using ButtonCoordinate = TemplateCoordinate<int>;