//
//  Mediator.hpp
//  DesignPatterns
//
//  Created by Anatoliy Goodz on 2/7/17.
//  Copyright © 2017 Anatoliy Goodz. All rights reserved.
//

#ifndef Mediator_hpp
#define Mediator_hpp

#include <memory>

namespace Mediator
{
    class Widget
    {
        public:
        
        virtual void changed() = 0;
    };
    
    class ListBox : public Widget
    {
        public:
        
        enum Color {
            kRed,
            kGreen,
            kBlue
        };
        
        virtual Color color() const = 0;
        virtual void setColor(Color color) = 0;
    };
    
    class ColorBox : public Widget
    {
        public:
        
        virtual ListBox::Color fillColor() const = 0;
        virtual void setFillColor(ListBox::Color color) = 0;
    };
    
    class DialogDirector
    {
        public:
        
        static DialogDirector& GetSharedDirector();
        
        virtual std::shared_ptr<ListBox> listBox() = 0;
        virtual std::shared_ptr<ColorBox> colorBox() = 0;
        
        virtual void widgetChanged(Widget* widget) = 0;
        virtual void createWidgets() = 0;
        
        protected:
        
        DialogDirector();
        virtual ~DialogDirector();
    };
}

#endif /* Mediator_hpp */
