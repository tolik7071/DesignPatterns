//
//  Adapter.hpp
//  DesignPatterns
//
//  Created by Anatoliy Goodz on 11/23/16.
//  Copyright © 2016 Anatoliy Goodz. All rights reserved.
//

#ifndef Adapter_hpp
#define Adapter_hpp

#include <vector>

namespace Adapter
{
    class IShape
    {
        public:
        
        virtual void Draw() = 0;
        virtual ~IShape();
    };
    
    class Line : public IShape
    {
        public:
        
        virtual void Draw();
    };
    
    class Polyline : public IShape
    {
        public:
        
        virtual void Draw();
    };
    
    class Text : public IShape
    {
        public:
        
        virtual void Draw();
    };
    
    class Drawer
    {
        public:
        
        ~Drawer();
        
        typedef std::vector<IShape* > TShapeArray;
        TShapeArray mShapes;
        
        void DrawShapes() const;
    };
    
    /* ***** ***** ***** ***** ***** ***** ***** */
    
    class NewTextView
    {
        public:
        
        virtual void DrawText();
        
        virtual ~NewTextView();
    };
    
    class NewTextViewAdapter : public IShape
    {
        public:
        
        NewTextViewAdapter(std::unique_ptr<NewTextView> textView);
        virtual ~NewTextViewAdapter();
        
        virtual void Draw();
        
        private:
        
        std::unique_ptr<NewTextView> mTextView;
    };
}

#endif /* Adapter_hpp */
