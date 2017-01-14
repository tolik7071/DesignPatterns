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
    class ICommand
    {
        public:
        
        virtual void execute() = 0;
    };
    
    class DeleteDocumentCommand : public ICommand
    {
        public:
        
        virtual void execute();
    };
    
    class CreateDocumentCommand : public ICommand
    {
        public:
        
        virtual void execute();
    };
    
    class Document
    {
        public:
        
        Document(const std::string& title);
        virtual ~Document();
        
        std::string title() const;
        
        private:
        
        std::string mTitle;
    };
    
    class Application
    {
        public:
        
        static Application& GetSharedInstance();
        
        class Menu
        {
            public:
            
            void createDocument() const;
            void deleteDocument() const;
        };
        
        const Menu * menu();
        
        std::shared_ptr<Document> createDocument();
        void deleteCurrentDocument();
        
        private:
        
        Application();
        ~Application();
        
        friend class Menu;
        
        void invoke(std::shared_ptr<ICommand> command);
        
        private:
        
        typedef std::vector<std::shared_ptr<Document> > TArrayOfDocuments;
        TArrayOfDocuments mDocuments;
        
        Menu *mMenu = nullptr;
        
        static void Cleanup();
        static Application *mInstance;
    };
}

#endif /* Command_hpp */
