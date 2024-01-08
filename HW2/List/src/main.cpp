/* @Author
Student Name : <"Selim Dilşad Ercan">
StudentID : < 150210104 >
Date :< "29.10.2023" > 
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <ios>
#include <time.h>
#include <list>

using namespace std;

////

class Employee {
  private:
    int id;
    int salary;
    int department;
  public:
    Employee() {}
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
    ~Employee() {}
};


////

void print_employees(list<Employee*>* arr) {
  for (auto& employee : *arr) {
    std::cout << employee->get_id() << ";" << employee->get_salary() << ";" << employee->get_department() << endl;
  }
}


void add_employee(list<Employee*>* arr, int salary, int department) {
  int biggestId = 0;
  for (auto& employee : *arr) {
    if (employee->get_id() > biggestId) {
      biggestId = employee->get_id();
    }
  }

  Employee* emp = new Employee();
  emp->set_id(biggestId + 1);
  emp->set_salary(salary);
  emp->set_department(department);

  arr->push_back(emp);
}


void update_employee(list<Employee*>* arr, int id, int salary, int department) {
  bool worked = false;
  for (auto& employee : *arr) {
    if (employee->get_id() == id) {
      employee->set_salary(salary);
      employee->set_department(department);
      worked = true;
    }
  }

  if(!worked){
    cout << "ERROR: An invalid ID to update";
  }
}


void delete_employee(list<Employee*>* arr, int id) {
  bool found = false;

  for (auto& employee : *arr) {
    if (employee->get_id() == id) {
      arr->remove(employee);
      found = true;
      break;
    }
  }
  
  if(!found){
    cout << "ERROR: An invalid ID to delete";
  }
}


////


int main(int argc, char** argv){
  // clock_t start = clock();

  string row1, id, salary, department, trash;
  fstream dataFile;

  dataFile.open(argv[1], ios::in);
  getline(dataFile, trash);

  list<Employee*>* arr = new list<Employee*>();

  while(getline(dataFile, row1)) {
    stringstream ss1(row1);

    getline(ss1, id, ';');
    getline(ss1, salary, ';');
    getline(ss1, department, ';');

    Employee* emp = new Employee();

    emp->set_id(stoi(id));
    emp->set_salary(stoi(salary));
    emp->set_department(stoi(department));

    arr->push_back(emp);
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
      add_employee(arr, stoi(first), stoi(second));
    }
    if(operation == "UPDATE") {
      update_employee(arr, stoi(first), stoi(second), stoi(third));
    }
    if(operation == "DELETE") {
      delete_employee(arr, stoi(first));
    }
  }

  operationsFile.close();

  // // ////

  ofstream result;
  result.open("list_solution.csv");
  result << "Employee_ID;Salary;Department" << endl;

  stringstream ssfinal;
  for (auto& employee : *arr) {
    ssfinal << employee->get_id() << ";" << employee->get_salary() << ";" << employee->get_department() << endl;
  }
  result << ssfinal.rdbuf();
  result.close();

  // clock_t end = clock();
  // double time = (double)(end - start) / CLOCKS_PER_SEC;
  // cout << "Time: " << time << endl;
  
  for (auto& employee : *arr) { delete employee; }
  delete arr;
  return 0;
}
