#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class AddVal
{
private:
    int val;

public:
    AddVal(int v)
    {
        val = v;
        
    }

    void operator()(int &i)
    {
        i = i + val;
    }
};

void incr(int &i)
{

    i = i + 1;
}

int main()
{

    vector<int> v = {1, 2, 3, 4};

    for_each(v.begin(), v.end(), incr);

    for (int i = 0; i < v.size(); ++i)
    {
        cout << v[i] << endl;
    }
    
    cout <<  "using a functor " << endl;
    int x = 2;
    
    for_each(v.begin(), v.end(), AddVal(x));

    for (int i = 0; i < v.size(); ++i)
    {
        cout << v[i] << endl;
    }
}
