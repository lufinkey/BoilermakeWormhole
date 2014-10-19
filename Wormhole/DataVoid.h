
#pragma once

namespace Wormhole
{
	typedef unsigned char byte;
	
	class DataVoid
	{
		byte*dataBytes;
		unsigned int total;
	public:
		DataVoid();
		DataVoid(unsigned int size);
		DataVoid(const void*data, unsigned int size);
		DataVoid(const DataVoid&data);
		virtual ~DataVoid();
		
		void*getData();
		unsigned int length();
		
		void resize(unsigned int size);
		void clear();
		DataVoid copy(unsigned int byteIndex, unsigned int size);
		void setData(void*data, unsigned int size);
		
		void add(void*data, unsigned int size);
		void add(unsigned int byteIndex, void*data, unsigned int size);
		void remove(unsigned int byteIndex, unsigned int size);
		void set(unsigned int byteIndex, void*data, unsigned int size);
		void*get(unsigned int byteIndex);
		
		void add(const DataVoid&data);
		void add(unsigned int byteIndex, const DataVoid&data);
		void set(unsigned int byteIndex, const DataVoid&data);
		
		void addByte(byte dataByte);
		void addByte(unsigned int byteIndex, byte dataByte);
		void removeByte(unsigned int byteIndex);
		void setByte(unsigned int byteIndex, byte dataByte);
		byte getByte(unsigned int byteIndex);
		
		static int toInt(void*data);
		static long toLong(void*data);
		static float toFloat(void*data);
		static double toDouble(void*data);
	};
}

