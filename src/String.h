#pragma once

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
		this->data = new char[this->length];
		for (int i = 0; i < this->length; i++)
		{
			this->data[i] = data[i];
		}
	}
	inline bool equals(String& str)
	{
		if (this->length != str.length) return false;
		bool same = true;
		for (int i = 0; i < this->length; i++)
		{
			if (this->data[i] != str.data[i]) same = false;
		}
		return same;
	}
	inline bool operator==(String& str)
	{
		return equals(str);
	}
	inline int getLength(const char* data)
	{
		int length = 0;
		while (data[length++] != '\0');
		return length;
	}
	inline int getLength()
	{
		return this->length;
	}

	inline String operator+(String str)
	{
		int newLength = this->length + str.length;
		char* newData = new char[newLength + 1];
		newData[newLength] = '\0';
		for (int i = 0; i < this->length; i++) newData[i] = this->data[i];
		for (int i = this->length; i < this->length + str.length; i++) newData[i] = str.data[i];
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
		for (int i = this->length; i < this->length + str.length; i++) this->data[i] = str.data[i];
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