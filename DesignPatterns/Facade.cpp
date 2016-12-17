//
//  Facade.cpp
//  DesignPatterns
//
//  Created by Anatoliy Goodz on 12/12/16.
//  Copyright © 2016 Anatoliy Goodz. All rights reserved.
//

#if defined(_MSC_VER)
#include "stdafx.h"
#endif // _MSC_VER
#include "Facade.hpp"
#include "common.h"
#include <algorithm>

using namespace Facade;

VisualElement::~VisualElement()
{
    LOG_FUNCTION();
}

void Background::Draw()
{
    LOG_FUNCTION();
}

void Menu::Draw()
{
    LOG_FUNCTION();
}

void Doc::Draw()
{
    LOG_FUNCTION();
}

void Desktop::create()
{
    mElements.push_back(std::shared_ptr<VisualElement>(new Background()));
    mElements.push_back(std::shared_ptr<VisualElement>(new Menu()));
    mElements.push_back(std::shared_ptr<VisualElement>(new Doc()));
}

void Desktop::Draw()
{
    std::for_each(mElements.begin(), mElements.end(),
        [](std::shared_ptr<VisualElement> element)
        {
            element->Draw();
        }
    );
}
