#include <iostream>
#include <string>
#include <map>



struct Entry{
    std::string name;
    int value;
};

Entry read_entry(){
    std::string name{};
    int value{};
    std::cin >> name >> value;
    // return an temporary object of Entry
    return {name , value};
}

// function that uses structured binding to increment all values of a map by 1
template <typename T>
void incrementMapValues(std::map<T,int>& map){
    for(auto& [key,value] : map){
        value++;
    }
}


int main(){

    // using structured binding, where the member variables of a user defined object are bound to local variables
    // in this example the member variables (name and value) of Entry object are bound to n and v
    auto [n,v] = read_entry();
    std::cout << "entered name:" << n << " entered value:" << v << std::endl;
    
    std::map<std::string,int> map{};
    
    for( int i = 0; i < 10; i++){
        map[std::to_string(i)]=i*2;
    }
    
    // using structural bindinding to iterate over the keys and values of a map
    for (const auto& [key,value]: map){
        std::cout << "this is the key:" << key << " and this is its value: " << value << std::endl;
    }

    return 0; 
}