#include <iostream>
#include <fstream>
#include <random>

using namespace std;

// Function to generate a random HSV value within the specified constraints
vector<float> generateHSV(float hueMin, float hueMax, float saturationMin, float saturationMax, float valueMin, float valueMax) {
  // Generate random values for hue, saturation, and value
  random_device rd;
  mt19937 gen(rd());
  uniform_real_distribution<float> hueDist(hueMin, hueMax);
  uniform_real_distribution<float> saturationDist(saturationMin, saturationMax);
  uniform_real_distribution<float> valueDist(valueMin, valueMax);

  float hue = hueDist(gen);
  float saturation = saturationDist(gen);
  float value = valueDist(gen);

  return {hue, saturation, value};
}

int main() {
  // Open the output CSV file
  ofstream outputFile("testingdata.csv");
  if (!outputFile.is_open()) {
    cout << "Error opening output file" << endl;
    return 1;
  }

  // Generate colors for each color category
  int numColorsPerCategory = 1000;

  // Dark green
  for (int i = 0; i < numColorsPerCategory; i++) {
    vector<float> hsv = generateHSV(70, 165, 20, 100, 20, 79);
    outputFile << "dark_green," << hsv[0] << "," << hsv[1] << "," << hsv[2] << endl;
  }

  // Light green
  for (int i = 0; i < numColorsPerCategory; i++) {
    vector<float> hsv = generateHSV(75, 155, 20, 100, 80, 100);
    outputFile << "light_green," << hsv[0] << "," << hsv[1] << "," << hsv[2] << endl;
  }

  // Yellow
  for (int i = 0; i < numColorsPerCategory; i++) {
    vector<float> hsv = generateHSV(45, 65, 20, 100, 85, 100);
    outputFile << "yellow," << hsv[0] << "," << hsv[1] << "," << hsv[2] << endl;
  }

  // Brown
  for (int i = 0; i < numColorsPerCategory; i++) {
    vector<float> hsv = generateHSV(20, 60, 20, 100, 20, 70);
    outputFile << "brown," << hsv[0] << "," << hsv[1] << "," << hsv[2] << endl;
  }

  // Close the output file
  outputFile.close();

  return 0;
}
