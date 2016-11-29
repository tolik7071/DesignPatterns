//
//  Bridge.cpp
//  DesignPatterns
//
//  Created by Anatoliy Goodz on 11/26/16.
//  Copyright © 2016 Anatoliy Goodz. All rights reserved.
//

#include "Bridge.hpp"
#include "common.h"

using namespace Bridge;

void WindowManagerBase::addWindow(std::unique_ptr<IWindow> window)
{
    mWindows.push_back(window);
}

class WindowWinOS : public IWindow
{
    public:
    
    WindowWinOS(const char * name)
        : mName(name)
    {
        
    }
    
    virtual ~WindowWinOS()
    {
        LOG_FUNCTION();
    }
    
    virtual void Draw()
    {
        std::cout << __FUNCTION__ << mName << std::endl;
    }
    
    std::string mName;
};

class WindowUbuntuOS : public IWindow
{
public:
    
    WindowUbuntuOS(const char * name)
        : mName(name)
    {
        
    }
    
    virtual ~WindowUbuntuOS()
    {
        LOG_FUNCTION();
    }
    
    virtual void Draw()
    {
        std::cout << __FUNCTION__ << mName << std::endl;
    }
    
    std::string mName;
};

void WindowManagerWinOS::createWindow(const char *title)
{
    addWindow(std::unique_ptr<IWindow>(new WindowWinOS(title)));
}

void WindowManagerUbuntuOS::createWindow(const char *title)
{
    addWindow(std::unique_ptr<IWindow>(new WindowUbuntuOS(title)));
}

void WindowManagerWinOS::ProcessWindows()
{
    std::for_each(mWindows.begin(), mWindows.end(), [](IWindow* window) { window->Draw(); } );
}

void WindowManagerUbuntuOS::ProcessWindows()
{
    std::for_each(mWindows.begin(), mWindows.end(), [](IWindow* window) { window->Draw(); } );
}

