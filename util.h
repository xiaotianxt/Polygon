#pragma once
#include <iostream>
#include <vector>
#include <assert.h>
#include <algorithm>
#include <stack>
#include <cstring>
#include <string>
#include <cstdio>
#include <time.h>
#include <iomanip>
#include <conio.h>
#include <windows.h>
#include <fstream>

using namespace std;

bool equal(double a, double b);

class Point //可以叉乘和点乘
{
public:
    double x, y;
    Point(double x_, double y_);
    Point();
    string Str(); // 打印该点的坐标（调试用）
    bool operator<(const Point &) const; // 用于排列坐标（好像没啥用了
                                         // TODO:
    bool operator>(const Point &) const;
    bool operator==(const Point &) const; // 判断相等

    Point operator-(const Point &) const;  // 减法
    double operator*(const Point &)const;  // 点积
    double operator^(const Point &) const; // 二维叉积
};

class Line
{
public:
    Point* from, *to; // 因为多边形没有风向，规定生成的点从小指向大（当然如果输入的点坐标一样不能改称为边，应当报错）
    Line(double, double, double, double); // 初始化
    Line(Point*, Point*);
    string Str(); // debug用，打印线
    void Swap(); // 交换from和to
};

class Polygon
{
    vector<Line> lines;

public:
    Polygon(vector<Line> lines_);
    void SortLines();
    bool CheckCross(Line, Line) const;
};


