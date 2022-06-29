/**
 * @file examples.cc
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-06-24
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <injects/injects.hh>
#include <iostream>
#include <string>
#include <sstream>

using namespace Injects;


class ClassB
{
public:
    INJECT_CONSTRUCTOR(ClassB, 0)
    {
        std::cout << "Construct ClassB" << std::endl;
    }
    ~ClassB(void)
    {
        std::cout << "Destruct ClassB" << std::endl;
    }
};

class ClassC
{
public:
    INJECT_CONSTRUCTOR(ClassC, 0)
    {
        std::cout << "Construct ClassC" << std::endl;
    }
    ~ClassC(void)
    {
        std::cout << "Destruct ClassC" << std::endl;
    }
};

class ClassA
{
public:
    INJECT_CONSTRUCTOR(ClassA, 0, ClassB, ClassC)
    {
        std::cout << "Construct ClassA" << std::endl;
    }
    ~ClassA(void)
    {
        std::cout << "Destruct ClassA" << std::endl;
    }
};

class ClassD
{
public:
    PROVIDES_CONSTRUCTOR(ClassD, 0, ClassB, ClassC)
    {
        std::cout << "Construct ClassD" << std::endl;
    }
    ~ClassD(void)
    {
        std::cout << "Destruct ClassD" << std::endl;
    }
};

class ClassE
{
public:
    PROVIDES_CONSTRUCTOR(ClassE, 0, ClassA, ClassD)
    {
        std::cout << "Construct ClassE" << std::endl;
    }
    ~ClassE(void)
    {
        std::cout << "Destruct ClassE" << std::endl;
    }
};

class ClassF
{
public:
    INJECT_CONSTRUCTOR(ClassF, 0, ClassA, ClassD)
    {
        std::cout << "Construct ClassF" << std::endl;
    }
    ~ClassF(void)
    {
        std::cout << "Destruct ClassF" << std::endl;
    }
};

class ClassG
{
public:
    INJECT_CONSTRUCTOR(ClassG, 0, ClassA, ClassD)
    {
        std::cout << "Construct ClassG" << std::endl;
    }
    ~ClassG(void)
    {
        std::cout << "Destruct ClassG" << std::endl;
    }
};

class ClassH
{
public:
    PROVIDES_CONSTRUCTOR(ClassH, Attribute::SINGLETON)
    {
        std::cout << "Construct ClassH" << std::endl;
    }
    ~ClassH(void)
    {
        std::cout << "Destruct ClassH" << std::endl;
    }
};
class ClassI
{
public:
    PROVIDES_CONSTRUCTOR(ClassI, Attribute::SINGLE)
    {
        std::cout << "Construct ClassI" << std::endl;
    }
    ~ClassI(void)
    {
        std::cout << "Destruct ClassI" << std::endl;
    }
    void do_something(void)
    {
        std::cout << "ClassI Do something" << std::endl;
    }
};

COMPONENT_CLASS(ClassComponent, ClassA, ClassE);
COMPONENT_CLASS(ClassComponent2, ClassF, ClassG, ClassH, ClassI);

class ClassJ
{
public:
    INJECT_CONSTRUCTOR(ClassJ, 0) {}
    std::string description(void)
    {
        return "ClassJ";
    }
};

class ClassK
{
public:
    INJECT_CONSTRUCTOR(ClassK, 0) {}
    std::string description(void)
    {
        return "ClassK";
    }
};

class ClassL
{
private:
    INJECT_PARAM_TYPE(ClassJ) m_j;
    INJECT_PARAM_TYPE(ClassK) m_k;
public:
    INJECT_CONSTRUCTOR(ClassL, 0, ClassJ, ClassK):
        m_j(INJECT_PARAM(ClassJ)), m_k(INJECT_PARAM(ClassK))
    {}
    std::string description(void)
    {
        std::stringstream ss;
        ss << "ClassL[" << m_j->description() << ", " << m_k->description() << "]";
        return ss.str();
    }
};

int main(int argc, char * argv[])
{
    {
        SP<ClassA> a1 = ClassComponent::get_ClassA();
    }
    SP<ClassA> a2 = ClassComponent::get_ClassA();
    SP<ClassA> a3 = ClassComponent::get_ClassA();
    SP<ClassE> e1 = ClassComponent::get_ClassE();
    SP<ClassE> e2 = ClassComponent::get_ClassE();
    SP<ClassF> f1 = ClassComponent2::get_ClassF();
    SP<ClassG> f2 = ClassComponent2::get_ClassG();
    SP<ClassH> h1 = ClassComponent2::get_ClassH();
    SP<ClassH> h2 = ClassComponent2::get_ClassH();
    SP<ClassI> i1 = ClassComponent2::get_ClassI();
    SP<ClassI> i2 = ClassComponent2::get_ClassI();

    Provider<ClassI> i3;
    i3.get()->do_something();
    Provider<ClassL> l1;
    std::cout << l1.get()->description() << std::endl;

    return 0;
}
