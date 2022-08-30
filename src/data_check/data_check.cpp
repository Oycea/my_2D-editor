#include "data_check.hpp"

// Функция проверяет корректность введенных значений для геометрических объектов.
void check_value(double& num) {
	std::cin >> num;
	while (std::cin.fail()) {
		std::cin.clear();
		std::cin.ignore(32767, '\n');
		std::cout << "Enter a rational number: ";
		std::cin >> num;
	}
}

// Функция проверяет корректность введенной команды.
void input_menu_command(int& command) {
	std::cin >> command;
	while (std::cin.fail()) {
		std::cin.clear();
		std::cin.ignore(32767, '\n');
		std::cout << "Enter the correct command number: ";
		std::cin >> command;
	}
}
