//
//  Singleton.cpp
//  DesignPatterns
//
//  Created by Anatoliy Goodz on 11/19/16.
//  Copyright © 2016 Anatoliy Goodz. All rights reserved.
//

#include "Singleton.hpp"
#include <cstdlib>
#include "common.h"

using namespace Singleton;

unsigned int Display::width() const
{
    return 1920U;
}

unsigned int Display::height() const
{
    return 1080U;
}

static Singleton::Display* gInstance = nullptr;

/*static */void Singleton::Display::CleanUp()
{
    delete gInstance;
    gInstance = NULL;
    LOG_FUNCTION();
}

/*static */const Singleton::Display& Singleton::Display::GetSharedInstance()
{
    if (gInstance == nullptr)
    {
        gInstance = new Display();
        std::atexit(CleanUp);
    }
    
    return *gInstance;
}
