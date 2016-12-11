//
//  Adapter.cpp
//  DesignPatterns
//
//  Created by Anatoliy Goodz on 11/23/16.
//  Copyright © 2016 Anatoliy Goodz. All rights reserved.
//

#if defined(_MSC_VER)
#include "stdafx.h"
#endif // _MSC_VER
#include "Adapter.hpp"
#include "common.h"
#include <algorithm>

using namespace Adapter;

IShape::~IShape()
{
    LOG_FUNCTION();
}

void Line::Draw()
{
    LOG_FUNCTION();
}

void Polyline::Draw()
{
    LOG_FUNCTION();
}

void Text::Draw()
{
    LOG_FUNCTION();
}

void Drawer::DrawShapes() const
{
    std::for_each(mShapes.begin(), mShapes.end(), [](IShape* shape) { shape->Draw(); });
}

Drawer::~Drawer()
{
    std::for_each(mShapes.begin(), mShapes.end(), [](IShape* shape) { delete shape; });
    LOG_FUNCTION();
}

void NewTextView::DrawText()
{
    LOG_FUNCTION();
}

NewTextView::~NewTextView()
{
    LOG_FUNCTION();
}

void NewTextViewAdapter::Draw()
{
    mTextView->DrawText();
}

NewTextViewAdapter::NewTextViewAdapter(std::unique_ptr<NewTextView> textView)
{
    mTextView = std::move(textView);
}

NewTextViewAdapter::~NewTextViewAdapter()
{
    LOG_FUNCTION();
}
