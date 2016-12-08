//
//  Composite.hpp
//  DesignPatterns
//
//  Created by Anatoliy Goodz on 12/6/16.
//  Copyright © 2016 Anatoliy Goodz. All rights reserved.
//

#ifndef Composite_hpp
#define Composite_hpp

#include <vector>
#include "common.h"

namespace Composite
{
    class Graphic
    {
        public:
        
        Graphic() {}
        virtual ~Graphic() { LOG_FUNCTION(); }
        
        virtual bool isComposite() { return false; }
        virtual void Draw() = 0;
        
        void add(std::shared_ptr<Graphic> graphic);
        void remove(std::shared_ptr<Graphic> graphic);
        std::shared_ptr<Graphic> childAtIndex(size_t index);
        
        protected:
        
        typedef std::vector<std::shared_ptr<Graphic> > TArray;
        TArray mChildren;
    };
    
    class Line : public Graphic
    {
        public:
        
        Line() {}
        
        virtual void Draw();
    };
    
    class Rectangle : public Graphic
    {
        public:
        
        Rectangle() {}
        
        virtual void Draw();
    };
    
    class Picture : public Graphic
    {
        public:
        
        Picture() {}
        
        virtual bool isComposite() { return true; }
        virtual void Draw();
    };
}

#endif /* Composite_hpp */
