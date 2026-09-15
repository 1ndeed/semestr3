/**
 * @file Task1.cpp
 * @brief Реализация класса Task1
 */

#include "Task1.h"
#include <stdexcept>

namespace miit::algebra {

    // ============================================================
    // Публичные методы
    // ============================================================

    void Task1::solve() {
        checkMatrixNotEmpty();

        size_t cols = matrix.getCols();

        // Для каждого столбца
        for (size_t j = 0; j < cols; ++j) {
            // Находим индекс строки с минимальным по модулю элементом
            size_t minRow = findMinAbsInColumn(j);

            // Заменяем найденный элемент на 0
            matrix[minRow][j] = 0;
        }
    }

    std::string Task1::getDescription() const {
        return "Replace the minimum absolute value element of each column with zero";
    }

    // ============================================================
    // Приватные методы
    // ============================================================

    size_t Task1::findMinAbsInColumn(const size_t col) const {
        checkMatrixNotEmpty();

        size_t rows = matrix.getRows();

        if (col >= matrix.getCols()) {
            throw std::out_of_range("Column index out of range: " + std::to_string(col));
        }

        // Начинаем с первого элемента
        size_t minRow = 0;
        int minValue = std::abs(matrix[0][col]);

        // Ищем минимальный по модулю элемент
        for (size_t i = 1; i < rows; ++i) {
            int absValue = std::abs(matrix[i][col]);
            if (absValue < minValue) {
                minValue = absValue;
                minRow = i;
            }
        }

        return minRow;
    }

    void Task1::checkMatrixNotEmpty() const {
        if (matrix.getRows() == 0 || matrix.getCols() == 0) {
            throw std::runtime_error("Matrix is empty. Cannot perform operation.");
        }
    }

} // namespace miit::algebra
