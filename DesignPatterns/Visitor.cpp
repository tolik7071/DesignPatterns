//
//  Visitor.cpp
//  DesignPatterns
//
//  Created by tolik7071 on 3/21/17.
//  Copyright © 2017 Anatoliy Goodz. All rights reserved.
//

#if defined(_MSC_VER)
#include "stdafx.h"
#endif // _MSC_VER
#include "Visitor.hpp"
#include <algorithm>
#include "common.h"

using namespace VisitorTest;

ElementA::ElementA()
{
    LOG_METHOD();
}

ElementA::~ElementA()
{
    LOG_METHOD();
}

void ElementA::accept(const IVisitor& visitor) const
{
    visitor.visit(*this);
}

ElementB::ElementB()
{
    LOG_METHOD();
}

ElementB::~ElementB()
{
    LOG_METHOD();
}

void ElementB::accept(const IVisitor& visitor) const
{
    visitor.visit(*this);
}

CompositeElement::CompositeElement()
{
    LOG_METHOD();
}

CompositeElement::~CompositeElement()
{
    LOG_METHOD();
}

void CompositeElement::accept(const IVisitor& visitor) const
{
    std::for_each(mElemenets.begin(), mElemenets.end(),
        [&visitor](const std::shared_ptr<IElement> element)
        {
            element->accept(visitor);
        }
    );
}

void RealVisitor::visit(const ElementA& element) const
{
    LOG_METHOD();
}

void RealVisitor::visit(const ElementB& element) const
{
    LOG_METHOD();
}

void RealVisitor::visit(const CompositeElement& element) const
{
    LOG_METHOD();
}

void ElementsContainer::inspectElements()
{
    std::for_each(mElements.begin(), mElements.end(),
        [this](const std::shared_ptr<IElement> element)
        {
            if (mVisitor.get() != nullptr)
            {
                element->accept(*(mVisitor.get()));
            }
        }
    );
}
