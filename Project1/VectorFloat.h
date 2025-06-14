//#pragma once
//#include <cmath>
//#include <cassert>
//#include <vector>
//
//template <typename Real, unsigned int NumElements>
//
//class VectorReal
//{
//public:
//
//	VectorReal() = default;
//
//	VectorReal(const VectorReal& other)
//	{
//		if (this != &other)
//		{
//			for (unsigned int i = 0; i < NumElements; ++i)
//			{
//				m_data[i] = other.m_data[i];
//			}
//		}
//	}
//
//	VectorReal(Real x, Real y)
//	{
//		static_assert(NumElements == 2, "This constructor is only valid for 2D vectors.");
//		m_data[0] = x;
//		m_data[1] = y;
//	}
//
//	~VectorReal() = default;
//
//	VectorReal& operator=(const VectorReal& other)
//	{
//		if (this != &other)
//		{
//			for (unsigned int i = 0; i < NumElements; ++i)
//			{
//				m_data[i] = other.m_data[i];
//			}
//		}
//		return *this;
//	}
//
//	Real& operator[](unsigned int index)
//	{
//		assert(index < NumElements);
//		return m_data[index];
//	}
//
//	const Real& operator[](unsigned int index) const
//	{
//		assert(index < NumElements);
//		return m_data[index];
//	}
//
//	VectorReal& operator [](const VectorReal& other)
//	{
//		if (this != other)
//		{
//			for (unsigned int i = 0; i < NumElements; ++i)
//			{
//				m_data[i] = other.m_data[i];
//			}
//		}
//		return *this;
//	}
//
//	bool operator== (const VectorReal& other) const
//	{
//		for (unsigned int i = 0; i <NumElements;++i)
//		{
//			if (m_data[i] != other.m_data[i])
//			{
//				return false;
//			}
//		}
//		return true;
//	}
//
//	bool operator!= (const VectorReal& other) const
//	{
//		return !(*this == other);
//	}
//
//	VectorReal operator+ (const VectorReal& other) const
//	{
//		VectorReal Result;
//		for (unsigned int i = 0; i < NumElements; ++i)
//		{
//			Result.m_data[i] = m_data[i] + other[i];
//		}
//		return Result;
//	}
//
//	VectorReal operator- (const VectorReal& other) const
//	{
//		VectorReal Result;
//		for (unsigned int i = 0; i < NumElements; ++i)
//		{
//			Result.m_data[i] = m_data[i] - other[i];
//		}
//		return Result;
//	}
//
//	VectorReal operator* (const Real scalar) const
//	{
//		VectorReal Result;
//		for (unsigned int i = 0; i < NumElements; ++i)
//		{
//			Result.m_data[i] = m_data[i] * scalar;
//		}
//		return Result;
//	}
//
//	VectorReal operator/ (const Real scalar ) const
//	{
//		VectorReal Result;
//		for (unsigned int i = 0; i < NumElements; ++i)
//		{
//			Result.m_data[i] = m_data[i] / scalar;
//		}
//		return Result;
//	}
//
//	VectorReal& operator+= (const VectorReal& other) 
//	{
//		for (unsigned int i = 0; i < NumElements; ++i)
//		{
//			m_data[i] += other[i];
//		}
//		return *this;
//	}
//
//	VectorReal& operator-= (const VectorReal& other) 
//	{
//		for (unsigned int i = 0; i < NumElements; ++i)
//		{
//			m_data[i] -= other[i];
//		}
//		return *this;
//	}
//
//	VectorReal& operator*= (const Real scalar) 
//	{
//		for (unsigned int i = 0; i < NumElements; ++i)
//		{
//			m_data[i] *= scalar;
//		}
//		return *this;
//	}
//
//	VectorReal& operator/= (const Real scalar) 
//	{
//		for (unsigned int i = 0; i < NumElements; ++i)
//		{
//			m_data[i] /= scalar;
//		}
//		return *this;
//	}
//
//
//	Real Length() const
//	{
//		Real sum = 0;
//
//		for (unsigned int i = 0; i < NumElements; ++i)
//		{
//			sum += m_data[i] * m_data[i];
//		}
//		return std::sqrt(sum);
//	}
//
//	void Normalize()
//	{
//		float length = Length();
//		if (length > 0.0f)
//		{
//			for (unsigned int i = 0; i < NumElements; ++i)
//			{
//				m_data[i] /= length;
//			}
//			m_length = length;
//		}
//		else
//		{
//			m_length = 0.0f;
//		}
//	}
//
//	VectorReal GetNormalized() const
//	{
//		VectorReal result = *this;
//		result.Normalize();
//		return result;
//	}
//
//private:
//	Real m_data[NumElements];
//	float m_length = 0.0f;
//};
//
//
//using Vector2f = VectorReal<float, 2>;
//using Vector3f = VectorReal<float, 3>;
