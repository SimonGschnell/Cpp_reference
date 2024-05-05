    
#include <iostream>
#include <initializer_list>
#include <algorithm>
#include <limits>

class MyVector{
    public:
        // constructor that creates a list with the usage of a initializer list parameter
        MyVector(std::initializer_list<double> list): data{new double[list.size()]}{
            // initializing size and element_count in the constructor body to avoid narrowing conversion
            if(list.size() > std::numeric_limits<int>::max()){
                throw std::overflow_error("initializer list size is greater than the limit of the integer numbers");
            }
            size=static_cast<int>(list.size());
            element_count=static_cast<int>(list.size());
            std::copy(std::begin(list), std::end(list), data);
        }
        // copy constructor for MyVector, special because memory management is done manually
        MyVector(const MyVector& other): data{new double[other.size]}, size{other.size}, element_count{other.element_count}{
            std::copy(other.data, other.data+size, data);
        }
        // also copy assignment has to be adapted to the copy and swap idiom
        MyVector& operator=(MyVector& other){
            swap(other);
            return *this;
        }
        // destructor deletes the allocated resource after the RAII principle
        ~MyVector(){
            delete[] data;
        }
        // swap function for MyVector to use the COPY and SWAP idiom
        // which is an indiom used to guarantee a strong exception safety when assigning         
        void swap(MyVector& other) noexcept {
            std::swap(size, other.size);
            std::swap(other.element_count, element_count);
            std::swap(data, other.data);
        }

        double& operator[](int index) const {
            return *(data+index);
        }
        // constructor that creates a list with the usage a push_back method
        double& push_back(const double& ele){
            if(element_count >= size){
                // if the array is too little double it and add element at last position
                double* new_data = new double[size*2];
                std::copy(data, data+size, new_data);
                std::swap(data,new_data);
                delete[] new_data;
                //update data members
                size *= 2;
                
            }
            data[element_count] = ele;
            element_count++;
            return data[element_count-1];
        } 
        // member functions begin and end to use range loops over this user defined type
        double* begin() const {
            return data;
        }

        double* end() const {
            return data+element_count;
        }

        // Getter method for size
        int getSize() const {
            return size;
        }

        // Getter method for element_count
        int getElementCount() const {
            return element_count;
        }
    private:

    //data memebers
        double* data;
        int size;
        int element_count;
};

int main(){

    MyVector vec{1.51,2.62,3.00};
    std::cout << "vec size: " << vec.getSize() << ", element count: " << vec.getElementCount() << '\n';
    vec.push_back(55.1);
    std::cout << "vec size: " << vec.getSize() << ", element count: " << vec.getElementCount() << '\n';
    vec.push_back(10.11);
    std::cout << "vec size: " << vec.getSize() << ", element count: " << vec.getElementCount() << '\n';
    for(const auto& ele : vec){
        std::cout << "element: " << ele << '\n';
    }
}