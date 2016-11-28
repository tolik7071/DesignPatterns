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
}

#endif /* Bridge_hpp */
