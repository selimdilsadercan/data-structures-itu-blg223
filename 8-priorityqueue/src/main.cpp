#include <iostream>
#include <queue>

using namespace std;

void print_queue(priority_queue<int>& pq) {
  while(!pq.empty()) {
    cout << pq.top() << " - ";
    pq.pop();
  }
  cout << endl;
}

int main() {
  priority_queue<int> pq;

  pq.push(30);
  pq.push(20);
  pq.push(40);
  pq.push(10);
  pq.push(400);
  
  print_queue(pq);

  return 0;
}