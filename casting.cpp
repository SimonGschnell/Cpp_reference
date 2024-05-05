#include <iostream>
#include <string>
#include <bit>
#include <typeinfo>

// type casting is used to convert one data type to another
//? c++ has 4 main types of casting 
// - static_cast (compile-time, used for conversions that are considered safe by the compiler)
// - dynamic_cast (run-time, does run-time checks to verify if the conversion was successful)
// - const_cast
// - reinterpret_cast / bit_cast
//! std::bit_cast available in c++20

class Base{
    public:
        Base(int value): m_value{value}{}
        void print_value(){
            std::cout << "this is the value: " << m_value << '\n';
        }
        virtual ~Base(){}
    private:
        int m_value{};
};

class Derived: public Base{
    public:
        Derived(int base_value, int derived_value): Base{base_value}, m_derived_value{derived_value}{}
    
        int getDerivedValue() const {
            return m_derived_value;
        }
    private:
        int m_derived_value{};
};

class OtherDerived: public Base{
    public:
        OtherDerived(int base_value, std::string derived_value): Base{base_value}, m_derived_value{derived_value}{}
    
        std::string getDerivedValue() const {
            return m_derived_value;
        }
    private:
        std::string m_derived_value{};
};

int main(){

    // static cast examples:
    //-------------------------------------------------------------------------------------------------------------------------

    // casting int to double (upcast)
    int int_number{5};
    double double_number{static_cast<double>(int_number)};
    std::cout << typeid(double_number).name() << '\n'; // prints 'd' for double

    // casting double to int (narrowing conversion, loss of information)
    //? classical example for that is the narrowing conversion from size_t to int when working with std container size type 
    int_number= static_cast<int>(double_number);
    std::cout << typeid(double_number).name() << '\n'; // prints 'd' for double

    // casting Derived objects to Base object ( called upcasting )
    Derived d{10,20};
    // only copies the Base part of the Derived object - //! performs object slicing (bad)
    Base base_object{static_cast<Base>(d)}; 
    // reference or pointers of a Base object storing a Derived object keeps also the Information specific to the Derived class
    Base& base_reference{static_cast<Base&>(d)}; 
    
    // casting a base class into a derived class ( called down casting ) //! and can be dangerous
    Derived& other_derived{static_cast<Derived&>(base_reference)};
    std::cout << other_derived.getDerivedValue() << std::endl;

    // if the Base reference/pointer does not actually contain a Derived object //! undefined behaviour occurs
    //other_derived = static_cast<Derived&>(base_object);
    //std::cout << other_derived.getDerivedValue() << std::endl;

    // dynamic cast examples:
    //-------------------------------------------------------------------------------------------------------------------------

    //? dynamic casts are mainly used to perform down casting (converting a pointer/reference of a base class to a derived class)
    // it ensures type safety by performing runtime checks to verify the validity of the conversion

    Base& base{*new Derived{1,2}};

    //! failing at downcasting a reference throws a std::bad_cast exception
    try{
        OtherDerived& otherderived_reference {dynamic_cast<OtherDerived&>(base)}; 
    }catch(const std::bad_cast& e ){
        std::cout << "downcasting to reference failed, error message: " << e.what() << std::endl;
    }

    //! failing at downcasting a pointer returns a nullptr that can be checked
    OtherDerived* otherderived_pointer {dynamic_cast<OtherDerived*>(&base)};
    if(otherderived_pointer){ // condition equal to - otherderived_pointer != nullptr
        std::cout << "downcasting to pointer was successful" << std::endl;
    }else{
        std::cout << "downcasting to pointer failed, dynamic_cast returned nullptr" << std::endl;
    }

    // const cast examples:
    //-------------------------------------------------------------------------------------------------------------------------

    // const_cast can be used to add or remove the const specifier from references / pointers
    //? const casts are used to cast away the const-ness of variables 
    //? to pass them to functions that don't modify their arguments but don't take const parameters
    
    const int& const_int{33};
    int& modifiable_reference_int{const_cast<int&>(const_int)};
    int* modifiable_pointer_int{const_cast<int*>(&const_int)};

    //! original const values should not be modified, constness is a guarantee made to the compiler that when broken causes undefined behaviour
    modifiable_reference_int=4;
    std::cout << const_int << std::endl;

    // const_cast can also be used to add the const specifier to a reference / pointer
    int non_const_int{22};
    const int& const_ref{const_cast<const int&>(const_int)};
    const int* cont_ptr{const_cast<const int*>(&const_int)};

    return 0;
}