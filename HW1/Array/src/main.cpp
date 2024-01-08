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

void print_employees(Employee* arr, int size){
  for(int i = 0; i < size; i++){
    cout << arr[i].get_id() << " " << arr[i].get_salary() << " " << arr[i].get_department() << endl;
  }
}


Employee* delete_employee(Employee* arr, int size, int id){
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

  if(!found){
    cout << "ERROR: There is no Employee" << endl;
  }
  
  return newArr;
}

void update_employee(Employee* arr, int size, int id, int salary, int department){
  bool worked = false;
  for(int i = 0; i < size; i++){
    if(arr[i].get_id() == id){
      arr[i].set_salary(salary);
      arr[i].set_department(department);
      worked = true;
    }
  } 

  if(!worked){
    cout << "ERROR: An invalid ID to update" << endl;
  }
}


Employee* add_employee(Employee* arr, int size,  int salary, int department){
  Employee* newArr = new Employee[size];

  int biggestId = 0;
  for(int i = 0; i < size-1; i++){
    if(arr[i].get_id() > biggestId){
      biggestId = arr[i].get_id();
    }
  }

  for(int i = 0; i < size-1; i++){
    newArr[i] = arr[i];
  }
  
  newArr[size-1].set_id(biggestId+1);
  newArr[size-1].set_salary(salary);
  newArr[size-1].set_department(department);

  return newArr;
}


////


int main(int argc, char** argv){
  clock_t start = clock();

  fstream dataFile;
  dataFile.open(argv[1], ios::in);

  string row1, id, salary, department, trash;
  dataFile >> trash;

  int size = 0;

  while(getline(dataFile, trash)) {
    size++;
  }

  size--;

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

  // print_employees(arr, size);

  ////

  fstream operationsFile;
  operationsFile.open("operations.txt", ios::in);

  string row2;

  // cout << "-------" << endl;

  while(getline(operationsFile, row2)){
    stringstream ss2(row2);
    string operation, first, second, third;

    getline(ss2, operation, ';');
    getline(ss2, first, ';');
    getline(ss2, second, ';');
    getline(ss2, third, ';');

    if(operation == "ADD"){
      // cout << "ADD - " << "salary:" << first << " department:" << second << endl;
      size++;
      arr = add_employee(arr, size, stoi(first), stoi(second));
    }
    if(operation == "UPDATE") {
      // cout << "UPDATE - " << "id:" << first << " salary:" << second << " department:" << third << endl;
      update_employee(arr, size, stoi(first), stoi(second), stoi(third));
    }
    if(operation == "DELETE") {
      // cout << "DELETE - " << "id:" << first << endl;
      size--;
      arr = delete_employee(arr, size, stoi(first));
    }

    // print_employees(arr, size);


    // cout << "-------" << endl;
  }

  operationsFile.close();

  ////

  ofstream result;
  result.open("array_solution.csv");

  stringstream ssfinal;

  for(int i = 0; i < size-1; i++) {
    ssfinal << arr[i].get_id() << ";" << arr[i].get_salary() << ";" << arr[i].get_department() << endl;
  } 

  result << ssfinal.rdbuf();

  result.close();

  clock_t end = clock();
  double time = (double)(end - start) / CLOCKS_PER_SEC;
  // cout << "Time: " << time << endl;

  return 0;
}
