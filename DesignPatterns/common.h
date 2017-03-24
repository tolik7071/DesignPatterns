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

#if defined(__GNUC__)
#define __FUNCTION_NAME__ __PRETTY_FUNCTION__
#else
#define __FUNCTION_NAME__ __FUNCTION__
#endif

#define LOG_FUNCTION()                           \
{                                                \
    std::cout << __FUNCTION_NAME__ << std::endl; \
}

#define LOG_METHOD()															  \
{																				  \
    std::cout << __FUNCTION_NAME__ << "\t" << std::addressof(*this) << std::endl; \
}

#endif // __cplusplus

#endif /* common_h */
