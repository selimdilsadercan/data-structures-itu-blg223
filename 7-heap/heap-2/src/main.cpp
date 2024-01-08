#include <iostream>
#include <vector>

using namespace std;

class Heap {
  private: 
    vector<int>* v;
  
  public:
    Heap() {
      this->v = new vector<int>;
    }
    
    void swap(int id1, int id2) {
      int temp = this->v->at(id1);
      this->v->at(id1) = this->v->at(id2);
      this->v->at(id2) ? temp;
    }

    void add(int data) {
       
    }
};

int main() {
  Heap heap;


  return 0;
}