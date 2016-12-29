//
//  Command.cpp
//  DesignPatterns
//
//  Created by Anatoliy Goodz on 12/24/16.
//  Copyright © 2016 Anatoliy Goodz. All rights reserved.
//

#if defined(_MSC_VER)
#include "stdafx.h"
#endif // _MSC_VER
#include "Command.hpp"
#include "common.h"
#include <algorithm>
#include <stdlib.h>

using namespace Command;

BaseCommand::BaseCommand(std::shared_ptr<Document> document)
{
    mDocument = document;
}

BaseCommand::~BaseCommand()
{
    LOG_FUNCTION();
}

std::shared_ptr<Document> BaseCommand::document()
{
    return mDocument;
}

void CreateCommand::execute()
{
    LOG_FUNCTION();
}

PrintCommand::PrintCommand(std::shared_ptr<Document> document)
    : BaseCommand(document)
{
}

void PrintCommand::execute()
{
    LOG_FUNCTION();
}

CloseCommand::CloseCommand(std::shared_ptr<Document> document)
    : BaseCommand(document)
{
}

void CloseCommand::execute()
{
    LOG_FUNCTION();
}

void ExitCommand::execute()
{
    LOG_FUNCTION();
}

Document::Document(std::string name)
{
    mName = name;
}

Document::~Document()
{
    LOG_FUNCTION();
}

std::string Document::name() const
{
    return mName;
}

void Document::print()
{
    LOG_FUNCTION();
}

void Document::close()
{
    LOG_FUNCTION();
}

MenuItem::MenuItem(std::string title, MenuIDs id)
{
    mTitle = title;
    mId = id;
}

MenuItem::~MenuItem()
{
    LOG_FUNCTION();
}

std::string MenuItem::title() const
{
    return mTitle;
}

void MenuItem::select() const
{
    switch (mId)
    {
        case MenuIDs::kCreateDocument:
        {
//            Application::GetSharedInstance().invoke(std::shared_ptr<ICommand>(new CreateCommand()));
            break;
        }
        
        case MenuIDs::kPrintDocument:
        {
            break;
        }
            
        case MenuIDs::kCloseDocument:
        {
            break;
        }
        
        case MenuIDs::kExit:
        {
            break;
        }
        
        case MenuIDs::kSeparator:
        {
            ; // Avoid compiler warning
        }
    }
}

Application* Application::mInstance = nullptr;

/*static */Application& Application::GetSharedInstance()
{
    if (mInstance == nullptr)
    {
        mInstance = new Application();
        std::atexit(CleanUp);
    }
    
    return *mInstance;
}

void Application::createMenu()
{
}

void Application::invoke(std::shared_ptr<ICommand> command)
{
    if (command.get() != nullptr)
    {
        command->execute();
    }
}

void Application::exit()
{
    CleanUp();
}

std::shared_ptr<Document> Application::createDocWithName(const std::string& name)
{
    std::shared_ptr<Document> result = documentWithName(name);
    
    if (result.get() == nullptr)
    {
        result.reset(new Document(name));
        mCurrentDoc = result;
    }
    
    return result;
}

std::shared_ptr<Document> Application::documentWithName(const std::string& name)
{
    std::shared_ptr<Document> result;
    
    TArrayOfDocs::iterator it = std::find_if(mDocuments.begin(), mDocuments.end(),
        [&name](std::shared_ptr<Document>& document)
            {
                bool result = false;

                if (document->name() == name)
                {
                    result = true;
                }

                return result;
            }
    );
    
    if (it != mDocuments.end())
    {
        result = *it;
    }
    
    return result;
}

void Application::setCurrentDocument(std::shared_ptr<Document> document)
{
    if (mCurrentDoc.get() != document.get())
    {
        mCurrentDoc = document;
        
        if (documentWithName(document->name()).get() == nullptr)
        {
            mDocuments.push_back(document);
        }
    }
}

std::shared_ptr<Document> Application::currentDocument() const
{
    return mCurrentDoc;
}

/*static */void Application::CleanUp()
{
    LOG_FUNCTION();
    
    delete mInstance;
    mInstance = NULL;
}

const std::vector<std::shared_ptr<MenuItem> > Application::menu() const
{
    return mMenuItems;
}
