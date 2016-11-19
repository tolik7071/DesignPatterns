//
//  AbstractFactory.hpp
//  DesignPatterns
//
//  Created by Anatoliy Goodz on 11/5/16.
//  Copyright © 2016 Anatoliy Goodz. All rights reserved.
//

#ifndef AbstractFactory_hpp
#define AbstractFactory_hpp

#include "common.h"

namespace AbstractFactory
{
    enum class ShapeType
    {
        Triangle,
        Rectangle,
        Circle
    };
    
    enum class ObjectType
    {
        Thin,
        Thick
    };

    class IShape
    {
        public:
        
        virtual void Draw() = 0;
        virtual ShapeType type() = 0;
        
        public:
        
        virtual ~IShape();
    };

    class ITriangle : public IShape
    {
    };

    class IRectangle : public IShape
    {
    };

    class ICircle : public IShape
    {
    };

    class IAbstractFactory
    {
        public:
        
        virtual IShape* CreateShape(ShapeType type) const = 0;
        virtual void ReleaseShape(IShape* shape) const = 0;
    };

    class ObjectTypeSelector
    {
        public:
        
        ObjectTypeSelector();
        
        public:
        
        ObjectType type() const;
        void setType(ObjectType type);
        
        private:
        
        ObjectType mObjectType;
    };
    
    const IAbstractFactory& GetFactory(const ObjectTypeSelector& selector);
}

#endif /* AbstractFactory_hpp */
