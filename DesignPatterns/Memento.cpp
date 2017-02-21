//
//  Memento.cpp
//  DesignPatterns
//
//  Created by tolik7071 on 2/17/17.
//  Copyright © 2017 Anatoliy Goodz. All rights reserved.
//

#if defined(_MSC_VER)
#include "stdafx.h"
#endif // _MSC_VER
#include "Memento.hpp"
#include "common.h"

using namespace Memento;

Memento::TextEditor::RestorePoint::RestorePoint()
{
    LOG_FUNCTION();
}

Memento::TextEditor::RestorePoint::~RestorePoint()
{
    LOG_FUNCTION();
}

void Memento::TextEditor::RestorePoint::setText(const std::string& text)
{
    mText = text;
}

const std::string& Memento::TextEditor::RestorePoint::text() const
{
    return mText;
}

std::shared_ptr<Memento::TextEditor::RestorePoint> Memento::TextEditor::createRestorePoint() const
{
    RestorePoint *restorePoint = new RestorePoint();
    restorePoint->setText(this->text());
    
    std::shared_ptr<Memento::TextEditor::RestorePoint> result(restorePoint);
    
    return result;
}

void Memento::TextEditor::applyRestorePoint(std::shared_ptr<Memento::TextEditor::RestorePoint> restorePoint)
{
    if (restorePoint.get() != nullptr)
    {
        mText = restorePoint->text();
    }
}

void Memento::TextEditor::setText(const std::string& text)
{
    mText = text;
}

const std::string& Memento::TextEditor::text() const
{
    return mText;
}
