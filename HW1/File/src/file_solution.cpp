/* @Author
Student Name : <"Selim Dilşad Ercan">
StudentID : < 150210104 >
Date :< "29.10.2023" > 
*/


#include <fstream>
#include <sstream>
#include <string>
#include <ios>
#include <iostream>
#include <time.h>


using namespace std;

////

void add_employee(string file, int salary, int department) {
  fstream dataFile("hw.csv", ios::in);
  string trash, row, id;
  getline(dataFile, trash);
  int biggestId = 0;
  while (getline(dataFile, row)) {
    stringstream ss(row);

    getline(ss, id, ';');
 
    if (stoi(id) > biggestId) {
      biggestId = stoi(id);
    }
  }
  dataFile.close();

  dataFile.open(file, ios::app);
  dataFile << to_string(biggestId+1) << ";" << salary << ";" << department << endl;
  dataFile.close();
}


void update_employee(string file, int id, int salary, int department) {
  fstream dataFile(file, ios::in | ios::out);
  fstream tempFile("temp.txt", ios::out);

  string line1;
  getline(dataFile, line1);
  tempFile << line1 << endl;

  string row, row_id;
  stringstream final;

  bool found = false;

  while(getline(dataFile, row)) {
    stringstream ss(row);

    getline(ss, row_id, ';');

    if (stoi(row_id) == id) {
      final << id << ";" << salary << ";" << department << endl;
      found = true;
    } 
    else {
      final << row << endl;
    }
  }

  tempFile << final.rdbuf();

  dataFile.close();
  tempFile.close();

  remove(file.c_str());
  rename("temp.txt", file.c_str());

  if (!found) {
    cout << "ERROR: An invalid ID to update" << endl;
  }
}


void delete_employee(string file, int id) {
  fstream dataFile(file, ios::in | ios::out);
  fstream tempFile("temp.txt", ios::out);

  string line1;
  getline(dataFile, line1);
  tempFile << line1 << endl;

  bool found = false;

  string row, row_id;

  stringstream final;
  while(getline(dataFile, row)) {
    stringstream ss(row);
    getline(ss, row_id, ';');

    if (stoi(row_id) != id) {
      final << row << endl;
    }
    else {
      found = true;
    }
  }

  if(!found) {
    cout << "ERROR: There is no Employee" << endl;
  }

  tempFile << final.rdbuf();
  dataFile.close();
  tempFile.close();

  remove(file.c_str());
  rename("temp.txt", file.c_str());
}

////

int main(int argc, char** argv){
  clock_t start = clock();

  fstream operationsFile;
  operationsFile.open(argv[2], ios::in);

  string row;

  while(getline(operationsFile, row)){
    stringstream ss(row);
    string operation, first, second, third;

    getline(ss, operation, ';');
    getline(ss, first, ';');
    getline(ss, second, ';');
    getline(ss, third, ';');

    if(operation == "ADD"){
      // cout << "ADD - " << "salary:" << first << " department:" << second << endl;
      add_employee(argv[1], stoi(first), stoi(second));
    }
    if(operation == "UPDATE") {
      // cout << "UPDATE - " << "id:" << first << " salary:" << second << " department:" << third << endl;
      update_employee(argv[1], stoi(first), stoi(second), stoi(third));
    }
    if(operation == "DELETE") {
      // cout << "DELETE - " << "id:" << first << endl;
      delete_employee(argv[1], stoi(first));
    }
  }

  operationsFile.close();

  clock_t end = clock();
  double time = (double)(end - start) / CLOCKS_PER_SEC;
  // cout << "Time: " << time << endl;

  return 0;
}