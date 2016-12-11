//
//  Bridge.hpp
//  DesignPatterns
//
//  Created by Anatoliy Goodz on 11/26/16.
//  Copyright © 2016 Anatoliy Goodz. All rights reserved.
//

#ifndef Bridge_hpp
#define Bridge_hpp

#include <vector>
#include <string>
#include <memory>
#include "common.h"

namespace Bridge
{
    class IWindow
    {
        public:
        
        virtual void Draw() = 0;
        
        virtual ~IWindow()
        {
            LOG_FUNCTION();
        }
    };
    
    class IWindowManager
    {
        public:
        
        virtual std::shared_ptr<IWindow> createWindow(const char * title) = 0;
        virtual void ProcessWindows() = 0;
        
        virtual ~IWindowManager()
        {
            LOG_FUNCTION();
        }
    };
    
    /* ***** ***** ***** ***** ***** ***** */
    
    class BaseManager : public IWindowManager
    {
        public:
        
        void addWindow(std::shared_ptr<IWindow> window);
        
        protected:
        
        typedef std::vector<std::shared_ptr<IWindow> > TArray;
        TArray mWindows;
    };
    
    class UbuntuManager : public BaseManager
    {
        public:
        
        virtual std::shared_ptr<IWindow> createWindow(const char * title);
        virtual void ProcessWindows();
    };
    
    class WindowsManager : public BaseManager
    {
        public:
        
        virtual std::shared_ptr<IWindow> createWindow(const char * title);
        virtual void ProcessWindows();
    };
    
    /* ***** ***** ***** ***** ***** ***** */
    
    class GraphicSystem
    {
        public:
        
        GraphicSystem(std::unique_ptr<IWindowManager> manager)
        {
            mWindowsManager = std::move(manager);
        }
        
        std::unique_ptr<IWindowManager> mWindowsManager;
    };
}

#endif /* Bridge_hpp */
