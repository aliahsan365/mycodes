#include <iostream>
#include <vector>
using namespace std;



void vector_print(vector<int> &v) {

  for(int i =0; i < v.size(); ++i) {
    cout << v[i] << " ";
  }
  cout << endl;
}



vector<int> my_insertion_sort(vector<int> &v) {
  int n = v.size();
  for (int i = 1; i < n-1; ++i) {
    int j =  i;
    while (j > 0 and v[j] < v[j-1]) {
      int pos1,pos2;
      pos1 = j-1;
      pos2 = j;
      int aux = v[pos1];
      v[pos1]= v[pos2];
      v[pos2] = aux;
      --j;
    }
  }
  return v;  
}






int main() {

  vector<int> v = {2,8,5,3,9,4};
  cout << "inicial1" << endl;
  vector_print(v);
  vector<int> res = my_insertion_sort(v);
  vector_print(res);





  vector<int> v2 = {1,2,3,4,5,6};
  cout << "inicial2" << endl;
  vector_print(v2);
  vector<int> res2 = my_insertion_sort(v2);
  vector_print(res2);



  vector<int> v3 = {5,4,3,2,1};
  cout << "inicial3" << endl;
  vector_print(v3);
  vector<int> res3 = my_insertion_sort(v3);
  vector_print(res3);



  vector<int> v4 = {1,1,0,1,-1,2};
  cout << "inicial4" << endl;
  vector_print(v4);
  vector<int> res4 = my_insertion_sort(v4);
  vector_print(res4);

}