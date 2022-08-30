#include "test.hpp"

// Далее идут функции для тестирования методов листа.

// Тестирование метода проверки листа на пустоту.
bool test_is_empty() {
	List<int> my_list;
	// В самом начале лист пустой.
	if (my_list.is_empty() != true) return false;
	my_list.push_back(1);
	// После добавления элемента он перестал быть пустым.
	if (my_list.is_empty() != false) return false;
	my_list.remove_last();
	// После удаления элемента лист снова пустой.
	if (my_list.is_empty() != true) return false;
	return true;
}

// Функция тестирования метода, который возвращает указатель на первый элемент списка.
bool test_front() {
	List<int> my_list;
	my_list.push_back(1);
	// Добавили один элемент в список, он теперь будет первым.
	if (my_list.front()->value() != 1) return false;
	my_list.push_back(2);
	// Второй элемент добавили в конец, поэтому первый должен остаться таким же.
	if (my_list.front()->value() != 1) return false;
	return true;
}

// Функция тестирования метода, который возвращает указатель на последний элемент списка.
bool test_back() {
	List<int> my_list;
	my_list.push_back(1);
	// Добавили один элемент в список, он теперь будет последним.
	if (my_list.back()->value() != 1) return false;
	my_list.push_back(2);
	// Второй элемент добавили в конец, поэтому последний должен поменяться.
	if (my_list.back()->value() != 2) return false;
	return true;
}

// Функция тестирует метод удаления первого элемента листа.
bool test_remove_first() {
	List<int> my_list;
	my_list.push_back(1);
	my_list.push_back(2);
	my_list.remove_first();
	// После удаления первого элемента списка, новый первый элемент должен быть равен второму
	// из списко до удаления.
	if (my_list.front()->value() != 2) return false;
	return true;
}

// Функция тестирует метод удаления последнего элемента листа.
bool test_remove_last() {
	List<int> my_list;
	my_list.push_back(1);
	my_list.push_back(2);
	my_list.remove_last();
	// После удаления последнего элемента списка, первый элемент не должен поменяться.
	if (my_list.front()->value() != 1) return false;
	return true;
}

// Далее идут дву функции, в которым разным способом несколько раз заполняется и очищается лист.
// После каждой чистки он должен быть пустым.
bool test_clear_list1() {
	List<int> my_list;
	for (int i = 0; i < 10; i++)
		my_list.push_back(i);
	for (int i = 0; i < 10; i++)
		my_list.remove_last();
	if (my_list.is_empty() != true) return false;

	for (int i = 0; i < 10; i++)
		my_list.push_front(i);
	for (int i = 0; i < 10; i++)
		my_list.remove_first();
	if (my_list.is_empty() != true) return false;
	return true;
}

bool test_clear_list2() {
	List<int> my_list;
	for (int i = 0; i < 10; i++)
		my_list.push_back(i);
	for (int i = 0; i < 10; i++)
		my_list.remove_first();
	if (my_list.is_empty() != true) return false;

	for (int i = 0; i < 10; i++)
		my_list.push_front(i);
	for (int i = 0; i < 10; i++)
		my_list.remove_last();
	if (my_list.is_empty() != true) return false;
	return true;
}

// Функция тестирует метод печати листа в консоль.
void test_list_print() {
	List<int> my_list;
	std::cout << "Должна напечататься \"елочка\"\n";
	for (int i = 0; i < 10; i++)
		my_list.push_front(i);
	my_list.print();
	for (int i = 0; i < 10; i++) {
		if (i % 2)
			my_list.remove_last();
		else
			my_list.remove_first();
		my_list.print();
	}
}

// Функция запускает подряд все тесты для листа.
void run_all_tests_list() {
	bool res = true;
	res = test_is_empty();
	res = test_front();
	res = test_back();
	res = test_remove_first();
	res = test_remove_last();
	res = test_clear_list1();
	res = test_clear_list1();
	res = test_clear_list2();
	test_list_print();
	if (res) 
		std::cout << "All good" << std::endl;
	else
		std::cout << "Not good";
}

// Далее идут тесты методов стека.

// Тест метода добавления элемента в стек.
bool test_stack_push() {
	Stack<int> steck;
	// Добавили элемент.
	steck.push(1);
	// Проверили, что он лежит в конце стека. 
	if (steck.back() != 1) return false;
	// И так еще раз.
	steck.push(2);
	if (steck.back() != 2) return false;
	return true;
}

// Тест метода удаления элемента из стека.
bool test_stack_pop() {
	Stack<int> steck;
	// Добавили.
	steck.push(1);
	// Удалили.
	steck.pop();
	// Проверили, что там больше ничего не лежит.
	try { steck.back(); }
	catch(const int& ex){ 
		std::cout<<"Stack is empty.\n"; 
	}
	// Добавили два, один удалили.
	steck.push(1);
	steck.push(2);
	steck.pop();
	// Проверили, что лежит тот, что добавили первым.
	if (steck.back() != 1) return false;
	return true;
}

// Тест метода взятия значения последнего элемента стека.
bool test_stack_back() {
	Stack<int> steck;
	// Произвольно добавляем/удаляем элементы.
	steck.push(1);
	steck.push(2);
	steck.push(4);
	steck.pop();
	steck.pop();
	steck.push(3);
	steck.pop();
	// Проверяем, что алгоритм верный.
	if (steck.back() != 1) return false;
	// Удаляем последний элемент, чтобы стек был пустым.
	steck.pop();
	// Проверяем, что метод выдает ошибку, т.е. список пуст и возвращать нечего.
	try { steck.back(); }
	catch (const int& ex) { 
		std::cout << "Stack is empty.\n"; 
	}
	return true;
}

// Объединяем все тесты.
void all_tests_stack() {
	bool res = true;
	res = test_stack_push();
	res = test_stack_pop();
	res = test_stack_back();
	if (res)
		std::cout << "Stack good" << std::endl;
	else
		std::cout << "Stack not good";
}