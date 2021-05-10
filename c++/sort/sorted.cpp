#include <iostream>
#include <vector>
using namespace std;


class sorted {

  public:
  //PRE : LEFT SIDE OF THE VECTOR IS SORTED.
  static vector<int> my_insertion_sort(vector<int> &v) {
    int n = v.size();
    for (int i = 0; i < n; ++i) {
      cout  << "i: " << i << endl; 
      int j = 0;
      int elem = v[i];
      //vector_print_partial(v);
      bool partial_sorted=false;
      while(j < i) {
        if (elem  < v[j] and not partial_sorted) {
          int correct_pos = j;
          int limit_swap = i;
          while (limit_swap > correct_pos) {
            int pos1,pos2;
            pos2 = limit_swap;
            pos1 = pos2-1;
            int aux =  v[pos1];
            v[pos1] = v[pos2];
            v[pos2] = aux;
            --limit_swap;
            partial_sorted=true;
            vector_print_partial(v);
          }
        }
        ++j;
      } 
    }
    return v;
  }


  //PRE : LEFT SIDE OF THE VECTOR IS SORTED.
  static vector<int> insertion_sort_original(vector<int> &v) {
    int n = v.size();
    for (int i = 1; i < n; ++i) {
      int j = i;
      while(j > 0 and v[j] < v[j-1]) {
        int pos1,pos2;
        pos2 = j;
        pos1 = j-1;
        int aux =  v[pos1];
        v[pos1] = v[pos2];
        v[pos2] = aux;
        --j;
      }
    }
    return v;   
  }


  


  static vector<int> merge_sort(vector<int> &v) {

    return v;

  }


  static vector<int> quick_sort(vector<int> &v) {

    return v;

  }




  static void vector_print_partial(vector<int> &v) {
    for(int i =0; i < v.size(); ++i) {
      cout << v[i] << " ";
    }
    cout << endl;
  }

  static void my_swap(int& a, int&b) {
    int aux = a;
    a = b;
    b = a;
  }


  //pre: a  and b are ordered vector (incrisily)
  static vector<int> merge(vector<int> &a, vector<int> &b) {
    vector<int> c;

    while (!a.empty() or !b.empty()) {
      if (a[0] < b[0]) {
        c.push_back(a[0]);
        a.erase(a.begin()+0);
      }
      else {
        c.push_back(b[0]);
        b.erase(b.begin()+0);
      }
    }

    //either a or b will be empty at this point

    while (!a.empty()) {
      c.push_back(a[0]);
      a.erase(a.begin()+0);
    }
    

    while (!b.empty()) {
      c.push_back(b[0]);
      b.erase(b.begin()+0);
    }
    return c;


  }

};





void vector_print(vector<int> &v) {

  for(int i =0; i < v.size(); ++i) {
    cout << v[i] << " ";
  }
  cout << endl;
}






int main() {

  vector<int> v = {2,8,5,3,9,4};
  cout << "inicial1" << endl;
  vector_print(v);
  vector<int> res = sorted::my_insertion_sort(v);
  vector_print(res);





  vector<int> v2 = {1,2,3,4,5,6};
  cout << "inicial2" << endl;
  vector_print(v2);
  vector<int> res2 = sorted::my_insertion_sort(v2);
  vector_print(res2);



  vector<int> v3 = {5,4,3,2,1};
  cout << "inicial3" << endl;
  vector_print(v3);
  vector<int> res3 = sorted::my_insertion_sort(v3);
  vector_print(res3);

  cout << "merge v2 v3" << endl;
  vector<int> merged = sorted::merge(v2,v3);
  vector_print(merged);





  vector<int> v4 = {1,2,-5,3,4};
  cout << "inicial4" << endl;
  vector_print(v4);
  vector<int> res4 = sorted::insertion_sort_original(v4);
  vector_print(res4);

  
  vector<int> v5 = {2,8,5,3,9,4};
  cout << "inicial5" << endl;
  vector_print(v5);
  vector<int> res5 = sorted::insertion_sort_original(v5);
  cout << "final5" << endl;
  vector_print(res5);


}