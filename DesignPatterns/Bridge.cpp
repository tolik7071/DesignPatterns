//
//  Bridge.cpp
//  DesignPatterns
//
//  Created by Anatoliy Goodz on 11/26/16.
//  Copyright © 2016 Anatoliy Goodz. All rights reserved.
//

#if defined(_MSC_VER)
#include "stdafx.h"
#endif // _MSC_VER
#include "Bridge.hpp"
#include <algorithm>

namespace Bridge
{
    class WindowOnUbuntu : public IWindow
    {
        public:
        
        WindowOnUbuntu(const char * title)
            : mTitle(title)
        {
            LOG_FUNCTION();
        }
        
        virtual void Draw()
        {
            LOG_FUNCTION();
        }
        
        std::string mTitle;
    };
}

namespace Bridge
{
    class WindowOnWindows : public IWindow
    {
    public:
        
        WindowOnWindows(const char * title)
        : mTitle(title)
        {
            LOG_FUNCTION();
        }
        
        virtual void Draw()
        {
            LOG_FUNCTION();
        }
        
        std::string mTitle;
    };
}

using namespace Bridge;

void BaseManager::addWindow(std::shared_ptr<IWindow> window)
{
    mWindows.push_back(window);
}

std::shared_ptr<IWindow> UbuntuManager::createWindow(const char * title)
{
    std::shared_ptr<IWindow> result(new WindowOnUbuntu(title));
    addWindow(result);
    
    return result;
}

void UbuntuManager::ProcessWindows()
{
    std::for_each(mWindows.begin(), mWindows.end(),
        [](std::shared_ptr<IWindow> window)
        {
            window->Draw();
        }
    );
}

std::shared_ptr<IWindow> WindowsManager::createWindow(const char * title)
{
    std::shared_ptr<IWindow> result(new WindowOnWindows(title));
    addWindow(result);
    
    return result;
}

void WindowsManager::ProcessWindows()
{
    std::for_each(mWindows.begin(), mWindows.end(),
        [](std::shared_ptr<IWindow> window)
        {
            window->Draw();
        }
    );
}