/* @Author
Student Name: "Selim Dilşad Ercan"
StudentID: 150210104
Date: "29.12.2023"
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <ios>
#include <time.h>
#include <cstdlib> 
#include <ctime> 

using namespace std;

////

class Employee {
  private:
    int id;
    int salary;
    int department;
  public:
    Employee(int id, int salary, int department) {
      this->id = id;
      this->salary = salary;
      this->department = department;
    }
    void setSalary(int salary) {
      this->salary = salary;
    }
    void setId(int id) {
      this->id = id;
    }
    void setDepartment(int department) {
      this->department = department;
    }
    int getId() {
      return this->id;
    }
    int getSalary() {
      return this->salary;
    }
    int getDepartment() {
      return this->department;
    }
};


class Node {
    private:
      Employee* employee;
      Node* next;
      Node* prev;
      Node* below;
      Node* above;
    public:
      Node(Employee* employee) {
        this->employee = employee;
        this->next = NULL;
        this->prev = NULL;
        this->below = NULL;
        this->above = NULL;
      }
      Employee* getEmployee() {
        return this->employee;
      }
      Node* getNext() {
        return this->next;
      }
      Node* getPrev() {
        return this->prev;
      }
      Node* getBelow() {
        return this->below;
      }
      Node* getAbove() {
        return this->above;
      }
      void setEmployee(Employee* employee) {
        this->employee = employee;
      }
      void setNext(Node* next) {
        this->next = next;
      }
      void setPrev(Node* prev) {
        this->prev = prev;
      }
      void setBelow(Node* below) {
        this->below = below;
      }
      void setAbove(Node* above) {
        this->above = above;
      }
};

class QuadruplySkipList {
  private:
    Node* head = NULL;
    int height;

    int generateRandomLevel() {
      int level = 1;
      while (rand() % 2 == 0 && level < height) {
        level++;
      }
      return level;
    }

  public: 
    QuadruplySkipList(int height_in) {
      this->height = height_in;
      srand(time(0));  
    };

    ~QuadruplySkipList() {
      delete this->head;
    };

    void insert(Employee* data) {
      if (head == NULL) {
        head = new Node(data);
        for (int i = 0; i < height-1; ++i) {
          Node* newNode = new Node(data);
          head->setBelow(newNode);
          newNode->setAbove(head);
        }
      }

      Node* current = head;
      Node* insertBelow = nullptr;
      Node* newHead = nullptr;

      Node* newNode = new Node(data);
      newNode->setBelow(insertBelow);
      insertBelow = newNode;

      while (current->getNext() != nullptr && current->getNext()->getEmployee() != nullptr && current->getNext()->getEmployee()->getId() < data->getId()) {
        current = current->getNext();
      }

      newNode->setNext(current->getNext());
      newNode->setPrev(current);
      if (current->getNext() != nullptr) {
        current->getNext()->setPrev(newNode);
      }
      current->setNext(newNode);

      // if (i == 0) {
      //   newHead = newNode;
      // }
      // if (i < height - 1 && rand() % 2 == 0) {
      //   Node* levelUpNode = new Node(nullptr);
      //   levelUpNode->setBelow(newHead);
      //   levelUpNode->setNext(newNode->getNext());
      //   levelUpNode->setPrev(newNode);
      //   newNode->setNext(levelUpNode);
      //   newNode->getNext()->setPrev(levelUpNode);

      //   // Set the above pointer of the node below at the lower level
      //   if (newHead->getBelow() != nullptr) {
      //     newHead->getBelow()->setAbove(levelUpNode);
      //   }

      //   newHead = levelUpNode;
      //   current = levelUpNode;
      // }
    }


    void printList() {
      Node* current = this->head;

      while (current != nullptr) {
        Node* nodeBelow = current;
        while (nodeBelow != nullptr) {
          Employee* employee = nodeBelow->getEmployee();
          if (employee != nullptr) {
            cout << employee->getId() << ";" << employee->getSalary() << ";" << employee->getDepartment() << " | ";
          }
          nodeBelow = nodeBelow->getBelow();
        }
        cout << endl;
        current = current->getNext();
      }
    }
};

////




int main(int argc, char** argv){
  // clock_t start = clock();

  string row1, id, salary, department, trash;
  fstream dataFile;
  int maxId = 0;

  dataFile.open(argv[1], ios::in);
  getline(dataFile, trash);

  QuadruplySkipList* arr = new QuadruplySkipList(3);

  arr->insert(new Employee(1, 1, 1));
  arr->insert(new Employee(2, 1, 1));
  arr->insert(new Employee(3, 1, 1));
  arr->insert(new Employee(4, 1, 1));
  arr->printList();
  
  // while(getline(dataFile, row1)) {
  //   stringstream ss1(row1);

  //   getline(ss1, id, ';');
  //   getline(ss1, salary, ';');
  //   getline(ss1, department, ';');

  //   arr->insert(new Employee(stoi(id), stoi(salary), stoi(department)));
  //   maxId++;
  // }

  // dataFile.close();


  ////

  // fstream operationsFile;
  // operationsFile.open(argv[2], ios::in);

  // string row2;

  // while(getline(operationsFile, row2)){
  //   if(row2.find("PRINT") != string::npos) {
  //     cout << "P" << endl;
  //     arr->printToConsole();
  //   }

  //   if(row2.find("HEIGHT") != string::npos) {
  //     cout << "H " << arr->getHeight() << endl;
  //   }

  //   stringstream ss2(row2);
  //   string operation, first, second, third;

  //   getline(ss2, operation, ';'); 
  //   getline(ss2, first, ';');
  //   getline(ss2, second, ';');
  //   getline(ss2, third, ';');


  //   if(operation == "ADD"){
  //     arr->insert(new Employee(++maxId, stoi(first), stoi(second)));
  //   }
  //   if(operation == "UPDATE") {
  //     arr->update(stoi(first), stoi(second), stoi(third));
  //   }
  //   if(operation == "DELETE") {
  //     arr->remove(stoi(first));
  //   }
  // }

  // operationsFile.close();

  ////

  // ofstream result;
  // result.open("output.csv");

  // arr->printToFile(result);

  // clock_t end = clock();
  // double time = (double)(end - start) / CLOCKS_PER_SEC;

  // cout << "Time: " << time << endl;
  
  // delete arr;
  return 0;
}
