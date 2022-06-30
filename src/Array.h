#pragma once

#include <cstdio>

template <typename type>
class Array
{
	int length;
public:
	type* data;
	int depth;

	Array()
	{
		this->data = new type[1];
		this->length = 1;
		this->depth = 0;
	}
	void add(const type& t)
	{
		if (this->depth + 1 >= this->length) resize(this->length * 2);
		this->data[this->depth++] = t;
	}
	type& get(int index)
	{
		if (index >= this->depth) return this->data[0];
		return this->data[index];
	}
	void resize(int newLength)
	{
		type* oldData = this->data;
		this->data = new type[newLength];
		for (int i = 0; i < this->length; i++)
		{
			this->data[i] = oldData[i];
		}
		delete[] oldData;
		this->length = newLength;
	}
};