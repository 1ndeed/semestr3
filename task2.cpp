#include "task2.h"

namespace miit::algebra {

    void Task2::solve() {
        matrix.removeColumnsWhereFirstGreaterThanLast();
    }

    std::string Task2::getDescription() const {
        return "Remove all columns where the first element is greater than the last element";
    }

} // namespace miit::algebra
