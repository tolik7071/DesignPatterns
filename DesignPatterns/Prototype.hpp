//
//  Prototype.hpp
//  DesignPatterns
//
//  Created by Anatoliy Goodz on 11/15/16.
//  Copyright © 2016 Anatoliy Goodz. All rights reserved.
//

#ifndef Prototype_hpp
#define Prototype_hpp

#include <string>

namespace Prototype
{
    class ICloneable
    {
        public:
        
        virtual ICloneable* clone() const = 0;
    };
    
    class IPerson : public ICloneable
    {
        public:
        
        virtual const std::string& firstName() const = 0;
        virtual const std::string& lastName() const = 0;
    };
    
    const IPerson* MakePerson();
    void DeletePerson(const IPerson* person);
    
}

#endif /* Prototype_hpp */
