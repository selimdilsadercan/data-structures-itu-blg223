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

using namespace std;

////

int total_error_count = 0;

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

void print_employees(Employee* arr, int size){
  for(int i = 0; i < size; i++){
    cout << arr[i].get_id() << " " << arr[i].get_salary() << " " << arr[i].get_department() << endl;
  }
}

bool isContains(Employee* arr, int size, int id) {
  for(int i = 0; i < size; i++) {
    if(arr[i].get_id() == id) {
      return true;
    };
  }
  return false;
}

bool isValid(Employee* arr, int size, int id, char type) {
  int total_error_count = 0;
  
  if(type == 'u') {
    if(!isContains(arr, size, id)) {
      if(total_error_count != 0) { cout << endl; }
      cout << "ERROR: An invalid ID to update";
      total_error_count++;
      return false;
    }
    else {
      return true;
    }
  }
  else if(type == 'd') {
    if(size == 0) {
      if(total_error_count != 0) { cout << endl; }
      cout << "ERROR: There is no Employee";
      total_error_count++;
      return false;
    }
    else if(!isContains(arr, size, id)) {
      if(total_error_count != 0) { cout << endl; }
      cout << "ERROR: An invalid ID to delete";
      total_error_count++;
      return false;
    }
    else {
      return true;
    }
  } else {
    return false;
  }
}

Employee* delete_employee(Employee* arr, int size, int id) {
  Employee* newArr = new Employee[size];

  bool found = false;
  for(int i = 0; i < size+1; i++){
    if(found) {
      newArr[i-1] = arr[i];
    }
    if(arr[i].get_id() == id) {
      found = true;
    };
    newArr[i] = arr[i];
  }

  return newArr;
}


void update_employee(Employee* arr, int size, int id, int salary, int department){
  for(int i = 0; i < size; i++){
    if(arr[i].get_id() == id){
      arr[i].set_salary(salary);
      arr[i].set_department(department);
    }
  } 
}


Employee* add_employee(Employee* arr, int size, int biggestId, int salary, int department){
  Employee* newArr = new Employee[size];

  for(int i = 0; i < size-1; i++){
    newArr[i] = arr[i];
  }
  
  newArr[size-1].set_id(biggestId);
  newArr[size-1].set_salary(salary);
  newArr[size-1].set_department(department);

  return newArr;
}


////


int main(int argc, char** argv){
  // clock_t start = clock();

  int size = 0;
  int biggestId = 0;

  fstream dataFile;
  dataFile.open(argv[1], ios::in);

  string row1, id, salary, department, trash;


  dataFile >> trash;
  while(getline(dataFile, trash)) {
    size++;
  }
  size--;
  biggestId = size;
  dataFile.close();


  dataFile.open(argv[1], ios::in);
  dataFile >> trash;

  Employee* arr = new Employee[size];

  for(int i = 0; i < size; i++) {
    dataFile >> row1;
    stringstream ss1(row1);

    getline(ss1, id, ';');
    getline(ss1, salary, ';');
    getline(ss1, department, ';');

    arr[i].set_id(stoi(id));
    arr[i].set_salary(stoi(salary));
    arr[i].set_department(stoi(department));
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
      size++;
      biggestId++;
      arr = add_employee(arr, size, biggestId, stoi(first), stoi(second));
    }
    if(operation == "UPDATE") {
      if(isValid(arr, size, stoi(first), 'u')) {
        update_employee(arr, size, stoi(first), stoi(second), stoi(third));
      }
    }
    if(operation == "DELETE") {
      if(isValid(arr, size, stoi(first), 'd')) {
        size--;
        arr = delete_employee(arr, size, stoi(first));
      }
    }    
  }

  operationsFile.close();

  ////

  ofstream result;
  result.open("array_solution.csv");

  result << "Employee_ID;Salary;Department" << endl;

  stringstream ssfinal;
  for(int i = 0; i < size; i++) {
    ssfinal << arr[i].get_id() << ";" << arr[i].get_salary() << ";" << arr[i].get_department() << endl;
  } 

  result << ssfinal.rdbuf();

  result.close();

  // clock_t end = clock();
  // double time = (double)(end - start) / CLOCKS_PER_SEC; //Time: 0.466459
  // cout << "Time: " << time << endl;

  return 0;
}
