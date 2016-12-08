//
//  Composite.cpp
//  DesignPatterns
//
//  Created by Anatoliy Goodz on 12/6/16.
//  Copyright © 2016 Anatoliy Goodz. All rights reserved.
//

#include "Composite.hpp"

using namespace Composite;

void Composite::Graphic::add(std::shared_ptr<Graphic> graphic)
{
    if (isComposite())
    {
        mChildren.push_back(graphic);
    }
}

void Composite::Graphic::remove(std::shared_ptr<Graphic> graphic)
{
    if (isComposite())
    {
        TArray::const_iterator deleted = std::find(mChildren.begin(), mChildren.end(), graphic);
        if (deleted != mChildren.end())
        {
            mChildren.erase(deleted);
        }
    }
}

std::shared_ptr<Composite::Graphic> Composite::Graphic::childAtIndex(size_t index)
{
    if (! isComposite())
    {
        throw std::exception();
    }
    
    return mChildren.at(index);
}

void Composite::Line::Draw()
{
    LOG_FUNCTION();
}

void Composite::Rectangle::Draw()
{
    LOG_FUNCTION();
}

void Composite::Picture::Draw()
{
    LOG_FUNCTION();
    
    std::for_each(mChildren.begin(), mChildren.end(),
        [](std::shared_ptr<Graphic> graphic)
            {
                graphic->Draw();
            }
    );
}
