#pragma once
#include<memory>
#include "Ndarray.h"

namespace numpy
{
	template<typename T>
	class Numpy
	{
	public:
		Numpy() = delete;
		~Numpy() = delete;

		//static Ndarray<T> Array(const unsigned int& demension, const unsigned int* arraySize, const unsigned int* data);
		static Ndarray<T> Zeros(const unsigned int* data);
		static Ndarray<T> Ones(const unsigned int* data);
		static Ndarray<T> Dot(const Ndarray<T>& a, const Ndarray<T>& b);
	private:
		static int mSeed;
	};

	//template<typename T>
	//Ndarray<T> Numpy<T>::Array(const unsigned int& demension, const unsigned int* arraySize, const unsigned int* data)
	//{
	//	return Ndarray<T>(); // TODO: Make function
	//}

	template<typename T>
	Ndarray<T> Numpy<T>::Zeros(const unsigned int* data)
	{
		unsigned int demension = static_cast<unsigned int>(sizeof(data) / sizeof(data[0]));

		unsigned int totalSize = 1;
		std::unique_ptr<unsigned int[]> arraySize = std::make_unique<unsigned int[]>(demension);
		for (unsigned int i = 0; i < demension; ++i)
		{
			arraySize[i] = data[i];
			totalSize *= data[i];
		}

		std::unique_ptr<T[]> array = std::make_unique<T[]>(totalSize);
		for (unsigned int i = 0; i < totalSize; ++i)
		{
			array[i] = 0;
		}

		return Ndarray<T>(demension, totalSize, arraySize, array);
	}

	template<typename T>
	Ndarray<T> Numpy<T>::Ones(const unsigned int* data)
	{
		unsigned int demension = static_cast<unsigned int>(sizeof(data) / sizeof(data[0]));

		unsigned int totalSize = 1;
		std::unique_ptr<unsigned int[]> arraySize = std::make_unique<unsigned int[]>(demension);
		for (unsigned int i = 0; i < demension; ++i)
		{
			arraySize[i] = data[i];
			totalSize *= data[i];
		}

		std::unique_ptr<T[]> array = std::make_unique<T[]>(totalSize);
		for (unsigned int i = 0; i < totalSize; ++i)
		{
			array[i] = 1;
		}

		return Ndarray<T>(demension, totalSize, std::move(arraySize), std::move(array));
	}

	template<typename T>
	inline Ndarray<T> Numpy<T>::Dot(const Ndarray<T>& a, const Ndarray<T>& b)
	{
		if (a.mDemension > 2 || b.mDemension > 2 || a.mDemension == 0 || b.mDemension == 0)
			return Ndarray<T>();
		if (a.mDemension == 1 && b.mArraySize[0] != 1)
			return Ndarray<T>();
		else if(a.mArraySize[1] != b.mArraySize[0])
			return Ndarray<T>();

		std::unique_ptr<unsigned int[]> arraySize = std::make_unique<unsigned int[]>(2);
		arraySize[0] = a.mArraySize[0];
		arraySize[1] = b.mDemension == 1 ? 1u : b.mArraySize[1];

		unsigned int totalSize = arraySize[0] * arraySize[1];
		std::unique_ptr<T[]> array = std::make_unique<T[]>(totalSize);

		for (unsigned int i = 0; i < totalSize; ++i)
		{
			unsigned int k = static_cast<unsigned int>(i / arraySize[0]);
			unsigned int y = static_cast<unsigned int>(i / arraySize[1]);
			for (unsigned int j = 0; j < b.mArraySize[0]; ++j)
			{
				array[i] += a.mArray[j + k * b.mArraySize[0]] * b.mArray[y + j * b.mArraySize[0]];
			}
		}

		return Ndarray<T>(2u, totalSize, arraySize, array);
	}
}

