#if !defined VECTOR2_HPP
#define VECTOR2_HPP
#include <iostream>


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
    vector2& operator+=(const vector2& rhs)
    {
        x+=rhs.x;
        y+=rhs.y;
    }
    vector2& operator-=(const vector2& rhs)
    {
        x-=rhs.x;
        y-=rhs.y;
    }
    vector2& operator=(vector2 rhs)
    {
        std::swap(x, rhs.x);
        std::swap(y, rhs.y);
        return*this;
    }
    vector2 operator-()
    {
        vector2 v;
        v.x = -x;
        v.y = -y;
        return v;
    }
    friend std::ostream& operator<<(std::ostream os, const vector2& v);
    friend std::istream& operator>>(std::istream& is, vector2& v);
};

std::ostream& operator<<(std::ostream os, const vector2& v);
std::istream& operator>>(std::istream& is, vector2& v);

inline vector2 operator+(vector2 lhs, vector2& rhs);
inline vector2 operator-(vector2 lhs, vector2& rhs);
inline vector2 operator*(vector2 lhs, float rhs);
inline vector2 operator/(vector2 lhs, float rhs);
inline bool operator==(const vector2& lhs, const vector2& rhs);
inline bool operator!=(const vector2& lhs, const vector2& rhs);


#endif // VECTOR2_HPP
