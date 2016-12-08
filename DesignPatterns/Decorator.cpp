//
//  Decorator.cpp
//  DesignPatterns
//
//  Created by Anatoliy Goodz on 12/8/16.
//  Copyright © 2016 Anatoliy Goodz. All rights reserved.
//

#include "Decorator.hpp"
#include "common.h"

using namespace Decorator;

TextView::~TextView()
{
    LOG_FUNCTION();
}

TextViewDecorator::~TextViewDecorator()
{
    LOG_FUNCTION();
}

void TextView::draw()
{
    LOG_FUNCTION();
}

void ScrollDecorator::doScroll()
{
    LOG_FUNCTION();
}

void ScrollDecorator::draw()
{
    LOG_FUNCTION();
    
    doScroll();
    
    if (mOther.get() != nullptr)
    {
        mOther->draw();
    }
}

void BorderDecorator::drawBorder()
{
    LOG_FUNCTION();
}

void BorderDecorator::draw()
{
    LOG_FUNCTION();
    
    if (mOther.get() != nullptr)
    {
        mOther->draw();
    }
    
    drawBorder();
}
