//
//  Builder.hpp
//  DesignPatterns
//
//  Created by Anatoliy Goodz on 11/9/16.
//  Copyright © 2016 Anatoliy Goodz. All rights reserved.
//

#ifndef Builder_hpp
#define Builder_hpp

#include <iostream>
#include "common.h"

namespace Builder
{
    typedef unsigned int TUInt;
    
    class PizzaRecipe
    {
        public:
        
        void setAmountOfSausage(TUInt newValue)
        {
            mAmountOfSausage = newValue;
        }
        
        TUInt amountOfSausage()
        {
            return mAmountOfSausage;
        }
        
        void setAmountOfAnanas(TUInt newValue)
        {
            mAmountOfAnanas = newValue;
        }
        
        TUInt amountOfAnanas()
        {
            return mAmountOfAnanas;
        }
        
        void setAmountOfCheese(TUInt newValue)
        {
            mAmountOfCheese = newValue;
        }
        
        TUInt amountOfCheese()
        {
            return mAmountOfCheese;
        }
        
        void setAmountOfPepper(TUInt newValue)
        {
            mAmountOfPepper = newValue;
        }
        
        TUInt amountOfPepper()
        {
            return mAmountOfPepper;
        }
        
        virtual ~PizzaRecipe()
        {
            LOG_FUNCTION();
        }
        
        private:
        
        TUInt mAmountOfSausage = 0;
        TUInt mAmountOfAnanas = 0;
        TUInt mAmountOfCheese = 0;
        TUInt mAmountOfPepper = 0;
    };
    
    class PizzaBuilder
    {
        public:
        
        virtual ~PizzaBuilder()
        {
            LOG_FUNCTION();
            delete mRecipe;
        }
        
        void PrintRecipe() const
        {
            std::cout
                << "Sausage " << mRecipe->amountOfSausage() << " mGr\n"
                << "Ananas " << mRecipe->amountOfAnanas() << " mGr\n"
                << "Cheese " << mRecipe->amountOfCheese() << " mGr\n"
                << "Pepper " << mRecipe->amountOfPepper() << " mGr\n"
                << "bon appétit!" << std::endl;
        }
        
        virtual void useSausage() = 0;
        virtual void useAnanas() = 0;
        virtual void useCheese() = 0;
        virtual void usePepper() = 0;
        
        protected:
        
        PizzaRecipe *mRecipe = new PizzaRecipe();
    };
    
    class PizzaBuilder1 : public PizzaBuilder
    {
        virtual void useSausage()
        {
            mRecipe->setAmountOfSausage(1000);
        }
        
        virtual void useAnanas()
        {
            mRecipe->setAmountOfAnanas(10);
        }
        
        virtual void useCheese()
        {
            mRecipe->setAmountOfCheese(500);
        }
        
        virtual void usePepper()
        {
            mRecipe->setAmountOfPepper(30);
        }
    };
    
    class Waiter
    {
        public:
        
        Waiter(PizzaBuilder *builder) : mBuilder(builder)
        {
            
        }
        
        virtual ~Waiter()
        {
            LOG_FUNCTION();
            delete mBuilder;
        }
        
        void preparePizza()
        {
            if (mBuilder == nullptr)
            {
                std::cerr << "No builder!" << std::endl;
                return;
            }
            
            mBuilder->useAnanas();
            mBuilder->useCheese();
            mBuilder->usePepper();
            mBuilder->useSausage();
            
            mBuilder->PrintRecipe();
        }
        
        private:
        
        PizzaBuilder *mBuilder = nullptr;
    };
}

#endif /* Builder_hpp */
