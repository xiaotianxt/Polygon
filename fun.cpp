#include "fun.h"

void Initialize()
{
    vector<Line> lines;        // ���ڴ洢���е��߶�
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
            smatch result;
            try
            {
                regex pattern("(-?\\d+\\.?\\d*?)\\s(-?\\d+\\.?\\d*?)\\s(-?\\d+\\.?\\d*?)\\s(-?\\d+\\.?\\d*?)\s*?");
                if (regex_match(temp, result, pattern))
                {
                    if (result.size() != 5)
                    {
                        cout << "������������ʽ����" << endl;
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
        cout << "�ļ��򿪴��������ļ��Ƿ���ڣ�" << endl;
        Initialize(); // ���³�ʼ��
        return;
    }

    cout << "�ļ���ȡ��ϣ���" << endl;
    /***************** ��ʼ�Զ���ν���ʶ�� ******************/

    Polygon poly(&lines);

    if (!poly.sortlines()) // �����߶Σ�p1 -> p2 -> ... -> pn) �����Ƿ���λ����
    {
        cout << "��������������������������Ϊ��" << endl;
        cout << poly.Str() << endl;
        Initialize();
        return;
    }

    cout << "����ɹ�����β��ӵ�˳������Ϊ\n" << poly.Str() << endl;

    if (!poly.checkcross()) // ������ִ��ڽ����
    {
        Initialize();
        return;
    }

    if (!poly.checkconv()) // �������͹�����
    {
        cout << "��������ǰ������" << endl;
    }
    else
    {
        cout << "���������͹�����" << endl;
    }

    poly.findbound(); // �ж��������
    cout << "�������Ϊ��\n"
         << poly.showbound();

    // TODO: ������������

    /***************** ��ʼ�жϵ��Ƿ��ڶ�����ڲ� ******************/
    cout << "�жϵ��Ƿ��������ڣ����������������꣨����x y˳��ʹ�ÿո�ָ,��0�˳�\n";

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
                    cout << "�õ��ڶ�����ڲ���" << endl;
                }
                else
                {
                    cout << "�õ㲻�ڶ�����ڲ�" << endl;
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