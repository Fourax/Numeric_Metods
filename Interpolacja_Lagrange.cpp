#include <iostream>
#include <vector>
#include<limits>
#include "matplotlibcpp.h"

namespace plt = matplotlibcpp;


double lagrangeInterpolation(const std::vector<std::pair<double, double>>& points, double x) {
    double result = 0.0;
    for (size_t i = 0; i < points.size(); i++) {
        double term = points[i].second; 
        for (size_t j = 0; j < points.size(); j++) {
            if (j != i) {
                term *= (x - points[j].first) / (points[i].first - points[j].first); 
            }
        }
        result += term; 
    }

    return result;
}

int main() {
   
    std::vector<std::pair<double, double>> points = { {0, 1}, {1, 3}, {2, 2}, {3, 4} };

    // Dane do rysowania
    std::vector<double> xs, ys;
    for (double x = 0; x <= 3; x += 0.1) {
        xs.push_back(x);
        ys.push_back(lagrangeInterpolation(points, x));
    }

    // Rysowanie wykresu
    plt::plot(xs, ys);
    plt::show();
}

