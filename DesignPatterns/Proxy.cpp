//
//  Proxy.cpp
//  DesignPatterns
//
//  Created by Anatoliy Goodz on 12/21/16.
//  Copyright © 2016 Anatoliy Goodz. All rights reserved.
//

#if defined(_MSC_VER)
#include "stdafx.h"
#endif // _MSC_VER
#include "Proxy.hpp"
#include "common.h"
#include <algorithm>

using namespace Proxy;

Proxy::Graphic::~Graphic()
{
    LOG_FUNCTION();
}

void Proxy::Image::draw()
{
    LOG_FUNCTION();
}

std::shared_ptr<Image> Proxy::ImageProxy::image()
{
    if (mImage.get() == nullptr)
    {
        mImage = std::shared_ptr<Image>(new Image());
    }
    
    return mImage;
}

void Proxy::ImageProxy::draw()
{
    LOG_FUNCTION();
    
    std::shared_ptr<Image> image = this->image();
    
    if (image->isLoaded())
    {
        image->draw();
    }
}

void Proxy::Editor::addImage(std::shared_ptr<ImageProxy> image)
{
    mImages.push_back(image);
}

void Proxy::Editor::ProcessImages()
{
    std::for_each(mImages.begin(), mImages.end(),
        [](std::shared_ptr<ImageProxy> image)
        {
            image->draw();
        }
    );
}
