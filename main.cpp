#include <iostream>
#include <string>
#include <cstdlib>
#include "Matrix.h"
#include "RandomGenerator.h"
#include "IStreamGenerator.h"
#include "ConstantGenerator.h"
#include "Task1.h"
#include "Task2.h"

using namespace miit::algebra;
constexpr int PRESET_CONSTANT_VALUE = 7;

// Способ заполнения матрицы
enum class FillMethod {
    Random = 1,
    Manual = 2,
    Constant = 3
};

size_t getSize(const std::string& message); 
FillMethod getChoice();
void demonstrateExercise(Exercise& exercise, const Matrix<int>& original,
    const std::string& taskName); 

int main() {
    try {

        size_t rows = getSize("Enter number of rows: ");
        size_t cols = getSize("Enter number of columns: ");

        Matrix<int> matrix(rows, cols);

        FillMethod choice = getChoice();

        switch (choice) {
        case FillMethod::Random: {
            std::cout << "Enter minimum value: ";
            int min;
            std::cin >> min;
            std::cout << "Enter maximum value: ";
            int max;
            std::cin >> max;
            if (min > max) {
                std::cerr << "Error: minimum value is greater than maximum\n";
                return 1;
            }
            RandomGenerator generator(min, max);
            matrix.fill(generator);
            break;
        }
        case FillMethod::Manual: {
            std::cout << "Enter matrix elements (separated by spaces):\n";
            IStreamGenerator generator(std::cin);
            matrix.fill(generator);
            break;
        }
        case FillMethod::Constant: {
            std::cout << "Using constant value preset in code: "
                << PRESET_CONSTANT_VALUE << "\n";
            ConstantGenerator generator(PRESET_CONSTANT_VALUE);
            matrix.fill(generator);
            break;
        }
        default:
            std::cerr << "Error: invalid choice\n";
            return 1;
        }

        std::cout << "\nCreated matrix:\n";
        std::cout << matrix.toString() << "\n";

        Task1 task1;
        demonstrateExercise(task1, matrix, "Task 1");

        Task2 task2;
        demonstrateExercise(task2, matrix, "Task 2");

        std::cout << "=============================================\n";
        std::cout << "  Additional demonstration (from task 4.3)\n";
        std::cout << "=============================================\n";

        Matrix<int> copyMatrix = matrix;

        std::cout << "\nOriginal matrix:\n";
        std::cout << copyMatrix.toString() << "\n";

        copyMatrix.replaceFirstThreeColumnsWithSquares();
        std::cout << "After replacing first three columns with squares:\n";
        std::cout << copyMatrix.toString() << "\n";

        Matrix<int> insertedMatrix = matrix.insertFirstRowAfterOddRows();
        std::cout << "After inserting first row after each odd row:\n";
        std::cout << insertedMatrix.toString() << "\n";

    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    std::cout << "\nPress Enter to exit...";
    std::cin.get();
    std::cin.get();

    return 0;
}
size_t getSize(const std::string& message) {
    std::cout << message;
    int value=0;
    std::cin >> value;
    if (value <= 0) {
        std::cerr << "Error: size must be positive\n";
        exit(1);
    }
    return static_cast<size_t>(value);
}
FillMethod getChoice() {
    std::cout << "Select array filling method:\n"
        << static_cast<int>(FillMethod::Random) << " - random numbers\n"
        << static_cast<int>(FillMethod::Manual) << " - manual input\n"
        << static_cast<int>(FillMethod::Constant) << " - constant value (preset in code)\n"
        << "Your choice: ";
    int choice;
    std::cin >> choice;
    return static_cast<FillMethod>(choice);
}
void demonstrateExercise(Exercise& exercise, const Matrix<int>& original,
    const std::string& taskName) {
    std::cout << "\n=== " << taskName << " ===\n";
    std::cout << "Description: " << exercise.getDescription() << "\n\n";

    std::cout << "Original matrix:\n";
    std::cout << original.toString() << "\n";

    exercise.setMatrix(original);
    exercise.solve();

    std::cout << "Result:\n";
    std::cout << exercise.getMatrix().toString() << "\n";
}
