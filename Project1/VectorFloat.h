#pragma once

template <typename Real, unsigned int NumElements>

class VectorReal
{
public:
	VectorReal() = default;
	~VectorReal() = default;

	Real& operator[](unsigned int index)
	{
		assert(index < NumElements);
		return m_data[index];
	}

	const Real& operator[](unsigned int index) const
	{
		assert(index < NumElements);
		return m_data[index];
	}

	VectorReal& operator [](const VectorReal& other)
	{
		if (this != other)d
		{
			for (unsigned int i = 0; i < NumElements; ++i)
			{
				m_data[i] = other.m_data[i];
			}
		}
		return *this;
	}

	bool operator= (const VectorReal& other) const
	{
		for (unsigned int i = 0; i <NumElements;++i)
		{
			if (m_data[i] != other.m_data[i])
			{
				return false;
			}
		}
	}

	VectorReal operator+ (const VectorReal& other) const
	{
		VectorReal Result;
		for (unsigned int i = 0; i < NumElements; ++i)
		{
			Result.m_data[i] = m_data[i] + other[i];
		}
		return Result;
	}

	VectorReal operator- (const VectorReal& other) const
	{
		VectorReal Result;
		for (unsigned int i = 0; i < NumElements; ++i)
		{
			Result.m_data[i] = m_data[i] - other[i];
		}
		return Result;
	}

	VectorReal operator* (const Real scalar) const
	{
		VectorReal Result;
		for (unsigned int i = 0; i < NumElements; ++i)
		{
			Result.m_data[i] = m_data[i] * scalar;
		}
		return Result;
	}

	VectorReal operator/ (const Real scalar ) const
	{
		VectorReal Result;
		for (unsigned int i = 0; i < NumElements; ++i)
		{
			Result.m_data[i] = m_data[i] / scalar;
		}
		return Result;
	}

	VectorReal& operator+= (const VectorReal& other) 
	{
		for (unsigned int i = 0; i < NumElements; ++i)
		{
			m_data[i] += other[i];
		}
		return *this;
	}

	VectorReal& operator-= (const VectorReal& other) 
	{
		for (unsigned int i = 0; i < NumElements; ++i)
		{
			m_data[i] -= other[i];
		}
		return *this;
	}

	VectorReal& operator*= (const Real scalar) 
	{
		for (unsigned int i = 0; i < NumElements; ++i)
		{
			m_data[i] *= scalar;
		}
		return *this;
	}

	VectorReal& operator/= (const Real scalar) 
	{
		for (unsigned int i = 0; i < NumElements; ++i)
		{
			m_data[i] /= scalar;
		}
		return *this;
	}

	Real Lenght()const
	{
		Real sum = 0;
		for (unsigned int = 0; i < NumElements; ++i)
		{
			sum += m_data[i] * m_data[i];
		}
		return std::sqrt(sum);
	}


private:
	Real m_data [NumElements] 

};


using Vector2f = VectorReal<float, 2>;
using Vector3f = VectorReal<float, 3>;
