#include <iostream>
#include <vector>
#include <limits>
#include "matplotlibcpp.h"
namespace plt = matplotlibcpp;


using Matrix = std::vector<std::vector<double>>;

Matrix transpose(const Matrix& A) {
    size_t rows = A.size();
    size_t cols = A[0].size();
    Matrix result(cols, std::vector<double>(rows));
    for (size_t i = 0; i < rows; ++i)
        for (size_t j = 0; j < cols; ++j)
            result[j][i] = A[i][j];
    return result;
}

Matrix multiply(const Matrix& A, const Matrix& B) {
    size_t rowsA = A.size();
    size_t colsA = A[0].size();
    size_t rowsB = B.size();
    size_t colsB = B[0].size();
    Matrix result(rowsA, std::vector<double>(colsB, 0));
    for (size_t i = 0; i < rowsA; ++i)
        for (size_t j = 0; j < colsB; ++j)
            for (size_t k = 0; k < colsA; ++k)
                result[i][j] += A[i][k] * B[k][j];
    return result;
}

Matrix inverse(const Matrix& A) {
    size_t n = A.size();
    Matrix result(n, std::vector<double>(n));
    Matrix B = A;

    
    for (size_t i = 0; i < n; ++i) {
        result[i][i] = 1.0;
    }

   
    for (size_t i = 0; i < n; ++i) {
        
        double pivot = B[i][i];
        if (pivot == 0) {
            std::cerr << "Macierz jest osobliwa." << std::endl;
            return Matrix();
        }

        
        for (size_t j = 0; j < n; ++j) {
            B[i][j] /= pivot;
            result[i][j] /= pivot;
        }

       
        for (size_t k = 0; k < n; ++k) {
            if (k != i) {
                double factor = B[k][i];
                for (size_t j = 0; j < n; ++j) {
                    B[k][j] -= B[i][j] * factor;
                    result[k][j] -= result[i][j] * factor;
                }
            }
        }
    }

    return result;
}


int main() {
    int n;
    std::cout << "Podaj liczbe punktow n: ";
    std::cin >> n;

    Matrix X(n, std::vector<double>(2)), Y(n, std::vector<double>(1));
    for (size_t i = 0; i < n; ++i) {
        std::cout << "Podaj x[" << i << "], y[" << i << "]: ";
        std::cin >> X[i][1] >> Y[i][0]; 
        X[i][0] = 1;
    }

    Matrix Xt = transpose(X);
    Matrix XtX = multiply(Xt, X);
    Matrix XtX_inv = inverse(XtX);
    Matrix XtY = multiply(Xt, Y);
    Matrix P = multiply(XtX_inv, XtY);

    std::cout << "Wspó³czynniki aproksymacji liniowej: p0 = " << P[0][0] << ", p1 = " << P[1][0] << std::endl;

 

    
    std::vector<double> x_plot, y_plot;
    double p0 = P[0][0]; 
    double p1 = P[1][0];

    
    std::vector<double> x_values(n);
    for (int i = 0; i < n; ++i) {
        x_values[i] = X[i][1];
    }

    double x_min = *std::min_element(x_values.begin(), x_values.end());
    double x_max = *std::max_element(x_values.begin(), x_values.end());

    for (double xi = x_min; xi <= x_max; xi += 0.1) {
        x_plot.push_back(xi);
        y_plot.push_back(p0 + p1 * xi);
    }

    
    std::vector<double> y_values;
    for (const auto& row : Y) {
        y_values.push_back(row[0]); 
    }
    plt::scatter(x_values, y_values, 10.0, { {"color", "red"} });
    plt::plot(x_plot, y_plot);
    plt::title("Aproksymacja Liniowa");
    plt::xlabel("x");
    plt::ylabel("y");
    plt::show();

    return 0;
}
