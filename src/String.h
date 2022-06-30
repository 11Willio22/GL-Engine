#pragma once
#include "Array.h"
#include <math.h>

class String
{
	int length;
public:
	char* data;
	inline String()
	{
		this->data = new char[1]{};
		this->length = 0;
	}
	inline String(const char* data)
	{
		this->length = getLength(data);
		this->data = new char[this->length + 1]{};
		for (int i = 0; i < this->length; i++)
		{
			this->data[i] = data[i];
		}
	}
	inline String(const String& str)
	{
		this->length = str.length;
		this->data = new char[this->length + 1]{};
		for (int i = 0; i < this->length; i++)
		{
			this->data[i] = str.data[i];
		}
	}
	inline bool equals(const String& str)
	{
		if (this->length != str.length) return false;
		bool same = true;
		for (int i = 0; i < this->length; i++)
		{
			if (this->data[i] != str.data[i]) same = false;
		}
		return same;
	}
	inline Array<String> split(const char del)
	{
		Array<String> result;
		int lastIndex = 0;
		for (int i = 0; i < this->length; i++)
		{
			if (this->data[i] == del)
			{
				result.add(slice(lastIndex,i));
				lastIndex = i + 1;
			}
		}
		result.add(slice(lastIndex, this->length));
		return result;
	}
	inline String slice(int left, int right)
	{
		String m;
		m.length = right - left;
		m.data = new char[m.length + 1]{};
		for (int i = left; i < right; i++)
		{
			m.data[i - left] = this->data[i];
		}
		m.data[m.length] = '\0';
		return m;
	}
	inline bool startsWith(const String& str)
	{
		if (this->length >= str.length)
		{
			for (int i = 0; i < str.length; i++)
			{
				if (this->data[i] != str.data[i]) return false;
			}
			return true;
		}
		return false;
	}
	inline bool operator==(const String& str)
	{
		return equals(str);
	}
	inline bool operator==(const char* str)
	{
		return equals(String(str));
	}
	inline int getLength(const char* data)
	{
		int length = 0;
		while (data[length++] != '\0');
		return length - 1;
	}
	inline int& getLength()
	{
		return this->length;
	}

	inline float parse()
	{
		return atof(this->data);
	}

	inline String operator+(String str)
	{
		int newLength = this->length + str.length;
		char* newData = new char[newLength + 1];
		newData[newLength] = '\0';
		for (int i = 0; i < this->length; i++) newData[i] = this->data[i];
		for (int i = this->length; i < this->length + str.length; i++) newData[i] = str.data[i - this->length];
		String result(newData);
		delete[] newData;
		return result;
	}

	inline String& operator+=(String str)
	{
		char* oldData = this->data;
		int newLength = this->length + str.length;
		this->data = new char[newLength + 1];
		this->data[newLength] = '\0';
		for (int i = 0; i < this->length; i++) this->data[i] = oldData[i];
		for (int i = this->length; i < this->length + str.length; i++) this->data[i] = str.data[i - this->length];
		this->length = newLength;
		delete[] oldData;
		return *this;
	}

	inline char& operator[](int index)
	{
		if (index >= this->length) return this->data[this->length - 1];
		return this->data[index];
	}
};