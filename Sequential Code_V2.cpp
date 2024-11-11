#include <iostream>
#include <vector>
#include <string>
#include <ctime> // library to calculate the time (for benchmarking)
using namespace std;

// Function to generate employee names
vector<string> generateEmployees(int size)
{
  vector<string> employees;
  for (int i = 1; i <= size; i++)
  {
    employees.push_back("employee_" + to_string(i));
  }
  return employees;
}

int main()
{
  // Start benchmarking for the entire program
  clock_t program_start = clock();

  clock_t start, end;
  double sequential_elapsed;

  // Start benchmarking for employee generation and printing
  start = clock();

  const int days = 5;
  string Days[days] = {"SUN", "MON", "TUE", "WED", "THU"};

  // Ask user for the number of employees to generate
  int numEmployees;
  cout << "Enter the number of employees to generate: ";
  cin >> numEmployees;

  // Dynamically generate employee names
  vector<string> Staff = generateEmployees(numEmployees);

  // Dynamically generate working hours for each employee
  vector<vector<int>> workingHours(numEmployees, vector<int>(days));

  // Randomly assigning working hours for each employee for simplicity
  srand(time(0)); // Initialize random seed
  for (int i = 0; i < numEmployees; i++)
  {
    for (int j = 0; j < days; j++)
    {
      workingHours[i][j] = rand() % 12 + 1; // Random hours between 1 and 12
    }
  }

  // Print employees and their working hours
  cout << endl
       << "\t \t";
  for (int i = 0; i < days; i++)
    cout << Days[i] << "\t ";
  cout << endl;

  for (int i = 0; i < numEmployees; i++)
  {
    cout << Staff[i] << "\t";
    for (int j = 0; j < days; j++)
      cout << workingHours[i][j] << "\t";
    cout << endl;
  }

  // End benchmarking for employee generation
  end = clock();
  sequential_elapsed = double(end - start) / CLOCKS_PER_SEC / 60;
  printf("\n\nTime taken to generate and print employees and their working hours: %.6f minutes\n\n", sequential_elapsed);

  // Start benchmarking for finding max and min working hours
  start = clock();

  // Find the day with the most and least total working hours
  int total, max = 0, indexMax, min, indexMin;
  for (int j = 0; j < days; j++)
  {
    total = 0;
    for (int i = 0; i < numEmployees; i++)
    {
      total += workingHours[i][j];
    }
    if (total > max)
    {
      max = total;
      indexMax = j;
    }
  }

  cout << "The day that most employees have high working hours: " << Days[indexMax] << endl;

  min = max; // Initialize minimum with the current maximum
  for (int j = 0; j < days; j++)
  {
    total = 0;
    for (int i = 0; i < numEmployees; i++)
    {
      total += workingHours[i][j];
    }
    if (total < min)
    {
      min = total;
      indexMin = j;
    }
  }
  cout << "The day that most employees have low working hours: " << Days[indexMin] << endl;

  // End benchmarking for finding max and min working hours
  end = clock();
  sequential_elapsed = double(end - start) / CLOCKS_PER_SEC / 60;
  printf("\n\nTime taken to find max and min working hours: %.6f minutes\n\n", sequential_elapsed);

  // Start benchmarking for employee-specific operations
  start = clock();

  // Employee-specific operations
  string employee;
  int emp_weeklyH = 0, highest_hours_day, day_index = 0, extra_day_index = 0;
  bool emp_exists = false;

  cout << "Enter an employee to find information about working hours in the week, the day of high working hour and salary: ";
  cin >> employee;
  cout << endl;

  for (int i = 0; i < numEmployees; i++)
  {
    if (employee == Staff[i])
    {
      emp_exists = true;
      highest_hours_day = workingHours[i][0];

      // Calculate weekly hours and find the day with the highest working hours
      for (int j = 0; j < days; j++)
      {
        emp_weeklyH += workingHours[i][j];
        if (highest_hours_day < workingHours[i][j])
        {
          highest_hours_day = workingHours[i][j];
          day_index = j;
        }
        if (highest_hours_day == workingHours[i][j] && j != day_index)
          extra_day_index = j;
      }
      cout << employee << " has worked " << emp_weeklyH << " hours in the week." << endl;

      if (extra_day_index)
      {
        cout << "The days that " << employee << " has high working hours are " << Days[day_index] << " and " << Days[extra_day_index] << endl;
      }
      else
      {
        cout << "The day that " << employee << " has high working hours is " << Days[day_index] << endl;
      }
      break;
    }
  }

  if (!emp_exists)
    cout << "Sorry, this employee does not exist." << endl;

  // Calculate and display the salary
  int salary = 0;
  int total_hours = 0;
  if (emp_exists)
  {
    int name = 0;
    for (int e = 0; e < numEmployees; e++)
    {
      if (Staff[e] == employee)
        name = e;
    }

    for (int i = 0; i < days; i++)
    {
      if (workingHours[name][i] > 9)
        total_hours += 9 + (2 * (workingHours[name][i] - 9));
      else
        total_hours += workingHours[name][i];
    }
    salary = total_hours * 100;
    cout << employee << " Salary: " << salary << " SAR in the week." << endl;
  }

  // End benchmarking for employee-specific operations
  end = clock();
  sequential_elapsed = double(end - start) / CLOCKS_PER_SEC / 60;
  printf("\n\nTime taken for employee-specific operations: %.6f minutes\n\n", sequential_elapsed);

  // End benchmarking for the entire program
  clock_t program_end = clock();
  double total_program_time = double(program_end - program_start) / CLOCKS_PER_SEC / 60;
  printf("\n\nTotal program time: %.6f minutes\n\n", total_program_time);

  return 0;
}