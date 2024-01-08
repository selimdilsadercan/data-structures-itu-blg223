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
#include <map>

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
};


////


void printMap(map<int, Employee*>* arr) {
  for (auto it = arr->begin(); it != arr->end(); ++it) {
    cout << it->second->get_id() << ";" << it->second->get_salary() << ";" << it->second->get_department() << endl;
  }
}


void add_employee(map<int, Employee*>* arr, int salary, int department) {
  int biggestId = 0;
  for (auto it = arr->begin(); it != arr->end(); ++it) {
    if (it->second->get_id() > biggestId) {
      biggestId = it->second->get_id();
    }
  }

  Employee* emp = new Employee();
  emp->set_id(biggestId + 1);
  emp->set_salary(salary);
  emp->set_department(department);

  arr->insert(pair<int, Employee*>(emp->get_id(), emp));
}


void update_employee(map<int, Employee*>* arr, int id, int salary, int department) {
  if (arr->count(id) > 0) {
    arr->at(id)->set_salary(salary);
    arr->at(id)->set_department(department);
  }
  else {
    cout << "ERROR: An invalid ID to update" << endl;
  }
}

void delete_employee(map<int, Employee*>* arr, int id) {
  if (arr->count(id) > 0) {
    arr->erase(id);
  }
  else {
    cout << "ERROR: An invalid ID to delete" << endl;
  }
}


int main(int argc, char** argv){
  clock_t start = clock();

  string row1, id, salary, department, trash;
  fstream dataFile;

  dataFile.open(argv[1], ios::in);
  getline(dataFile, trash);

  map<int, Employee*>* arr = new map<int, Employee*>();
  
  while(getline(dataFile, row1)) {
    stringstream ss1(row1);

    getline(ss1, id, ';');
    getline(ss1, salary, ';');
    getline(ss1, department, ';');

    Employee* emp = new Employee();

    emp->set_id(stoi(id));
    emp->set_salary(stoi(salary));
    emp->set_department(stoi(department));

    arr->insert(pair<int, Employee*>(stoi(id), emp));
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

  // ////

  ofstream result;
  result.open("output.csv");
  result << "Employee_ID;Salary;Department" << endl;

  stringstream ssfinal;

  for(auto it = arr->begin(); it != arr->end(); ++it) {
    ssfinal << it->second->get_id() << ";" << it->second->get_salary() << ";" << it->second->get_department() << endl;
  } 

  result << ssfinal.rdbuf();

  result.close();

  clock_t end = clock();
  double time = (double)(end - start) / CLOCKS_PER_SEC;

  cout << "Time: " << time << endl;
  
  for (auto it = arr->begin(); it != arr->end(); ++it) { delete it->second; }
  delete arr;
  return 0;
}
