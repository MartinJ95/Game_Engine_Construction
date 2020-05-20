#if !defined VECTOR2_HPP
#define VECTOR2_HPP
#include <iostream>
#include <cmath>


class vector2
{
    private:

    public:
    float x{0},y{0};
    vector2();
    vector2(float px, float py);
    vector2(const vector2& other);
    ~vector2();
    float getX() const;
    float getY() const;
    void setX(const float x);
    void setY(const float y);
    float length();
    vector2 normalise();
    void normaliseInPlace();
    inline vector2& operator+=(const vector2& rhs)
    {
        x+=rhs.x;
        y+=rhs.y;
    }
	inline vector2& operator-=(const vector2& rhs)
    {
        x-=rhs.x;
        y-=rhs.y;
    }
	inline vector2& operator=(vector2 rhs)
    {
        std::swap(x, rhs.x);
        std::swap(y, rhs.y);
        return*this;
    }
	inline vector2 operator-()
    {
        vector2 v;
        v.x = -x;
        v.y = -y;
        return v;
    }

    friend std::ostream& operator<<(std::ostream& os, const vector2& v);
    friend std::istream& operator>>(std::istream& is, vector2& v);

};

std::ostream& operator<<(std::ostream& os, const vector2& v);
std::istream& operator>>(std::istream& is, vector2& v);

inline vector2 operator+(vector2 lhs, vector2& rhs)
{
	lhs.x += rhs.x;
	lhs.y += rhs.y;
	return lhs;
}
inline vector2 operator-(vector2 lhs, vector2& rhs)
{
	lhs.x -= rhs.x;
	lhs.y -= rhs.y;
	return lhs;
}
inline vector2 operator*(vector2 lhs, float rhs)
{
	lhs.x *= rhs;
	lhs.y *= rhs;
	return lhs;
}
inline vector2 operator/(vector2 lhs, float rhs)
{
	lhs.x /= rhs;
	lhs.y /= rhs;
	return lhs;
}
inline bool operator==(const vector2& lhs, const vector2& rhs)
{
	if (lhs.x == rhs.x && lhs.y == rhs.y)
	{
		return true;
	}
	else
	{
		return false;
	}
}
inline bool operator!=(const vector2& lhs, const vector2& rhs)
{
	if (lhs.x != rhs.x && lhs.y != rhs.y)
	{
		return true;
	}
	else
	{
		return false;
	}
}


#endif // VECTOR2_HPP
