#include "fun.h"

const int MAX_LINES = 1000;
vector<Vertex> Graph;
vector<Polygon> polys;
vector<Line> lines;        // ���ڴ洢���е��߶�

void Initialize()
{
    /***************** �����һ�ִ������� ******************/
    vector<Vertex> tempg;
    Graph.swap(tempg);
    vector<Polygon> tempp;
    polys.swap(tempp);
    vector<Line> templ;
    lines.swap(templ);


    /***************** ׼����ȡ���� ******************/
    ifstream fin;              // ��ȡ�ļ���
    string temp;               // ��ʱ��������
    string file = "input.txt"; // �ļ�·��
    cout << "�س�Ĭ�϶�ȡ����Ŀ¼�µ�input.txt������������Ҫ�򿪵��ļ�·��" << endl;

    char c = getchar(); // �ж��Ƿ�������ǻس�

    if (c != '\n') // �������Ĳ��ǻس�,˵����Ҫ���Լ����ļ�
    {
        cin.putback(c);
        cin >> file;
    }
    fin.open(file);
    cout << "/***************** ��ʼ��ȡ�ļ� ******************/" << endl;
    if (fin.is_open())
    {
        while (!fin.eof()) // ֻҪû�ж���ͼ�����������
        {
            getline(fin, temp);
            smatch result; // ������ʽƥ�����������
            try
            {
                regex pattern("(-?\\d+\\.?\\d*)\\s(-?\\d+\\.?\\d*)\\s(-?\\d+\\.?\\d*)\\s(-?\\d+\\.?\\d*)\\s*"); // ������ʽ��������
                if (regex_match(temp, result, pattern)) // ���ƥ������
                {
                    if (result.size() != 5) // debug
                    {
                        cout << "������������ʽ����" << endl;
                        Initialize();
                    }
                    Line temp(result[1], result[2], result[3], result[4]); // �½�һ����
                    lines.push_back(temp);
                    cout << lines.back().Str() << endl; // �����
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
        cout << "�ļ��򿪴��������ļ��Ƿ���ڣ�" << endl;
        Initialize(); // ���³�ʼ��
        return;
    }

    cout << "�ļ���ȡ��ϣ��� ";


    /***************** ��ʼ�Զ���ν���ʶ�� ******************/
    FindPoly();
    cout << "���ҵ������ " << polys.size() << " �� " << endl;

    if (polys.size() == 0) // ���û�ж������
    {
        cout << "δ�ҵ�����Σ����¶�ȡ����" << endl;
        Initialize(); // ���½���
        return;
    }

    for (int i = 0; i < polys.size(); i++)
    {
        cout << i + 1 << ". " << endl;

        if (!polys[i].sortlines()) // 1. �����߶Σ�p1 -> p2 -> ... -> pn) �����Ƿ���λ����
        {
            cout << "  ��������������������������Ϊ��" << endl;
            cout << "  " << polys[i].Str() << endl;
            Initialize(); // ���½���
            return;
        }

        cout << "  ���꣺\n" << polys[i].Str() << endl;

        if (!polys[i].checkcross()) // 2. Ѱ���Ƿ��н����
        {
            Initialize();
            return;
        }

        if (!polys[i].checkconv()) // 3. �ж϶������״
        {
            cout << "  ��״���������\n" << endl;
        }
        else
        {
            cout << "  ��״��͹�����\n" << endl;
        }

        polys[i].findbound(); // 4. �ж��������
        cout << "  ������Σ�\n  "
            << polys[i].showbound();

        cout << "  ���Ϊ��" << polys[i].area() << "\n\n";
    }


    /***************** Ѱ�ҵ��� ******************/
    cin.clear();

    cout << "�Ƿ��жϵ��죿 (y/n) : ";
    c = getchar();
    cout << "\n";
    if (c == 'y' || c == 'Y') // �жϵ���
    {
        for (int i = 0; i < polys.size(); i++) // �������ж����
        {
            cout << "\n��ʼ���� " << i + 1 << " �ţ�(û�����Զ�����)\n\n";
            for (int j = 0; j < polys.size(); j++)
            {
                if (i == j) continue;
                for (int k = 0; k < polys[j].lines.size(); k++) 
                    // �ж϶����j���еĵ��Ƿ���i��
                {
                    if (!polys[i].in(polys[j].lines[k].from) || !polys[i].in(polys[j].lines[k].to)) 
                        // �������κ�һ���㲻�ڶ����i�ڲ�
                    {
                        goto notin;
                    }
                }
                cout << "  �ҵ����죺 ����� " << j + 1 << " �� " << i+1 << " �ڲ�"<< endl;
            notin:
                NULL;
            }
        }
    }
    cin.get();
    cin.clear();


    /***************** �жϵ��Ƿ��ڶ�����ڲ� ******************/
    cout << "�жϵ��Ƿ��������ڲ�(�ڱ��ϲ���)\n�����������꣨��ʽ��x y��������0���أ�����exit�˳�\n";

    smatch result;

    while (true)
    {
        getline(cin, temp);
        if (temp == "0") // ����
        {
            Initialize();
            break;
        }
        else if (temp == "exit") // �˳�
        {
            return;
        }
        try
        {
            regex pattern("(-?\\d+\\.?\\d*)\\s(-?\\d+\\.?\\d*)\\s*"); // ������ʽƥ��
            if (regex_match(temp, result, pattern)) // ƥ��ɹ�
            {
                assert(result.size() == 3);
                cout << "�� " << Point(result[1], result[2]).Str() << " : \n";
                for (int i = 0; i < polys.size(); i++)
                {
                    if (polys[i].in(Point(result[1], result[2]))) // �ж��Ƿ��ڶ������
                    {
                        cout << "  �ڶ���� " << i + 1 << " ��" << endl;
                    }
                    else
                    {
                        cout << "  ���ڶ���� " << i + 1 << " ��" << endl;
                    }
                }
            }
            else
            {
                cout << "������������������" << endl;
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
    /***************** ����ͼ ******************/
    Vertex temp(0); // ��ʷ�������� �������ֲ��첻�����޸�
    Graph.push_back(temp);
    int counter = 1;

    /***************** �������� ******************/
    for (size_t i = 0; i < lines.size(); i++) // �����нڵ�һ��id
    {
        // ��from����һ��id
        if (lines[i].from.id == 0) // �����û��id��˵�����Թ�ȥ��
        {
            lines[i].from.id = counter;
            for (size_t j = 0; j < lines.size(); j++) // �������нڵ㣬�Һ�from��ͬ�Ľڵ㣬��ֵͬһ��id
            {
                if (lines[j].from == lines[i].from) // ���lines[j]�Ľڵ��lines[i].from �Ľڵ�һ��
                    lines[j].from.id = counter; // ���ýڵ�id
                if (lines[j].to == lines[i].from) // ���lines[j]��to�ڵ��lines[i].from �Ľڵ���ͬ
                    lines[j].to.id = counter;
            }
            counter++;
        }
        // ��to����һ��id
        if (lines[i].to.id == 0) // ������fromһ��
        {
            lines[i].to.id = counter;
            for (size_t j = 0; j < lines.size(); j++) // �������нڵ㣬�Һ�to��ͬ�Ľڵ㣬��ֵͬһ��id
            {
                if (lines[j].from == lines[i].to) // ���lines[j]��from�ڵ��lines[i].to �Ľڵ�һ��
                    lines[j].from.id = counter; // ���ýڵ�id
                if (lines[j].to == lines[i].to) // ���lines[j]��to�ڵ��lines[i].to �Ľڵ���ͬ
                    lines[j].to.id = counter;
            }
            counter++;
        }
    }
    counter--; // ����counter�ǽڵ������

    for (int i = 1; i <= counter; i++) // �������еĽڵ㲢Ѱ���ڽӽڵ�
    {
        Vertex temp(i); // �����ýڵ��vertex
        for (int j = 0; j < lines.size(); j++) // Ѱ��һ���Ľڵ�
        {
            if (lines[j].from.id == i) // �ҵ�����ͬ�Ľڵ㣬��ô��һ���ڵ����i���ڽӽڵ�
            {
                temp.adjacence.push_back(lines[j].to.id);
            }
            if (lines[j].to.id == i)
            {
                temp.adjacence.push_back(lines[j].from.id);
            }
        }
        Graph.push_back(temp); // ���ڵ����ͼ��
    }

    FindCir(counter);
    
    return;

}

bool ifnear(Line a, Line b)
{

    if (a.from == b.to || a.from == b.from\
        || a.to == b.from || a.to == b.to) // �ж��ڽӹ�ϵ��ab��һ������ͬ
        return true;
    else
        return false;
}

bool in(vector<int> a, int b)
{
    for (int i = 0; i < a.size(); i++) // �ж��Ƿ���vector�ڲ�
    {
        if (b == a[i])
            return true;
    }
    return false;
}

int FindCirStart(int length, vector<int> path)
{
    int counter = 0;
    int last = path.back(); // last����һ���Ľڵ�
    int pathlen = path.size(); // pathlen ���߹��ĳ���

    if (pathlen == length - 1) // ���ֻʣһ����
    {
        for (int i = 0; i < Graph[last].adjacence.size(); i++) // ����ÿһ���ڽӽڵ�
        {
            if ((Graph[last].adjacence[i] > path[1]) && // ������Ҫ�����ڵ�
                !in(path, Graph[last].adjacence[i]) && // �������Ѿ��߹��Ľڵ�
                in(Graph[Graph[last].adjacence[i]].adjacence, path[0])) // �ýڵ㻹�����ܺ����һ���ڵ�����
            {
                Polygon temp; // �½�һ��polygon
                
                for (int j = 0; j + 1 < path.size(); j++) // ����·��Ѱ��id
                {
                    for (int k = 0; k < lines.size(); k++)
                    {
                        if ((lines[k].from.id == path[j] && lines[k].to.id == path[j + 1]) ||
                            (lines[k].from.id == path[j + 1] && lines[k].to.id == path[j])) // ����ҵ���һ���ߣ����������ú�path[j],path[j+1]ƥ����
                        {
                            temp.lines.push_back(lines[k]); // ��linesk�Ž�ȥ
                            break;
                        }
                    }
                }
                for (int k = 0; k < lines.size(); k++)
                {
                    if ((lines[k].from.id == Graph[last].adjacence[i] && lines[k].to.id == path.back()) ||
                        (lines[k].from.id == path.back() && lines[k].to.id == Graph[last].adjacence[i]))
                        // �����ҵ���ƥ�� path[-1] �� Graph[last].adjacence[i] �Ľڵ�
                    {
                        temp.lines.push_back(lines[k]); // ��lines[k]�Ž�ȥ
                    }
                    else if ((lines[k].from.id == path[0] && lines[k].to.id == Graph[last].adjacence[i]) ||
                        (lines[k].from.id == Graph[last].adjacence[i] && lines[k].to.id == path[0]))
                        // �����ҵ���ƥ�� path[0] �� Graph[last].adjacence[i] �Ľڵ�
                    {
                        temp.lines.push_back(lines[k]); // ��lines[k]�Ž�ȥ
                    }
                }
                // ����temp�����µĶ����
                polys.push_back(temp);

                counter++;
            }
        }
    }
    else // ��û���ߵ����һ��
    {
        for (int i = 0; i < Graph[path.back()].adjacence.size(); i++) // ����ÿһ���ڽӽڵ�
        {
            if ((Graph[last].adjacence[i] > path[0]) && // �ýڵ㲻����С��path[0]�Ľڵ㣨�����ظ���
                !in(path, Graph[last].adjacence[i])) // �ýڵ�Ҳ�������Ѿ��߹��Ľڵ�
            {
                vector<int> newpath(path);
                newpath.push_back(Graph[path.back()].adjacence[i]); // ��ʼ�ݹ�
                counter += FindCirStart(length, newpath);
            }
        }
    }
    return counter; // ���������Ķ��������
}

int FindCirLen(int n, int length)
{
    int counter = 0;

    for (int i = 1; i < n - length + 2; i++) // �Ե�1~n-length+1Ϊ��㣬�����Ƿ��ж����
    {
        vector<int> path; // ����·�����������ڴ洢�߹���·��
        path.push_back(i); // ������ڵ��ŷ���
        counter += FindCirStart(length, path); // �����Ƿ���ڽڵ� ����û��ѡ��dfs��Ϊdfs���Ը㶨�޷��������
    }

    return counter; // ���ض��������
}

int FindCir(int ver_size)
{
    int counter = 0; // �����������ڼ�¼����θ���
    for (int i = 3; i < ver_size + 1; i++)
    {
        counter += FindCirLen(ver_size, i); // �ݹ�����Ƿ��ж����
    }

    return counter;
}
