#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <iterator>
using namespace std;

typedef vector<int> t;

void print_row(const t &f)
{
    int n = f.size();
    for (int i = 0; i < n; ++i)
    {
        cout << f[i] << " ";
    }
    cout << endl;
}

int main()
{

    vector<t> mat = vector<t>();

    mat.push_back({1, 2, 3});
    mat.push_back({-1, 2, 3});
    mat.push_back({1, 478, 3});

    mat.push_back({1, 2, 3, 4, 5, 2, 4, 5, 5, 2, 1, 1});

    mat.push_back({1, 2, 2, 34, 100, 4, 5, 5, 2, 1, 1});
    //sorted using
    sort(mat.begin(), mat.end(), [](const t f1, const t f2)
         {
             int suma1 = 0;
             int suma2 = 0;
             for (int i = 0; i < f1.size(); ++i)
             {
                 suma1 = suma1 + f1[i];
             }
             for (int i = 0; i < f2.size(); ++i)
             {
                 suma2 = suma2 + f2[i];
             }
             return suma1 < suma2;
         });
    for_each(mat.begin(), mat.end(), print_row);
}