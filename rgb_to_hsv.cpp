#include <bits/stdc++.h> 
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std; 
  
vector<double> rgb_to_hsv(double r, double g, double b) 
{ 
  
    // R, G, B values are divided by 255 
    // to change the range from 0..255 to 0..1 
    r = r / 255.0; 
    g = g / 255.0; 
    b = b / 255.0; 
  
    // h, s, v = hue, saturation, value 
    double cmax = max(r, max(g, b)); // maximum of r, g, b 
    double cmin = min(r, min(g, b)); // minimum of r, g, b 
    double diff = cmax - cmin; // diff of cmax and cmin. 
    double h = -1, s = -1; 
  
    // if cmax and cmax are equal then h = 0 
    if (cmax == cmin) 
        h = 0; 
  
    // if cmax equal r then compute h 
    else if (cmax == r) 
        h = fmod(60 * ((g - b) / diff) + 360, 360); 
  
    // if cmax equal g then compute h 
    else if (cmax == g) 
        h = fmod(60 * ((b - r) / diff) + 120, 360); 
  
    // if cmax equal b then compute h 
    else if (cmax == b) 
        h = fmod(60 * ((r - g) / diff) + 240, 360); 
  
    // if cmax equal zero 
    if (cmax == 0) 
        s = 0; 
    else
        s = (diff / cmax) * 100; 
  
    // compute v 
    double v = cmax * 100; 
    vector<double> hsv {h,s,v};
    return hsv;
} 
  
int main() {
    // Read input CSV file
    ifstream inputFile("training.csv");
    if (!inputFile.is_open()) {
        cout << "Error opening input file" << endl;
        return 1;
    }

    // Open output CSV file
    ofstream outputFile("trainingHSV.csv");
    if (!outputFile.is_open()) {
        cout << "Error opening output file" << endl;
        return 1;
    }

    // Skip the first line (header)
    string line;
    getline(inputFile, line);

    // Process each line of the input CSV file
    while (getline(inputFile, line)) {
        stringstream ss(line);
        string label, strR, strG, strB;

        // Extract label, R, G, and B values from the line
        getline(ss, label, ',');
        getline(ss, strR, ',');
        getline(ss, strG, ',');
        getline(ss, strB, ',');

        // Convert RGB values to HSV
        double r = stod(strR);
        double g = stod(strG);
        double b = stod(strB);
        double h, s, v;
        vector<double> hsv_vect;
        hsv_vect = rgb_to_hsv(r, g, b);

        h = hsv_vect[0];
        s = hsv_vect[1];
        v = hsv_vect[2];

        // Write converted HSV values to the output CSV file
        outputFile << label << "," << h << "," << s << "," << v << endl;
    }

    // Close input and output files
    inputFile.close();
    outputFile.close();

    return 0;
}