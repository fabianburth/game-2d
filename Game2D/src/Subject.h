#pragma once

#include <memory>

#include "Observer.h"
template<class T>
class Subject
{
public:
	virtual void addObserver(const std::shared_ptr<Observer<T>>&) = 0;
	virtual void removeObserver(const std::shared_ptr<Observer<T>>&) = 0;
	virtual void notify() = 0;
};