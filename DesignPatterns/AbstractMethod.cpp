//
//  AbstractMethod.cpp
//  DesignPatterns
//
//  Created by Anatoliy Goodz on 11/12/16.
//  Copyright © 2016 Anatoliy Goodz. All rights reserved.
//

#include "AbstractMethod.hpp"
#include "common.h"
#include <algorithm>

using namespace AbstractMethod;

Document::Document(const char *name) : mName(name)
{
    LOG_FUNCTION();
}

Document::~Document()
{
    LOG_FUNCTION();
}

std::string& Document::name()
{
    return mName;
}

Application::~Application()
{
    std::for_each(mDocuments.begin(), mDocuments.end(), [](Document* document){ delete document; });
    mDocuments.clear();
}

Document* Application::GetDocument(std::string name)
{
    Document* result = nullptr;
    
    TDocumentArray::iterator it = mDocuments.begin();
    for (; it != mDocuments.end(); ++it)
    {
        if ((*it)->name() == name)
        {
            result = (*it);
            break;
        }
    }
    
    return result;
}

Document* Application::GetDocument(size_t index)
{
    Document* result = nullptr;
    
    if (index < mDocuments.size())
    {
        result = mDocuments[index];
    }
    
    return result;
}

MyDocument::MyDocument(const char *name) : Document(name)
{
    LOG_FUNCTION();
}

MyDocument::~MyDocument()
{
    LOG_FUNCTION();
}

void MyDocument::Open()
{
    std::cout << "Open document " << this->name() << std::endl;
}

void MyDocument::Close()
{
    std::cout << "Close document " << this->name() << std::endl;
}

Document* MyApplication::CreateDocument(const char *documentName)
{
    Document* result = new MyDocument(documentName);
    
    mDocuments.push_back(result);
    
    return result;
}
