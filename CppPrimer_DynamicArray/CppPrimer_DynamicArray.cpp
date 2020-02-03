#include <iostream>
#include <cstdlib>

using namespace std;

//custom exception types
class OutOfRange
{
private:
	int m_flag;//different flag identify different error
	int m_len;//the length of array
	int m_index;//index of array
public:
	OutOfRange() {};
	OutOfRange(int len, int index) :m_len(len), m_index(index), m_flag(2) {}
	void what() const;//obtain specific error information
};

void OutOfRange::what() const
{
	if (m_flag == 1)
	{
		cout << "Error: empty array, no elements to pop." << endl;
	}
	else if(m_flag == 2)
	{
		cout << "Error: out of range(array length " << m_len << ", access index " << m_index << ") " << endl;
	}
	else
	{
		cout << "Unknown exception." << endl;
	}
}

//implement dynamic array
class Array
{
private:
	int m_len;//the length of array
	int m_capacity; //the number element of the current memory hold
	int* m_p; // memory pointer

	static const int m_stepSize = 50; // step size per expansion

public:
	Array();
	~Array() { free(m_p); }

	int operator[] (int i) const;//obtain element in array
	int push(int ele);//insert element of array at the rear
	int pop();//delete element of array at the rear
	int length() const { return m_len; }//obtain the length of array
};

Array::Array()
{
	m_p = (int*)malloc(sizeof(int) * m_stepSize);
	m_capacity = m_stepSize;
	m_len = 0;
}

int Array::operator[](int index) const
{
	if (index < 0 || index >= m_len)
	{
		throw OutOfRange(m_len, index);//throw expection
	}
	
	return *(m_p + index);
}

int Array::push(int ele)
{
	if (m_len >= m_capacity)
	{
		m_capacity += m_stepSize;
		m_p = (int*)realloc(m_p, sizeof(int) * m_capacity); // expand
	}
	*(m_p + m_len) = ele;
	m_len++;

	return m_len - 1;
}

int Array::pop()
{
	if (m_len == 0)
	{
		throw OutOfRange();//throw expection
	}
	m_len--;

	return *(m_p + m_len);
}

void printArray(Array& arr)
{
	int len = arr.length();

	if (len == 0)
	{
		cout << "Empty array! No element to print." << endl;
		return;
	}

	for (int i = 0; i < len; i++)
	{
		if (i == len - 1)
		{
			cout << arr[i] << endl;
		}
		else
		{
			cout << arr[i] << endl;
		}
	}
}

int main()
{
	Array nums;
	for (int i = 0; i < 10; i++)
	{
		nums.push(i);
	}
	printArray(nums);

	try
	{
		cout << nums[20] << endl;
	}
	catch (OutOfRange & e)
	{
		e.what();
	}

	try
	{
		for (int i = 0; i < 20; i++)
		{
			nums.pop();
		}
	}
	catch (OutOfRange & e)
	{
		e.what();
	}

	printArray(nums);

	return 0;
}