//
//  Iterator.hpp
//  DesignPatterns
//
//  Created by Anatoliy Goodz on 1/28/17.
//  Copyright © 2017 Anatoliy Goodz. All rights reserved.
//

#ifndef Iterator_hpp
#define Iterator_hpp

#include <stddef.h>
#include <stdexcept>
#include <string>
#include <initializer_list>
#include "common.h"

namespace Iterator
{
    template <typename Type, size_t Size>
    class SimpleArray
    {
        public:
        
        typedef Type value_type;
        typedef value_type& reference;
        typedef const value_type& const_reference;
        typedef size_t size_type;
        typedef value_type* iterator;
        typedef const value_type* const_iterator;
        
        public:
        
        value_type mElements[(Size > 0) ? Size : 1];
        
        public:
        
        inline value_type* data() { return mElements; }
        inline const value_type* data() const { return mElements; }
        
        reference first() { return mElements[0]; }
        reference last() { return mElements[(Size > 0) ? (Size - 1) : 0]; }
        
        reference operator[](size_type index) { return mElements[index]; }
        const_reference operator[](size_type index) const { return mElements[index]; }
        
        const_reference at(size_type index) const
        {
            if (index >= Size)
            {
                std::string description(__FUNCTION_NAME__);
                description += ": ";
                description += std::to_string(index);
                description += " - wrong value for index.";
                throw std::out_of_range(description);
            }
            
            return mElements[index];
        }
        
        size_type size() const { return Size; }
        bool empty() const { return Size == 0; }
        
        iterator begin() { return iterator(mElements); }
        const_iterator begin() const { return const_iterator(mElements); }
        iterator end() { return iterator(mElements + Size); }
        const_iterator end() const { return const_iterator(mElements + Size); }
    };
    
    template <size_t Size>
    class StringArrayAdapter : public SimpleArray<std::string, Size>
    {
        public:
        
        template<typename... T>
        StringArrayAdapter(const T... args)
        {
            size_t index = 0;
            
			std::initializer_list<std::string> arguments = { args... };
			std::initializer_list<std::string>::iterator it = arguments.begin();
			for (; it != arguments.end(); ++it)
            {
                this->operator[] (index++) = *it;
            }
        }
        
        typename SimpleArray<std::string, Size>::value_type* next()
        {
            typename SimpleArray<std::string, Size>::value_type* result = nullptr;
            
            if (mCurrent == nullptr)
            {
                mCurrent = this->begin();
            }
            
            if (mCurrent != this->end())
            {
                result = mCurrent;
                mCurrent++;
            }
            
            return result;
        }
        
        void reset()
        {
            mCurrent = this->begin();
        }
        
        private:
        
        typename SimpleArray<std::string, Size>::value_type* mCurrent = nullptr;
    };
}

#endif /* Iterator_hpp */
