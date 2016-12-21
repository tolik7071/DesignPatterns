//
//  Proxy.hpp
//  DesignPatterns
//
//  Created by Anatoliy Goodz on 12/21/16.
//  Copyright © 2016 Anatoliy Goodz. All rights reserved.
//

#ifndef Proxy_hpp
#define Proxy_hpp

#include <memory>
#include <vector>

namespace Proxy
{
    class Graphic
    {
        public:
        
        virtual void draw() = 0;
        
        virtual ~Graphic();
    };
    
    class Image : public Graphic
    {
        public:
        
        virtual void draw();
        
        void setIsLoaded(bool flag) { mIsLoaded = flag; }
        bool isLoaded() const { return mIsLoaded; }
        
        private:
        
        bool mIsLoaded = false;
    };
    
    class ImageProxy : public Image
    {
        public:
        
        virtual void draw();
        
        std::shared_ptr<Image> image();
        
        private:
        
        std::shared_ptr<Image> mImage;
    };
    
    class Editor
    {
        public:
        
        void addImage(std::shared_ptr<ImageProxy> image);
        void ProcessImages();
        
        private:
        
        typedef std::vector<std::shared_ptr<ImageProxy> > TArrayOfImages;
        TArrayOfImages mImages;
    };
}

#endif /* Proxy_hpp */
