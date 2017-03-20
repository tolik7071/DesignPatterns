//
//  TemplateMethod.cpp
//  DesignPatterns
//
//  Created by tolik7071 on 3/16/17.
//  Copyright © 2017 Anatoliy Goodz. All rights reserved.
//

#if defined(_MSC_VER)
#include "stdafx.h"
#endif // _MSC_VER
#include "TemplateMethod.hpp"
#include "common.h"

void TemplateMethod::CaffeinBeverage::prepareRecipe()
{
    LOG_FUNCTION();
    
    boilWater();
    brew();
    pourInCup();
    addCondiments();
}

void TemplateMethod::CaffeinBeverage::boilWater()
{
    LOG_FUNCTION();
}

void TemplateMethod::CaffeinBeverage::pourInCup()
{
    LOG_FUNCTION();
}

void TemplateMethod::CaffeinBeverage::brew()
{
    LOG_FUNCTION();
}

void TemplateMethod::CaffeinBeverage::addCondiments()
{
    LOG_FUNCTION();
}

void TemplateMethod::Tea::brew()
{
    LOG_FUNCTION();
}

void TemplateMethod::Tea::addCondiments()
{
    LOG_FUNCTION();
}

void TemplateMethod::Coffee::brew()
{
    LOG_FUNCTION();
}

void TemplateMethod::Coffee::addCondiments()
{
    LOG_FUNCTION();
}
