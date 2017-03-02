//
//  Observer.cpp
//  DesignPatterns
//
//  Created by tolik7071 on 2/25/17.
//  Copyright © 2017 Anatoliy Goodz. All rights reserved.
//

#if defined(_MSC_VER)
#include "stdafx.h"
#endif // _MSC_VER
#include "Observer.hpp"

using namespace Observer;

const std::string& Observer::TextEditor::text() const
{
    return mText;
}

void Observer::TextEditor::setText(const std::string& text)
{
    mText = text;
    
    TObservers observers = findObservers("text");
    std::for_each(observers.begin(), observers.end(),
                  [](TObservers::reference observer)
        {
            observer->didChanged("text");
        }
    );
}

void Observer::IPropertyChangeObserving::addObserver(
    std::shared_ptr<IChangesObserver> observer,
    const std::string& property)
{
    if (observer.get() != nullptr)
    {
        mObservers[property].push_back(observer);
    }
}

void Observer::IPropertyChangeObserving::removeObserver(
    std::shared_ptr<IChangesObserver> observer,
    const std::string& property)
{
    TObserversMap::mapped_type& observers = mObservers[property];
    if (observers.size() != 0)
    {
        TObserversMap::mapped_type::iterator it = std::find(observers.begin(), observers.end(), observer);
        if (it != observers.end())
        {
            observers.erase(it);
        }
    }
}

Observer::IPropertyChangeObserving::TObservers
    Observer::IPropertyChangeObserving::findObservers(const std::string& property)
{
    TObservers observer = mObservers[property];
    return observer;
}
