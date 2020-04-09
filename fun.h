#pragma once
#include "util.h"

using namespace std;



void Initialize();
void FindPoly();
bool ifnear(Line a, Line b);

/*********************************
* ���ƣ�		Vertex
* ������		ͼ�Ľڵ�
* 
* ������
*	������	id, ��¼ͼ��id
            vector<int> adjacence, ��¼�ڽӽڵ���
*	������	Vertex(int id), �������ɽڵ�
*********************************/
class Vertex
{
public:
    int id = 0;
    vector<int> adjacence;
    Vertex(int id) : id(id) {}
};

/*********************************
* ���ƣ�	    in
* ������	    �ж�b�Ƿ���vector a��	
*   
* ������		vector<int> a , int b
* ����ֵ��	true / false
*********************************/
bool in(vector<int> a, int b);

/*********************************
* ���ƣ�		FindCirStart
* ������		�ݹ������Ƿ񹹳ɶ����
* ������		int length // ��Ҫ���ҵĳ��ȣ��ݹ��յ㣩
        	vector<int> path // �洢·��
* ����ֵ��   int counter;
*********************************/
int FindCirStart(int length, vector<int> path);

/*********************************
* ���ƣ�		FindCirLen
* ������		���ڶ�n���ڵ���������length���ڵ��Ƿ������ɶ����
* 
* ������		int n // �ڵ����
            int length // ��Ҫ�Ķ���γ���
* ����ֵ��	int counter // �������ɵĶ���θ���
*********************************/
int FindCirLen(int n, int length);

/*********************************
* ���ƣ�		FindCir
* ������		ѭ�����ҵ�3 - n�����Ƿ������ɶ����
* 
* ������		int n // ��ĸ���
* ����ֵ��	counter // ����θ���
*********************************/
int FindCir(int ver_size);

extern const int MAX_LINES;
extern vector<Vertex> Graph;
extern vector<Polygon> polys;
