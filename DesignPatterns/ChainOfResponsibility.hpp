//
//  ChainOfResponsibility.hpp
//  DesignPatterns
//
//  Created by Anatoliy Goodz on 12/23/16.
//  Copyright © 2016 Anatoliy Goodz. All rights reserved.
//

#ifndef ChainOfResponsibility_hpp
#define ChainOfResponsibility_hpp

#include <string>
#include <memory>
#include <vector>

namespace ChainOfResponsibility
{
    class HelpProvider
    {
        public:
        
        virtual bool hasHelp() const = 0;
        virtual const char* help() const = 0;
    };
    
    class Control : private HelpProvider
    {
        public:
        
        Control(const char *help = nullptr);
        virtual ~Control();
        
        virtual void draw() = 0;
        
        virtual bool hasHelp() const;
        virtual const char* help() const;
        
        protected:
        
        std::string mHelp;
    };
    
    class Button : public Control
    {
        public:
        
        Button(const char *help = nullptr);
        
        virtual void draw();
    };
    
    class Slider : public Control
    {
        public:
        
        Slider(const char *help = nullptr);
        
        virtual void draw();
    };
    
    class Window
    {
        public:
        
        void createControls();
        const char* findHelp();
        
        typedef std::vector<std::shared_ptr<Control> > TArrayOfControls;
        TArrayOfControls mControls;
    };
}

#endif /* ChainOfResponsibility_hpp */
