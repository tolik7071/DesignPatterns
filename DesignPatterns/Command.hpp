//
//  Command.hpp
//  DesignPatterns
//
//  Created by Anatoliy Goodz on 12/24/16.
//  Copyright © 2016 Anatoliy Goodz. All rights reserved.
//

#ifndef Command_hpp
#define Command_hpp

#include <memory>
#include <string>
#include <vector>

namespace Command
{
    class Document;
    
    class ICommand
    {
        public:
        
        virtual void execute() = 0;
    };
    
    class BaseCommand : public ICommand
    {
        public:
        
        BaseCommand(std::shared_ptr<Document> document);
        virtual ~BaseCommand();
        
        std::shared_ptr<Document> document();
        
        private:
        
        std::shared_ptr<Document> mDocument;
    };
    
    class CreateCommand : public ICommand
    {
        public:
        
        virtual void execute();
    };
    
    class PrintCommand : public BaseCommand
    {
        public:
        
        PrintCommand(std::shared_ptr<Document> document);
        
        virtual void execute();
    };
    
    class CloseCommand : public BaseCommand
    {
        public:
        
        CloseCommand(std::shared_ptr<Document> document);
        
        virtual void execute();
    };
    
    class ExitCommand : public ICommand
    {
        public:
        
        virtual void execute();
    };
    
    class Document
    {
        public:
        
        Document(std::string name);
        ~Document();
        
        std::string name() const;
        
        void print();
        void close();
        
        private:
        
        std::string mName;
    };
    
    enum class MenuIDs
    {
        kCreateDocument,
        kPrintDocument,
        kCloseDocument,
        kSeparator,
        kExit
    };
    
    class MenuItem
    {
        public:
        
        MenuItem(std::string title, MenuIDs id);
        virtual ~MenuItem();
        
        std::string title() const;
        
        void select() const;
        
        private:
        
        std::string mTitle;
        MenuIDs mId;
    };
    
    class Application
    {
        public:
        
        static Application& GetSharedInstance();
        
        std::shared_ptr<Document> createDocWithName(const std::string& name);
        std::shared_ptr<Document> documentWithName(const std::string& name);
        
        std::shared_ptr<Document> currentDocument() const;
        void setCurrentDocument(std::shared_ptr<Document> document);
        
        const std::vector<std::shared_ptr<MenuItem> > menu() const;
        
        void exit();
        
        private:
        
        /*
         
         'New document'
         'Print document'
         'Close document'
         ---
         'Quit'
         
         */
        void createMenu();
        
        void invoke(std::shared_ptr<ICommand> command);
        
        static void CleanUp();
        static Application *mInstance;
        
        typedef std::vector<std::shared_ptr<Document> > TArrayOfDocs;
        TArrayOfDocs mDocuments;
        
        std::shared_ptr<Document> mCurrentDoc;
                
        typedef std::vector<std::shared_ptr<MenuItem> > TArrayOfMenuItems;
        TArrayOfMenuItems mMenuItems;
    };
}

#endif /* Command_hpp */
