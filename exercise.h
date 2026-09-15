#pragma once

#include "Matrix.h"
#include "Generator.h"
#include <memory>

namespace miit::algebra {

    /**
     * @brief Абстрактный базовый класс для упражнений
     */
    class Exercise {
    protected:
        Matrix<int> matrix;
        std::unique_ptr<Generator> generator;

    public:
        Exercise() = default;
        virtual ~Exercise() = default;

        /**
         * @brief Устанавливает матрицу
         */
        void setMatrix(const Matrix<int>& mat);

        /**
         * @brief Устанавливает генератор
         */
        void setGenerator(const std::unique_ptr<Generator> gen);

        /**
         * @brief Получает текущую матрицу
         * @return ссылка на матрицу
         */
        const Matrix<int>& getMatrix() const;

        /**
         * @brief Решение задачи (чисто виртуальный метод)
         */
        virtual void solve() = 0;

        /**
         * @brief Возвращает описание задачи
         */
        virtual std::string getDescription() const = 0;
    };

} // namespace miit::algebra
