#pragma once
#include<memory>
#include "Ndarray.h"

namespace numpy
{
	template<typename T>
	class Numpy final
	{
	public:
		Numpy() = delete;
		~Numpy() = delete;

		static Ndarray<T> array(const unsigned int& demension, const unsigned int* arraySize, const unsigned int* data);
		static Ndarray<T> Zeros(const unsigned int* data);
		static Ndarray<T> Ones(const unsigned int* data);
	private:
		static int mSeed;
	};

	template<typename T>
	inline Ndarray<T> Numpy<T>::array(const unsigned int& demension, const unsigned int* arraySize, const unsigned int* data)
	{
		return Ndarray<T>();
	}

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
}

