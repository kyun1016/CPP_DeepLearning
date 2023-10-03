#pragma once
#include<memory>
#include<cassert>
#include<iostream>

namespace numpy
{
	template<typename T>
	class Ndarray final
	{
	public:
		Ndarray();
		Ndarray(const unsigned int& demension, const unsigned int& totalSize, std::unique_ptr<unsigned int[]> arraySize, std::unique_ptr<T[]> array);
		Ndarray(const unsigned int& demension, const unsigned int& totalSize, const unsigned int* arraySize, const unsigned int* array);
		Ndarray(const Ndarray<T>& rhs);
		Ndarray(Ndarray<T>&& rhs);
		~Ndarray() = default;
		Ndarray<T>& operator=(const Ndarray<T>& rhs);
		Ndarray<T>& operator=(Ndarray<T>&& rhs);

		bool operator==(const Ndarray<T>& rhs);
		Ndarray<T> operator+(const Ndarray<T>& rhs);
		void Reshape(const unsigned int arraySize[]);




		friend std::ostream& operator<<(std::ostream& os, const Ndarray<T>& rhs)
		{
			for (unsigned int i = 0; i < rhs.mTotalSize; ++i)
			{
				unsigned int size = 1;
				for (unsigned int j = rhs.mDemension; j > 0; --j)
				{
					size *= rhs.mArraySize[j - 1];
					if (i % size == 0)
					{
						os << "[";
					}
				}
				os << rhs.mArray[i];

				size = 1;
				for (unsigned int j = rhs.mDemension; j > 0; --j)
				{
					size *= rhs.mArraySize[j - 1];
					if (i % size == size - 1)
					{
						os << "]";
						if (j == 0)
						{
							os << std::endl;
						}
					}
					else
					{
						os << " ";
					}

				}
			}
			return os;
		}
	private:
		unsigned int mDemension;
		unsigned int mTotalSize;
		std::unique_ptr<unsigned int[]> mArraySize;
		std::unique_ptr<T[]> mArray;
	};

	template<typename T>
	Ndarray<T>::Ndarray()
		: mDemension(0)
		, mTotalSize(0)
		, mArraySize(nullptr)
		, mArray(nullptr)
	{
	}

	template<typename T>
	Ndarray<T>::Ndarray(const unsigned int& demension, const unsigned int& totalSize, std::unique_ptr<unsigned int[]> arraySize, std::unique_ptr<T[]> array)
		: mDemension(demension)
		, mTotalSize(totalSize)
		, mArraySize(std::move(arraySize))
		, mArray(std::move(array))
	{
	}

	template<typename T>
	Ndarray<T>::Ndarray(const unsigned int& demension, const unsigned int& totalSize, const unsigned int* arraySize, const unsigned int* array)
		: mDemension(demension)
		, mTotalSize(totalSize)
	{
		mArraySize = std::make_unique<unsigned int[]>(mDemension);
		for (unsigned int i = 0; i < mDemension; ++i)
		{
			mArraySize[i] = arraySize[i];
		}

		mArray = std::make_unique<T[]>(mTotalSize);
		for (unsigned int i; i < mTotalSize; ++i)
		{
			mArray[i] = array[i];
		}
	}

	template<typename T>
	Ndarray<T>::Ndarray(const Ndarray<T>& rhs)
		: mDemension(rhs.mDemension)
		, mTotalSize(rhs.mTotalSize)
	{
		mArraySize = std::make_unique<unsigned int[]>(mDemension);
		for (unsigned int i = 0; i < mDemension; ++i)
		{
			mArraySize[i] = rhs.mArraySize[i];
		}
		mArray = std::make_unique<T[]>(mTotalSize);
		for (unsigned int i = 0; i < mTotalSize; ++i)
		{
			mArray[i] = rhs.mArray[i];
		}
	}

	template<typename T>
	Ndarray<T>::Ndarray(Ndarray<T>&& rhs)
		: mDemension(rhs.mDemension)
		, mTotalSize(rhs.mTotalSize)
	{
		rhs.mDemension = 0u;
		rhs.mTotalSize = 0u;
		mArraySize = std::move(rhs.mArraySize);
		mArray = std::move(rhs.mArray);
	}

	template<typename T>
	Ndarray<T>& Ndarray<T>::operator=(const Ndarray<T>& rhs)
	{
		if (this == &rhs)
		{
			return *this;
		}
		mDemension = rhs.mDemension;
		mTotalSize = rhs.mTotalSize;
		mArraySize = std::make_unique<unsigned int[]>(mDemension);
		for (unsigned int i = 0; i < mDemension; ++i)
		{
			mArraySize[i] = rhs.mArraySize[i];
		}
		mArray = std::make_unique<T[]>(mTotalSize);
		for (unsigned int i = 0; i < mTotalSize; ++i)
		{
			mArray[i] = rhs.mArray[i];
		}

		return *this;
	}

	template<typename T>
	Ndarray<T>& Ndarray<T>::operator=(Ndarray<T>&& rhs)
	{
		if (this == &rhs)
		{
			return *this;
		}
		mDemension = rhs.mDemension;
		rhs.mDemension = 0u;
		mTotalSize = rhs.mTotalSize;
		rhs.mTotalSize = 0u;
		mArraySize = std::move(rhs.mArraySize);
		mArray = std::move(rhs.mArray);

		return *this;
	}

	template<typename T>
	void Ndarray<T>::Reshape(const unsigned int arraySize[])
	{
		unsigned int demension = static_cast<unsigned int>(sizeof(arraySize) / sizeof(arraySize[0]));

		unsigned int totalSize = 1;
		std::unique_ptr<unsigned int[]> newArraySize = std::make_unique<unsigned int[]>(demension);
		for (unsigned int i = 0; i < demension; ++i)
		{
			newArraySize[i] = arraySize[i];
			totalSize *= arraySize[i];
		}

		// assert(totalSize == mTotalSize, "must same total size");

		mDemension = demension;
		mArraySize = std::move(newArraySize);
	}

	template<typename T>
	inline bool Ndarray<T>::operator==(const Ndarray<T>& rhs)
	{
		if (mDemension != rhs.mDemension)
			return false;
		if (mTotalSize != rhs.mTotalSize)
			return false;
		for (unsigned int i = 0; i < mDemension; ++i)
			if (mArraySize[i] != rhs.mArraySize[i])
				return false;
		for (unsigned int i = 0; i < mTotalSize; ++i)
			if (mArray[i] != rhs.mArray[i])
				return false;

		return true;
	}

	template<typename T>
	Ndarray<T> Ndarray<T>::operator+(const Ndarray<T>& rhs)
	{
		if (this->mDemension != rhs.mDemension)
			return Ndarray<T>();
		if (this->mTotalSize != rhs.mTotalSize)
			return Ndarray<T>();
		for (unsigned int i = 0; i < mDemension; ++i)
			if (mArraySize[i] != rhs.mArraySize[i])
				return Ndarray<T>();

		std::unique_ptr<unsigned int[]> arraySize = std::make_unique<unsigned int[]>(mDemension);
		for (unsigned int i = 0; i < mDemension; ++i)
		{
			arraySize[i] = rhs.mArraySize[i];
		}

		std::unique_ptr<T[]> array = std::make_unique<T[]>(mTotalSize);
		for (unsigned int i = 0; i < mTotalSize; ++i)
		{
			array[i] = this->mArray[i] + rhs.mArray[i];
		}
		Ndarray<T> ret(rhs.mDemension, rhs.mArraySize, std::move(arraySize), std::move(array)); // TODO: change unique_ptr
		return Ndarray<T>();
	}
}