/* @Author
Student Name: "Selim Dilşad Ercan"
StudentID: 150210104
Date: "16.12.2023"
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <ios>
#include <time.h>
#include <vector>

using namespace std;
const int SIZE = 5000;

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
      Node* left;
      Node* right;
    public:
      Node(Employee* employee) {
        this->employee = employee;
        this->left = NULL;
        this->right = NULL;
      }
      Employee* getEmployee() {
        return this->employee;
      }
      Node* getLeft() {
        return this->left;
      }
      Node* getRight() {
        return this->right;
      }
      void setEmployee(Employee* employee) {
        this->employee = employee;
      }
      void setLeft(Node* left) {
        this->left = left;
      }
      void setRight(Node* right) {
        this->right = right;
      }
};

class BinaryTree {
  private:
    Node* root = NULL;

    Node* removeRecursion(Node* node, int id) {
      if (node == NULL) {
        return node;
      }

      if (id < node->getEmployee()->getId()) {
        node->setLeft(removeRecursion(node->getLeft(), id));
        return node;
      }

      if (id > node->getEmployee()->getId()) {
        node->setRight(removeRecursion(node->getRight(), id));
        return node;
      }

      if (node->getLeft() == NULL) {
        Node* temp = node->getRight();
        delete node;
        return temp;
      } 

      if (node->getRight() == NULL) {
        Node* temp = node->getLeft();
        delete node;
        return temp;
      }

      Node* temp = node->getRight();
      while (temp->getLeft() != NULL) {
        temp = temp->getLeft();
      }
      node->setEmployee(temp->getEmployee());
      node->setRight(removeRecursion(node->getRight(), temp->getEmployee()->getId()));
      return node;
    }

    void preorderRecursion(Node* top) {
      cout << top->getEmployee()->getId() << ";" << top->getEmployee()->getSalary() << ";" << top->getEmployee()->getDepartment() << "\n";
      if(top->getLeft()) { this->preorderRecursion(top->getLeft()); }
      if(top->getRight()) { this->preorderRecursion(top->getRight()); }
    }

    string inorderRecursion(Node* top) {
      stringstream ss;
      if(top->getLeft()) { ss << this->inorderRecursion(top->getLeft()); }
      ss << top->getEmployee()->getId() << ";" << top->getEmployee()->getSalary() << ";" << top->getEmployee()->getDepartment() << endl;
      if(top->getRight()) { ss << this->inorderRecursion(top->getRight()); }
      return ss.str();
    }

    int getHeightRecursion(Node* top) {
      if (top == NULL) {
        return 0;
      }
      int leftHeight = getHeightRecursion(top->getLeft());
      int rightHeight = getHeightRecursion(top->getRight());

      return max(leftHeight, rightHeight) + 1;
    }

    public:
      BinaryTree() {};

      ~BinaryTree() {
        delete this->root;
      };

      void insert(Employee* employee) {
        if (this->root == NULL) {
          this->root = new Node(employee);
        }
        Node* current = this->root;
        while(true) {
          if (employee->getId() == current->getEmployee()->getId()){
            break;
          }
          else if (employee->getId() < current->getEmployee()->getId()) {
            if(current->getLeft()) { 
              current = current->getLeft(); 
            }
            else {
              current->setLeft(new Node(employee)); 
              break;
            }
          }
          else if (employee->getId() > current->getEmployee()->getId()) {
            if(current->getRight()) { 
              current = current->getRight(); 
            }
            else {
              current->setRight(new Node(employee)); 
              break;
            }
          }
        } 
      }

      void remove(int id) {
        if (search(id) == NULL) {
          cout << "ERROR: An invalid ID to delete" << endl;
          return;
        }
        this->root = removeRecursion(this->root, id);
      }

      void update(int id, int salary, int department) {
        if (this->search(id) == NULL) {
          cout << "ERROR: An invalid ID to update" << endl;
          return;
        }
        Employee* emp = this->search(id)->getEmployee();
        emp->setSalary(salary);
        emp->setDepartment(department);
      }

      Node* search(int id) {
        Node* current = this->root;
        while(true) {
          if (id == current->getEmployee()->getId()){
            return current;
          }
          else if (id < current->getEmployee()->getId()) {
            if(current->getLeft()) { current = current->getLeft(); }
            else { break; }
          }
          else if (id > current->getEmployee()->getId()) {
            if(current->getRight()) { current = current->getRight(); }
            else { break; }
          } 
        }
        return NULL;
      };

      int getHeight() {
        return getHeightRecursion(this->root);
      }

      void printToConsole() {
        if (this->root == NULL) {
          cout << "Tree is empty" << endl;
          return;
        }
        this->preorderRecursion(this->root);
      }

      void printToFile(ofstream &output_file) {
        if (this->root == NULL) {
          cout << "Tree is empty" << endl;
          return;
        }

        output_file << "Employee_ID;Salary;Department" << endl;

        stringstream ssfinal;
        ssfinal << inorderRecursion(this->root);

        output_file << ssfinal.rdbuf();
        output_file.close();
      }
};

class CustomVector {
  private:
    vector<BinaryTree*>* arr;

  public:
    CustomVector() {
      this->arr = new vector<BinaryTree*>();
    }

    ~CustomVector() {
      delete this->arr;
    }

    void insert(int id, int salary, int department) {
      unsigned int index = id / SIZE;
      if(this->arr->size() <= index) {
        this->arr->insert(this->arr->begin() + index, new BinaryTree());
      }
      this->arr->at(index)->insert(new Employee(id, salary, department));
    }

    void update(int id, int salary, int department) {
      int index = id / SIZE;
      this->arr->at(index)->update(id, salary, department);
    }

    void remove(int id) {
      int index = id / SIZE;
      this->arr->at(index)->remove(id);
    }
   
    void printToFile(ofstream &output_file) {
      for(unsigned int i = 0; i < this->arr->size(); i++) {
        this->arr->at(i)->printToFile(output_file);
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

  CustomVector* arr = new CustomVector();

  while(getline(dataFile, row1)) {
    stringstream ss1(row1);

    getline(ss1, id, ';');
    getline(ss1, salary, ';');
    getline(ss1, department, ';');

    arr->insert(stoi(id), stoi(salary), stoi(department));
    maxId++;
  }

  dataFile.close();
  
  ////

  fstream operationsFile;
  operationsFile.open(argv[2], ios::in);

  string row2;

  while(getline(operationsFile, row2)){
    stringstream ss2(row2);
    string operation, first, second, third;

    getline(ss2, operation, ';');
    getline(ss2, first, ';');
    getline(ss2, second, ';');
    getline(ss2, third, ';');

    if(operation == "ADD"){
      cout << "ADD: " << maxId + 1 << " " << first << " " << second << endl;
      arr->insert(++maxId, stoi(first), stoi(second));
    }
    if(operation == "UPDATE") {
      arr->update(stoi(first), stoi(second), stoi(third));
    }
    if(operation == "DELETE") {
      arr->remove(stoi(first));
    }
  }

  operationsFile.close();

  ////
  ofstream result;
  result.open("output.csv");

  arr->printToFile(result);

  // clock_t end = clock();
  // double time = (double)(end - start) / CLOCKS_PER_SEC;

  // cout << "Time: " << time << endl;
  
  delete arr;
  return 0;
}
