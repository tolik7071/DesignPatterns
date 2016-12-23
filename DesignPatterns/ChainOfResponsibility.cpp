//
//  ChainOfResponsibility.cpp
//  DesignPatterns
//
//  Created by Anatoliy Goodz on 12/23/16.
//  Copyright © 2016 Anatoliy Goodz. All rights reserved.
//

#include "ChainOfResponsibility.hpp"
#include "common.h"
#include <algorithm>

using namespace ChainOfResponsibility;

Control::Control(const char *help/* = nullptr*/)
{
    if (help != nullptr)
    {
        mHelp = help;
    }
}

Control::~Control()
{
    LOG_FUNCTION();
}

bool Control::hasHelp() const
{
    return (mHelp.data() != nullptr && mHelp.length() > 0);
}

const char* Control::help() const
{
    return mHelp.data();
}

Button::Button(const char *help/* = nullptr*/)
    : Control(help)
{
}

void Button::draw()
{
    LOG_FUNCTION();
}

Slider::Slider(const char *help/* = nullptr*/)
    : Control(help)
{
}

void Slider::draw()
{
    LOG_FUNCTION();
}

void Window::createControls()
{
    for (int i = 1; i <= 10; i++)
    {
        std::shared_ptr<Control> control;
        const char * help = (i % 5 == 0) ? "This is a help!" : nullptr;
        
        if (i % 2 != 0)
        {
            control.reset(new Button(help));
        }
        else
        {
            control.reset(new Slider(help));
        }
        
        mControls.push_back(control);
    }
}

const char* Window::findHelp()
{
    const char* result = nullptr;
    
    TArrayOfControls::iterator it = mControls.begin();
    for (; it != mControls.end(); ++it)
    {
        if ((*it)->hasHelp())
        {
            result = (*it)->help();
            break;
        }
    }
    
    return result;
}
