#include <iostream>
#include <stack>

using namespace std;

const int CAPACITY = 5;

class MyStack {
    private:
        int top;
         int* arr = new int[CAPACITY];
    public: 
        MyStack(){
            this->top = -1;
        }
        ~MyStack() {
            delete[] arr;
        }
        bool push(int value) {
            if(this->isFull()) {
                return false;
            }
            this->arr[++this->top] = value;
            return true;
        }
        int pop() {
            return this->arr[this->top--];
        }
        bool isEmpty() {
            return this->top == -1;
        }
        bool isFull() {
            return this->top == CAPACITY - 1;
        }
        void clear() {
            this->top = -1;
        }
        int peek() {
            return this->arr[this->top];
        }
        void print() {
            for(int i = 0; i <= CAPACITY; i++) {
                cout << this->arr[i] << " ";
            }
            cout << " - ";
            for(int i = 0; i <= this->top; i++) {
                cout << this->arr[i] << " ";
            }
            cout << endl;
        }
};



void print_array1(int* arr) {
    for (int i = 0; i < 5; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}


void print_array2(int* arr, int top) {
    cout << "top: " << top << " - ";

    for (int i = 0; i < 5; i++) {
        cout << arr[i] << " ";
    }

    cout << endl;
}


void stack_03() {
    MyStack ms = MyStack();

    ms.print();
    cout << endl;
    cout << "isEmpty: " << ms.isEmpty() << endl; // arr.isEmpty()
    cout << "isFull: " << ms.isFull() << endl; // arr.isFull()
    cout << endl;

    ms.push(8);
    ms.print();

    ms.push(9);
    ms.print();

    cout << endl;
    cout << "isEmpty: " << ms.isEmpty() << endl; // arr.isEmpty()
    cout << "isFull: " << ms.isFull() << endl; // arr.isFull()
    cout << endl;   

    ms.pop();
    ms.print();

    cout << "pop: " << ms.pop() << endl;
    ms.print();

    cout << endl;
    cout << "isEmpty: " << ms.isEmpty() << endl; // arr.isEmpty()
    cout << "isFull: " << ms.isFull() << endl; // arr.isFull()
    cout << endl;   

    ms.push(1);
    ms.print();

    ms.push(2);
    ms.print();

    cout << "peek: " << ms.peek() << endl;

    ms.push(3);
    ms.print();

    ms.push(4);
    ms.print();

    ms.clear();
    ms.print();

    ms.push(5);
    ms.print();

    cout << endl;
    cout << "isEmpty: " << ms.isEmpty() << endl; // arr.isEmpty()
    cout << "isFull: " << ms.isFull() << endl; // arr.isFull()
    cout << endl;  
}

void stack_02() {
    int* arr = new int[5];
    int top = -1;

    print_array2(arr, top);
    cout << endl;
    cout << "isEmpty: " << (top == -1) << endl; // arr.isEmpty()
    cout << "isFull: " << (top == 4) << endl; // arr.isFull()
    cout << endl;

    arr[++top] = 8; // arr.push(8)
    print_array2(arr, top);

    arr[++top] = 9; // arr.push(9)
    print_array2(arr, top); 

    
    cout << endl;
    cout << "isEmpty: " << (top == -1) << endl; // arr.isEmpty()
    cout << "isFull: " << (top == 4) << endl; // arr.isFull()
    cout << endl;

    
    print_array2(arr, --top); // arr.pop()

    arr[++top] = 4; // arr.push(4)
    print_array2(arr, top); 


    cout << endl;
    cout << "isEmpty: " << (top == -1) << endl; // arr.isEmpty()
    cout << "isFull: " << (top == 4) << endl; // arr.isFull()
    cout << endl;


    print_array2(arr, --top); // arr.pop()

    print_array2(arr, --top); // arr.pop()


    cout << endl;
    cout << "isEmpty: " << (top == -1) << endl; // arr.isEmpty()
    cout << "isFull: " << (top == 4) << endl; // arr.isFull()
    cout << endl;


    arr[++top] = 1; // arr.push(1)
    print_array2(arr, top); 

    arr[++top] = 2; // arr.push(2)
    print_array2(arr, top); 

    arr[++top] = 3; // arr.push(3)
    print_array2(arr, top); 

    arr[++top] = 4; // arr.push(4)
    print_array2(arr, top);   

    arr[++top] = 5; // arr.push(5)
    print_array2(arr, top); 


    cout << endl;
    cout << "isEmpty: " << (top == -1) << endl; // arr.isEmpty()
    cout << "isFull: " << (top == 4) << endl; // arr.isFull()
    cout << endl;
}


void stack_01() {
    int* arr = new int[5];

    arr[0] = 8; // arr.push(8)
    print_array1(arr);

    arr[1] = 9; // arr.push(9)
    print_array1(arr);


    cout << endl;
    cout << "isEmpty: " << (arr[0] == -1) << endl; // arr.isEmpty()
    cout << "isFull: " << (arr[4] != 0 && arr[4] != -1) << endl; // arr.isFull()
    cout << endl;


    arr[1] = -1; // arr.pop()
    print_array1(arr);

    arr[0] = -1; // arr.pop()
    print_array1(arr);

    cout << endl;
    cout << "isEmpty: " << (arr[0] == -1 || arr[0] == 0) << endl; // arr.isEmpty()
    cout << "isFull: " << (arr[4] != 0 && arr[4] != -1) << endl; // arr.isFull()
    cout << endl;

    arr[0] = 8; // arr.push(8)
    print_array1(arr);

    arr[1] = 9; // arr.push(9)
    print_array1(arr);

    arr[2] = 8; // arr.push(8)
    print_array1(arr);

    arr[3] = 9; // arr.push(9)
    print_array1(arr);

    arr[4] = 8; // arr.push(8)
    print_array1(arr);

    cout << endl;
    cout << "isEmpty: " << (arr[0] == -1) << endl; // arr.isEmpty()
    cout << "isFull: " << (arr[4] != 0 && arr[5] != -1) << endl; // arr.isFull()
    cout << endl;
}

class islem {
    private:
        char text;
        bool type;
    public:
        islem(char text, bool type) {
            this->text = text;
            this->type = type;
        }
};

int main() {
    stack<islem*> gecmis = stack<islem*>();
    gecmis.push(new islem('A', true));
    gecmis.push(new islem('B', true));
    gecmis.push(new islem('B', false));

    for(int i = 0; i <= gecmis.size(); i++) {
        cout << a;
    }


    return 0;
}