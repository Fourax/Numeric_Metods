#include <iostream>
#include <vector>
#include <limits>
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
   
    std::vector<std::pair<double, double>> points = { {-2, 9}, {-1, 4}, {1, 0}, {3, 4}, {4, 9}, {5, 16}, {7, 20}, {11, 5} };


    
    std::vector<double> xs, ys;
    for (double x = -2; x <= 11; x += 0.1) {
        xs.push_back(x);
        ys.push_back(lagrangeInterpolation(points, x));
    }

    plt::plot(xs, ys);

    
    std::vector<double> px, py;
    for (const auto& p : points) {
        px.push_back(p.first);
        py.push_back(p.second);
    }
    plt::scatter(px, py, 10.0, { {"color", "red"} });

    plt::show();

}

