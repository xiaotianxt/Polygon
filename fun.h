#pragma once
#include "util.h"

using namespace std;



void Initialize();
void FindPoly();
bool ifnear(Line a, Line b);

/*********************************
* 名称：		Vertex
* 描述：		图的节点
* 
* 包含：
*	变量：	id, 记录图的id
            vector<int> adjacence, 记录邻接节点编号
*	函数：	Vertex(int id), 用于生成节点
*********************************/
class Vertex
{
public:
    int id = 0;
    vector<int> adjacence;
    Vertex(int id) : id(id) {}
};

/*********************************
* 名称：	    in
* 描述：	    判断b是否在vector a中	
*   
* 参数：		vector<int> a , int b
* 返回值：	true / false
*********************************/
bool in(vector<int> a, int b);

/*********************************
* 名称：		FindCirStart
* 描述：		递归搜索是否构成多边形
* 参数：		int length // 需要查找的长度（递归终点）
        	vector<int> path // 存储路径
* 返回值：   int counter;
*********************************/
int FindCirStart(int length, vector<int> path);

/*********************************
* 名称：		FindCirLen
* 描述：		用于对n个节点搜索任意length个节点是否可以组成多边形
* 
* 参数：		int n // 节点个数
            int length // 需要的多边形长度
* 返回值：	int counter // 可以生成的多边形个数
*********************************/
int FindCirLen(int n, int length);

/*********************************
* 名称：		FindCir
* 描述：		循环查找第3 - n个点是否可以组成多边形
* 
* 参数：		int n // 点的个数
* 返回值：	counter // 多边形个数
*********************************/
int FindCir(int ver_size);

extern const int MAX_LINES;
extern vector<Vertex> Graph;
extern vector<Polygon> polys;
