//
//  Flyweight.hpp
//  DesignPatterns
//
//  Created by Anatoliy Goodz on 12/16/16.
//  Copyright © 2016 Anatoliy Goodz. All rights reserved.
//

#ifndef Flyweight_hpp
#define Flyweight_hpp

#include "common.h"
#include <vector>
#include <memory>
#include <map>

namespace Flyweight
{
    class Context;
    
    class Primitive
    {
        public:
        
        virtual void draw(Context& context) = 0;
        
        virtual ~Primitive()
        {
            LOG_FUNCTION();
        }
    };
    
    class Circle : public Primitive
    {
        public:
        
        Circle(int radius)
            : mRadius(radius)
        {
            LOG_FUNCTION();
        }
        
        
        virtual void draw(Context& context)
        {
            LOG_FUNCTION();
        }
        
        private:
        
        int mRadius;
    };
    
    class Square : public Primitive
    {
        public:
        
        Square(int height, int width)
            : mHeight(height)
            , mWidth(width)
        {
            LOG_FUNCTION();
        }
        
        virtual void draw(Context& context)
        {
            LOG_FUNCTION();
        }
        
        private:
        
        int mHeight;
        int mWidth;
    };
    
    class Point : public Primitive
    {
        public:
        
        Point()
        {
            LOG_FUNCTION();
        }
        
        virtual void draw(Context& context)
        {
            LOG_FUNCTION();
        }
    };
    
    class Picture : public Primitive
    {
        public:
        
        void addChild(std::shared_ptr<Primitive> primitive);
        virtual void draw(Context& context);
        
        private:
        
        typedef std::vector<std::shared_ptr<Primitive> > TArray;
        TArray mChildrens;
    };
    
    struct Context
    {
        int x;
        int y;
        int color;
        
        Context(int x, int y, int color)
        {
            this->x = x;
            this->y = y;
            this->color = color;
        }
    };
    
    class PrimitiveFactory
    {
        public:
        
        std::shared_ptr<Picture> createPicture();
        std::shared_ptr<Circle> createCircle(int radius);
        std::shared_ptr<Square> createSquare(int height, int width);
        std::shared_ptr<Point> createPoint();
        
        private:
        
        std::map<int, std::shared_ptr<Circle> > mCircles;
        std::map<int, std::shared_ptr<Square> > mSquares;
        std::shared_ptr<Point> mPoint;
    };
}

#endif /* Flyweight_hpp */
