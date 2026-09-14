#include "Exercise.h"

namespace miit::algebra {

    void Exercise::setMatrix(const Matrix<int>& mat) {
        matrix = mat;
    }

    void Exercise::setGenerator(std::unique_ptr<Generator> gen) {
        generator = std::move(gen);
    }

    const Matrix<int>& Exercise::getMatrix() const {
        return matrix;
    }

} // namespace miit::algebra