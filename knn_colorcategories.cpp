#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <unordered_map>
#include <string>
#include <sstream>


// K value = 5
// Euclidean Distance Formula
// 98.65% accuracy

using namespace std;

// Define the HSV color structure
struct HSVColor {
    string label;
    double hue;
    double saturation;
    double value;
};

// Calculate the Euclidean distance between two HSV colors
// Measures the distance (similarity) of 2 HSV values
double euclideanDistance(const HSVColor& color1, const HSVColor& color2) {
    double hDiff = color1.hue - color2.hue;
    if (hDiff < 0) {
        hDiff += 360;
    }

    double sDiff = color1.saturation - color2.saturation;
    double vDiff = color1.value - color2.value;

    return sqrt(hDiff * hDiff + sDiff * sDiff + vDiff * vDiff);
}

// KNN classification function
string knnClassify(const HSVColor& color, const vector<HSVColor>& trainingData, const vector<string>& labels, int k) {
    // color: An HSVColor object representing the new data point to be classified
    // trainingData: A vector of HSVColor objects representing the training data
    // labels: A vector of strings representing the labels of the training data
    // k: An integer representing the number of nearest neighbors to consider

    // store of distances between test data and each training data point
    vector<pair<double, string>> distances;

    for (int i = 0; i < trainingData.size(); i++) {
        double distance = euclideanDistance(color, trainingData[i]);
        distances.push_back(make_pair(distance, labels[i]));
    }
            

    sort(distances.begin(), distances.end()); // making the closest neighbor the first

    // Count the occurrences of each label among the k nearest neighbors
    unordered_map<string, int> labelCounts;
    for (int i = 0; i < k; i++) {
        string label = distances[i].second;
        labelCounts[label]++;
    }

    // Find the majority label (most common label of the amount of neighbors)
    string majorityLabel;
    int maxCount = 0;
    for (const auto& pair : labelCounts) {
        string label = pair.first;
        int count = pair.second;

        if (count > maxCount) {
            majorityLabel = label;
            maxCount = count;
        }
    }

    return majorityLabel;
}

// Function to parse CSV file and load training data
void loadTrainingData(const string& filename, vector<HSVColor>& trainingData, vector<string>& labels) {
    ifstream csvFile(filename);
    string line;

    while (getline(csvFile, line)) {
        stringstream ss(line);
        string labelStr, hueStr, saturationStr, valueStr;
        getline(ss, labelStr, ',');
        getline(ss, hueStr, ',');
        getline(ss, saturationStr, ',');
        getline(ss, valueStr);

        HSVColor color{labelStr, stod(hueStr), stod(saturationStr), stod(valueStr)};
        trainingData.push_back(color);
        labels.push_back(labelStr);
    }

    csvFile.close();
}

// Function to evaluate KNN classification on testing data
void evaluateKNN(const string& testingDataFile, const vector<HSVColor>& trainingData, const vector<string>& labels, int k) {
    int trueCount = 0;
    int falseCount = 0;

    ifstream testingFile(testingDataFile);
    string line;

    while (getline(testingFile, line)) {
        stringstream ss(line);
        string actualLabelStr, hueStr, saturationStr, valueStr;
        getline(ss, actualLabelStr, ',');
        getline(ss, hueStr, ',');
        getline(ss, saturationStr, ',');
        getline(ss, valueStr);

        HSVColor color{actualLabelStr, stod(hueStr), stod(saturationStr), stod(valueStr)};
        string predictedLabel = knnClassify(color, trainingData, labels, k);

        if (actualLabelStr == predictedLabel) {
            trueCount++;

        } else {
            falseCount++;
            cout << "Actual Label: " << actualLabelStr << endl;
            cout << "Predicted Label: " << predictedLabel << endl;
            cout << "H: " << hueStr << ", S: " << saturationStr << ", V: " << valueStr << endl;
        }
    }

    testingFile.close();

    cout << "True predictions: " << trueCount << endl;
    cout << "False predictions: " << falseCount << endl;
}

int main() {
    // Load training data from CSV file
    vector<HSVColor> trainingData;
    vector<string> labels;
    loadTrainingData("training_data.csv", trainingData, labels);

    // Evaluate KNN classification on testing data (k=5)
    evaluateKNN("shuffled_testingdata.csv", trainingData, labels, 3);


    /*
    K = 1:
        True predictions: 4000
        False predictions: 0
    K = 2:
        True predictions: 3940
        False predictions: 60
    K = 3: 
        True predictions: 3963
        False predictions: 37
    K = 4:
        True predictions: 3933
        False predictions: 67
    K = 5: 
        True predictions: 3946
        False predictions: 54
    K = 6:
        True predictions: 3911
        False predictions: 89
    K = 7:
        True predictions: 3925
        False predictions: 75
    */
    return 0;
}
