//
//  Memento.hpp
//  DesignPatterns
//
//  Created by tolik7071 on 2/17/17.
//  Copyright © 2017 Anatoliy Goodz. All rights reserved.
//

#ifndef Memento_hpp
#define Memento_hpp

#include <string>
#include <memory>

namespace Memento
{
    class TextEditor
    {
        public:
        
        class RestorePoint
        {
            friend class TextEditor;
            
            public:
            
            ~RestorePoint();
            
            private:
            
            RestorePoint();
            
            void setText(const std::string& text);
            const std::string& text() const;
            
            std::string mText;
        };
        
        void setText(const std::string& text);
        const std::string& text() const;
        
        std::shared_ptr<RestorePoint> createRestorePoint() const;
        void applyRestorePoint(std::shared_ptr<RestorePoint> restorePoint);
        
        private:
        
        std::string mText;
    };
}

#endif /* Memento_hpp */
