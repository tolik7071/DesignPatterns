//
//  Mediator.cpp
//  DesignPatterns
//
//  Created by Anatoliy Goodz on 2/7/17.
//  Copyright © 2017 Anatoliy Goodz. All rights reserved.
//

#if defined(_MSC_VER)
#include "stdafx.h"
#endif // _MSC_VER
#include "Mediator.hpp"
#include "common.h"

using namespace Mediator;

class ListBoxImpl : public ListBox
{
    public:
    
    Color mColor = kRed;
    DialogDirector* mDirector = nullptr;
    
    ListBoxImpl(DialogDirector* director)
        : mDirector(director)
    {
        LOG_FUNCTION();
    }
    
    ~ListBoxImpl()
    {
        LOG_FUNCTION();
    }
    
    virtual Color color() const
    {
        return mColor;
    }
    
    virtual void setColor(Color color)
    {
        if (mColor != color)
        {
            mColor = color;
            changed();
        }
    }
    
    virtual void changed()
    {
        if (mDirector != nullptr)
        {
            mDirector->widgetChanged(this);
        }
    }
};

class ColorBoxImpl : public ColorBox
{
    public:
    
    ListBox::Color mFillColor = ListBox::Color::kRed;
    DialogDirector* mDirector = nullptr;
    
    ColorBoxImpl(DialogDirector* director)
        : mDirector(director)
    {
        LOG_FUNCTION();
    }
    
    ~ColorBoxImpl()
    {
        LOG_FUNCTION();
    }
    
    virtual ListBox::Color fillColor() const
    {
        return mFillColor;
    }
    
    virtual void setFillColor(ListBox::Color color)
    {
        if (mFillColor != color)
        {
            mFillColor = color;
            changed();
        }
    }
    
    virtual void changed()
    {
        if (mDirector != nullptr)
        {
            mDirector->widgetChanged(this);
        }
    }
};

DialogDirector::DialogDirector()
{
    LOG_FUNCTION();
}

DialogDirector::~DialogDirector()
{
    LOG_FUNCTION();
}

class DialogDirectorImpl : public DialogDirector
{
    public:
    
    std::shared_ptr<ListBoxImpl> mListBox;
    std::shared_ptr<ColorBoxImpl> mColorBox;
    
    virtual void widgetChanged(Widget* widget)
    {
        if (widget == mListBox.get())
        {
            mColorBox->setFillColor(mListBox->color());
        }
    }
    
    virtual void createWidgets()
    {
        if (mListBox.get() == nullptr)
        {
            mListBox.reset(new ListBoxImpl(this));
        }
        
        if (mColorBox.get() == nullptr)
        {
            mColorBox.reset(new ColorBoxImpl(this));
        }
    }
    
    virtual std::shared_ptr<ListBox> listBox()
    {
        return mListBox;
    }
    
    virtual std::shared_ptr<ColorBox> colorBox()
    {
        return mColorBox;
    }
};

static DialogDirectorImpl * gDirector = nullptr;

static void Cleanup()
{
    LOG_FUNCTION();
    
    delete gDirector;
    gDirector = nullptr;
}

/* static */DialogDirector& DialogDirector::GetSharedDirector()
{
    if (gDirector == nullptr)
    {
        gDirector = new DialogDirectorImpl();
        std::atexit(Cleanup);
    }
    
    return *(gDirector);
}
