//
//  Interpreter.hpp
//  DesignPatterns
//
//  Created by Anatoliy Goodz on 1/23/17.
//  Copyright © 2017 Anatoliy Goodz. All rights reserved.
//

#ifndef Interpreter_hpp
#define Interpreter_hpp

#include <string>
#include <memory>

namespace Interpreter
{
    class Expression
    {
        public:
        
        virtual ~Expression();
        
        virtual bool interpret(const std::string& context) = 0;
    };
    
    class TerminalExpression : public Expression
    {
        public:
        
        TerminalExpression(const std::string& data);
        
        virtual bool interpret(const std::string& context);
        
        private:
        
        std::string mData;
    };
    
    class BinExpression : public Expression
    {
        public:
        
        BinExpression(std::shared_ptr<Expression> left, std::shared_ptr<Expression> right);
        
        protected:
        
        std::shared_ptr<Expression> mLeft;
        std::shared_ptr<Expression> mRight;
    };

    class OrExpression : public BinExpression
    {
        public:
        
        OrExpression(std::shared_ptr<Expression> left, std::shared_ptr<Expression> right);
        
        virtual bool interpret(const std::string& context);
    };
    
    class AndExpression : public BinExpression
    {
        public:
        
        AndExpression(std::shared_ptr<Expression> left, std::shared_ptr<Expression> right);
        
        virtual bool interpret(const std::string& context);
    };
}

#endif /* Interpreter_hpp */
