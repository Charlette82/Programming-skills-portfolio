
#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

// Function to get distance travelled
double getDistance() {
    double distance;
    cout << "Enter distance travelled in miles: ";
    cin >> distance;

    while (distance < 0) {
        cout << "Distance cannot be negative. Enter again: ";
        cin >> distance;
    }
    return distance;
}

// Function to get fuel type
string getFuelType() {
    string fuel;
    cout << "Enter fuel type (Diesel or Petrol): ";
    cin >> fuel;

    while (fuel != "Diesel" && fuel != "diesel" &&
           fuel != "Petrol" && fuel != "petrol") {
        cout << "Invalid fuel type. Enter Diesel or Petrol: ";
        cin >> fuel;
    }
    return fuel;
}

// Function to calculate CO2 emissions
double calculateEmissions(double distance, string fuel) {
    const double consumption = 9.66;
    double emissionFactor;

    if (fuel == "Diesel" || fuel == "diesel") {
        emissionFactor = 2.68;
    } else {
        emissionFactor = 2.31;
    }

    double fuelUsed = (distance / 100.0) * consumption;
    return fuelUsed * emissionFactor;
}

int main() {
    double distance = getDistance();
    string fuel = getFuelType();

    double emissions = calculateEmissions(distance, fuel);

    cout << fixed << setprecision(2);
    cout << "\nDistance travelled: " << distance << " miles";
    cout << "\nFuel type: " << fuel;
    cout << "\nEstimated CO2 emissions: "
         << emissions << " kg CO2" << endl;

    return 0;
}