#include "matrix.h"
#include <sstream>
#include <stdexcept>

namespace miit::algebra {

    template <typename T>
    Matrix<T>::Matrix() : rows(0), cols(0) {}

    template <typename T>
    Matrix<T>::Matrix(size_t rows, size_t cols) : rows(rows), cols(cols) {
        data.resize(rows, std::vector<T>(cols, T()));
    }

    template <typename T>
    size_t Matrix<T>::getRows() const {
        return rows;
    }

    template <typename T>
    size_t Matrix<T>::getCols() const {
        return cols;
    }

    template <typename T>
    bool Matrix<T>::isEmpty() const {
        return rows == 0 || cols == 0;
    }

    template <typename T>
    std::vector<T>& Matrix<T>::operator[](const size_t index) {
        if (index >= rows) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    template <typename T>
    const std::vector<T>& Matrix<T>::operator[](const size_t index) const {
        if (index >= rows) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    template <typename T>
    void Matrix<T>::resize(const size_t newRows, const size_t newCols) {
        rows = newRows;
        cols = newCols;
        data.resize(rows);
        for (auto& row : data) {
            row.resize(cols);
        }
    }

    template <typename T>
    void Matrix<T>::clear() {
        resize(0, 0);
    }

    template <typename T>
    void Matrix<T>::fill(const T& value) {
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                data[i][j] = value;
            }
        }
    }

    template <typename T>
    std::string Matrix<T>::toString() const {
        std::ostringstream oss;
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                oss << data[i][j] << " ";
            }
            oss << "\n";
        }
        return oss.str();
    }

    template <typename T>
    std::unique_ptr<Matrix<T>> Matrix<T>::clone() const {
        return std::make_unique<Matrix<T>>(*this);
    }

    // Явная инстанциация шаблона для типа int
    template class Matrix<int>;

} // namespace miit::algebra
