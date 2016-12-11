//
//  AbstractFactory.cpp
//  DesignPatterns
//
//  Created by Anatoliy Goodz on 11/5/16.
//  Copyright © 2016 Anatoliy Goodz. All rights reserved.
//

#if defined(_MSC_VER)
#include "stdafx.h"
#endif // _MSC_VER
#include "AbstractFactory.hpp"

using namespace AbstractFactory;

IShape::~IShape()
{
    LOG_FUNCTION();
}

class TriangleBase : public ITriangle
{
    public:
    
    virtual ShapeType type()
    {
        return ShapeType::Triangle;
    }
};

class RectangleBase : public IRectangle
{
    public:
    
    virtual ShapeType type()
    {
        return ShapeType::Rectangle;
    }
};

class CircleBase : public ICircle
{
    public:
    
    virtual ShapeType type()
    {
        return ShapeType::Circle;
    }
};

class TriangleThin : public TriangleBase
{
    public:
    
    virtual void Draw()
    {
        LOG_FUNCTION();
    }
};

class TriangleThick : public TriangleBase
{
    public:
    
    virtual void Draw()
    {
        LOG_FUNCTION();
    }
};

class RectangleThin : public RectangleBase
{
    public:
    
    virtual void Draw()
    {
        LOG_FUNCTION();
    }
};

class RectangleThick : public RectangleBase
{
    public:
    
    virtual void Draw()
    {
        LOG_FUNCTION();
    }
};

class CircleThin : public CircleBase
{
    public:
    
    virtual void Draw()
    {
        LOG_FUNCTION();
    }
};

class CircleThick : public CircleBase
{
    public:
    
    virtual void Draw()
    {
        LOG_FUNCTION();
    }
};

class ObjectFactoryBase : public IAbstractFactory
{
    public:
    
    void ReleaseShape(IShape* shape) const
    {
        delete shape;
    }
};

class ThinObjectFactory : public ObjectFactoryBase
{
    virtual IShape* CreateShape(ShapeType type) const
    {
        IShape *result = NULL;
        
        if (type == ShapeType::Triangle)
        {
            result = new TriangleThin();
        }
        else if (type == ShapeType::Rectangle)
        {
            result = new RectangleThin();
        }
        else if (type == ShapeType::Circle)
        {
            result = new CircleThin();
        }
        
        return result;
    }
};

class ThickObjectFactory : public ObjectFactoryBase
{
    virtual IShape* CreateShape(ShapeType type) const
    {
        IShape *result = NULL;
        
        if (type == ShapeType::Triangle)
        {
            result = new TriangleThick();
        }
        else if (type == ShapeType::Rectangle)
        {
            result = new RectangleThick();
        }
        else if (type == ShapeType::Circle)
        {
            result = new CircleThick();
        }
        
        return result;
    }
};

const IAbstractFactory& AbstractFactory::GetFactory(const ObjectTypeSelector& selector)
{
    static IAbstractFactory* factoryMap[] = {
        new ThickObjectFactory(),
        new ThinObjectFactory()
    };
    
    IAbstractFactory* result = NULL;
    
    if (selector.type() == ObjectType::Thick)
    {
        result = factoryMap[0];
    }
    else
    {
        result = factoryMap[1];
    }
    
    return (*result);
}

ObjectTypeSelector::ObjectTypeSelector() : mObjectType(ObjectType::Thin)
{
}

ObjectType ObjectTypeSelector::type() const
{
    return mObjectType;
}

void ObjectTypeSelector::setType(ObjectType type)
{
    mObjectType = type;
}
