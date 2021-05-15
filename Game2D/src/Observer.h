#pragma once
template<class T>
class Observer
{
public:
	virtual void update(T gameObject) = 0;
};