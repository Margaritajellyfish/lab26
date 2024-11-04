#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>
#include <list>
#include <set>
#include <algorithm>
#include <iomanip>

using namespace std;
using namespace std::chrono;

void load_data(const string &filename, vector<string> &vec);
void load_data(const string &filename, list<string> &lst);
void load_data(const string &filename, set<string> &st);

template <typename name>
long readData(name &container) {
  ifstream fin("codes.txt");
  string line;
  auto start = high_resolution_clock::now();
  while (getline(fin, line)) {
    container.insert(container.end(), line); 
  }
  auto end = high_resolution_clock::now();
  fin.close();

  return duration_cast<microseconds>(end - start).count();
}

template <>
long readData(set<string> &container) {
  ifstream fin("codes.txt");
  string line;
  auto start = high_resolution_clock::now();
  while (getline(fin, line)) {
    container.insert(line); 
  }
  auto end = high_resolution_clock::now();
  fin.close();

  return duration_cast<microseconds>(end - start).count();
}

template <typename name>
long deleteData(name &container) {
  auto start = high_resolution_clock::now();
  auto it = container.begin();
  advance(it, container.size() / 2);
  container.erase(it);
  auto end = high_resolution_clock::now();
  return duration_cast<microseconds>(end - start).count();
}

template <>
long deleteData(set<string> &container) {
  auto start = high_resolution_clock::now();
  auto it = container.begin();
  advance(it, container.size() / 2);
  container.erase(it); 
  auto end = high_resolution_clock::now();
  return duration_cast<microseconds>(end - start).count();
}

template <typename name>
long insertData(name &container) {
  auto start = high_resolution_clock::now();
  auto it = container.begin();
  advance(it, container.size() / 2);
  container.insert(it, "TESTCODE");
  auto end = high_resolution_clock::now();
  return duration_cast<microseconds>(end - start).count();
}

template <>
long insertData(set<string> &container) {
  auto start = high_resolution_clock::now();
  container.insert("TESTCODE"); // Direct insertion into the set
  auto end = high_resolution_clock::now();
  return duration_cast<microseconds>(end - start).count();
}

long sortData(vector<string> &vec) {
  auto start = high_resolution_clock::now();
  sort(vec.begin(), vec.end());
  auto end = high_resolution_clock::now();
  return duration_cast<microseconds>(end - start).count();
}

long sortData(list<string> &lst) {
  auto start = high_resolution_clock::now();
  lst.sort();
  auto end = high_resolution_clock::now();
  return duration_cast<microseconds>(end - start).count();
}

long sortData(set<string> &st) {
  return -1; 
}

int main() {
  const int numRuns = 15;
  const int numOperations = 4;
  long results[numRuns][numOperations][3] = {0};
  long averages[numOperations][3] = {0};

  vector<string> vec;
  list<string> lst;    
  set<string> st;

  for (int run = 0; run < numRuns; ++run) {
    

        results[run][0][0] = readData(vec);
        results[run][0][1] = readData(lst);
        results[run][0][2] = readData(st);


        results[run][1][0] = sortData(vec);
        results[run][1][1] = sortData(lst);
        results[run][1][2] = sortData(st);


        results[run][2][0] = insertData(vec);
        results[run][2][1] = insertData(lst);
        results[run][2][2] = insertData(st);


        results[run][3][0] = deleteData(vec);
        results[run][3][1] = deleteData(lst);
        results[run][3][2] = deleteData(st);
    }


    for (int op = 0; op < numOperations; ++op) {
        for (int container = 0; container < 3; ++container) {
            long sum = 0;
            for (int run = 0; run < numRuns; ++run) {
                sum += results[run][op][container];
            }
            averages[op][container] = sum / numRuns;
        }
    }
  cout << left << setw(15) << "Operation" << setw(12) << "Vector" << setw(12)
       << "List" << setw(12) << "Set" << endl;

  cout << left << setw(15) << "Read" << setw(12) << readData(vec) << setw(12)
       << readData(lst) << setw(12) << readData(st) << endl;

  cout << left << setw(15) << "Sort" << setw(12) << sortData(vec) << setw(12)
       << sortData(lst) << setw(12) << sortData(st) << endl;

  cout << left << setw(15) << "Insert" << setw(12) << insertData(vec)
       << setw(12) << insertData(lst) << setw(12) << insertData(st) << endl;

  cout << left << setw(15) << "Delete" << setw(12) << deleteData(vec)
       << setw(12) << deleteData(lst) << setw(12) << deleteData(st) << endl;

  cout << "microseconds";
  return 0;
}
