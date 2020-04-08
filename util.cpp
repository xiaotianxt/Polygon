#include "util.h"

const double eps = 1e-8; // double precision

inline int sig(double x) { return (x > eps) - (x < -eps); }

inline bool equal(double a, double b) // �����ж������������Ƿ���ȡ�����Ϊeps.
{
    if ((a - b) > -eps && (a - b) < eps)
        return true;
    else
        return false;
}

Point::Point(double x_, double y_) // ���ڳ�ʼ��Point
{
    x = x_;
    y = y_;
}

Point::Point(string x_, string y_)
{
    x = atof(x_.c_str());
    y = atof(y_.c_str());
}

Point::Point() // ������ʱ����һ��Point
{
    x = 0;
    y = 0;
}

string Point::Str() // �������������꣨�����ã�
{
    string temp = "( " + to_string(x) + " , " + to_string(y) + " )";
    return temp;
}

/*
Point�Ա�ԭ��
    �������ĵ����
    ������һ���ĵ㣬�������ĵ����
*/
bool Point::operator<(const Point &other) const
{
    if (this->x < other.x) // �Լ��������С
        return true;
    else if (this->x == other.x) //��������ȱȽ�������
    {
        if (this->y < other.y) // �Լ��������С
        {
            return true;
        }
    }
    return false; // ��������£��Լ���δ��С
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
    return false;
}

bool Point::operator==(const Point &other) const // �ж��������Ƿ���ȣ�������
{
    return (equal(this->x, other.x) && equal(this->y, other.y));
}

Point Point::operator-(const Point &other) const // ���ؼ�������
{
    Point temp(this->x - other.x, this->y - other.y);
    return temp;
}

double Point::operator*(const Point &other) const // ���ص��
{
    return x * other.x + y * other.y;
}

double Point::operator^(const Point &other) const // ���ز�����������Ϊz��������ȫΪ0������������������һά��
{
    return x * other.y - y * other.x;
}

Line::Line(double x1, double y1, double x2, double y2) // ���ڳ�ʼ��һ����
{
    Point *from_ = new Point(x1, y1);
    Point *to_ = new Point(x2, y2);

    from = from_;
    to = to_;
}

Line::Line(string x1, string y1, string x2, string y2)
{
    Point *from_ = new Point(atof(x1.c_str()), atof(y1.c_str()));
    Point *to_ = new Point(atof(x2.c_str()), atof(y2.c_str()));

    from = from_;
    to = to_;
}

Line::Line(Point from_, Point to_) // ���ڳ�ʼ��һ���ߣ������жϵ��Ƿ��ڶ�����ڲ�
{
    from = &from_;
    to = &to_;
}

string Line::Str() // ���ڴ�ӡĳ�����꣨�����ã�
{
    string temp = from->Str() + " --> " + to->Str();
    return temp;
}

void Line::Swap() // ���ڽ���from��to
{
    Point *temp = from;
    from = to;
    to = temp;
    return;
}

double Line::operator^(const Line &b) const
{
    return (*(this->to) - *(this->from)) ^ (*b.to - *b.from);
}

Polygon::Polygon(vector<Line> *lines_) // ����γ�ʼ�������ж϶�������ͣ�
{
    lines = *lines_;
}

Polygon::Polygon()
{
    NULL;
}

bool Polygon::sortlines()
// ����Ѱ�Ҷ˵�
{
    size_t lines_index = 0;                                              // �����߶�����
    Point *last = NULL;                                                  //
    bool flag = 0;                                                       // ���ڱ���Ƿ����ƥ��
    for (lines_index = 0; lines_index + 1 < lines.size(); lines_index++) // ֻҪ
    {
        last = lines[lines_index].to; // ��lines[0].to��Ϊ���鿴�Ƿ���Խ������ߴ�����
        flag = 0;
        for (int target = lines_index + 1; target < lines.size(); target++) // ע��lines_index��ֹ�������ڶ�λ
        {
            if (*(lines[target].from) == *last) // ���ƥ�䵽��from
            {
                swap(lines[target], lines[lines_index + 1]); // ��target��Ӧ���ߺ�lines_index��һ������
                flag = 1;
            }
            else if (*(lines[target].to) == *last) // ���to��lastƥ����
            {
                lines[target].Swap();                        // ������Ҫ����from��to
                swap(lines[target], lines[lines_index + 1]); // ��ν������߷���lines_index��һ��
                flag = 1;
            }
        }
        if (!flag) // δ���ƥ�䣬˵���������ݺܿ�������
        {
            cout << "�������Ķ�����ļ������Ƿ����󣡣�" << endl;
            return false;
        }
    }
    assert(*(lines[0].from) == *(lines.back().to)); // Ӧ����β���
    return true;
}

bool Polygon::checkcross()
{
    if (lines.size() < 3) // ��ʱ��������ɶ����
    {
        cout << "ֻ������" << lines.size() << "���ߣ��޷����ɶ����" << endl;
        return false;
    }
    else
    {
        for (size_t i = 0; i + 2 < lines.size(); i++) // �������жԱ�
        {
            if (CheckCross(lines[i], lines[i + 2])) // ����н���
            {
                cout << "������ıߣ�" << lines[i].Str() << "��" << lines[i + 2].Str() << "֮���н���" << endl;
                return false;
            }
            else
                NULL;
        }
    }
    return true;
}

void Polygon::findbound() // ���Ҷ���ε�������Σ���ʱÿ���ߵ�����from���ñ��������е�
{
    bound_yu = lines[0].from->y;  // yu, yd ��Ӧ�Ͻ��½�
    bound_yd = lines[0].from->y;
    bound_xl = lines[0].from->x; // xl, xr ��Ӧ����ҽ�
    bound_xr = lines[0].from->x;
    for (size_t i = 0; i < lines.size(); i++) // �������бߣ�Ѱ�����ֵ
    {
        if (bound_yu < lines[i].from->y)
            bound_yu = lines[i].from->y;
        if (bound_yd > lines[i].from->y)
            bound_yd = lines[i].from->y;
        if (bound_xl > lines[i].from->x)
            bound_xl = lines[i].from->x;
        if (bound_xr < lines[i].from->x)
            bound_xr = lines[i].from->x;
    }
}

bool Polygon::checkconv() // ���ԭ�򣬴ӵ�һ���߿�ʼ���鿴��һ���ߺʹαߵĲ���Ƿ�ͬ��
{
    double temp = lines.back() ^ lines[0]; // �����һ���͵�һ�������
    for (size_t i = 0; i + 1 < lines.size(); i++)
    {
        if (temp * (lines[i] ^ lines[i + 1]) < 0) // ��������ţ�˵����͹�����
        {
            return false;
        }
    }
    return true;
}

bool Polygon::in(Point point) // �����Ƿ��ڶ�����ڲ�
{
    /***************** ����Ƿ��ڶ������ ******************/
    for (size_t i = 0; i < lines.size(); i++)
    {
        if (equal(point.x, lines[i].from->x) || equal(point.y, lines[i].from->y)) // ������ڽ��㴦
        {
            cout << "���ڱ���" << endl;
            return false;
        }
        else
        {
            double d1 = (point - *lines[i].from) ^ (*lines[i].to - *lines[i].from); // ��from��������point��ʸ�� x ��to��ʸ��
            double d2 = (point - *lines[i].from) ^ (*lines[i].from - *lines[i].to); // ��to��������point��ʸ�� x ��from��ʸ��
            cout << d1 << ' ' << d2 << endl;
            if (equal(d1, 0.0) && equal(d2, 0.0)) // ˵���ڱ�*���ڵ�ֱ��*��
            {
                double tempx = (point.x - lines[i].from->x) * (point.x - lines[i].to->x);
                double tempy = (point.y - lines[i].from->y) * (point.y - lines[i].to->y);
                if (tempx > 0 || tempy > 0) // ��ͬһ��ֱ���ϣ����ڸ��߶�֮��
                {
                    // ע�����͹����Σ���ʱ�Ѿ����Ե��ڶ�����⣬���Ƕ��ڰ�����Σ�����Ҫ�ж��Ƿ��ܴ���һ���������ҵ�����
                    Line radial(*lines[i].from, point);
                    for (size_t j = 0; j < lines.size(); j++)
                    {
                        if (i == j) continue;
                        
                        if (CheckCross(radial, lines[j])) // ����һ���������жϺ������ı��Ƿ��н���
                        {
                            cout << "���ڶ�����ڲ�" << endl;
                            return true;
                        }
                    }
                    // �����෴������û�н���ģ�˵�����ⲿ
                    cout << "���ڶ�����ⲿ" << endl;
                    return false;
                }

            }
        }
    }

    /***************** ����Ƿ�Ͷ���ν������� ******************/

    Point to(bound_xr + 1, point.y);          // �½�һ���㣬���жϵĵ�ƽ�У�����������ε���ߣ��䵱���ߵġ�ĩβ����
    Line radial(point, to);                   // �½�һ������
    int count = 0;                            // ������
    for (size_t i = 0; i < lines.size(); i++) // ����ÿһ���ߣ������鿴�����Ƿ񴩹������
    {
        if (CheckCross(radial, lines[i])) // �������
        {
            count++;
        }
    }

    if (count >= 2) //�����������ʱ˵�����������ý����������ߵĽ���
    {
        cout << "�㲻�ڶ���ε��ڲ�" << endl;
        return false; // ����
    }
    else
    {
        cout << "���ڶ���ε��ڲ�" << endl;
        return true;
    }
}

string Polygon::Str()
{
    string temp;
    for (size_t i = 0; i < lines.size(); i++)
    {
        temp += lines[i].Str() + "\n";
    }
    return temp;
}

string Polygon::showbound()
{
    string temp = "x: " + to_string(bound_xl) + "<--->" + to_string(bound_xr) + "\ny:" + to_string(bound_yd) + "<--->" + to_string(bound_yu) + '\n';
    return temp;
}

bool CheckCross(Line a, Line b) // �鿴�������Ƿ��ཻ�����淶�ཻҲ��
{
    double p1 = (*a.to - *a.from) ^ (*b.from - *a.from);
    double p2 = (*a.to - *a.from) ^ (*b.to - *a.from);
    double p3 = (*b.to - *b.from) ^ (*a.from - *b.from);
    double p4 = (*b.to - *b.from) ^ (*a.to - *a.from);
    /***************** �ǹ淶�ཻ ******************/
    if (equal(p1, 0.0) || equal(p2, 0.0) || equal(p3, 0.0) || equal(p4, 0.0)) // �����һ�����Ϊ0�� ˵��Ϊ�ǹ淶�ཻ
    {
        return true;
    }
    /***************** �жϹ淶�ཻ ******************/
    else if (p1 * p2 < 0 && p3 * p4 < 0) // ȫ����ţ�˵���淶�ཻ
    {
        return true;
    }
    else
    {
        return false; // �����ཻ
    }
}