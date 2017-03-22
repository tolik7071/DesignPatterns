//
//  Visitor.hpp
//  DesignPatterns
//
//  Created by tolik7071 on 3/21/17.
//  Copyright © 2017 Anatoliy Goodz. All rights reserved.
//

#ifndef Visitor_hpp
#define Visitor_hpp

#include <vector>
#include <memory>

namespace VisitorTest
{
    struct IVisitor;
    
    struct IElement
    {
        virtual void accept(const IVisitor& visitor) const = 0;
    };
    
    struct ElementA : public IElement
    {
        ElementA();
        virtual ~ElementA();
        virtual void accept(const IVisitor& visitor) const;
    };
    
    struct ElementB : public IElement
    {
        ElementB();
        virtual ~ElementB();
        virtual void accept(const IVisitor& visitor) const;
    };
    
    struct CompositeElement : public IElement
    {
        CompositeElement();
        virtual ~CompositeElement();
        
        virtual void accept(const IVisitor& visitor) const;
        
        typedef std::vector<std::shared_ptr<IElement> > TElemenets;
        TElemenets mElemenets;
    };
    
    struct IVisitor
    {
        virtual void visit(const ElementA& element) const = 0;
        virtual void visit(const ElementB& element) const = 0;
        virtual void visit(const CompositeElement& element) const = 0;
    };
    
    struct RealVisitor : public IVisitor
    {
        virtual void visit(const ElementA& element) const;
        virtual void visit(const ElementB& element) const;
        virtual void visit(const CompositeElement& element) const;
    };
    
    struct ElementsContainer
    {
        std::shared_ptr<IVisitor> mVisitor;
        std::vector<std::shared_ptr<IElement> > mElements;
        
        void inspectElements();
    };
}

#endif /* Visitor_hpp */
