#include "fun.h"

const int MAX_LINES = 1000;
vector<Vertex> Graph;
vector<Polygon> polys;
vector<Line> lines;        // 用于存储所有的线段

void Initialize()
{
    /***************** 清空上一轮储存内容 ******************/
    vector<Vertex> tempg;
    Graph.swap(tempg);
    vector<Polygon> tempp;
    polys.swap(tempp);
    vector<Line> templ;
    lines.swap(templ);


    /***************** 准备读取坐标 ******************/
    ifstream fin;              // 读取文件流
    string temp;               // 临时储存输入
    string file = "input.txt"; // 文件路径
    cout << "回车默认读取工程目录下的input.txt，或输入你想要打开的文件路径" << endl;

    char c = getchar(); // 判断是否输入的是回车

    if (c != '\n') // 如果输入的不是回车,说明需要打开自己的文件
    {
        cin.putback(c);
        cin >> file;
    }
    fin.open(file);
    cout << "/***************** 开始读取文件 ******************/" << endl;
    if (fin.is_open())
    {
        while (!fin.eof()) // 只要没有读完就继续读入数据
        {
            getline(fin, temp);
            smatch result; // 正则表达式匹配输入的文字
            try
            {
                regex pattern("(-?\\d+\\.?\\d*)\\s(-?\\d+\\.?\\d*)\\s(-?\\d+\\.?\\d*)\\s(-?\\d+\\.?\\d*)\\s*"); // 正则表达式具体内容
                if (regex_match(temp, result, pattern)) // 如果匹配上了
                {
                    if (result.size() != 5) // debug
                    {
                        cout << "请检查你的输入格式！！" << endl;
                        Initialize();
                    }
                    Line temp(result[1], result[2], result[3], result[4]); // 新建一条线
                    lines.push_back(temp);
                    cout << lines.back().Str() << endl; // 输出线
                }
            }
            catch (const char *msg)
            {
                cerr << msg << endl;
            }
        }
    }
    else
    {
        cin.clear();
        cin.ignore();
        cout << "文件打开错误！请检查文件是否存在！" << endl;
        Initialize(); // 重新初始化
        return;
    }

    cout << "文件读取完毕！！ ";


    /***************** 开始对多边形进行识别 ******************/
    FindPoly();
    cout << "共找到多边形 " << polys.size() << " 个 " << endl;

    if (polys.size() == 0) // 如果没有多边形了
    {
        cout << "未找到多边形，重新读取数据" << endl;
        Initialize(); // 重新进入
        return;
    }

    for (int i = 0; i < polys.size(); i++)
    {
        cout << i + 1 << ". " << endl;

        if (!polys[i].sortlines()) // 1. 整理线段（p1 -> p2 -> ... -> pn) 返回是否首位相连
        {
            cout << "  多边形坐标数据有误！输入的坐标为：" << endl;
            cout << "  " << polys[i].Str() << endl;
            Initialize(); // 重新进入
            return;
        }

        cout << "  坐标：\n" << polys[i].Str() << endl;

        if (!polys[i].checkcross()) // 2. 寻找是否有交叉点
        {
            Initialize();
            return;
        }

        if (!polys[i].checkconv()) // 3. 判断多边形形状
        {
            cout << "  形状：凹多边形\n" << endl;
        }
        else
        {
            cout << "  形状：凸多边形\n" << endl;
        }

        polys[i].findbound(); // 4. 判断外包矩形
        cout << "  外包矩形：\n  "
            << polys[i].showbound();

        cout << "  面积为：" << polys[i].area() << "\n\n";
    }


    /***************** 寻找岛屿 ******************/
    cin.clear();

    cout << "是否判断岛屿？ (y/n) : ";
    c = getchar();
    cout << "\n";
    if (c == 'y' || c == 'Y') // 判断岛屿
    {
        for (int i = 0; i < polys.size(); i++) // 遍历所有多边形
        {
            cout << "\n开始查找 " << i + 1 << " 号：(没有则自动跳过)\n\n";
            for (int j = 0; j < polys.size(); j++)
            {
                if (i == j) continue;
                for (int k = 0; k < polys[j].lines.size(); k++) 
                    // 判断多边形j所有的点是否都在i内
                {
                    if (!polys[i].in(polys[j].lines[k].from) || !polys[i].in(polys[j].lines[k].to)) 
                        // 但凡有任何一个点不在多边形i内部
                    {
                        goto notin;
                    }
                }
                cout << "  找到岛屿： 多边形 " << j + 1 << " 在 " << i+1 << " 内部"<< endl;
            notin:
                NULL;
            }
        }
    }
    cin.get();
    cin.clear();


    /***************** 判断点是否在多边形内部 ******************/
    cout << "判断点是否在坐标内部(在边上不算)\n请输入点的坐标（格式：x y），输入0返回，输入exit退出\n";

    smatch result;

    while (true)
    {
        getline(cin, temp);
        if (temp == "0") // 返回
        {
            Initialize();
            break;
        }
        else if (temp == "exit") // 退出
        {
            return;
        }
        try
        {
            regex pattern("(-?\\d+\\.?\\d*)\\s(-?\\d+\\.?\\d*)\\s*"); // 正则表达式匹配
            if (regex_match(temp, result, pattern)) // 匹配成功
            {
                assert(result.size() == 3);
                cout << "点 " << Point(result[1], result[2]).Str() << " : \n";
                for (int i = 0; i < polys.size(); i++)
                {
                    if (polys[i].in(Point(result[1], result[2]))) // 判断是否在多边形内
                    {
                        cout << "  在多边形 " << i + 1 << " 内" << endl;
                    }
                    else
                    {
                        cout << "  不在多边形 " << i + 1 << " 内" << endl;
                    }
                }
            }
            else
            {
                cout << "输入有误！请重新输入" << endl;
            }
        }
        catch (const exception &e)
        {
            cerr << e.what() << '\n';
        }

    }
}

void FindPoly()
{
    /***************** 建立图 ******************/
    Vertex temp(0); // 历史遗留问题 索引出现差异不得以修复
    Graph.push_back(temp);
    int counter = 1;

    /***************** 建立索引 ******************/
    for (size_t i = 0; i < lines.size(); i++) // 给所有节点一个id
    {
        // 给from建立一个id
        if (lines[i].from.id == 0) // 如果还没有id，说明被略过去了
        {
            lines[i].from.id = counter;
            for (size_t j = 0; j < lines.size(); j++) // 遍历所有节点，找和from相同的节点，赋值同一个id
            {
                if (lines[j].from == lines[i].from) // 如果lines[j]的节点和lines[i].from 的节点一样
                    lines[j].from.id = counter; // 给该节点id
                if (lines[j].to == lines[i].from) // 如果lines[j]的to节点和lines[i].from 的节点相同
                    lines[j].to.id = counter;
            }
            counter++;
        }
        // 给to建立一个id
        if (lines[i].to.id == 0) // 与上面from一样
        {
            lines[i].to.id = counter;
            for (size_t j = 0; j < lines.size(); j++) // 遍历所有节点，找和to相同的节点，赋值同一个id
            {
                if (lines[j].from == lines[i].to) // 如果lines[j]的from节点和lines[i].to 的节点一样
                    lines[j].from.id = counter; // 给该节点id
                if (lines[j].to == lines[i].to) // 如果lines[j]的to节点和lines[i].to 的节点相同
                    lines[j].to.id = counter;
            }
            counter++;
        }
    }
    counter--; // 现在counter是节点的数量

    for (int i = 1; i <= counter; i++) // 遍历所有的节点并寻找邻接节点
    {
        Vertex temp(i); // 建立该节点的vertex
        for (int j = 0; j < lines.size(); j++) // 寻找一样的节点
        {
            if (lines[j].from.id == i) // 找到了相同的节点，那么另一个节点就是i的邻接节点
            {
                temp.adjacence.push_back(lines[j].to.id);
            }
            if (lines[j].to.id == i)
            {
                temp.adjacence.push_back(lines[j].from.id);
            }
        }
        Graph.push_back(temp); // 将节点放入图中
    }

    FindCir(counter);
    
    return;

}

bool ifnear(Line a, Line b)
{

    if (a.from == b.to || a.from == b.from\
        || a.to == b.from || a.to == b.to) // 判断邻接关系，ab有一个点相同
        return true;
    else
        return false;
}

bool in(vector<int> a, int b)
{
    for (int i = 0; i < a.size(); i++) // 判断是否在vector内部
    {
        if (b == a[i])
            return true;
    }
    return false;
}

int FindCirStart(int length, vector<int> path)
{
    int counter = 0;
    int last = path.back(); // last是上一步的节点
    int pathlen = path.size(); // pathlen 是走过的长度

    if (pathlen == length - 1) // 如果只剩一步了
    {
        for (int i = 0; i < Graph[last].adjacence.size(); i++) // 对于每一个邻接节点
        {
            if ((Graph[last].adjacence[i] > path[1]) && // 至少需要三个节点
                !in(path, Graph[last].adjacence[i]) && // 不能是已经走过的节点
                in(Graph[Graph[last].adjacence[i]].adjacence, path[0])) // 该节点还必须能和最后一个节点连上
            {
                Polygon temp; // 新建一个polygon
                
                for (int j = 0; j + 1 < path.size(); j++) // 遍历路径寻找id
                {
                    for (int k = 0; k < lines.size(); k++)
                    {
                        if ((lines[k].from.id == path[j] && lines[k].to.id == path[j + 1]) ||
                            (lines[k].from.id == path[j + 1] && lines[k].to.id == path[j])) // 如果找到了一条边，两个点正好和path[j],path[j+1]匹配上
                        {
                            temp.lines.push_back(lines[k]); // 将linesk放进去
                            break;
                        }
                    }
                }
                for (int k = 0; k < lines.size(); k++)
                {
                    if ((lines[k].from.id == Graph[last].adjacence[i] && lines[k].to.id == path.back()) ||
                        (lines[k].from.id == path.back() && lines[k].to.id == Graph[last].adjacence[i]))
                        // 或者找到了匹配 path[-1] 和 Graph[last].adjacence[i] 的节点
                    {
                        temp.lines.push_back(lines[k]); // 将lines[k]放进去
                    }
                    else if ((lines[k].from.id == path[0] && lines[k].to.id == Graph[last].adjacence[i]) ||
                        (lines[k].from.id == Graph[last].adjacence[i] && lines[k].to.id == path[0]))
                        // 或者找到了匹配 path[0] 和 Graph[last].adjacence[i] 的节点
                    {
                        temp.lines.push_back(lines[k]); // 将lines[k]放进去
                    }
                }
                // 现在temp就是新的多边形
                polys.push_back(temp);

                counter++;
            }
        }
    }
    else // 还没有走到最后一步
    {
        for (int i = 0; i < Graph[path.back()].adjacence.size(); i++) // 遍历每一个邻接节点
        {
            if ((Graph[last].adjacence[i] > path[0]) && // 该节点不能是小于path[0]的节点（避免重复）
                !in(path, Graph[last].adjacence[i])) // 该节点也不能是已经走过的节点
            {
                vector<int> newpath(path);
                newpath.push_back(Graph[path.back()].adjacence[i]); // 开始递归
                counter += FindCirStart(length, newpath);
            }
        }
    }
    return counter; // 返回遇到的多边形数量
}

int FindCirLen(int n, int length)
{
    int counter = 0;

    for (int i = 1; i < n - length + 2; i++) // 以第1~n-length+1为起点，查找是否有多边形
    {
        vector<int> path; // 建立路径向量，用于存储走过的路径
        path.push_back(i); // 将进入节点编号放入
        counter += FindCirStart(length, path); // 搜索是否存在节点 这里没有选中dfs因为dfs难以搞定无方向的问题
    }

    return counter; // 返回多边形数量
}

int FindCir(int ver_size)
{
    int counter = 0; // 计数器，用于记录多边形个数
    for (int i = 3; i < ver_size + 1; i++)
    {
        counter += FindCirLen(ver_size, i); // 递归查找是否有多边形
    }

    return counter;
}
