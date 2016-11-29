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

namespace Bridge
{
/*
    typedef int TError;
    typedef unsigned char TByte;
    
    class FileSystemImpl
    {
        public:
        
        virtual TError writeHeader(...) = 0;
        virtual TError write(const TByte* bytes) = 0;
        virtual TError read(TByte* bytes) = 0;
    };
    
    class FileSystemItem
    {
        public:
        
        enum ItemType
        {
            kFolder,
            kFile
        };
        
        FileSystemItem(const char * name, ItemType type);
        virtual ~FileSystemItem();
        
        ItemType type() const;
        const char * name() const;
        
        bool addChild(FileSystemItem* child);
        bool removeChild(FileSystemItem* child);
        
        size_t numberOfChildren() const;
        std::shared_ptr<FileSystemItem* > childAtIndex(size_t index);
        
        static FileSystemItem* CreateRoot(FileSystemImpl* impl);
        
        protected:
        
        FileSystemItem(FileSystemImpl* impl);
        
        typedef std::vector<std::shared_ptr<FileSystemItem* > > TArray;
        TArray mChildren;
        
        std::string mName;
    };
*/
    
    class IWindow
    {
        public:
        
        virtual void Draw() = 0;
    };
    
    class IWindowManager
    {
        public:
        
        virtual void ProcessWindows() = 0;
    };
    
    /* ***** ***** ***** ***** ***** ***** */
    
    class WindowManagerBase : public IWindowManager
    {
        public:
        
        virtual void createWindow(const char * title) = 0;
        virtual void ProcessWindows() = 0;
        
        protected:
        
        void addWindow(std::unique_ptr<IWindow> window);
        
        typedef std::vector<std::unique_ptr<IWindow> > TArray;
        TArray mWindows;
    };
    
    class WindowManagerWinOS : public WindowManagerBase
    {
        public:
        
        virtual void createWindow(const char * title);
        virtual void ProcessWindows();
    };
    
    class WindowManagerUbuntuOS : public WindowManagerBase
    {
        public:
        
        virtual void createWindow(const char * title);
        virtual void ProcessWindows();
    };
    
    /* ***** ***** ***** ***** ***** ***** */
    
    class GraphicSystem
    {
        public:
        
        GraphicSystem(std::unique_ptr<WindowManagerBase> manager);
        
        std::unique_ptr<WindowManagerBase> mWindowsManager;
    };
}

#endif /* Bridge_hpp */
