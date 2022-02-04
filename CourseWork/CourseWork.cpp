#include <iostream>
#include <queue>
#include <string>
#include <cstring>
#include <stack>
#include <vector>

#define SIZE 16 // ������ �����

using namespace std;

char vertex_alphabet[] // ������� ��������� �� ������ ������� �) (���. 17)
{
    '�', '�', '�', '�', '�', '�', '�', '�', '�', '�', '�', '�', '�', '�', '�', '�'
};

int graph[SIZE][SIZE] =
{   // ����� ����� ������ ����
    {0, 0, 0, 1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 5, 6, 0, 0, 0, 0, 3, 0, 0, 0, 0},
    {0, 0, 0, 7, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {1, 0, 7, 0, 0, 0, 4, 3, 3, 3, 0, 0, 0, 0, 0, 0},
    {2, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0},
    {0, 5, 0, 0, 0, 0, 7, 0, 0, 0, 0, 9, 0, 0, 0, 0},
    {0, 6, 3, 4, 0, 7, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0},
    {0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0},
    {0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0},
    {0, 0, 0, 3, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 5},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 4, 0, 0, 0},
    {0, 3, 0, 0, 0, 9, 2, 0, 0, 0, 5, 0, 3, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 3, 0, 4, 17, 0},
    {0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 4, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 2, 5, 0, 0, 17, 0, 0, 8},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 8, 0},
};

void define_graph_vertex(int a)
{   // �����, ����� ����� ������� (�� ������ ��������� ��������) ��������� ��� ������ �������
    cout << vertex_alphabet[a] << " ";
}

void solve_first_problem(bool used[SIZE], int s, int f, int p[SIZE]);
void solve_second_problem(int x);
void print_first_solution(bool used[SIZE], int p[SIZE], int f);

int main()
{
    setlocale(LC_ALL, ".1251");
    
    int a, b;    // ������ ������, ��� "a" - ������, � "b" - ����
    bool used[SIZE];
    int x; // ����� �������
    int ancestor[SIZE];    // ancestor[] - ������ �������,
    // ������ ���������� �������, �� ������� �� ������ � ������� �������
    
    cout << "1-�� ����� �������..." << endl;
    cout << "������� ������� �1 (������) ������� �2: ";
    cin >> a >> b;
    cout << "����� ���� �� ������� ";
    define_graph_vertex(a);
    cout << "�� ������� ";
    define_graph_vertex(b);
    cout << "." << endl;

    // ��� ������� ������ ������� (������� ����� 1) �)
    solve_first_problem(used, a, b, ancestor);
    print_first_solution(used, ancestor, b);
    
    // ������� (������� ����� 2) �)
    cout << endl;
    cout << "2-�� ����� �������..." << endl;
    cout << "������� ����� ������ (X), ����� ��������� �� ���� ��� ��������� ���� ����� 3" << endl;
    cout << "������� X: ";
    cin >> x;
    solve_second_problem(x);

    return 0;
}

void solve_first_problem(bool used[SIZE], int s, int f, int ancestor[SIZE])
{
    queue<int> queue;
    queue.push(s);
    for (int i = 0; i < SIZE; i++)
        used[i] = false;

    used[s] = true;
    ancestor[s] = -1;
    bool flag = false;
    while (!flag && !queue.empty())
    {
        int v = queue.front();
        queue.pop();
        for (int i = 0; i < SIZE && !flag; i++)
        {
            if (!used[i] && graph[v][i] != 0)
            {
                used[i] = true;
                queue.push(i);
                ancestor[i] = v;
                if (i == f)
                    flag = true;
            }
        }
    }
}

void print_first_solution(bool used[SIZE], int ancestor[SIZE], int f)
{
    int distance = 0;

    if (!used[f])
        cerr << "No way!" << endl;
    else
    {
        vector<int> way;
        for (int v = f; v != -1; v = ancestor[v])
            way.push_back(v);
        reverse(way.begin(), way.end());
        cout << "����: ";
        define_graph_vertex(way[0]);
        for (size_t i = 1, j = 0; i < way.size(); i++, j++)
        {
            define_graph_vertex(way[i]);
            distance += graph[way[i]][way[j]];
        }
        cout << endl;
        cout << "���������� = " << distance << endl;
    }
}

void solve_second_problem(int x)
{
    for (int j = 0; j < SIZE; j++)
    {
        if (graph[x][j] != 0)
        {
            for (int i = 0; i < SIZE; i++)
            {
                if (graph[i][j] != 0 && i != x)
                {
                    for (int k = 0; k < SIZE; k++)
                    {
                        if (graph[i][k] != 0 && k != j && k != x)
                        {
                            define_graph_vertex(x);
                            cout << "-> ";
                            define_graph_vertex(j);
                            cout << "-> ";
                            define_graph_vertex(i);
                            cout << "-> ";
                            define_graph_vertex(k);
                            cout << "= " << graph[x][j] + graph[i][j] + graph[i][k] << endl;
                        }
                    }
                }
            }
        }
    }
}
