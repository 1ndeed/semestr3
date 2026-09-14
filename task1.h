/**
 * @file Task1.h
 * @brief Задание 1: замена минимальных по модулю элементов
 * @author Student
 * @version 1.0
 * @date 2024
 */

#pragma once

#include "Exercise.h"
#include <string>
#include <cmath>

namespace miit::algebra {

    /**
     * @brief Класс для выполнения задания 1
     *
     * Задание: Заменить минимальный по модулю элемент каждого столбца нулем
     *
     * Алгоритм:
     * 1. Для каждого столбца найти элемент с минимальным абсолютным значением
     * 2. Заменить найденный элемент на 0
     */
    class Task1 : public Exercise {
    public:
        /**
         * @brief Конструктор по умолчанию
         */
        Task1() = default;

        /**
         * @brief Выполняет задание
         *
         * Реализует алгоритм замены минимальных по модулю элементов
         */
        void solve() override;

        /**
         * @brief Возвращает описание задания
         * @return Описание задания
         */
        std::string getDescription() const override;

    private:
        /**
         * @brief Найти индекс строки с минимальным по модулю элементом в столбце
         * @param col Индекс столбца
         * @return Индекс строки с минимальным по модулю элементом
         * @throws std::runtime_error если матрица пустая
         * @throws std::out_of_range если индекс столбца вне диапазона
         */
        size_t findMinAbsInColumn(size_t col) const;

        /**
         * @brief Проверить, что матрица не пустая
         * @throws std::runtime_error если матрица пустая
         */
        void checkMatrixNotEmpty() const;
    };

} // namespace miit::algebra