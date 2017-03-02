//
//  main.cpp
//  DesignPatterns
//
//  Created by Anatoliy Goodz on 11/5/16.
//  Copyright © 2016 Anatoliy Goodz. All rights reserved.
//


#if defined(_MSC_VER)
#include "stdafx.h"
#endif // _MSC_VER
#include <iostream>
#include <memory>
#include <string>
#include <math.h>
#include <assert.h>
#include <thread>
#include <ctime>
#include "AbstractFactory.hpp"
#include "Builder.hpp"
#include "AbstractMethod.hpp"
#include "Prototype.hpp"
#include "Singleton.hpp"
#include "Adapter.hpp"
#include "Bridge.hpp"
#include "Composite.hpp"
#include "Decorator.hpp"
#include "Facade.hpp"
#include "Flyweight.hpp"
#include "Proxy.hpp"
#include "ChainOfResponsibility.hpp"
#include "Command.hpp"
#include "Interpreter.hpp"
#include "Iterator.hpp"
#include "Mediator.hpp"
#include "Memento.hpp"
#include "Observer.hpp"

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
        // TODO
        
        class A
        {
            public:
            
            A() { std::cout << __FUNCTION__ << ": " << (const void *)this << std::endl; }
            ~A() { std::cout << __FUNCTION__ << ": " << (const void *)this << std::endl; }
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
        
        GraphicSystem gs(std::unique_ptr<IWindowManager>(new UbuntuManager()));
        gs.mWindowsManager->createWindow("First Window");
        gs.mWindowsManager->createWindow("Second Window");
        gs.mWindowsManager->ProcessWindows();
        
        gs.mWindowsManager = std::move(std::unique_ptr<IWindowManager>(new WindowsManager()));
        gs.mWindowsManager->createWindow("First Window");
        gs.mWindowsManager->createWindow("Second Window");
        gs.mWindowsManager->ProcessWindows();
    }
    
    {
        using namespace Composite;
        
        std::shared_ptr<Composite::Graphic> line1(new Composite::Line());
        std::shared_ptr<Composite::Graphic> line2(new Composite::Line());
        std::shared_ptr<Composite::Graphic> rect1(new Composite::Rectangle());
        std::shared_ptr<Composite::Graphic> rect2(new Composite::Rectangle());
        std::shared_ptr<Composite::Graphic> rect3(new Composite::Rectangle());
        
        std::shared_ptr<Composite::Graphic> picture1(new Composite::Picture());
        picture1->add(line1);
        picture1->add(rect2);
        picture1->add(rect3);
        picture1->Draw();
        
        std::shared_ptr<Composite::Graphic> picture2(new Composite::Picture());
        picture2->add(rect2);
        picture2->add(picture1);
        picture2->Draw();
        
        try
        {
            line1->childAtIndex(0);
        }
        catch (std::exception& ex)
        {
            std::cout << "Ops!" << ex.what() << std::endl;
        }
    }
    
    {
        using namespace Decorator;
        
        std::shared_ptr<TextView> textView(new TextView());
        
        std::shared_ptr<ScrollDecorator> scrollView(new ScrollDecorator());
        scrollView->setWrappedObject(textView);
        scrollView->draw();
        
        std::shared_ptr<BorderDecorator> borderDecorator(new BorderDecorator());
        borderDecorator->setWrappedObject(textView);
        borderDecorator->draw();
    }
    
    {
        using namespace Facade;
        
        Desktop desktop;
        desktop.create();
        desktop.Draw();
    }
    
    {
        using namespace Flyweight;
        
        PrimitiveFactory factory;
        std::shared_ptr<Picture> picture = factory.createPicture();
        picture->addChild(factory.createPoint());
        picture->addChild(factory.createCircle(10));
        picture->addChild(factory.createSquare(5, 22));
        picture->addChild(factory.createSquare(11, 22));
        picture->addChild(factory.createSquare(5, 22));
        picture->addChild(factory.createPoint());
        
        Context context(15, 10, 0x445522);
        picture->draw(context);
    }
    
    {
        using namespace Proxy;
        
        Editor editor;
        
        editor.addImage(std::shared_ptr<ImageProxy>(new ImageProxy()));
        editor.addImage(std::shared_ptr<ImageProxy>(new ImageProxy()));
        
        std::shared_ptr<ImageProxy> imageProxy(new ImageProxy());
        editor.addImage(imageProxy);
        imageProxy->image()->setIsLoaded(true);
        
        editor.addImage(std::shared_ptr<ImageProxy>(new ImageProxy()));
        
        editor.ProcessImages();
    }
    
    {
        using namespace ChainOfResponsibility;
        
        ChainOfResponsibility::Window window;
        window.createControls();
        
        std::cout << window.findHelp() << std::endl;
    }
    
    {
        using namespace Command;
        
        Application& app = Application::GetSharedInstance();
        
        app.menu()->createDocument();
        app.menu()->createDocument();
        app.menu()->createDocument();
        app.menu()->deleteDocument();
        app.menu()->createDocument();
        app.deleteCurrentDocument();
    }
    
    {
        using namespace Interpreter;
        
        std::shared_ptr<Expression> red(new TerminalExpression("red"));
        std::shared_ptr<Expression> green(new TerminalExpression("green"));
        
        std::shared_ptr<Expression> redOrGreen(new OrExpression(red, green));
        std::cout << std::boolalpha << redOrGreen->interpret("red") << std::endl;
        std::cout << std::boolalpha << redOrGreen->interpret("blue") << std::endl;
        
        std::shared_ptr<Expression> redAndGreen(new AndExpression(red, green));
        std::cout << std::boolalpha << redOrGreen->interpret("red green blue") << std::endl;
    }
    
    {
        using namespace Iterator;
        
        typedef SimpleArray<int, 5> TIntArray;
        TIntArray data = { 66, 15, -1, 0, -5 };
        
        std::cout << data.first() << std::endl;
        std::cout << data.last() << std::endl;
        
        for (int i = 0; i < data.size(); ++i)
        {
            std::cout << data.at(i) << std::endl;
        }
        
        try
        {
            std::cout << data.at(100) << std::endl;
        }
        catch (std::exception& e)
        {
            std::cout << e.what() << std::endl;
        }
        
        std::sort(data.begin(), data.end());
        
        std::for_each(data.begin(), data.end(),
            [](typename TIntArray::value_type element)
            {
                std::cout << element << std::endl;
            }
        );
        
        SimpleArray<int, 0> empty = {};
        std::cout << empty.first() << std::endl;
        std::cout << empty.last() << std::endl;
        std::cout << std::boolalpha << empty.empty() << std::endl;
        
        SimpleArray<std::string, 3> strings = { "1", "2", "3" };
        
        std::for_each(strings.begin(), strings.end(),
            [](typename SimpleArray<std::string, 3>::value_type element)
            {
                std::cout << element << std::endl;
            }
        );
        
        StringArrayAdapter<3> strings2 = { "10", "20", "30" };
        const std::string* str = nullptr;
        while (nullptr != (str = strings2.next()))
        {
            std::cout << *str << std::endl;
        }
    }
    
    {
        using namespace Mediator;
        
        DialogDirector& director = DialogDirector::GetSharedDirector();
        director.createWidgets();
        
        director.listBox()->setColor(Mediator::ListBox::kGreen);
        assert(director.colorBox()->fillColor() == Mediator::ListBox::kGreen);
    }
    
    {
        using namespace Memento;
        
        TextEditor editor;
        editor.setText("Test string");
        assert(editor.text() == "Test string");
        
        std::shared_ptr<TextEditor::RestorePoint> restorePoint = editor.createRestorePoint();
        
        editor.setText("Test string 2");
        assert(editor.text() == "Test string 2");
        
        editor.applyRestorePoint(restorePoint);
        assert(editor.text() == "Test string");
    }
    
    {
        // TODO
        
        typedef std::chrono::high_resolution_clock TClock;
        
        TClock::time_point start = TClock::now();
        
        for (int i = 0; i < 5; i++)
        {
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
        
        TClock::time_point end = TClock::now();
        
        TClock::duration elapsed = end - start;
        std::cout << "Elapsed " << elapsed.count() << " nanoseconds" << std::endl;
        std::cout << "Elapsed " << std::chrono::duration_cast<std::chrono::seconds>(elapsed).count() << " seconds" << std::endl;
        
        /* ********** */
        
        typedef std::chrono::system_clock TSystemClock;
        
        std::time_t now = TSystemClock::to_time_t(TSystemClock::now());
        std::cout << std::asctime(std::localtime(&now)) << std::endl;
    }
    
    {
        // TODO
        
        typedef std::map<std::string, std::vector<int> > TDataMap;
        TDataMap data;
        
        TDataMap::mapped_type& values = data["1"];
        if (values.size() == 0)
        {
            data["1"] = {1, -5, 0, 7};
        }
        
        for (const auto& pair : data)
        {
            std::cout << pair.first << ":" << std::endl;
            for (const auto& value : pair.second)
            {
                std::cout << "\t" << value << std::endl;
            }
        }
    }
    
    {
        // TODO
        
        struct SomeData
        {
            int mData = 0;
            
            static void Foo() { LOG_FUNCTION(); }
            
            int data() const { return mData; }
            void setData(int value) { mData = value; }
        };
        
        std::function<void()> callFoo = &SomeData::Foo;
        callFoo();
        
        SomeData data;
        
        std::function<int(const SomeData&)> getter = &SomeData::data;
        int result = getter(data);
        assert(result == 0);
        
        std::function<void(SomeData&, int)> setter = &SomeData::setData;
        setter(data, 11);
        result = getter(data);
        assert(result == 11);
    }
    
    {
        using namespace Observer;
        
        class Observer : public IChangesObserver
        {
            public:
            
            virtual void didChanged(const std::string& property)
            {
                std::cout << (void *)(this) << ": Property \'" << property << "\' " << "has been changed" << std::endl;
            }
        };
        
        std::shared_ptr<IChangesObserver> observer1(new Observer());
        std::shared_ptr<IChangesObserver> observer2(new Observer());
        std::shared_ptr<IChangesObserver> observer3(new Observer());
        
        TextEditor editor;
        editor.setText("This is a simple string.");
        
        editor.addObserver(observer1, "text");
        editor.addObserver(observer2, "text");
        
        editor.setText("");
        
        editor.removeObserver(observer1, "text");
        editor.removeObserver(observer2, "text");
        
        editor.setText("12345");
        
        editor.addObserver(observer3, "text");
        editor.addObserver(std::shared_ptr<IChangesObserver>(), "text");
        
        editor.setText("00000");
    }
    
    return 0;
}
