#include <iostream>
#include <vector>
#include <cmath>
#include "matplotlibcpp.h"
namespace plt = matplotlibcpp;


std::vector<std::vector<double>> createMatrix(int rows, int cols) {
    return std::vector<std::vector<double>>(rows, std::vector<double>(cols, 0.0));
}

void fillMatrix(std::vector<std::vector<double>>& matrix, const std::vector<double>& x, int degree) {
    for (size_t i = 0; i < matrix.size(); i++) {
        double val = 1.0;
        for (int j = 0; j <= degree; j++) {
            matrix[i][j] = val;
            val *= x[i];
        }
    }
}

std::vector<std::vector<double>> transposeMatrix(const std::vector<std::vector<double>>& matrix) {
    std::vector<std::vector<double>> transposed(matrix[0].size(), std::vector<double>(matrix.size()));
    for (size_t i = 0; i < matrix.size(); i++) {
        for (size_t j = 0; j < matrix[0].size(); j++) {
            transposed[j][i] = matrix[i][j];
        }
    }
    return transposed;
}

std::vector<std::vector<double>> multiplyMatrices(const std::vector<std::vector<double>>& a, const std::vector<std::vector<double>>& b) {
    std::vector<std::vector<double>> product(a.size(), std::vector<double>(b[0].size(), 0.0));
    for (size_t i = 0; i < a.size(); i++) {
        for (size_t j = 0; j < b[0].size(); j++) {
            for (size_t k = 0; k < b.size(); k++) {
                product[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    return product;
}

std::vector<std::vector<double>> inverseMatrix(const std::vector<std::vector<double>>& matrix) {
    int n = matrix.size();
    std::vector<std::vector<double>> result(n, std::vector<double>(n));
    std::vector<std::vector<double>> copy = matrix;

    // Inicjalizacja macierzy wynikowej jako macierzy jednostkowej
    for (int i = 0; i < n; ++i) {
        result[i][i] = 1.0;
    }

    // Przetwarzanie macierzy
    for (int i = 0; i < n; ++i) {
        // Ustalanie elementu g³ównego
        double pivot = copy[i][i];
        if (pivot == 0.0) {
            // Macierz jest osobliwa i nie mo¿e byæ odwrócona
            throw std::runtime_error("Matrix is singular and cannot be inverted.");
        }

        // Dzielenie wiersza przez element g³ówny
        for (int j = 0; j < n; ++j) {
            copy[i][j] /= pivot;
            result[i][j] /= pivot;
        }

        // Eliminacja Gaussa
        for (int k = 0; k < n; ++k) {
            if (k != i) {
                double factor = copy[k][i];
                for (int j = 0; j < n; ++j) {
                    copy[k][j] -= copy[i][j] * factor;
                    result[k][j] -= result[i][j] * factor;
                }
            }
        }
    }

    return result;
}


std::vector<double> polynomialRegression(const std::vector<double>& x, const std::vector<double>& y, int degree) {
    std::vector<std::vector<double>> X = createMatrix(x.size(), degree + 1);
    std::vector<std::vector<double>> Y = createMatrix(y.size(), 1);

    fillMatrix(X, x, degree);
    for (size_t i = 0; i < y.size(); i++) {
        Y[i][0] = y[i];
    }

    std::vector<std::vector<double>> Xt = transposeMatrix(X);
    std::vector<std::vector<double>> XtX = multiplyMatrices(Xt, X);
    std::vector<std::vector<double>> XtY = multiplyMatrices(Xt, Y);
    std::vector<std::vector<double>> XtX_inv = inverseMatrix(XtX);

    std::vector<std::vector<double>> coefficients = multiplyMatrices(XtX_inv, XtY);

    std::vector<double> result(degree + 1);
    for (int i = 0; i <= degree; i++) {
        result[i] = coefficients[i][0];
    }

    return result;
}

int main() {
    // Przyk³adowe dane
    std::vector<double> x = { 1, 2, 3, 4, 5 };  // x-values
    std::vector<double> y = { 2, 4, 6, 8, 10 }; // y-values
    int degree = 2; // Stopieñ wielomianu

    std::vector<double> coeffs = polynomialRegression(x, y, degree);

    std::cout << "Wspolczynniki wielomianu: ";
    for (double coeff : coeffs) {
        std::cout << coeff << " ";
    }
    std::cout << std::endl;
    // Generowanie punktów na wykresie
    std::vector<double> x_vals, y_vals;
    for (double x_val = 0; x_val < 10; x_val += 0.1) {
        double y_val = 0;
        for (size_t i = 0; i < coeffs.size(); i++) {
            y_val += coeffs[i] * pow(x_val, i);
        }
        x_vals.push_back(x_val);
        y_vals.push_back(y_val);
    }

    
    plt::scatter(x, y);
    plt::plot(x_vals, y_vals);
    plt::show();

    return 0;
}

