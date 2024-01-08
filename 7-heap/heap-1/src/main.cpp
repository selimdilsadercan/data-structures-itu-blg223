#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
  vector<int> heap = {12, 35, 21, 10, 11, 8, 22, 23, 30};
  make_heap(heap.begin(), heap.end());

  for(int item : heap) {
    cout << item << " - ";
  }
  cout << endl;

  heap.push_back(45);
  push_heap(heap.begin(), heap.end());

  for(int item : heap) {
    cout << item << " - ";
  }
  cout << endl;

  sort_heap(heap.begin(), heap.end())

  for(int item : heap) {
    cout << item << " - ";
  }
  cout << endl;

  return 0;
}