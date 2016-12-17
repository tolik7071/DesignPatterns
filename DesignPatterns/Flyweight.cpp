//
//  Flyweight.cpp
//  DesignPatterns
//
//  Created by Anatoliy Goodz on 12/16/16.
//  Copyright © 2016 Anatoliy Goodz. All rights reserved.
//

#include "Flyweight.hpp"
#include <algorithm>

using namespace Flyweight;

void Flyweight::Picture::addChild(std::shared_ptr<Flyweight::Primitive> primitive)
{
    mChildrens.push_back(primitive);
}

void Flyweight::Picture::draw(Flyweight::Context& context)
{
    std::for_each(mChildrens.begin(), mChildrens.end(),
        [&context](std::shared_ptr<Flyweight::Primitive>& primitive)
        {
            primitive->draw(context);
        }
    );
}

std::shared_ptr<Picture> PrimitiveFactory::createPicture()
{
    std::shared_ptr<Picture> result(new Picture());
    return result;
}

std::shared_ptr<Circle> PrimitiveFactory::createCircle(int radius)
{
    std::shared_ptr<Circle> result;
    
    std::map<int, std::shared_ptr<Circle> >::iterator circle = mCircles.find(radius);
    if (circle != mCircles.end())
    {
        result = mCircles.at(radius);
    }
    else
    {
        result = std::shared_ptr<Circle>(new Circle(radius));
        mCircles.insert(std::make_pair(radius, result));
    }
    
    return result;
}

std::shared_ptr<Square> PrimitiveFactory::createSquare(int height, int width)
{
    std::shared_ptr<Square> result;
    
    int key = height * 10 + width;
    
    std::map<int, std::shared_ptr<Square> >::iterator square = mSquares.find(key);
    if (square != mSquares.end())
    {
        result = mSquares.at(key);
    }
    else
    {
        result = std::shared_ptr<Square>(new Square(height, width));
        mSquares.insert(std::make_pair(key, result));
    }
    
    return result;
}

std::shared_ptr<Point> PrimitiveFactory::createPoint()
{
    if (mPoint.get() == nullptr)
    {
        mPoint = std::shared_ptr<Point>(new Point());
    }
    
    return mPoint;
}
