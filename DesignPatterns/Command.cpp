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

Document::Document(const std::string& title)
    : mTitle(title)
{
    LOG_FUNCTION();
}

Document::~Document()
{
    LOG_FUNCTION();
}

std::string Document::title() const
{
    return mTitle;
}

Application::Application()
{
    LOG_FUNCTION();
}

Application::~Application()
{
    LOG_FUNCTION();
    
    delete mMenu;
}

Application* Application::mInstance = nullptr;

/*static */Application& Application::GetSharedInstance()
{
    if (mInstance == nullptr)
    {
        mInstance = new Application();
        std::atexit(Cleanup);
    }
    
    return *mInstance;
}

/*static */void Application::Cleanup()
{
    LOG_FUNCTION();
    
    delete mInstance;
    mInstance = nullptr;
}

const Application::Menu * Application::menu()
{
    if (mMenu == nullptr)
    {
        mMenu = new Menu();
    }
    
    return mMenu;
}


void Application::invoke(std::shared_ptr<ICommand> command)
{
    if (command.get() != nullptr)
    {
        command->execute();
    }
}

std::shared_ptr<Document> Application::createDocument()
{
    static int count = 0;
    
    std::string title("New Document #");
    title += std::to_string(++count);
    std::shared_ptr<Document> result(new Document(title));
    
    mDocuments.push_back(result);
    
    return result;
}

void Application::deleteCurrentDocument()
{
    if (0 < mDocuments.size())
    {
        std::shared_ptr<Document> currentDocument = mDocuments.back();
        mDocuments.pop_back();
        currentDocument.reset();
    }
}

void Application::Menu::createDocument() const
{
    std::shared_ptr<ICommand> command(new CreateDocumentCommand());
    Application::GetSharedInstance().invoke(command);
}

void Application::Menu::deleteDocument() const
{
    std::shared_ptr<ICommand> command(new DeleteDocumentCommand());
    Application::GetSharedInstance().invoke(command);
}

void CreateDocumentCommand::execute()
{
    Application::GetSharedInstance().createDocument();
}

void DeleteDocumentCommand::execute()
{
    Application::GetSharedInstance().deleteCurrentDocument();
}
