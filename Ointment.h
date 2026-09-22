#pragma once
//
// Ointment.h
// Класс-наследник "Мазь" - лекарство для наружного применения.
// Дополнительное поле: масса тюбика в граммах.
//
#include "Medicine.h"

/**
 * @brief Лекарство в форме мази для наружного/местного применения.
 *        Добавляет к общим полям Medicine массу тюбика (в граммах).
 */
class Ointment : public Medicine {
public:
    /**
     * @brief Создаёт лекарство в форме мази.
     * @param name           Торговое название.
     * @param expirationDate Срок годности.
     * @param annotation     Текст описания.
     * @param price          Цена в местной валюте.
     * @param manufacturer   Название изготовителя.
     * @param diseases       Болезни/недуги, при которых применяется лекарство.
     * @param massGrams      Масса тюбика, в граммах.
     */
    Ointment(std::string name,
        Date expirationDate,
        std::string annotation,
        double price,
        std::string manufacturer,
        std::vector<std::string> diseases,
        double massGrams);

    /** @brief Возвращает массу тюбика, в граммах. */
    double GetMassGrams() const;

    /** @brief Возвращает название формы выпуска: "Мазь" ("Ointment"). */
    std::string GetReleaseForm() const override;

protected:
    /** @brief Возвращает короткую строку с массой тюбика. */
    std::string GetSpecificInfo() const override;

private:
    double massGrams_;
};
