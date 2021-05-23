#include <iostream>
#include <fstream>
#include <windows.h>
#include <iomanip>
#define N 15
#define INFINITY 10000
using namespace std;

void OSTD(int** m);
void Bellman(int** Mas, int start);

int main()
{
    cout << "#1\n";
    int start, finish;
    setlocale(LC_ALL, "russian");
    ifstream fi1("..\\Laba4_alg\\input.txt");
    ifstream fi2("..Laba4_alg\\input1.txt");
    int** A = new int* [N];
    for (int i = 0; i < N; i++)
        A[i] = new int[N];
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            fi1 >> A[i][j];
    fi1.close();
    cout << "Введите начальную вершину: ";
    cin >> start;
    Bellman(A, start);
    cout << "\n#2\n";
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            fi2 >> A[i][j];
            if (A[i][j] == 0) A[i][j] = INFINITY;
        }
    }
    OSTD(A);
    cout << endl;
    fi2.close();
    system("pause");
    return 0;
}

void OSTD(int** m) {
    int a = 0, b = 0, k = 1;
    int visited[N] = { 0 }, min = 0, minweight = 0;
    int path[N] = { 0 }; 
    int path_index = 0;
    visited[0] = 1;
    cout << "\nОстовное дерево: ";
    while (k < N) {
        min = INFINITY;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (visited[i] != 0) {
                    if (m[i][j] < min) {
                        min = m[i][j];
                        a = i;
                        b = j;
                    }
                }
            }
        }
        if (visited[a] == 0 || visited[b] == 0) {
            path[path_index] = b;
            path_index++;
            k++;
            cout << "\nP" << a << "  P" << b << "(" << min << ")";
            minweight += min;
            visited[b] = 1;

        }
        m[a][b] = m[b][a] = INFINITY;
    }
    cout << "\nВес дерева - " << minweight << endl << endl;
}

void Bellman(int** Mas, int start)
{
    int shortest[N], pred[N],m=0;
    for (int i = 0; i < N; i++)
    {
        shortest[i] = INFINITY;
        pred[i] = NULL;
    }


    shortest[start] = 0;
    for (int k = 0; k < N - 1; k++)
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                    if (Mas[i][j] != 0)
                        if (shortest[i] + Mas[i][j] < shortest[j])
                        {
                            shortest[j] = shortest[i] + Mas[i][j];
                            pred[i] = k;
                        }

    for (int i = 0; i < N; i++)
        if (i == start) cout << "Вершина " << start << " - начальная." << endl;
        else if (shortest[i] == INFINITY) cout << "Пути из вершины " << start << " в вершину " << i << " не существует." << endl;
        else cout << "Кратчайшее расстояние из вершины " << start << " в вершину " << i << " равно " << shortest[i] << ", предпоследняя вершина пути: " << pred[i] << endl;
    cout << endl;
        
}