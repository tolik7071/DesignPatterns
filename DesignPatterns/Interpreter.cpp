//
//  Interpreter.cpp
//  DesignPatterns
//
//  Created by Anatoliy Goodz on 1/23/17.
//  Copyright © 2017 Anatoliy Goodz. All rights reserved.
//

#if defined(_MSC_VER)
#include "stdafx.h"
#endif // _MSC_VER
#include "Interpreter.hpp"
#include "common.h"

using namespace Interpreter;

Expression::~Expression()
{
    LOG_FUNCTION();
}

TerminalExpression::TerminalExpression(const std::string& data)
    : mData(data)
{
    LOG_FUNCTION();
}

/*virtual */bool TerminalExpression::interpret(const std::string& context)
{
    bool result = context.find(mData) != std::string::npos;
    return result;
}

BinExpression::BinExpression(std::shared_ptr<Expression> left, std::shared_ptr<Expression> right)
    : mLeft(left)
    , mRight(right)
{
}

OrExpression::OrExpression(std::shared_ptr<Expression> left, std::shared_ptr<Expression> right)
    : BinExpression(left, right)
{
    LOG_FUNCTION();
}

/*virtual */bool OrExpression::interpret(const std::string &context)
{
    bool result = mLeft->interpret(context) || mRight->interpret(context);
    return result;
}

AndExpression::AndExpression(std::shared_ptr<Expression> left, std::shared_ptr<Expression> right)
    : BinExpression(left, right)
{
    LOG_FUNCTION();
}

/*virtual */bool AndExpression::interpret(const std::string &context)
{
    bool result = mLeft->interpret(context) && mRight->interpret(context);
    return result;
}
