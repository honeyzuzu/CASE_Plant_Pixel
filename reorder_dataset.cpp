#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <string>
#include <algorithm>

using namespace std;

int main() {
  // Open the CSV file
  ifstream csvfile("training_data.csv");

  // Read the CSV file into a vector of strings
  vector<string> rows;
  string line;
  while (getline(csvfile, line)) {
    rows.push_back(line);
  }
  csvfile.close();

  // Shuffle the vector of strings
  random_device rd;
  mt19937 engine(rd());
  shuffle(rows.begin(), rows.end(), engine);

  // Write the shuffled rows to a new CSV file
  ofstream newfile("shuffled_testingdata.csv");
  for (const string& row : rows) {
    newfile << row << endl;
  }
  newfile.close();

  return 0;
}