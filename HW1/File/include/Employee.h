#pragma once

using namespace std;

class Employee {
  private:
    int id;
    int salary;
    int department;
  public:
    Employee(int, int, int);
    ~Employee();
    void set_salary(int);
    void set_id(int);
    void set_department(int);
    int get_id();
    int get_salary();
    int get_department();
};
