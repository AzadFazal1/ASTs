
#include "stack.h"

namespace cs225
{

template <class T>
const T& stack<T>::top() const
{
	return arr_.at(0);
}

template <class T>
T& stack<T>::top()
{
	return arr_.at(0);
}

template <class T>
void stack<T>::push(const T& elem)
{
    arr_.push_front(std::move(elem));
}

template <class T>
void stack<T>::push(T&& elem)
{
        arr_.push_front(std::move(elem));

}

template <class T>
void stack<T>::pop()
{
    arr_.pop_front();
}

template <class T>
uint64_t stack<T>::size() const
{
	arr_.size();
}

template <class T>
bool stack<T>::empty() const
{
	return arr_.empty();
}
}
