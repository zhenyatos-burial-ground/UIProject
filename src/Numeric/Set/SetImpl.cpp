#include "ISet.h"
#include <vector>

namespace
{
	class SetImpl : public ISet
	{
	private:
		size_t dim_;
		std::vector<IVector*> data_;
		ILogger* logger_;
		
	public:
		SetImpl();
		~SetImpl() override;

		RESULT_CODE insert(const IVector* pVector, IVector::NORM norm, double tolerance) override;
		RESULT_CODE get(IVector*& pVector, size_t index) const override; 
		RESULT_CODE get(IVector*& pVector, IVector const* pSample, IVector::NORM norm, double tolerance) const override;
		size_t getDim() const override;
		size_t getSize() const override;
	};

	SetImpl::SetImpl()
		: dim_(0)
	{
		logger_ = ILogger::createLogger(this);
	}

	SetImpl::~SetImpl()
	{
		logger_->destroyLogger(this);
	}
	
	RESULT_CODE SetImpl::insert(const IVector* pVector, IVector::NORM norm, double tolerance)
	{
		if (pVector == nullptr || tolerance < 0)
			return RESULT_CODE::WRONG_ARGUMENT;

		if (data_.empty()) {
			IVector* clone = pVector->clone();
			if (clone == nullptr)
				return RESULT_CODE::OUT_OF_MEMORY;
			dim_ = pVector->getDim();
			data_.push_back(clone);
			return RESULT_CODE::SUCCESS;
		}

		if (dim_ != pVector->getDim())
			return RESULT_CODE::WRONG_DIM;

		for (IVector* vec : data_)
		{
			IVector* diff = IVector::sub(vec, pVector, logger_);
			if (diff == nullptr)
				return RESULT_CODE::CALCULATION_ERROR;
			if (diff->norm(norm) < tolerance)
			{
				delete diff;
				return RESULT_CODE::SUCCESS;
			}
			delete diff;
		}
		
		IVector* clone = pVector->clone();
		if (clone == nullptr)
			return RESULT_CODE::OUT_OF_MEMORY;
		data_.push_back(clone);

		return RESULT_CODE::SUCCESS;
	}

	RESULT_CODE SetImpl::get(IVector*& pVector, size_t index) const
	{
		size_t maxIndex = data_.size() - 1;
		if (index > maxIndex)
		{
			pVector = nullptr;
			return RESULT_CODE::OUT_OF_BOUNDS;
		}

		pVector = data_[index]->clone();
		if (pVector == nullptr)
			return RESULT_CODE::OUT_OF_MEMORY;
		return RESULT_CODE::SUCCESS;
	}

	RESULT_CODE SetImpl::get(IVector *& pVector, IVector const* pSample, IVector::NORM norm, double tolerance) const
	{
		if (pSample == nullptr || tolerance < 0)
		{
			pVector == nullptr;
			return RESULT_CODE::WRONG_ARGUMENT;
		}

		if (pSample->getDim() != dim_)
		{
			pVector == nullptr;
			return RESULT_CODE::WRONG_DIM;
		}

		for (IVector* vec : data_)
		{
			IVector* diff = IVector::sub(vec, pSample, logger_);
			if (diff == nullptr)
				return RESULT_CODE::CALCULATION_ERROR;
			if (diff->norm(norm) < tolerance)
			{
				delete diff;
				pVector = vec->clone();
				if (pVector == nullptr)
					return RESULT_CODE::OUT_OF_MEMORY;
				return RESULT_CODE::SUCCESS;
			}
			delete diff;
		}

		return RESULT_CODE::SUCCESS;
	}

	size_t SetImpl::getDim() const
	{
		return dim_;
	}

	size_t SetImpl::getSize() const
	{
		return data_.size();
	}
}