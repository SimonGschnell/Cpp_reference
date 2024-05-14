#include <iostream>

//! its best practice to make every constructor that accepts a single argument explicit by default. implicit conversations from other types would be allowed otherwise

class Person{
    private:
        std::string m_name{};
        int m_age{};
    public:
        //? by default all constructors classify as converting constructors
        //* in this case a std::string_view can be implicitly converted to a Person because the age parameter has a default value
        Person(std::string_view name, int age=20): m_name{name}, m_age{age}{}

        //! explicit constructor are no longer converting constructors and cannot be used to implicitly create a Person object from other types
        explicit Person(int age , std::string_view name ="test" ): m_name{name}, m_age{age}{}

        const std::string& get_name() const { return m_name;}
};


void print_person(const Person& p){
    std::cout << p.get_name() << std::endl;
}


int main(){
    using namespace std::literals;

    //? here we are implicitly converting a std::string_view to a Person
    print_person("simon"sv);

    //! we can prevent implicit conversions to objects using explicit constructors
    //* explicit constructors cannot be used for 
    //* - implicit conversions
    //* - copy list initialization
    //* - copy initialization
    //? BUT they can be used for
    //? - direct initialization
    //? - direct list initialization
    // print_person(10); //! because the int->Person constructor was declared explicit, it is no longer possible to implicitly convert from int to Person
    // Person p = {10}; //! throws error, copy list initialization
    Person p{10}; // direct initialization
    Person p2(10); // direct list initialization

    //! the line below throws a compiler error because the compiler can't explicitly convert more than once
    // print_person("simon"); //? first implicit conversion from C like string to std::string_view and second implicit conversion from std::string_view to Person
    


    return 0;
}