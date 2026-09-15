#pragma once

#include "Exercise.h"
#include <string>

namespace miit::algebra {

    /**
     * @brief Задание 2: Удалить все столбцы, в которых первый элемент больше последнего
     */
    class Task2 : public Exercise {
    public:
        Task2() = default;

        /**
         * @brief Выполняет задание: удаляет столбцы, где первый элемент больше последнего
         */
        void solve() override;

        /**
         * @brief Возвращает описание задания
         */
        std::string getDescription() const override;
    };

} // namespace miit::algebra
