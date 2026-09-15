#include "task2.h"
#include <vector>

namespace miit::algebra {

    void Task2::solve() {
        const size_t rows = matrix.getRows();
        const size_t cols = matrix.getCols();

        if (rows == 0) {
            return;
        }

        // Отбираем индексы столбцов, которые нужно оставить:
        // первый элемент столбца не больше последнего
        std::vector<size_t> columnsToKeep;
        for (size_t j = 0; j < cols; ++j) {
            if (!(matrix[0][j] > matrix[rows - 1][j])) {
                columnsToKeep.push_back(j);
            }
        }

        // Собираем новую матрицу только из отобранных столбцов
        Matrix<int> result(rows, columnsToKeep.size());
        for (size_t i = 0; i < rows; ++i) {
            for (size_t k = 0; k < columnsToKeep.size(); ++k) {
                result[i][k] = matrix[i][columnsToKeep[k]];
            }
        }

        matrix = result;
    }

    std::string Task2::getDescription() const {
        return "Remove all columns where the first element is greater than the last element";
    }

} // namespace miit::algebra
