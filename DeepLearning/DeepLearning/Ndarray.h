#pragma once
#include<memory>
#include<cassert>
#include<iostream>
#include<initializer_list>

namespace numpy
{
	template<typename T>
	class Numpy;

	template<typename T>
	class Ndarray final
	{
		friend class Numpy<T>;
	public:
		Ndarray();
		Ndarray(const std::initializer_list<int> arraySize, const T& value);
		Ndarray(const std::initializer_list<int> arraySize);
		Ndarray(const unsigned int& dimension, const unsigned int& totalSize, const std::unique_ptr<unsigned int[]>& arraySize, const std::unique_ptr<T[]>& array);
		Ndarray(const unsigned int& dimension, const unsigned int& totalSize, const unsigned int* arraySize, const unsigned int* array);
		Ndarray(const Ndarray<T>& rhs);
		Ndarray(Ndarray<T>&& rhs);
		~Ndarray() = default;

		Ndarray<T>& operator=(const Ndarray<T>& rhs);
		Ndarray<T>& operator=(Ndarray<T>&& rhs);
		bool operator==(const Ndarray<T>& rhs) const;
		bool operator!=(const Ndarray<T>& rhs) const;
		Ndarray<T> operator+(const Ndarray<T>& rhs) const;
		Ndarray<T> operator+(const int& rhs) const;
		Ndarray<T> operator+(const float& rhs) const;
		Ndarray<T> operator*(const Ndarray<T>& rhs) const;
		Ndarray<T> operator*(const int& rhs) const;
		Ndarray<T> operator*(const float& rhs) const;

		void Reshape(const unsigned int* arraySize);

		friend std::ostream& operator<<(std::ostream& os, const Ndarray<T>& rhs)
		{
			for (unsigned int i = 0; i < rhs.mTotalSize; ++i)
			{
				unsigned int size = 1;
				for (unsigned int j = rhs.mDimension; j > 0; --j)
				{
					size *= rhs.mArraySize[j - 1];
					if (i % size == 0)
					{
						os << "[";
					}
				}
				os << rhs.mArray[i];

				size = 1;
				for (unsigned int j = rhs.mDimension; j > 0; --j)
				{
					size *= rhs.mArraySize[j - 1];
					if (i % size == size - 1)
					{
						os << "]";
						if(i != rhs.mTotalSize-1)
							os << std::endl;
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
		unsigned int mDimension;
		unsigned int mTotalSize;
		std::unique_ptr<unsigned int[]> mArraySize;
		std::unique_ptr<T[]> mArray;
	};

	template<typename T>
	Ndarray<T>::Ndarray()
		: mDimension(0)
		, mTotalSize(0)
		, mArraySize(nullptr)
		, mArray(nullptr)
	{
	}

	template<typename T>
	inline Ndarray<T>::Ndarray(const std::initializer_list<int> arraySize, const T& value)
	{
		int i = 0;
		mDimension = arraySize.size();
		mArraySize = std::make_unique<unsigned int[]>(mDimension);
		mTotalSize = 1;
		for (auto a : arraySize)
		{
			mArraySize[i] = static_cast<unsigned int>(a);
			mTotalSize *= mArraySize[i];
			if (mArraySize[i++] == 0)
			{
				mDimension = 0;
				mTotalSize = 0;
				mArraySize = nullptr;
				mArray = nullptr;
				return;
			}
		}

		
		mArray = std::make_unique<T[]>(mTotalSize);
		for (unsigned int i = 0; i < mTotalSize; ++i)
		{
			mArray[i] = value;
		}
	}

	template<typename T>
	inline Ndarray<T>::Ndarray(const std::initializer_list<int> arraySize)
	{
		Ndarray(arraySize, 0);
	}

	template<typename T>
	inline Ndarray<T>::Ndarray(const unsigned int& dimension, const unsigned int& totalSize, const std::unique_ptr<unsigned int[]>& arraySize, const std::unique_ptr<T[]>& array)
		: mDimension(dimension)
		, mTotalSize(totalSize)
	{
		mArraySize = std::make_unique<unsigned int[]>(mDimension);
		for (unsigned int i = 0; i < mDimension; ++i)
		{
			mArraySize[i] = arraySize[i];
			if (mArraySize[i] == 0)
			{
				mDimension = 0;
				mTotalSize = 0;
				mArraySize = nullptr;
				mArray = nullptr;
				return;
			}
		}

		mArray = std::make_unique<T[]>(mTotalSize);
		for (unsigned int i = 0; i < mTotalSize; ++i)
		{
			mArray[i] = array[i];
		}
	}

	template<typename T>
	Ndarray<T>::Ndarray(const unsigned int& dimension, const unsigned int& totalSize, const unsigned int* arraySize, const unsigned int* array)
		: mDimension(dimension)
		, mTotalSize(totalSize)
	{
		mArraySize = std::make_unique<unsigned int[]>(mDimension);
		for (unsigned int i = 0; i < mDimension; ++i)
		{
			mArraySize[i] = arraySize[i];
		}

		mArray = std::make_unique<T[]>(mTotalSize);
		for (unsigned int i = 0; i < mTotalSize; ++i)
		{
			mArray[i] = array[i];
		}
	}

	template<typename T>
	Ndarray<T>::Ndarray(const Ndarray<T>& rhs)
		: mDimension(rhs.mDimension)
		, mTotalSize(rhs.mTotalSize)
	{
		mArraySize = std::make_unique<unsigned int[]>(mDimension);
		for (unsigned int i = 0; i < mDimension; ++i)
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
		: mDimension(rhs.mDimension)
		, mTotalSize(rhs.mTotalSize)
	{
		rhs.mDimension = 0u;
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
		mDimension = rhs.mDimension;
		mTotalSize = rhs.mTotalSize;
		mArraySize = std::make_unique<unsigned int[]>(mDimension);
		for (unsigned int i = 0; i < mDimension; ++i)
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
		mDimension = rhs.mDimension;
		rhs.mDimension = 0u;
		mTotalSize = rhs.mTotalSize;
		rhs.mTotalSize = 0u;
		mArraySize = std::move(rhs.mArraySize);
		mArray = std::move(rhs.mArray);

		return *this;
	}

	template<typename T>
	inline bool Ndarray<T>::operator==(const Ndarray<T>& rhs) const
	{
		if (mDimension != rhs.mDimension)
			return false;
		if (mTotalSize != rhs.mTotalSize)
			return false;
		for (unsigned int i = 0; i < mDimension; ++i)
			if (mArraySize[i] != rhs.mArraySize[i])
				return false;
		for (unsigned int i = 0; i < mTotalSize; ++i)
			if (mArray[i] != rhs.mArray[i])
				return false;

		return true;
	}

	template<typename T>
	inline bool Ndarray<T>::operator!=(const Ndarray<T>& rhs) const
	{
		return !(*this == rhs);
	}

	template<typename T>
	Ndarray<T> Ndarray<T>::operator+(const Ndarray<T>& rhs) const
	{
		if (mDimension != rhs.mDimension)
			return Ndarray<T>();
		if (mTotalSize != rhs.mTotalSize)
			return Ndarray<T>();
		for (unsigned int i = 0; i < mDimension; ++i)
			if (mArraySize[i] != rhs.mArraySize[i])
				return Ndarray<T>();

		std::unique_ptr<unsigned int[]> arraySize = std::make_unique<unsigned int[]>(mDimension);
		for (unsigned int i = 0; i < mDimension; ++i)
		{
			arraySize[i] = mArraySize[i];
		}

		std::unique_ptr<T[]> array = std::make_unique<T[]>(mTotalSize);
		for (unsigned int i = 0; i < mTotalSize; ++i)
		{
			array[i] = mArray[i] + rhs.mArray[i];
		}

		return Ndarray<T>(mDimension, mTotalSize, std::move(arraySize), std::move(array));
	}
	template<typename T>
	inline Ndarray<T> Ndarray<T>::operator+(const int& rhs) const
	{
		std::unique_ptr<unsigned int[]> arraySize = std::make_unique<unsigned int[]>(mDimension);
		for (unsigned int i = 0; i < mDimension; ++i)
		{
			arraySize[i] = mArraySize[i];
		}

		std::unique_ptr<T[]> array = std::make_unique<T[]>(mTotalSize);
		for (unsigned int i = 0; i < mTotalSize; ++i)
		{
			array[i] = mArray[i] + rhs;
		}

		return Ndarray<T>(mDimension, mTotalSize, std::move(arraySize), std::move(array));
	}
	template<typename T>
	inline Ndarray<T> Ndarray<T>::operator+(const float& rhs) const
	{
		std::unique_ptr<unsigned int[]> arraySize = std::make_unique<unsigned int[]>(mDimension);
		for (unsigned int i = 0; i < mDimension; ++i)
		{
			arraySize[i] = mArraySize[i];
		}

		std::unique_ptr<T[]> array = std::make_unique<T[]>(mTotalSize);
		for (unsigned int i = 0; i < mTotalSize; ++i)
		{
			array[i] = mArray[i] + rhs;
		}

		return Ndarray<T>(mDimension, mTotalSize, std::move(arraySize), std::move(array));
	}
	template<typename T>
	inline Ndarray<T> Ndarray<T>::operator*(const Ndarray<T>& rhs) const
	{
		if (mDimension != rhs.mDimension)
			return Ndarray<T>();
		if (mTotalSize != rhs.mTotalSize)
			return Ndarray<T>();
		for (unsigned int i = 0; i < mDimension; ++i)
			if (mArraySize[i] != rhs.mArraySize[i])
				return Ndarray<T>();

		std::unique_ptr<unsigned int[]> arraySize = std::make_unique<unsigned int[]>(mDimension);
		for (unsigned int i = 0; i < mDimension; ++i)
		{
			arraySize[i] = mArraySize[i];
		}

		std::unique_ptr<T[]> array = std::make_unique<T[]>(mTotalSize);
		for (unsigned int i = 0; i < mTotalSize; ++i)
		{
			array[i] = mArray[i] * rhs.mArray[i];
		}

		return Ndarray<T>(mDimension, mTotalSize, std::move(arraySize), std::move(array));
	}

	template<typename T>
	inline Ndarray<T> Ndarray<T>::operator*(const int& rhs) const
	{
		std::unique_ptr<unsigned int[]> arraySize = std::make_unique<unsigned int[]>(mDimension);
		for (unsigned int i = 0; i < mDimension; ++i)
		{
			arraySize[i] = mArraySize[i];
		}

		std::unique_ptr<T[]> array = std::make_unique<T[]>(mTotalSize);
		for (unsigned int i = 0; i < mTotalSize; ++i)
		{
			array[i] = mArray[i] * rhs;
		}

		return Ndarray<T>(mDimension, mTotalSize, std::move(arraySize), std::move(array));
	}

	template<typename T>
	inline Ndarray<T> Ndarray<T>::operator*(const float& rhs) const
	{
		std::unique_ptr<unsigned int[]> arraySize = std::make_unique<unsigned int[]>(mDimension);
		for (unsigned int i = 0; i < mDimension; ++i)
		{
			arraySize[i] = mArraySize[i];
		}

		std::unique_ptr<T[]> array = std::make_unique<T[]>(mTotalSize);
		for (unsigned int i = 0; i < mTotalSize; ++i)
		{
			array[i] = mArray[i] * rhs;
		}

		return Ndarray<T>(mDimension, mTotalSize, std::move(arraySize), std::move(array));
	}


	template<typename T>
	void Ndarray<T>::Reshape(const unsigned int* arraySize)
	{
		unsigned int dimension = static_cast<unsigned int>(sizeof(arraySize) / sizeof(arraySize[0]));

		unsigned int totalSize = 1;
		std::unique_ptr<unsigned int[]> newArraySize = std::make_unique<unsigned int[]>(dimension);
		for (unsigned int i = 0; i < dimension; ++i)
		{
			newArraySize[i] = arraySize[i];
			totalSize *= arraySize[i];
		}

		if (totalSize != mTotalSize)
			return;

		mDimension = dimension;
		mArraySize = std::move(newArraySize);
	}
}