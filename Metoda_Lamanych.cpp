#include <iostream>
#include <vector>
#include <functional>
#include "matplotlibcpp.h"

namespace plt = matplotlibcpp;

std::function<double(double, double)> chooseFunction()
{
    int choice;
    std::cout << "Wybierz postac funkcji F(x, y):\n";
    std::cout << "1: F(x,y) = a*x + b*y\n";
    std::cout << "2: F(x,y) = a*x - b*y\n";
    std::cout << "3: F(x,y) = a*x*b*y\n";
    std::cout << "4: F(x,y) = (a*x) / (b*y)\n";
    std::cin >> choice;

    double a, b;
    std::cout << "Podaj wartosc a: ";
    std::cin >> a;
    std::cout << "Podaj wartosc b: ";
    std::cin >> b;

    switch (choice) {
    case 1: return [a, b](double x, double y) { return a * x + b * y; };
    case 2: return [a, b](double x, double y) { return a * x - b * y; };
    case 3: return [a, b](double x, double y) { return a * x * b * y; };
    case 4: return [a, b](double x, double y) { return (b * y == 0) ? 0 : (a * x) / (b * y); };
    default: std::cout << "Niepoprawny wybor, uzywam domyslnej funkcji F(x,y) = a*x + b*y\n";
        return [a, b](double x, double y) { return a * x + b * y; };
    }
}


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

    double x0 = 0;
    double y0 = 1;
    double h = 0.1; 
    int n = 10;
    int choice;

    std::cout << "Wybierz metode do narysowania wykresu:\n";
    std::cout << "1: Metoda Eulera\n";
    std::cout << "2: Metoda Heuna\n";
    std::cin >> choice;

    std::vector<double> x_vals, y_vals;

    switch (choice) {
    case 1:
        eulerMethod(F, x0, y0, h, n, x_vals, y_vals);
        plt::plot(x_vals, y_vals, "r-"); 
        plt::title("Wykres metody Eulera");
        break;
    case 2:
        heunMethod(F, x0, y0, h, n, x_vals, y_vals);
        plt::plot(x_vals, y_vals, "b-"); 
        plt::title("Wykres metody Heuna");
        break;
    default:
        std::cout << "Niepoprawny wybor." << std::endl;
        return 1;
    }

    plt::xlabel("x");
    plt::ylabel("y");
    plt::show();

    return 0;

}
