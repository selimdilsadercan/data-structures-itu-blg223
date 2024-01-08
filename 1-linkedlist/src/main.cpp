#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <ios>
#include <time.h>
#include <vector>

using namespace std;

class DoubleNode {
  private:
    int data;
    DoubleNode* next;
    DoubleNode* prev;
  public:
    DoubleNode(int data) {
      this->data = data;
      this->next = NULL;
      this->prev = NULL;
    }
    void set_data(int data){
      this->data = data;
    }
    int get_data(){
      return this->data;
    }
    void set_next(DoubleNode* next){
      this->next = next;
    }
    DoubleNode* get_next(){
      return this->next;
    }
    void set_prev(DoubleNode* prev){
      this->prev = prev;
    }
    DoubleNode* get_prev() {
      return this->prev;
    }
};
class AscendingDoubleLinkedList {
  private:
    DoubleNode* head;
    DoubleNode* tail;
  public:
    AscendingDoubleLinkedList() {
      this->head = NULL;
      this->tail = NULL;
    }

    ~AscendingDoubleLinkedList() {
      clear();
    }

    bool contains(int data) {
      DoubleNode* current = head;
      while(current != NULL) {
        if(data == current->get_data()) {
          return true;
        }
        current = current->get_next();
      }
      return false;
    }

    DoubleNode* search(int data) {
      DoubleNode* prev = this->head;
      if(data <= prev->get_data()) {
        return NULL;
      }
      while(prev->get_next() != NULL) {
        if(data <= prev->get_next()->get_data()) {
          return prev;
        }
        prev = prev->get_next();
      }
      return prev;
    }

    DoubleNode* find(int data) {
      DoubleNode* current = this->head;
      while(current != NULL) {
        if(data == current->get_data()) {
          return current;
        }
        current = current->get_next();
      }
    }

    void add(int data) {
      DoubleNode* n = new DoubleNode(data);
      if(this->head == NULL) {
        this->head = n;
        tail = n;
        return;
      }
      DoubleNode* prev = search(data);
      if(prev == NULL) {
        n->set_next(this->head);
        this->head->set_prev(n);
        this->head = n;
        return;
      }
      if(prev->get_next() == NULL) {
        tail = n;
      }
      n->set_next(prev->get_next());
      if(n->get_next() != NULL) {
        n->get_next()->set_prev(n);
      }
      prev->set_next(n);
      n->set_prev(prev);
    }

    void remove(int data) {
      if(this->head == NULL) {
        cout << "List is empty." << endl;
        return;
      }
      if(!contains(data)) {
        cout << "Element " << data << " is not in the list." << endl;
        return;
      }
      if(head == tail) {
        head = NULL;
        tail = NULL;
        return;
      }
      DoubleNode* current = find(data);
      DoubleNode* prev = current->get_prev();
      DoubleNode* next = current->get_next();
      if(next == NULL) {
        tail = prev;
      }
      else {
        next->set_prev(prev);
      }
      if(prev == NULL) {
        head = next;
      }
      else {
        prev->set_next(next);
      }
    }

    void print() {
      if(this->head == NULL) {
        cout << "List is empty." << endl;
        return;
      }
      DoubleNode* current = this->head;
      cout << current->get_data();
      while(current->get_next() != NULL) {
        current = current->get_next();
        cout << " -> " << current->get_data();
      }
      cout << endl;
    }

    void printReverse() {
      if(this->head == NULL) {
        cout << "List is empty." << endl;
        return;
      }
      DoubleNode* current = this->tail;
      cout << current->get_data();
      while(current->get_prev() != NULL) {
        current = current->get_prev();
        cout << " <- " << current->get_data();
      }
      cout << endl;
    }

    void clear() {
      DoubleNode* current = this->head;
      DoubleNode* next;

      while(current != NULL) {
        next = current->get_next();
        delete current;
        current = next;
      }

      this->head = NULL;
      this->tail = NULL;
    }
};
void LinkedList_03() {
  AscendingDoubleLinkedList list;
  list.add(5);
  list.add(3);
  list.add(2);
  list.add(7);
  list.add(4);
  list.print();
  list.printReverse();

  list.remove(97);
  list.remove(7);
  list.remove(3);
  list.remove(2);
  list.print();
  list.printReverse();

  list.remove(5);
  list.print();
  list.printReverse();

  list.remove(4);
  list.print();
  list.printReverse();
}

class Node {
  private:
    int data;
    Node* next;
  public:
    Node(int data){
      this->data = data;
      this->next = NULL;
    }
    int get_data(){
      return this->data;
    }
    Node* get_next(){
      return this->next;
    }
    void set_data(int data){
      this->data = data;
    }
    void set_next(Node* next){
      this->next = next;
    }
};
class AscendingLinkedList {
  private:
    Node* head;
    Node* tail;

  public: 
    AscendingLinkedList() {
      this->head = NULL;
      this->tail = NULL;
    }

    ~AscendingLinkedList(){
      clear();
    }

    Node* search(int data) {
      Node* prev = this->head;

      if(data <= head->get_data()) {
        return NULL;
      }
      while(prev->get_next() != NULL) {
        if(prev->get_next()->get_data() >= data) {
          return prev;
        }
        prev = prev->get_next();
      }
      return prev;
    }

    bool contains(int data) {
      Node* current = this->head;
      while(current != NULL) {
        if(current->get_data() == data){
          return true;
        }
        current = current->get_next();
      }
      return false;
    }

    void add(int data) {
      Node* n = new Node(data);
      if(this->head == NULL) {
        this->head = n;
        this->tail = n;
        return;
      }
      Node* prev = search(data);
      if(prev == NULL) {
        n->set_next(this->head);
        this->head = n;
        return;
      }
      if(prev->get_next() == NULL){
        this->tail = n;
      }
      n->set_next(prev->get_next());
      prev->set_next(n);
    }

    void remove(int data) {
      if(this->head == NULL) {
        cout << "List is empty." << endl;
        return;
      }
      if(!contains(data)) {
        cout << "Element " << data << " is not in the list." << endl;
        return;
      }
      if(tail == head) {
        head = NULL;
        tail = NULL;
        return;
      }
      Node* prev = search(data);
      if(prev == NULL){
        head = head->get_next();
        return;
      }
      Node* current = prev->get_next();
      prev->set_next(current->get_next());
      if(current->get_next() == NULL){
        this->tail = prev;
      }
    }

    void print() {
      if(this->head == NULL) {
        cout << "List is empty." << endl;
        return;
      }
      Node* current = this->head;

      cout << current->get_data();

      while(current->get_next() != NULL) {
        cout << " -> " << current->get_next()->get_data();
        current = current->get_next();
      } 
      cout << endl;
    }

    void clear() {
      Node* current = this->head;
      Node* next;

      while(current != NULL) {
        next = current->get_next();
        delete current;
        current = next;
      }

      this->head = NULL;
      this->tail = NULL;
    }
};
void LinkedList_02() {
  AscendingLinkedList list;
  list.add(5);
  list.add(3);
  list.add(2);
  list.add(7);
  list.add(4);
  list.print();

  list.remove(97);
  list.remove(7);
  list.remove(3);
  list.remove(2);
  list.print();

  list.remove(5);
  list.print();

  list.remove(4);
  list.print();
}

void printNodes(Node* head) {
  Node* current = head;

  cout << current->get_data();

  while(current->get_next() != NULL) {
    cout << " -> " << current->get_next()->get_data();
    current = current->get_next();
  } 
  cout << endl;
}
void linkedlist_01() {
  Node* head = new Node(5);
  head->set_next(new Node(1));
  head->get_next()->set_next(new Node(10));
  head->get_next()->get_next()->set_next(new Node(8));
  printNodes(head);
}

int main(){
  // linkedlist_01();
  // LinkedList_02();
  LinkedList_03();

  return 0;
}