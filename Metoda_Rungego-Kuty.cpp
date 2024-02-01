#include <iostream>
#include <functional>
#include <cmath>

using ODEFunction = std::function<double(double, double)>;

double rungeKutta3(double y0, double t0, double tEnd, double h, ODEFunction f) {
    double y = y0;
    double t = t0;

    while (t < tEnd) {
        double k1 = h * f(t, y);
        double k2 = h * f(t + h / 2, y + k1 / 2);
        double k3 = h * f(t + h, y - k1 + 2 * k2);

        y += (k1 + 4 * k2 + k3) / 6;
        t += h;
    }

    return y;
}

double rungeKutta4(double y0, double t0, double tEnd, double h, ODEFunction f) {
    double y = y0;
    double t = t0;

    while (t < tEnd) {
        double k1 = h * f(t, y);
        double k2 = h * f(t + h / 2, y + k1 / 2);
        double k3 = h * f(t + h / 2, y + k2 / 2);
        double k4 = h * f(t + h, y + k3);

        y += (k1 + 2 * k2 + 2 * k3 + k4) / 6;
        t += h;
    }

    return y;
}

int main() {
    double a, b;
    int choice, order;
    std::cout << "Podaj wartosci stalych a i b: ";
    std::cin >> a >> b;

    std::cout << "Wybierz forme funkcji F(x, y):\n"
        << "1: a * x + b * y\n"
        << "2: a * x - b * y\n"
        << "3: a * x * b * y\n"
        << "4: a * x / (b * y)\n";
    std::cin >> choice;

    std::cout << "Wybierz rzad metody Rungego-Kutty (3 lub 4): ";
    std::cin >> order;

    
    ODEFunction f;
    switch (choice) {
    case 1: f = [a, b](double x, double y) { return a * x + b * y; }; break;
    case 2: f = [a, b](double x, double y) { return a * x - b * y; }; break;
    case 3: f = [a, b](double x, double y) { return a * x * b * y; }; break;
    case 4: f = [a, b](double x, double y) { return (b != 0) ? a * x / (b * y) : std::numeric_limits<double>::infinity(); }; break;
    default: std::cout << "Nieprawidlowy wybor!\n"; return 1;
    }

    double y0, t0, tEnd, h;
    std::cout << "Podaj wartosc poczatkowa y0, czas poczatkowy t0, czas koncowy tEnd i krok h: ";
    std::cin >> y0 >> t0 >> tEnd >> h;

    double result = (order == 3) ? rungeKutta3(y0, t0, tEnd, h, f) : rungeKutta4(y0, t0, tEnd, h, f);

    std::cout << "Wynik: " << result << std::endl;
    return 0;
}
