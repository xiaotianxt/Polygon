#include "fun.h"

void Initialize()
{
    vector<Line> lines;        // 用于存储所有的线段
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
            smatch result;
            try
            {
                regex pattern("(-?\\d+\\.?\\d*?)\\s(-?\\d+\\.?\\d*?)\\s(-?\\d+\\.?\\d*?)\\s(-?\\d+\\.?\\d*?)\s*?");
                if (regex_match(temp, result, pattern))
                {
                    if (result.size() != 5)
                    {
                        cout << "请检查你的输入格式！！" << endl;
                        Initialize();
                    }
                    Line temp(result[1], result[2], result[3], result[4]);
                    lines.push_back(temp);
                    cout << lines.back().Str() << endl;
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

    cout << "文件读取完毕！！" << endl;
    /***************** 开始对多边形进行识别 ******************/

    Polygon poly(&lines);

    if (!poly.sortlines()) // 整理线段（p1 -> p2 -> ... -> pn) 返回是否首位相连
    {
        cout << "多边形坐标数据有误！输入的坐标为：" << endl;
        cout << poly.Str() << endl;
        Initialize();
        return;
    }

    cout << "整理成功！首尾相接的顺序排列为\n" << poly.Str() << endl;

    if (!poly.checkcross()) // 如果发现存在交叉点
    {
        Initialize();
        return;
    }

    if (!poly.checkconv()) // 如果不是凸多边形
    {
        cout << "您输入的是凹多边形" << endl;
    }
    else
    {
        cout << "您输入的是凸多边形" << endl;
    }

    poly.findbound(); // 判断外包矩形
    cout << "外包矩形为：\n"
         << poly.showbound();

    // TODO: 待完成其他情况

    /***************** 开始判断点是否在多边形内部 ******************/
    cout << "判断点是否在坐标内，请输入任意点的坐标（按照x y顺序，使用空格分割）,按0退出\n";

    smatch result;

    while (true)
    {
        getline(cin, temp);
        if (temp == "0")
        {
            break;
        }
        try
        {
            regex pattern("(-?\\d+\\.?\\d*?)\\s(-?\\d+\\.?\d*?)\\s*?");
            if (regex_match(temp, result, pattern))
            {
                assert(result.size() == 3);
                if (poly.in(Point(result[1], result[2]))) //
                {
                    cout << "该点在多边形内部！" << endl;
                }
                else
                {
                    cout << "该点不在多边形内部" << endl;
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