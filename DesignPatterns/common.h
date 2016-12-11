//
//  common.h
//  DesignPatterns
//
//  Created by Anatoliy Goodz on 11/10/16.
//  Copyright © 2016 Anatoliy Goodz. All rights reserved.
//

#ifndef common_h
#define common_h

#if defined(__cplusplus)

#include <iostream>

#define LOG_FUNCTION() \
{ \
    std::cout << __FUNCTION__ << std::endl; \
}

#endif // __cplusplus

#endif /* common_h */
