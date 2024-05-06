#include <iostream>
#include <string>
#include <string_view>
#include <format>

class Printable{
    public:
        // a class that has at least one pure virtual function is a abstract class (can't instantiate an abstract class and has to be derived)  
        virtual void print() const =0;
        //! the destructor has to be virtual in a base class that gets inherited to be sure to call all derived destructors 
        virtual ~Printable() {}
};

// if the Derived class of an abstract class doesn't implement/override the virtual function it is a abstract class itself
class Tiger: public Printable{
    public:
        Tiger(std::string_view race): m_race{race}{}
        // not implementing pure virtual function print() from Printable makes this class abstract
    private:
        std::string m_race{};
};

class Person: public Printable{
    public:
        Person(std::string_view name): m_name{name}{}
        void print() const override {
            std::cout << std::format("Person {{ name: {} }}",m_name) << std::endl;
        }
       
    private:
        std::string m_name{};
};


class SpecialNumber: public Printable{
    public:
        SpecialNumber(int number): m_number{number}{}
        void print() const override {
            std::cout << std::format("Special Number {{ value: {} }}", m_number) << std::endl;
        }
        
    private:
        int m_number{};
};

void print(const Printable&);

int main (){

    //Tiger t{"siberian"}; //! doesn't work because Tiger did not override the pure virtual function and is abstract itself
    Person p {"simon"};
    SpecialNumber s{7};

    print(p);
    print(s);

    return 0;
}

void print(const Printable& p){
    p.print();
}