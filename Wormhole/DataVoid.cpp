
#include "DataVoid.h"
#include "../AppEngine/Util/String.h"
#include <stdlib.h>
#include <cstdlib>

namespace Wormhole
{
	DataVoid::DataVoid()
	{
		dataBytes = NULL;
		total = 0;
	}
	
	DataVoid::DataVoid(unsigned int size)
	{
		dataBytes = (byte*)std::malloc(size);
		for(unsigned int i=0; i<size; i++)
		{
			dataBytes[i] = 0;
		}
		total = size;
	}
	
	DataVoid::DataVoid(void*data, unsigned int size)
	{
		if(size>0)
		{
			dataBytes = (byte*)malloc(size);
			byte*copyBytes = (byte*)data;
			for(unsigned int i=0; i<size; i++)
			{
				dataBytes[i] = copyBytes[i];
			}
			total = size;
		}
		else
		{
			dataBytes = NULL;
			total = 0;
		}
	}
	
	DataVoid::DataVoid(const DataVoid&data)
	{
		if(data.dataBytes == NULL)
		{
			dataBytes = NULL;
			total = 0;
		}
		else
		{
			dataBytes = (byte*)malloc(data.total);
			for(unsigned int i=0; i<data.total; i++)
			{
				dataBytes[i] = data.dataBytes[i];
			}
			total = data.total;
		}
	}
	
	DataVoid::~DataVoid()
	{
		if(dataBytes!=NULL)
		{
			free(dataBytes);
			dataBytes = NULL;
			total = 0;
		}
	}
	
	void*DataVoid::getData()
	{
		return (void*)dataBytes;
	}
	
	unsigned int DataVoid::length()
	{
		return total;
	}
	
	void DataVoid::resize(unsigned int size)
	{
		if(size > 0)
		{
			if(dataBytes==NULL)
			{
				dataBytes = (byte*)malloc(size);
				for(unsigned int i=0; i<size; i++)
				{
					dataBytes[i] = 0;
				}
				total = size;
			}
			else
			{
				dataBytes = (byte*)realloc(dataBytes, size);
				if(size>total)
				{
					for(unsigned int i=total; i<size; i++)
					{
						dataBytes[i] = 0;
					}
				}
				total = size;
			}
		}
		else
		{
			if(dataBytes!=NULL)
			{
				free(dataBytes);
				dataBytes = NULL;
				total = 0;
			}
		}
	}
	
	void DataVoid::clear()
	{
		if(dataBytes!=NULL)
		{
			free(dataBytes);
			dataBytes = NULL;
			total = 0;
		}
	}
	
	void DataVoid::add(void*data, unsigned int size)
	{
		if(dataBytes == NULL)
		{
			dataBytes = (byte*)malloc(size);
			byte*copyBytes = (byte*)data;
			for(unsigned int i=0; i<size; i++)
			{
				dataBytes[i] = copyBytes[i];
			}
			total = size;
		}
		else
		{
			unsigned int total2 = total + size;
			dataBytes = (byte*)realloc(dataBytes, total2);
			byte*copyBytes = (byte*)data;
			unsigned int counter = 0;
			for(unsigned int i=total; i<total2; i++)
			{
				dataBytes[i] = copyBytes[counter];
				counter++;
			}
			total = total2;
		}
	}
	
	void DataVoid::add(unsigned int byteIndex, void*data, unsigned int size)
	{
		if(dataBytes == NULL)
		{
			if(byteIndex == 0)
			{
				dataBytes = (byte*)malloc(size);
				byte*copyBytes = (byte*)data;
				for(unsigned int i=0; i<size; i++)
				{
					dataBytes[i] = copyBytes[i];
				}
				total = size;
			}
			else
			{
				//error
				throw ((char*)((String)"byteIndex " + byteIndex + " out of bounds. DataVoid length is 0"));
			}
		}
		else if(byteIndex <= total)
		{
			unsigned int total2 = total+size;
			dataBytes = (byte*)realloc(dataBytes, total2);
			byte*copyBytes = (byte*)data;
			unsigned int counter = byteIndex;
			for(unsigned int i=(total2-1); i>byteIndex; i--)
			{
				dataBytes[i] = dataBytes[i-1];
			}
			counter = byteIndex;
			for(unsigned int i=0; i<size; i++)
			{
				dataBytes[byteIndex] = copyBytes[i];
				counter++;
			}
			total = total2;
		}
		else
		{
			//error
			throw ((char*)((String)"byteIndex " + byteIndex + " out of bounds. DataVoid length is " + total));
		}
	}
	
	void DataVoid::add(const DataVoid&data)
	{
		if(dataBytes == NULL)
		{
			dataBytes = (byte*)malloc(data.total);
			for(unsigned int i=0; i<data.total; i++)
			{
				dataBytes[i] = data.dataBytes[i];
			}
			total = data.total;
		}
		else
		{
			unsigned int total2 = total + data.total;
			dataBytes = (byte*)realloc(dataBytes, total2);
			unsigned int counter = 0;
			for(unsigned int i=total; i<total2; i++)
			{
				dataBytes[i] = data.dataBytes[counter];
				counter++;
			}
			total = total2;
		}
	}
	
	void DataVoid::add(unsigned int byteIndex, const DataVoid&data)
	{
		if(dataBytes == NULL)
		{
			if(byteIndex == 0)
			{
				dataBytes = (byte*)malloc(data.total);
				for(unsigned int i=0; i<data.total; i++)
				{
					dataBytes[i] = data.dataBytes[i];
				}
				total = data.total;
			}
			else
			{
				//error
				throw ((char*)((String)"byteIndex " + byteIndex + " out of bounds. DataVoid length is 0"));
			}
		}
		else if(byteIndex <= total)
		{
			unsigned int total2 = total+data.total;
			dataBytes = (byte*)realloc(dataBytes, total2);
			unsigned int counter = byteIndex;
			for(unsigned int i=(total2-1); i>byteIndex; i--)
			{
				dataBytes[i] = dataBytes[i-1];
			}
			counter = byteIndex;
			for(unsigned int i=0; i<data.total; i++)
			{
				dataBytes[byteIndex] = data.dataBytes[i];
				counter++;
			}
			total = total2;
		}
		else
		{
			//error
			throw ((char*)((String)"byteIndex " + byteIndex + " out of bounds. DataVoid length is " + total));
		}
	}
	
	void DataVoid::addByte(byte dataByte)
	{
		if(dataBytes == NULL)
		{
			dataBytes = (byte*)malloc(1);
			dataBytes[0] = dataByte;
			total = 1;
		}
		else
		{
			dataBytes = (byte*)realloc(dataBytes, total+1);
			dataBytes[total] = dataByte;
			total += 1;
		}
	}
	
	void DataVoid::addByte(unsigned int byteIndex, byte dataByte)
	{
		if(dataBytes == NULL)
		{
			if(byteIndex == 0)
			{
				dataBytes = (byte*)malloc(1);
				dataBytes[0] = dataByte;
				total = 1;
			}
			else
			{
				//error
				throw ((char*)((String)"byteIndex " + byteIndex + " out of bounds. DataVoid length is 0"));
			}
		}
		else if(byteIndex <= total)
		{
			unsigned int total2 = total+1;
			dataBytes = (byte*)realloc(dataBytes, total2);
			for(unsigned int i=(total2-1); i>byteIndex; i--)
			{
				dataBytes[i] = dataBytes[i-1];
			}
			dataBytes[byteIndex] = dataByte;
			total = total2;
		}
		else
		{
			//error
			throw ((char*)((String)"byteIndex " + byteIndex + " out of bounds. DataVoid length is " + total));
		}
	}
	
	void DataVoid::remove(unsigned int byteIndex, unsigned int size)
	{
		if(dataBytes==NULL)
		{
			throw ((char*)((String)"byteIndex " + byteIndex + " and size " + size + " out of bounds. DataVoid length is 0"));
		}
		else if(byteIndex<total && (byteIndex+size)<=total)
		{
			unsigned int endOfRemove = byteIndex+size;
			unsigned int counter = byteIndex;
			for(unsigned int i=endOfRemove; i<total; i++)
			{
				dataBytes[counter] = dataBytes[i];
				counter++;
			}
			unsigned int total2 = total - size;
			dataBytes = (byte*)realloc(dataBytes, total2);
			total = total2;
		}
		else
		{
			throw ((char*)((String)"byteIndex " + byteIndex + " and size " + size + " out of bounds. DataVoid length is " + total));
		}
	}
	
	void DataVoid::removeByte(unsigned int byteIndex)
	{
		if(dataBytes == NULL)
		{
			throw ((char*)((String)"byteIndex " + byteIndex + " out of bounds. DataVoid length is 0"));
		}
		else if(byteIndex<total)
		{
			unsigned int endOfRemove = byteIndex+1;
			unsigned int counter = byteIndex;
			for(unsigned int i=endOfRemove; i<total; i++)
			{
				dataBytes[counter] = dataBytes[i];
				counter++;
			}
			unsigned int total2 = total - 1;
			dataBytes = (byte*)realloc(dataBytes, total2);
			total = total2;
		}
		else
		{
			throw ((char*)((String)"byteIndex " + byteIndex + " out of bounds. DataVoid length is " + total));
		}
	}
	
	void DataVoid::set(unsigned int byteIndex, void*data, unsigned int size)
	{
		if(dataBytes == NULL)
		{
			throw ((char*)((String)"byteIndex " + byteIndex + " and size " + size + " out of bounds. DataVoid length is 0"));
		}
		else if(byteIndex<total && (byteIndex+size)<=total)
		{
			byte*copyBytes = (byte*)data;
			unsigned int counter = byteIndex;
			for(unsigned int i=0; i<size; i++)
			{
				dataBytes[counter] = copyBytes[i];
			}
		}
		else
		{
			throw ((char*)((String)"byteIndex " + byteIndex + " and size " + size + " out of bounds. DataVoid length is " + total));
		}
	}
	
	void DataVoid::set(unsigned int byteIndex, const DataVoid&data)
	{
		if(dataBytes == NULL)
		{
			throw ((char*)((String)"byteIndex " + byteIndex + " and data size " + data.total + " out of bounds. DataVoid length is 0"));
		}
		else if(byteIndex<total && (byteIndex+data.total)<=total)
		{
			unsigned int counter = byteIndex;
			for(unsigned int i=0; i<data.total; i++)
			{
				dataBytes[counter] = data.dataBytes[i];
				counter++;
			}
		}
		else
		{
			throw ((char*)((String)"byteIndex " + byteIndex + " and data size " + data.total + " out of bounds. DataVoid length is " + total));
		}
	}
	
	void DataVoid::setByte(unsigned int byteIndex, byte dataByte)
	{
		if(dataBytes == NULL)
		{
			throw ((char*)((String)"byteIndex " + byteIndex + " out of bounds. DataVoid length is 0"));
		}
		else if(byteIndex<total)
		{
			dataBytes[byteIndex] = dataByte;
		}
		else
		{
			throw ((char*)((String)"byteIndex " + byteIndex + " out of bounds. DataVoid length is " + total));
		}
	}
	
	void*DataVoid::get(unsigned int byteIndex)
	{
		if(dataBytes==NULL)
		{
			return NULL;
		}
		else
		{
			return (void*)(dataBytes + byteIndex);
		}
	}
	
	byte DataVoid::getByte(unsigned int byteIndex)
	{
		if(dataBytes==NULL)
		{
			return 0;
		}
		else
		{
			return dataBytes[byteIndex];
		}
	}
	
	DataVoid DataVoid::copy(unsigned int byteIndex, unsigned int size)
	{
		if(dataBytes == NULL)
		{
			throw ((char*)((String)"byteIndex " + byteIndex + " and size " + size + " out of bounds. DataVoid length is 0"));
		}
		else if(byteIndex<total && (byteIndex+size)<=total)
		{
			return DataVoid((void*)(dataBytes + byteIndex), size);
		}
		else
		{
			throw ((char*)((String)"byteIndex " + byteIndex + " and size " + size + " out of bounds. DataVoid length is " + total));
		}
		return DataVoid();
	}
	
	void DataVoid::setData(void*data, unsigned int size)
	{
		if(dataBytes!=NULL)
		{
			free(dataBytes);
			dataBytes = NULL;
			total = 0;
		}
		dataBytes = (byte*)malloc(size);
		byte*copyBytes = (byte*)data;
		for(unsigned int i=0; i<size; i++)
		{
			dataBytes[i] = copyBytes[i];
		}
		total = size;
	}
	
	int DataVoid::toInt(void*data)
	{
		unsigned int size = sizeof(int);
		unsigned char*buffer = new unsigned char[size];
		unsigned char*copy = (unsigned char*)data;
		for(unsigned int i=0; i<size; i++)
		{
			buffer[i] = copy[i];
		}
		int r = *((int*)buffer);
		delete[] buffer;
		return r;
	}
	
	long DataVoid::toLong(void*data)
	{
		unsigned int size = sizeof(long);
		unsigned char*buffer = new unsigned char[size];
		unsigned char*copy = (unsigned char*)data;
		for(unsigned int i=0; i<size; i++)
		{
			buffer[i] = copy[i];
		}
		long r = *((long*)buffer);
		delete[] buffer;
		return r;
	}
	
	float DataVoid::toFloat(void*data)
	{
		unsigned int size = sizeof(float);
		unsigned char*buffer = new unsigned char[size];
		unsigned char*copy = (unsigned char*)data;
		for(unsigned int i=0; i<size; i++)
		{
			buffer[i] = copy[i];
		}
		float r = *((float*)buffer);
		delete[] buffer;
		return r;
	}
	
	double DataVoid::toDouble(void*data)
	{
		unsigned int size = sizeof(double);
		unsigned char*buffer = new unsigned char[size];
		unsigned char*copy = (unsigned char*)data;
		for(unsigned int i=0; i<size; i++)
		{
			buffer[i] = copy[i];
		}
		double r = *((double*)buffer);
		delete[] buffer;
		return r;
	}
}