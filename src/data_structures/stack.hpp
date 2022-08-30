#ifndef STACK_HPP
#define STACK_HPP

#include "dllist.hpp"

template <class Type>
class Stack {
private:
	List<Type> _list;
public:
	Stack() : _list(List<Type>()) {}
	~Stack() {}
	void push(Type key);
	void pop();
	Type back();
};

template <class Type>
void Stack<Type>::push(Type key) {
	_list.push_back(key);
}

template <class Type>
void Stack<Type>::pop() {
	_list.remove_last();
}

template <class Type>
Type Stack<Type>::back() {
	if(_list.is_empty()) throw 1;
	return _list.back()->value();
}

#endif //STACK_HPP
