// main.cpp
#include <iostream>
#include <string>
enum class Type { ptr, num };

// a struct that can hold either a pointer or an integer, depending on the value of the Type enum
//? member p and i are never used at the same time, memory space will be wasted this way
struct Entry{
    std::string name;
    Type t;
    int* p;
    int i;
};

//? use a union for the value part instead which can only be as big as its biggest member, to save memory space
// both member p and i will be stored inside the same memory address
//! which value is hold by the union, is something the user has to check for himself and is error prone
union Value{
    int* p;
    int i;
};

// struct with the usage of the union, which can be either a pointer or an integer value
struct Entry_with_union{
    std::string name;
    Type t;
    Value v;
};

// std::variant is a simplier, less error prone, encapsulated way to use unions
#include <variant>

// struct with the usage of std::variant, which can be either a pointer or an integer value
struct Entry_with_variant{
    std::string name;
    std::variant<int*,int> value;
};

// overloaded function accepting the variant type
void f(const Entry_with_variant& e){
    // checking what type the variant is holding with std::holds_alternative<>
    if(std::holds_alternative<int>(e.value)){
        // getting the actual value from the variant with the std::get<>
        std::cout << std::get<int>(e.value) << '\n';
    }else{
        if(std::get<int*>(e.value)){
            std::cout << *std::get<int*>(e.value) << '\n';
        }
    }
}

// function that resolves the type of the Entry struct and prints the value
// error prone do to user errors
void f(const Entry& e){
    if(e.t == Type::num){
        std::cout << e.i << '\n';
    }else{
        if(e.p)
        std::cout << *(e.p) << '\n';
    }
}

// overloaded function version that uses the struct with the union
void f(const Entry_with_union& e){
    if(e.t == Type::num){
        std::cout << e.v.i << '\n';
    }else{
        if(e.v.p)
        std::cout << *(e.v.p) << '\n';
    }
}

int main(){

    Value v;
    v.i = 55;

    // creation of an entry and resolution of the type to print the value
    Entry entry{"entryName", Type::num, nullptr,5 };
    Entry_with_union e_u{"entryName", Type::num, v};
    Entry_with_variant e_v{"entryName", 44};
    f(entry);
    f(e_u);
    f(e_v);

    return 0;

}