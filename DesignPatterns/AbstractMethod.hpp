//
//  AbstractMethod.hpp
//  DesignPatterns
//
//  Created by Anatoliy Goodz on 11/12/16.
//  Copyright © 2016 Anatoliy Goodz. All rights reserved.
//

#ifndef AbstractMethod_hpp
#define AbstractMethod_hpp

#include <stdio.h>
#include <string>
#include <vector>

namespace AbstractMethod
{
    class Document
    {
        public:
        
        Document(const char *name);
        virtual ~Document();
        
        std::string& name();
        
        public:
        
        virtual void Open() = 0;
        virtual void Close() = 0;
        
        private:
        
        std::string mName;
    };
    
    class Application
    {
        public:
        
        virtual ~Application();
        
        public:
        
        virtual Document* CreateDocument(const char *documentName) = 0;
        
        public:
        
        Document* GetDocument(std::string name);
        Document* GetDocument(size_t index);
        
        protected:
        
        typedef std::vector<Document *> TDocumentArray;
        TDocumentArray mDocuments;
    };
 
    class MyDocument : public Document
    {
        public:
        
        MyDocument(const char *name);
        virtual ~MyDocument();
        
        public:
        
        virtual void Open();
        virtual void Close();
    };
    
    class MyApplication : public Application
    {
        public:
        
        virtual Document* CreateDocument(const char *documentName);
    };
}

#endif /* AbstractMethod_hpp */
