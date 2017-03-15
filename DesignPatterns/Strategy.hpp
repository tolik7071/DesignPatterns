//
//  Strategy.cpp
//  DesignPatterns
//
//  Created by tolik7071 on 3/13/17.
//  Copyright © 2017 Anatoliy Goodz. All rights reserved.
//

#pragma once

#include <memory>

namespace Strategy
{
	template <typename T>
	struct BinaryOperation
	{
		virtual T operator() (const T& first, const T& second)
		{
			return T();
		}
	};

	template <typename T>
	struct OperationPlus : public BinaryOperation<T>
	{
		virtual T operator() (const T& first, const T& second)
		{
			return (first + second);
		}
	};

	template <typename T>
	struct OperationMinus : public BinaryOperation<T>
	{
		virtual T operator() (const T& first, const T& second)
		{
			return (first - second);
		}
	};

	template <typename T>
	struct Data
	{
		T first;
		T second;

		Data(const T& first, const T& second)
		{
			this->first = first;
			this->second = second;
		}

		typedef typename T Result;

		std::shared_ptr<BinaryOperation<T> > operation;

		T calculate() const
		{
			T result = T();

			if (operation.get() != nullptr)
			{
				result = operation->operator()(first, second);
			}

			return result;
		}
	};
}
