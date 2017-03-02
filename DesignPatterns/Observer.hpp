//
//  Observer.hpp
//  DesignPatterns
//
//  Created by tolik7071 on 2/25/17.
//  Copyright © 2017 Anatoliy Goodz. All rights reserved.
//

#ifndef Observer_hpp
#define Observer_hpp

#include <memory>
#include <vector>
#include <string>
#include <map>

namespace Observer
{
    struct IChangesObserver
    {
        virtual void didChanged(const std::string& property) = 0;
    };
    
    struct IPropertyChangeObserving
    {
        void addObserver(std::shared_ptr<IChangesObserver> observer, const std::string& property);
        void removeObserver(std::shared_ptr<IChangesObserver> observer, const std::string& property);
        
        protected:
        
        typedef std::vector<std::shared_ptr<IChangesObserver> > TObservers;
        TObservers findObservers(const std::string& property);
        
        private:
        
        typedef std::map<std::string, std::vector<std::shared_ptr<IChangesObserver> > > TObserversMap;
        TObserversMap mObservers;
    };
    
    class TextEditor : public IPropertyChangeObserving
    {
        public:
        
        const std::string& text() const;
        void setText(const std::string& text);
        
        private:
        
        std::string mText;
    };
}

#endif /* Observer_hpp */
