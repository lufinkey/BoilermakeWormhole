
#include <vector>

#pragma once

template <class T>
class ArrayList
{
private:
	std::vector<T> objects;
	int total;
		
public:
	ArrayList()
	{
		total = 0;
	}
		
	ArrayList(const ArrayList<T>& arr)
	{
		total = arr.total;
		objects.resize(total);
		for(int i=0; i<total; i++)
		{
			objects[i] = arr[i];
		}
	}
		
	ArrayList(int size)
	{
		objects.resize(size);
		total = size;
	}
		
	virtual ~ArrayList()
	{
		objects.resize(0);
		total = 0;
	}
		
	T& get(int index)
	{
		T&obj = (T&)objects[index];
		return obj;
	}
		
	const T& get(int index) const
	{
		return (const T&)objects[index];
	}
		
	T& operator[] (int index)
	{
		T&obj = (T&)objects[index];
		return obj;
	}
		
	const T& operator[] (int index) const
	{
		return (const T&)objects[index];
	}
		
	void set(int index, const T&obj)
	{
		if(index<total)
		{
			objects[index] = obj;
		}
	}
		
	void add(const T&obj)
	{
		total++;
		int oldSize = objects.size();
		do
		{
			objects.resize(total);
		}
		while(objects.size()==oldSize);
		objects[total-1] = obj;
	}
		
	void add(int index, const T&obj)
	{
		if(index<=total && index>=0)
		{
			total++;
			objects.resize(total);
			for(int i=(total-1); i>index; i--)
			{
				objects[i] = objects[i-1];
			}
			objects[index] = obj;
		}
	}
		
	void remove(int index)
	{
		if(total==1 && index==0)
		{
			objects.resize(0);
			total = 0;
		}
		else if(index<total && index>=0)
		{
			for(int i=(index+1); i<total; i++)
			{
				objects[i-1] = objects[i];
			}
			total--;
			objects.resize(total);
		}
	}
		
	void clear()
	{
		objects.resize(0);
		total = 0;
	}
		
	int size() const
	{
		return total;
	}
		
	ArrayList<T>& operator=(const ArrayList<T>& arr)
	{
		total = arr.total;
		objects.resize(total);
		for (int i = 0; i < total; i++)
		{
			objects[i] = arr.objects[i];
		}
			
		return *this;
	}

	bool contains(const T&obj) const
	{
		for(int i=0; i<total; i++)
		{
			const T& cmp = (const T&)objects[i];
			if ((const T&)obj==(const T&)cmp)
			{
				return true;
			}
		}
		return false;
	}
};
