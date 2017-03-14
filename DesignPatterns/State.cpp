//
//  State.cpp
//  DesignPatterns
//
//  Created by tolik7071 on 3/13/17.
//  Copyright © 2017 Anatoliy Goodz. All rights reserved.
//

#if defined(_MSC_VER)
#include "stdafx.h"
#endif // _MSC_VER
#include "State.hpp"
#include "common.h"
#include <map>
#include <algorithm>

namespace State
{
    struct State1;
    struct State2;
    struct State3;
}

State::IState::IState()
{
    LOG_FUNCTION();
}

State::IState::~IState()
{
    LOG_FUNCTION();
}

struct State::State1 : public State::IState
{
    virtual void doWork()
    {
        std::cout << "State #1 has been used." << std::endl;
    }
};

struct State::State2 : public State::IState
{
    virtual void doWork()
    {
        std::cout << "State #2 has been used." << std::endl;
    }
};

struct State::State3 : public State::IState
{
    virtual void doWork()
    {
        std::cout << "State #3 has been used." << std::endl;
    }
};

typedef std::map<State::SomeObject::StateID, State::IState* > TStatesMap;
static TStatesMap gStates;

static void Cleanup()
{
    LOG_FUNCTION();
    
    std::for_each(gStates.begin(), gStates.end(),
        [](TStatesMap::value_type& pair)
        {
            delete pair.second;
        }
    );
}

void State::SomeObject::setState(StateID state)
{
    if (gStates.empty())
    {
        gStates[StateID::kState1] = new State::State1();
        gStates[StateID::kState2] = new State::State2();
        gStates[StateID::kState3] = new State::State3();
        
        std::atexit(Cleanup);
    }
    
    mCurrentState = gStates[state];
}

void State::SomeObject::execute()
{
    if (mCurrentState != nullptr)
    {
        mCurrentState->doWork();
    }
}
