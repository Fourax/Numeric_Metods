#include <iostream>
#include <vector>
#include <functional>
#include "matplotlibcpp.h"

namespace plt = matplotlibcpp;

std::function<double(double, double)> chooseFunction() 
{
    int choice;
    std::cout << "Wybierz postaæ funkcji F(x, y):\n";
    std::cout << "1: F(x,y) = a*x + b*y\n";
    std::cout << "2: F(x,y) = a*x - b*y\n";
    std::cout << "3: F(x,y) = a*x*b*y\n";
    std::cout << "4: F(x,y) = (a*x) / (b*y)\n";
    std::cin >> choice;

    double a, b;
    std::cout << "Podaj wartoœæ a: ";
    std::cin >> a;
    std::cout << "Podaj wartoœæ b: ";
    std::cin >> b;

    switch (choice) {
    case 1: return [a, b](double x, double y) { return a * x + b * y; };
    case 2: return [a, b](double x, double y) { return a * x - b * y; };
    case 3: return [a, b](double x, double y) { return a * x * b * y; };
    case 4: return [a, b](double x, double y) { return (b * y == 0) ? 0 : (a * x) / (b * y); };
    default: std::cout << "Niepoprawny wybór, u¿ywam domyœlnej funkcji F(x,y) = a*x + b*y\n";
        return [a, b](double x, double y) { return a * x + b * y; };
    }
}

// Metoda Eulera
double eulerMethod(std::function<double(double, double)> F, double x0, double y0, double h, int n, std::vector<double>& x_vals, std::vector<double>& y_vals) {
    double x = x0, y = y0;
    x_vals.push_back(x);
    y_vals.push_back(y);

    for (int i = 0; i < n; ++i) {
        y += h * F(x, y);
        x += h;
        x_vals.push_back(x);
        y_vals.push_back(y);
    }
    return y;
}

// Metoda Heuna (ulepszona metoda Eulera)
double heunMethod(std::function<double(double, double)> F, double x0, double y0, double h, int n, std::vector<double>& x_vals, std::vector<double>& y_vals) {
    double x = x0, y = y0;
    x_vals.push_back(x);
    y_vals.push_back(y);

    for (int i = 0; i < n; ++i) {
        double slope1 = F(x, y);
        double y_predict = y + h * slope1;
        double slope2 = F(x + h, y_predict);
        y += h * 0.5 * (slope1 + slope2);
        x += h;

        x_vals.push_back(x);
        y_vals.push_back(y);
    }
    return y;
}

int main() {
    auto F = chooseFunction();

    double x0 = 0; // Punkt startowy x
    double y0 = 1; // Punkt startowy y
    double h = 0.1; // Krok
    int n = 10; // Liczba kroków

    std::vector<double> x_vals_euler, y_vals_euler; // Wektory dla metody Eulera
    std::vector<double> x_vals_heun, y_vals_heun; // Wektory dla metody Heuna

    eulerMethod(F, x0, y0, h, n, x_vals_euler, y_vals_euler);
    heunMethod(F, x0, y0, h, n, x_vals_heun, y_vals_heun);

    plt::plot(x_vals_euler, y_vals_euler, "r-"); // "r-" oznacza czerwon¹ liniê ci¹g³¹
    plt::plot(x_vals_heun, y_vals_heun, "b-"); // "b-" oznacza niebiesk¹ liniê ci¹g³¹

    plt::title("Porównanie metod Eulera i Heuna");
    plt::xlabel("x");
    plt::ylabel("y");
    plt::legend();
    plt::show();

    return 0;

}
