//
//  Prototype.cpp
//  DesignPatterns
//
//  Created by Anatoliy Goodz on 11/15/16.
//  Copyright © 2016 Anatoliy Goodz. All rights reserved.
//

#include "Prototype.hpp"
#include "common.h"

using namespace Prototype;

class RealPerson : public IPerson
{
    public:
    
    RealPerson(const std::string& firstName, const std::string& lastName)
        : mFirstName(firstName)
        , mLastName(lastName)
    {
        LOG_FUNCTION();
    }
    
    virtual ~RealPerson()
    {
        LOG_FUNCTION();
    }
    
    public:
    
    virtual ICloneable* clone() const
    {
        ICloneable *result = new RealPerson(mFirstName, mLastName);
        return result;
    }
    
    public:
    
    virtual const std::string& firstName() const
    {
        return mFirstName;
    }
    
    virtual const std::string& lastName() const
    {
        return mLastName;
    }
    
    private:
    
    std::string mFirstName;
    std::string mLastName;
};

const Prototype::IPerson* Prototype::MakePerson()
{
    return static_cast<IPerson *>(new RealPerson("Jonh", "Smith"));
}

void Prototype::DeletePerson(const Prototype::IPerson* person)
{
    const RealPerson* realPerson = static_cast<const RealPerson*>(person);
    delete realPerson;
}
