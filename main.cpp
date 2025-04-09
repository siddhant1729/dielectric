#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
#include <limits>

using namespace std;

struct DataPoint {
    double temperature;
    double capacitance;
    double epsilon;
};

// Constants
const double A = 8.0 * 6.0;         // Area in mm²
const double t = 1.42;              // Thickness in mm
const double epsilon_0 = 8.85e-3;   // pF/mm

double calculateEpsilon(double C) {
    return (C * t) / (A * epsilon_0);
}

int main() {
    int n;
    cout << "Enter number of readings: ";
    cin >> n;

    vector<DataPoint> data(n);

    cout << "\nEnter Temperature (°C) and Capacitance (pF) for each reading:\n";

    for (int i = 0; i < n; ++i) {
        cout << "Reading " << i + 1 << ":\n";
        cout << "  Temperature (°C): ";
        cin >> data[i].temperature;
        cout << "  Capacitance (pF): ";
        cin >> data[i].capacitance;

        data[i].epsilon = calculateEpsilon(data[i].capacitance);
    }

    // Find Curie temperature (max epsilon)
    double maxEpsilon = numeric_limits<double>::min();
    double curieTemp = 0;

    for (const auto& point : data) {
        if (point.epsilon > maxEpsilon) {
            maxEpsilon = point.epsilon;
            curieTemp = point.temperature;
        }
    }

    // Output table
    cout << "\nTemperature vs Dielectric Constant:\n";
    cout << "-----------------------------------\n";
    cout << "Temp (°C)\tCapacitance (pF)\tDielectric Constant\n";
    for (const auto& point : data) {
        cout << fixed << setprecision(2)
             << point.temperature << "\t\t"
             << point.capacitance << "\t\t\t"
             << point.epsilon << endl;
    }

    cout << "\nEstimated Curie Temperature (max ε): " << curieTemp << " °C\n";

    // Save to CSV
    ofstream file("data.csv");
    file << "Temperature,Capacitance,Epsilon\n";
    for (const auto& point : data) {
        file << point.temperature << "," << point.capacitance << "," << point.epsilon << "\n";
    }
    file.close();
    cout << "\nData saved to data.csv\n";

    return 0;
}
