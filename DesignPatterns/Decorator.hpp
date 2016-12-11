//
//  Decorator.hpp
//  DesignPatterns
//
//  Created by Anatoliy Goodz on 12/8/16.
//  Copyright © 2016 Anatoliy Goodz. All rights reserved.
//

#ifndef Decorator_hpp
#define Decorator_hpp

#include <vector>

namespace Decorator
{
    class Graphic
    {
        public:
        
        virtual void draw() = 0;
    };
    
    class TextView : public Graphic
    {
        public:
        
        virtual ~TextView();
        
        virtual void draw();
    };
    
    class TextViewDecorator : public Graphic
    {
        public:
        
        virtual ~TextViewDecorator();
        
        void setWrappedObject(std::shared_ptr<Graphic> other)
        {
            mOther = other;
        }
        
        protected:
        
        std::shared_ptr<Graphic> mOther;
    };
    
    class ScrollDecorator : public TextViewDecorator
    {
        public:
        
        virtual void draw();
        
        private:
        
        void doScroll();
    };
    
    class BorderDecorator : public TextViewDecorator
    {
        public:
        
        virtual void draw();
        
        private:
        
        void drawBorder();
    };
}

#endif /* Decorator_hpp */
