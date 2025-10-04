#include <iostream>
#include <iomanip>
#include "Dice.h"
#include "ThreeDicePool.h"
#include "PenaltyDice.h"
#include "BonusDice.h"
#include "DoubleDice.h"
#include "utils.h"

void task1()
{
    std::cout << "=== Задание 1: Рефакторинг ===" << std::endl;

    Dice d100(100, 42);
    ThreeDicePool threeD6(6, 1, 2, 3);

    std::cout << "Матожидание Dice(100): "
              << expected_value(d100, 10000) << std::endl;
    std::cout << "Теоретическое матожидание: " << (1 + 100) / 2.0 << std::endl;

    std::cout << "Матожидание ThreeDicePool(6): "
              << expected_value(threeD6, 10000) << std::endl;
    std::cout << "Теоретическое матожидание: " << 3 * (1 + 6) / 2.0 << std::endl;
    std::cout << std::endl;
}

void task2()
{
    std::cout << "=== Задание 2: Штрафы и преимущества ===" << std::endl;

    Dice d100(100, 42);
    PenaltyDice penaltyD100(d100);
    BonusDice bonusD100(d100);

    ThreeDicePool threeD6(6, 1, 2, 3);

    std::cout << "Матожидание Dice(100): " << expected_value(d100, 10000) << std::endl;
    std::cout << "Матожидание PenaltyDice(100): " << expected_value(penaltyD100, 10000) << std::endl;
    std::cout << "Матожидание BonusDice(100): " << expected_value(bonusD100, 10000) << std::endl;

    std::cout << "\nВероятность выпадения 50 для Dice(100): "
              << value_probability(50, d100, 10000) * 100 << "%" << std::endl;
    std::cout << "Вероятность выпадения 50 для PenaltyDice(100): "
              << value_probability(50, penaltyD100, 10000) * 100 << "%" << std::endl;
    std::cout << "Вероятность выпадения 50 для BonusDice(100): "
              << value_probability(50, bonusD100, 10000) * 100 << "%" << std::endl;

    std::cout << "\nГистограмма Dice(100):" << std::endl;
    auto hist1 = build_histogram(d100, 10000);
    print_histogram(hist1);

    std::cout << "Гистограмма PenaltyDice(100):" << std::endl;
    auto hist2 = build_histogram(penaltyD100, 10000);
    print_histogram(hist2);

    std::cout << "Гистограмма BonusDice(100):" << std::endl;
    auto hist3 = build_histogram(bonusD100, 10000);
    print_histogram(hist3);

    std::cout << "Гистограмма ThreeDicePool(6):" << std::endl;
    auto hist4 = build_histogram(threeD6, 10000);
    print_histogram(hist4);

    std::cout << std::endl;
}

void task3()
{
    std::cout << "=== Задание 3: Множественное наследование ===" << std::endl;

    Dice d100(100, 42);
    DoubleDice doubleD100(d100);
    DoubleDiceMI doubleD100MI(d100);

    std::cout << "Матожидание DoubleDice(100): "
              << expected_value(doubleD100, 10000) << std::endl;

    std::cout << "Матожидание DoubleDiceMI(100): "
              << expected_value(doubleD100MI, 10000) << std::endl;

    std::cout << "\nГистограмма DoubleDice(100):" << std::endl;
    auto hist = build_histogram(doubleD100, 10000);
    print_histogram(hist);

    std::cout << "Гистограмма DoubleDiceMI(100):" << std::endl;
    auto hist2 = build_histogram(doubleD100MI, 10000);
    print_histogram(hist2);
}

int main()
{
    std::cout << "Лабораторная работа 1: Вероятности" << std::endl;
    std::cout << "Проверка статистических свойств псевдослучайных величин\n"
              << std::endl;

    task1();
    task2();
    task3();

    return 0;
}