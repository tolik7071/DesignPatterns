//
//  Singleton.cpp
//  DesignPatterns
//
//  Created by Anatoliy Goodz on 11/19/16.
//  Copyright © 2016 Anatoliy Goodz. All rights reserved.
//

#include "Singleton.hpp"

using namespace Singleton;

unsigned int Display::width() const
{
    return 1920U;
}

unsigned int Display::height() const
{
    return 1080U;
}

/*static */const Singleton::Display& Singleton::Display::GetSharedInstance()
{
    static Singleton::Display* instance = nullptr;
    
    if (instance == nullptr)
    {
        instance = new Display();
    }
    
    return *instance;
}