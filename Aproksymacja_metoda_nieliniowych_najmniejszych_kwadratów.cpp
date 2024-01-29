#include <iostream>
#include <vector>
#include <cmath>
#include "matplotlibcpp.h"

namespace plt = matplotlibcpp;

std::vector<double> solveLinearEquations() {
    // Twoje równania: 6A + 900b = 25.999, 900A + 198000b = 3786
    double a11 = 6, a12 = 900, b1 = 25.999;
    double a21 = 900, a22 = 198000, b2 = 3786;

    // Obliczanie za pomoc¹ wzoru Cramera
    double det = a11 * a22 - a12 * a21;
    double detA = b1 * a22 - b2 * a12;
    double detB = a11 * b2 - a21 * b1;

    double A = detA / det;
    double b = detB / det;

    return { A, b };
}

int main() {
    // Rozwi¹zanie uk³adu równañ
    auto solution = solveLinearEquations();
    double A = solution[0], b = solution[1];
    double a = std::exp(A); // a = exp(A)

    std::cout << "Rozwi¹zanie: A = " << A << ", b = " << b << std::endl;
    std::cout << "a = exp(A) = " << a << std::endl;

    // Przygotowanie danych do rysowania wykresu
    std::vector<double> x_line, y_line;
    for (double x_val = 0; x_val <= 300; x_val += 1) {
        x_line.push_back(x_val);
        y_line.push_back(a * std::exp(b * x_val)); // y = a * exp(b * x) dla linii
    }

    // Przygotowanie wybranych punktów do zaznaczenia
    std::vector<double> x_points = { 0, 50, 100, 150, 200, 250, 300 };
    std::vector<double> y_points;
    for (double x_val : x_points) {
        y_points.push_back(a * std::exp(b * x_val)); // y = a * exp(b * x) dla punktów
    }

    // Rysowanie wybranych punktów jako kropek
    

    // Rysowanie wykresu linii
    plt::plot(x_line, y_line);
    plt::scatter(x_points, y_points, 10.0, { {"color", "red"} });
    plt::title("Wykres funkcji y = a * exp(b * x)");
    plt::xlabel("x");
    plt::ylabel("y");
    plt::show();

    return 0;
}
//Powyzej przyk³ad wykonany z obliczeñ

