
#pragma once
#include <iostream>
#include <vector>
#include <assert.h>

using namespace std;

class Point {
    double x, y;
    Point(double x, double y)
    {
        this->x = x;
        this->y = y;
    }
};

class Line
{
    Point from, to;

    Line(double x1, double x2, double y1, double y2) // 默认将
    {
        this->from(x1, x2);
        this->to(y1, y2);   
    }

};

class Polygon
{
public:
    vector<int[2]> lines;

    Polygon(vector<int>, vector<int>);
};

Polygon::Polygon(vector<int> x, vector<int> y)
{
    assert(x.size() == y.size()); // 应当在创建之前就明确两者体积相同
    for (int i = 0;i < x.size(); i++)
    {
        
    }
}