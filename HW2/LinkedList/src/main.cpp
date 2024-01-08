/* @Author
Student Name: "Selim Dilşad Ercan"
StudentID: 150210104
Date: "29.10.2023"
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <ios>
#include <time.h>
#include <vector>

using namespace std;

////

class Employee {
  private:
    int id;
    int salary;
    int department;
    Employee* next;
  public:
    Employee(int id, int salary, int department) {
      this->id = id;
      this->salary = salary;
      this->department = department;
      this->next = nullptr;
    }
    void set_salary(int salary) {
      this->salary = salary;
    }
    void set_id(int id) {
      this->id = id;
    }
    void set_department(int department) {
      this->department = department;
    }
    int get_id() {
      return this->id;
    }
    int get_salary() {
      return this->salary;
    }
    int get_department() {
      return this->department;
    }
    void set_next(Employee* next) {
      this->next = next;
    }
    Employee* get_next() {
      return this->next;
    }
    ~Employee() {}
};


class SingleLinkedList {
  private:
    Employee* head;
    Employee* tail;

  public:
    SingleLinkedList() {
      head = nullptr;
      tail = nullptr;
    }

    void add(Employee* employee) {
      if (head == nullptr) {
        head = employee;
        tail = employee;
      } else {
        tail->set_next(employee);
        tail = employee;
      }
    }

    void update(int id, int salary, int department) {
      Employee* current = head;

      bool worked = false;
      while (current != nullptr) {
        if (current->get_id() == id) {
          current->set_salary(salary);
          current->set_department(department);
          break;
        }
        current = current->get_next();
        worked = true;
      }

      if(!worked){
        cout << "ERROR: An invalid ID to update";
      }
    }

    void remove(int id) {
      Employee* previous = nullptr;
      Employee* current = head;

      bool found = false;
      while (current != nullptr) {
        if (current->get_id() == id) {
          if (previous == nullptr) {
            head = current->get_next();
          } 
          else {
            previous->set_next(current->get_next());
          }

          if (current == tail) {
            tail = previous;
          }

          delete current;
          found = true;
          break;
        }
        previous = current;
        current = current->get_next();
      }

      if(!found){
        cout << "ERROR: An invalid ID to delete";
      }
    }

    void print_list() {
      Employee* current = head;
      while (current != nullptr) {
        cout << current->get_id() << ";" << current->get_salary() << ";" << current->get_department() << endl;
        current = current->get_next();
      }
    }

    int find_biggest_id() {
      Employee* current = head;
      int biggest_id = 0;

      while (current != nullptr) {
        if (current->get_id() > biggest_id) {
          biggest_id = current->get_id();
        }
        current = current->get_next();
      }

      return biggest_id;
    }

    void add_employee_operation(int salary, int department) {
      int biggest_id = find_biggest_id();
      add(new Employee(biggest_id + 1, salary, department));
    }

    bool isContains(int id) {
      Employee* current = head;
      while (current != nullptr) {
        if (current->get_id() == id) {
          return true;
        }
        current = current->get_next();
      }
      return false;
    }

    stringstream create_ss() {
      stringstream ss;

      for (Employee* current = head; current != nullptr; current = current->get_next()) {
        ss << current->get_id() << ";" << current->get_salary() << ";" << current->get_department() << endl;
      }

      return ss;
    }

    ~SingleLinkedList() {
      Employee* current = head;
      while (current != nullptr) {
        Employee* next = current->get_next();
        delete current;
        current = next;
      }
    }
};


////


int main(int argc, char** argv){
  // clock_t start = clock();

  string row1, id, salary, department, trash;
  fstream dataFile;

  dataFile.open(argv[1], ios::in);
  getline(dataFile, trash);

  SingleLinkedList* arr = new SingleLinkedList();

  while(getline(dataFile, row1)) {
    stringstream ss1(row1);

    getline(ss1, id, ';');
    getline(ss1, salary, ';');
    getline(ss1, department, ';');

    arr->add(new Employee(stoi(id), stoi(salary), stoi(department)));
  }

  dataFile.close();


  // ////

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
      arr->add_employee_operation(stoi(first), stoi(second));
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
  result.open("linked_list_solution.csv");
  result << "Employee_ID;Salary;Department" << endl;

  stringstream ssfinal = arr->create_ss();
  result << ssfinal.rdbuf();
  result.close();

  // clock_t end = clock();
  // double time = (double)(end - start) / CLOCKS_PER_SEC;
  // cout << "Time: " << time << endl; //Time: 0.824929

  delete arr;
  return 0;
}
