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
#include <algorithm>
#include <array>
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
#include "State.hpp"
#include "Strategy.hpp"
#include "TemplateMethod.hpp"
#include "Visitor.hpp"

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
        
        for (size_t i = 0; i < data.size(); ++i)
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
        
        editor.removeObserver(observer3, "text");
        editor.removeObserver(std::shared_ptr<IChangesObserver>(), "text");
    }
    
    {
        using namespace State;
        
        SomeObject obj;
        
        obj.execute();
        
        obj.setState(State::SomeObject::StateID::kState2);
        obj.execute();
        
        obj.setState(State::SomeObject::StateID::kState1);
        obj.execute();
        
        obj.setState(State::SomeObject::StateID::kState2);
        obj.execute();
    }

	{
		using namespace Strategy;

		typedef Data<int> TIntData;
		TIntData data(11, 44);

		TIntData::Result result = data.calculate();
		assert(result == 0);

		data.operation = std::make_shared<OperationPlus<TIntData::Result> >(OperationPlus<TIntData::Result>());
		result = data.calculate();
		assert(result == 55);

		data.operation = std::make_shared<OperationMinus<TIntData::Result> >(OperationMinus<TIntData::Result>());
		result = data.calculate();
		assert(result == -33);
	}
    
    {
        using namespace TemplateMethod;
        
        std::array<std::shared_ptr<CaffeinBeverage>, 2> beverages =
        {
            std::make_shared<Tea>(Tea()),
            std::make_shared<Coffee>(Coffee())
        };
        
        std::for_each(beverages.begin(), beverages.end(),
            [](std::shared_ptr<CaffeinBeverage> beverage)
            {
                beverage->prepareRecipe();
            }
        );
    }
    
    {
        using namespace VisitorTest;
        
        ElementsContainer container;
        
        container.mVisitor = std::make_shared<RealVisitor>(RealVisitor());
        
        container.mElements.push_back(std::make_shared<ElementA>(ElementA()));
        container.mElements.push_back(std::make_shared<ElementB>(ElementB()));
        container.mElements.push_back(std::make_shared<ElementA>(ElementA()));
        
        CompositeElement composite;
        composite.mElemenets.push_back(std::make_shared<ElementA>(ElementA()));
        composite.mElemenets.push_back(std::make_shared<ElementB>(ElementB()));
        container.mElements.push_back(std::make_shared<CompositeElement>(composite));
        
        container.inspectElements();
    }
    
    return 0;
}
