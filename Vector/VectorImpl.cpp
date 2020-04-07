#include "IVector.h"
#include <cmath>

namespace
{
	class VectorImpl : public IVector
	{
	private:
		size_t dim_ = 0;
		double* data_ = nullptr;
	public:
		VectorImpl(size_t dim, double* data);
		~VectorImpl() override;

		IVector* clone() const override;
		double getCoord(size_t index) const override;
		RESULT_CODE setCoord(size_t index, double value) override;
		double norm(NORM norm) const override;
		size_t getDim() const override;
	};

	VectorImpl::VectorImpl(size_t dim, double* data)
		: dim_(dim), data_(data)
	{}

	VectorImpl::~VectorImpl()
	{
		if (data_ != nullptr)
		{
			delete[] data_;
			data_ = nullptr;
		}
	}

	IVector* VectorImpl::clone() const
	{
		double* data = new (std::nothrow)double[dim_];
		if (data == nullptr)
			return nullptr;
		
		for (int i = 0; i < dim_; i++)
			data[i] = data_[i];

		return new (std::nothrow)VectorImpl(dim_, data);
	}

	size_t VectorImpl::getDim() const
	{
		return dim_;
	}

	double VectorImpl::getCoord(size_t index) const
	{
		if (index >= dim_ || data_ == nullptr)
			return 0.0;
		
		return data_[index];
	}

	RESULT_CODE VectorImpl::setCoord(size_t index, double value)
	{
		if (data_ == nullptr)
			return RESULT_CODE::OUT_OF_MEMORY;

		if (index >= dim_)
			return RESULT_CODE::OUT_OF_BOUNDS;

		data_[index] = value;

		return RESULT_CODE::SUCCESS;
	}

	double VectorImpl::norm(NORM norm) const
	{
		double value = 0;

		switch (norm)
		{
		case NORM::NORM_1:
			for (int i = 0; i < dim_; i++)
				value += fabs(data_[i]);
			break;

		case NORM::NORM_2:
			for (int i = 0; i < dim_; i++)
				value += fabs(data_[i] * data_[i]);
			value = sqrt(value);
			break;

		case NORM::NORM_INF:
			for (int i = 0; i < dim_; i++)
				if (value < fabs(data_[i]))
					value = fabs(data_[i]);
			break;

		default:
			break;
		}

		return value;
	}
}

IVector::~IVector()
{}