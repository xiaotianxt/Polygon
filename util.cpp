#include "util.h"

const double eps = 1e-8; // double precision

inline int sig(double x) { return (x > eps) - (x < -eps); }

inline bool equal(double a, double b)  // 用于判断两个浮点数是否相等。精度为eps.
{
    if ((a - b) > -eps && (a - b) < eps)
        return true;
    else
        return false;
}

Point::Point(double x_, double y_) // 用于初始化Point
{
    x = x_;
    y = y_;
}

Point::Point() // 用于临时生成一个Point
{
    x = 0;
    y = 0;
}

string Point::Str() // 用于输出点的坐标（调试用）
{
    string temp = "( " + to_string(x) + " , " + to_string(y) + " )";
    return temp;
}

/*
Point对比原则：
    横坐标大的点更大
    横坐标一样的点，纵坐标大的点更大
*/
bool Point::operator<(const Point &other) const
{
    if (this->x < other.x) // 自己横坐标更小
        return true;
    else if (this->x == other.x) //横坐标相等比较纵坐标
    {
        if (this->y < other.y) // 自己纵坐标更小
        {
            return true;
        }
    }
    return false; // 其他情况下，自己都未必小
}

bool Point::operator>(const Point &other) const
{
    if (this->x > other.x)
    {
        return true;
    }
    else if (this->x == other.x)
    {
        if (this->y > other.y)
        {
            return true;
        }
    }
}

bool Point::operator==(const Point &other) const // 判断两坐标是否相等（补偿误差）
{
    return (equal(this->x, other.x) && equal(this->y, other.y));
}

Point Point::operator-(const Point &other) const // 重载减法运算
{
    Point temp(this->x - other.x, this->y - other.y);
    return temp;
}

double Point::operator*(const Point &other) const // 重载点积
{
    return x * other.x + y * other.y;
}

double Point::operator^(const Point &other) const // 重载叉积（可以理解为z方向坐标全为0的向量叉积，结果看做一维）
{
    return x * other.y - y * other.x;
}

Line::Line(double x1, double x2, double y1, double y2) // 用于初始化一条线
{
    from = &Point(x1, y1);
    to = &Point(x2, y2);
}

Line::Line(Point* from_, Point* to_) // 用于初始化一条线，用于判断点是否在多边形内部
{
    from = from_;
    to = to_;
}

string Line::Str() // 用于打印某点坐标（调试用）
{
    string temp = "from " + from->Str() + " to " + to->Str();
    return temp;
}

void Line::Swap() // 用于交换from和to
{
    Point* temp = from;
    from = to;
    to = temp;
    return;
}

Polygon::Polygon(vector<Line> lines_) // 多边形初始化（并判断多边形类型）
{
    lines = lines_;
    SortLines();
}

bool Polygon::CheckCross(Line a, Line b) const
{
    for (int i = 0; i < lines.size(); i++)
    {
        for (int j = i + 1; j < lines.size(); j++)
        {
            double d1, d2, d3, d4;
            d1 = (lines[i].to - lines[i].from) ^ (lines[j].from - lines[i].from); // 
            d2 = (lines[i].to - lines[i].from) ^ (lines[j].to - lines[i].from);
            d3 = (lines[j].to - lines[j].from) ^ (lines[i].from - lines[j].from);
            d4 = (lines[j].to - lines[j].from) ^ (lines[i].to - lines[i].from);
            
            
        }
    }
}

void Polygon::SortLines()
// 用于寻找端点
{
    for (int i = 0; i < lines.size(); i++)
    {
    }
}