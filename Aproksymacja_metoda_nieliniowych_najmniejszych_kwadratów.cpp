#include <iostream>
#include <vector>
#include <cmath>
#include "matplotlibcpp.h"

namespace plt = matplotlibcpp;

std::vector<double> solveLinearEquations() {
    
    double a11 = 6, a12 = 900, b1 = 25.999;
    double a21 = 900, a22 = 198000, b2 = 3786;

   
    double det = a11 * a22 - a12 * a21;
    double detA = b1 * a22 - b2 * a12;
    double detB = a11 * b2 - a21 * b1;

    double A = detA / det;
    double b = detB / det;

    return { A, b };
}

int main() {
    
    auto solution = solveLinearEquations();
    double A = solution[0], b = solution[1];
    double a = std::exp(A); 

    std::cout << "Rozwiazanie: A = " << A << ", b = " << b << std::endl;
    std::cout << "a = exp(A) = " << a << std::endl;

    
    std::vector<double> x_line, y_line;
    for (double x_val = 0; x_val <= 300; x_val += 1) {
        x_line.push_back(x_val);
        y_line.push_back(a * std::exp(b * x_val)); 
    }

    
    std::vector<double> x_points = { 0, 50, 100, 150, 200, 250, 300 };
    std::vector<double> y_points;
    for (double x_val : x_points) {
        y_points.push_back(a * std::exp(b * x_val)); 
    }

    
    

    
    plt::plot(x_line, y_line);
    plt::scatter(x_points, y_points, 10.0, { {"color", "red"} });
    plt::title("Wykres funkcji y = a * exp(b * x)");
    plt::xlabel("x");
    plt::ylabel("y");
    plt::show();

    return 0;
}


