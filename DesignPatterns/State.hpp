//
//  State.hpp
//  DesignPatterns
//
//  Created by tolik7071 on 3/13/17.
//  Copyright © 2017 Anatoliy Goodz. All rights reserved.
//

#ifndef State_hpp
#define State_hpp

#include <memory>

namespace State
{
    struct IState
    {
        IState();
        virtual ~IState();
        
        virtual void doWork() = 0;
    };
    
    struct SomeObject
    {
        enum class StateID
        {
            kState1,
            kState2,
            kState3
        };
        
        void setState(StateID state);
        
        void execute();
        
        private:
        
        IState* mCurrentState = nullptr;
    };
}

#endif /* State_hpp */
