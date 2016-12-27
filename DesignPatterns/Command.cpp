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

ICommand::~ICommand()
{
    LOG_FUNCTION();
}

PrintCommand::PrintCommand(std::shared_ptr<Document> document)
{
    mDocument = document;
}

void PrintCommand::execute()
{
    LOG_FUNCTION();
}

CloseCommand::CloseCommand(std::shared_ptr<Document> document)
{
    mDocument = document;
}

void CloseCommand::execute()
{
    LOG_FUNCTION();
}

void ExitCommand::execute()
{
    LOG_FUNCTION();
}

Document::~Document()
{
    LOG_FUNCTION();
}

Document::Document(std::string name)
{
    mName = name;
}

std::string Document::name() const
{
    return mName;
}

void Document::print()
{
    LOG_FUNCTION();
    
//    std::shared_ptr<ICommand> command(new PrintCommand(std::shared_ptr<Document> (this)));
}

void Document::exit()
{
    LOG_FUNCTION();
}

MenuItem::MenuItem(std::string title, std::shared_ptr<ICommand> command)
{
    mTitle = title;
    mCommand = command;
}

std::string MenuItem::title() const
{
    return mTitle;
}

void MenuItem::select()
{
    
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

std::shared_ptr<Document> Application::createDocWithName(const std::string& name)
{
    std::shared_ptr<Document> result = documentWithName(name);
    
    if (result.get() == nullptr)
    {
        result.reset(new Document(name));
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

std::shared_ptr<Document> Application::currentDoc() const
{
    std::shared_ptr<Document> result;
    
    if (! mDocuments.empty())
    {
        result = mDocuments.at(0);
    }
    
    return result;
}

/*static */void Application::CleanUp()
{
    delete mInstance;
    mInstance = NULL;
    LOG_FUNCTION();
}
