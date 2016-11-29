//
//  main.cpp
//  DesignPatterns
//
//  Created by Anatoliy Goodz on 11/5/16.
//  Copyright © 2016 Anatoliy Goodz. All rights reserved.
//

#include <iostream>
#include <memory>
#include "AbstractFactory.hpp"
#include "Builder.hpp"
#include "AbstractMethod.hpp"
#include "Prototype.hpp"
#include "Singleton.hpp"
#include "Adapter.hpp"
#include "Bridge.hpp"

int main(int argc, const char * argv[])
{
    {
        using namespace AbstractFactory;
        
        ObjectTypeSelector selector;
        
        const IAbstractFactory &factory1 = GetFactory(selector);
        
        IShape *triangle = factory1.CreateShape(ShapeType::Triangle);
        triangle->Draw();
        
        factory1.ReleaseShape(triangle);
        triangle = NULL;
        
        selector.setType(AbstractFactory::ObjectType::Thick);
        const IAbstractFactory &factory2 = GetFactory(selector);
        ICircle *circle = static_cast<ICircle *>(factory2.CreateShape(ShapeType::Circle));
        circle->Draw();
        
        factory2.ReleaseShape(circle);
        circle = NULL;
    }
    
    {
        using namespace Builder;
        
        Waiter waiter(new PizzaBuilder1());
        waiter.preparePizza();
    }
    
    {
        using namespace AbstractMethod;
        
        MyApplication app;
        
        Document *document = app.CreateDocument("Document #1");
        app.CreateDocument("Document #2");
        
        document->Open();
        
        document = app.GetDocument(1);
        document->Open();
    }
    
    {
        class A
        {
            public:
            
            A() { std::cout << __PRETTY_FUNCTION__ << ": " << (const void *)this << std::endl; }
            ~A() { std::cout << __PRETTY_FUNCTION__ << ": " << (const void *)this << std::endl; }
        };
     
        /* ********************************************* */
        
        A *a = new A();
        
        std::shared_ptr<A> shared1(a);
        std::shared_ptr<A> shared2 = shared1;
        
        std::cout << "USE COUNT: " << shared2.use_count() << std::endl;
        
        /* ********************************************* */
        
        a = new A();
        
        std::unique_ptr<A> unique(a);
        
        std::unique_ptr<A> unique1 = std::move(unique);
        std::cout << "UNIQUE: " <<  unique.get() <<std::endl;
        std::cout << "UNIQUE1: " <<  unique1.get() <<std::endl;
        
        unique = std::move(unique1);
        std::cout << "UNIQUE: " <<  unique.get() <<std::endl;
        std::cout << "UNIQUE1: " <<  unique1.get() <<std::endl;
        
        /* ********************************************* */
        
        std::shared_ptr<A> shared3 = std::make_shared<A>();
        shared3.reset(new A());
        std::shared_ptr<A> shared4 = shared3;
        
        std::weak_ptr<A> weak(shared3);
        std::cout << "USE COUNT: " << shared3.use_count() << std::endl;
        
        if (std::shared_ptr<A> shared = weak.lock())
        {
            std::cout << "USE COUNT: " << shared3.use_count() << std::endl;
        }
        
        shared4.reset();
        shared3.reset();
        
        if (std::shared_ptr<A> shared = weak.lock())
        {
            std::cout << "USE COUNT: " << shared3.use_count() << std::endl;
        }
        else
        {
            std::cout << "Cannot lock pointer!" << std::endl;
        }
    }
    
    {
        using namespace Prototype;
        
        const IPerson *person = MakePerson();
        std::cout << person->firstName() << ", " << person->lastName() << std::endl;
        
        IPerson *clone = dynamic_cast<IPerson *>(person->clone());
        std::cout << clone->firstName() << ", " << clone->lastName() << std::endl;
        
        DeletePerson(person);
        DeletePerson(clone);
    }
    
    {
        using namespace Singleton;
        
        const Display& display = Display::GetSharedInstance();
        std::cout << display.height() << "x" << display.width() << std::endl;
    }
    
    {
        using namespace Adapter;
        
        Drawer drawer;
        
        drawer.mShapes.push_back(new Line);
        drawer.mShapes.push_back(new Polyline);
        drawer.mShapes.push_back(new Text);
        
        drawer.mShapes.push_back(new NewTextViewAdapter(std::unique_ptr<NewTextView>(new NewTextView())));
        
        drawer.DrawShapes();
    }
    
    {
        using namespace Bridge;
        
        GraphicSystem gs(std::unique_ptr<WindowManagerBase>(new WindowManagerUbuntuOS()));
        
        gs.mWindowsManager->createWindow("WOW!");
        gs.mWindowsManager->createWindow("Test");
        gs.mWindowsManager->createWindow("utility");
        
        gs.mWindowsManager->ProcessWindows();
    }
    
    return 0;
}
