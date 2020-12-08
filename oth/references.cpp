#include <iostream>
#include <cstdlib>

class Z{
    void* ptr;
    int temp;
public:
    Z(){
        temp = 4;
        std::cout << "reached point\n";
        ptr = (void*) &temp;
        std::cout << "exited point\n";
    }
    ~Z(){
        std::cout << "Within destructor(Z)\n";
    }
    void* getZ(){
        return ptr;
    }
};

class A{
    int a;
    Z* z = new Z();
public:
    A(){
        a = 5;
        z = new Z();
        void* p = z->getZ();
        std::cout << "Within A, z.getZ() is: " << *(int*) p << std::endl;
    }
    A(int x){
        a = x;
    }
    ~A(){
        std::cout << "In destructor(A)\n";
        delete z;
        std::cout << "successfully deleted z\n";
    }
    void print(){
        std::cout << "a is: " << a << std::endl;
        if(z) std::cout << "z is: " << *(int*)z->getZ() << std::endl;
    }
};

template<class T>
class B{
    int b;
    A* _a;
    T* t;
public:
    B(){
        b = 2;
        std::cout << "Attempting to create new T(1)...\n";
        t = new T(1);
        std::cout << "Created T(1)\n";
        t->print();
    }
    B(int x){
        b = x;
    }
    ~B(){
        std::cout << "In destructor(B)\n";
        delete t;
        std::cout << "In destructor(B), successfully deleted t\n";
    }
    // without copy elicitation
    A getA(){
        return _a[0];
    }
    T getT(){
        return t[0];
    }
    
};

int main(){
    // A class_a;
    B<A> class_b;

    std::cout << "IN MAIN\n";
    // class_a.print();
    class_b.getT().print();

    return 0;
}
