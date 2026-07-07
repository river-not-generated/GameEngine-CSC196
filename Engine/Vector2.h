#pragma once

#include <cmath>

namespace nu
{
	struct Vector2 {
		float x, y;

		Vector2() = default;
		Vector2(float x, float y) : x{ x }, y{ y } {};
		Vector2(float v) : x{ v }, y{ v } {};

		// a^2 + b^2 = c^2
		float LengthSqr() const {
			return pow(x, 2) + pow(y, 2);
		}

		// returns c
		float Length() const {
			return std::sqrt(LengthSqr());
		}

		Vector2 operator + (const Vector2& v) const {
			return Vector2{ this->x + v.x, this->y + v.y };
		}
		Vector2 operator - (const Vector2& v) const {
			return Vector2{ this->x - v.x, this->y - v.y };
		}
		Vector2 operator * (const Vector2& v) const {
			return Vector2{ this->x * v.x, this->y * v.y };
		}
		Vector2 operator / (const Vector2& v) const {
			return Vector2{ this->x / v.x, this->y / v.y };
		}

		Vector2 operator += (const Vector2& v) {
			this->x += v.x;
			this->y += v.y;
			return *this;
		}
		Vector2 operator -= (const Vector2& v) {
			this->x -= v.x;
			this->y -= v.y;
			return *this;
		}
		Vector2 operator *= (const Vector2& v) {
			this->x *= v.x;
			this->y *= v.y;
			return *this;
		}
		Vector2 operator /= (const Vector2& v) {
			this->x /= v.x;
			this->y /= v.y;
			return *this;
		}

		Vector2 operator + (float num) const {
			return Vector2{ this->x + num, this->y + num };
		}
		Vector2 operator - (float num) const {
			return Vector2{ this->x - num, this->y - num };
		}
		Vector2 operator * (float num) const {
			return Vector2{ this->x * num, this->y * num };
		}
		Vector2 operator / (float num) const {
			return Vector2{ this->x / num, this->y / num };
		}

		Vector2 operator += (float num) {
			this->x += num;
			this->y += num;
			return *this;
		}
		Vector2 operator -= (float num) {
			this->x -= num;
			this->y -= num;
			return *this;
		}
		Vector2 operator *= (float num) {
			this->x *= num;
			this->y *= num;
			return *this;
		}
		Vector2 operator /= (float num) {
			this->x /= num;
			this->y /= num;
			return *this;
		}
	};
}