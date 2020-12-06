#include "md.h"
#include "backend.h"

#include <iostream>
#include <vector>

namespace FVIEWS{
    const char* v1 = "MD [N] - Run a brute force MD simulation ";
    const char* v2 = "MD [N] [V] - MD with a specified potential function V";
    const char* v3 = "BM [N] - Benchmark MD on N particles";
    const char* v4 = "help - Display a doc";

    std::vector<std::string> vec = {v1, v2, v3, v4};
}

void view_message();

int main(){
    welcome_message();
    while(true){
        // prompt the users to enter what they want to view
        view_message();
    }
    return 0;
}

void view_message(){
    for(std::string s: FVIEWS::vec){
        std::cout << s << std::endl;
    }
}

void welcome_message(){
    using namespace std;
    cout << "\n\t========================" << endl;
    cout << "\t  Welcome to Hyper Sim" << endl;
    cout << "\t========================" << endl;
}
