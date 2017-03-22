//
//  TemplateMethod.hpp
//  DesignPatterns
//
//  Created by tolik7071 on 3/16/17.
//  Copyright © 2017 Anatoliy Goodz. All rights reserved.
//

#ifndef TemplateMethod_hpp
#define TemplateMethod_hpp

#include <string>
#include <memory>
#include <vector>
#include <iostream>

namespace TemplateMethod
{
    struct CaffeinBeverage
    {
        void prepareRecipe();
        
        protected:
        
        void boilWater();
        virtual void brew();
        void pourInCup();
        virtual void addCondiments();
    };
    
    struct Tea : public CaffeinBeverage
    {
        protected:
        
        virtual void brew();
        virtual void addCondiments();
    };
    
    struct Coffee : public CaffeinBeverage
    {
        protected:
        
        virtual void brew();
        virtual void addCondiments();
    };
}

#endif /* TemplateMethod_hpp */
