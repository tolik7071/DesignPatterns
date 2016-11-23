//
//  Singleton.hpp
//  DesignPatterns
//
//  Created by Anatoliy Goodz on 11/19/16.
//  Copyright © 2016 Anatoliy Goodz. All rights reserved.
//

#ifndef Singleton_hpp
#define Singleton_hpp

#include <string>

namespace Singleton
{
    class Display
    {
        public:
        
        unsigned int width() const;
        unsigned int height() const;
        
        static const Display& GetSharedInstance();
        
        protected:
        
        static void CleanUp();
        
        Display() {}
        ~Display() {}
    };
}

#endif /* Singleton_hpp */
