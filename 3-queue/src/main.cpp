#include <iostream>

using namespace std;

const int CAPACITY = 5;

class MyQueue {
    private:
        int* arr = new int[CAPACITY];
        int front;
        int back;
        int num_of_items;
    public: 
        MyQueue(){
            front = 0;
            back = -1;
            num_of_items = 0;
        }
        ~MyQueue() {
            delete[] arr;
        }
        
        bool isEmpty() {
            return this->num_of_items == 0;
        }
        bool isFull() {
            return this->num_of_items == CAPACITY;
        }
        void clear(){
            front = 0;
            back = -1;
            num_of_items = 0;
        }

        int peek_front(){
            if(!this->isEmpty())
                return this->arr[this->front];
            return -1;
        }
        int peek_back(){
            if(!this->isEmpty())
                return this->arr[this->back];
            return -1;
        }

        bool enqueue(int element){
            if(!this->isFull()){
                this->back = (this->back+1) % CAPACITY;
                this->arr[this->back] = element;
                this->num_of_items++;
                return true;
            }
            return false;
        }
        int dequeue(){
            if(!this->isEmpty()){
                int element = this->arr[this->front];
                this->front = (this->front+1) % CAPACITY;
                this->num_of_items--;
                return element;
            }
            return -1;
        }

        void print() {
            for(int i = 0; i <= CAPACITY; i++) {
                cout << this->arr[i] << " ";
            }
            cout << " - ";
            for(int i = this->back; i <= this->front; i++) {
                cout << this->arr[i] << " ";
            }
            cout << endl;
        }
};



void queue_01() {
    MyQueue que = MyQueue();

    que.print();
    cout << endl;
    cout << "isEmpty: " << que.isEmpty() << endl; // arr.isEmpty()
    cout << "isFull: " << que.isFull() << endl; // arr.isFull()
    cout << endl;

    que.push(8);
    que.print();

    que.push(9);
    que.print();

    cout << endl;
    cout << "isEmpty: " << que.isEmpty() << endl; // arr.isEmpty()
    cout << "isFull: " << que.isFull() << endl; // arr.isFull()
    cout << endl;   

    que.pop();
    que.print();

    cout << "pop: " << que.pop() << endl;
    que.print();

    cout << endl;
    cout << "isEmpty: " << que.isEmpty() << endl; // arr.isEmpty()
    cout << "isFull: " << que.isFull() << endl; // arr.isFull()
    cout << endl;   

    que.push(1);
    que.print();

    que.push(2);
    que.print();

    cout << "peek: " << que.peek() << endl;

    que.push(3);
    que.print();

    que.push(4);
    que.print();

    que.clear();
    que.print();

    que.push(5);
    que.print();

    cout << endl;
    cout << "isEmpty: " << que.isEmpty() << endl; // arr.isEmpty()
    cout << "isFull: " << que.isFull() << endl; // arr.isFull()
    cout << endl;  
}


int main() {
    queue_01();
    
    return 0;
}