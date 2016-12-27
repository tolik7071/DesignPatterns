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
        
        virtual ~ICommand();
    };
    
    class PrintCommand : public ICommand
    {
        public:
        
        PrintCommand(std::shared_ptr<Document> document);
        
        virtual void execute();
        
        private:
        
        std::shared_ptr<Document> mDocument;
    };
    
    class CloseCommand : public ICommand
    {
        public:
        
        CloseCommand(std::shared_ptr<Document> document);
        
        virtual void execute();
        
        private:
        
        std::shared_ptr<Document> mDocument;
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
        void exit();
        
        private:
        
        std::string mName;
    };
    
    class MenuItem
    {
        public:
        
        MenuItem(std::string title, std::shared_ptr<ICommand> command);
        
        std::string title() const;
        
        void select();
        
        private:
        
        std::string mTitle;
        std::shared_ptr<ICommand> mCommand;
    };
    
    class Application
    {
        public:
        
        static Application& GetSharedInstance();
        
        std::shared_ptr<Document> createDocWithName(const std::string& name);
        std::shared_ptr<Document> documentWithName(const std::string& name);
        std::shared_ptr<Document> currentDoc() const;
        
        private:
        
        /*
         
         'New document'
         'Print document'
         'Close document'
         ---
         'Quit'
         
         */
        void createMenu();
        
        static void CleanUp();
        static Application *mInstance;
        
        typedef std::vector<std::shared_ptr<Document> > TArrayOfDocs;
        TArrayOfDocs mDocuments;
        
        typedef std::vector<std::shared_ptr<ICommand> > TArrayOfCommands;
        TArrayOfCommands mCommands;
    };
}

#endif /* Command_hpp */
