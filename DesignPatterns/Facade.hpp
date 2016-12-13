//
//  Facade.hpp
//  DesignPatterns
//
//  Created by Anatoliy Goodz on 12/12/16.
//  Copyright © 2016 Anatoliy Goodz. All rights reserved.
//

#ifndef Facade_hpp
#define Facade_hpp

#include <memory>
#include <vector>

namespace Facade
{
    class VisualElement
    {
        public:
        
        virtual void Draw() = 0;
        
        virtual ~VisualElement();
    };
    
    class Background : public VisualElement
    {
        public:
        
        virtual void Draw();
    };
    
    class Menu : public VisualElement
    {
        public:
        
        virtual void Draw();
    };
    
    class Doc : public VisualElement
    {
        public:
        
        virtual void Draw();
    };
    
    class Desktop
    {
        public:
        
        void create();
        void Draw();
        
        private:
        
        typedef std::vector<std::shared_ptr<VisualElement> > TArray;
        TArray mElements;
    };
}

#endif /* Facade_hpp */
