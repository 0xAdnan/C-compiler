//
// Created by satyam on 2/4/24.
//

#ifndef CCOMPILER_SEMANTICEXCEPTION_H
#define CCOMPILER_SEMANTICEXCEPTION_H

#include <exception>
#include <iostream>
#include <string>
#include <utility>

using namespace std;

class SemanticException: public exception{
private:
    string message;

public:
    // Constructor accepts a const char* that is used to set
    // the exception message
    explicit SemanticException(const char* msg): message(msg){
    }

    explicit SemanticException(string msg): message(std::move(msg)){
    }

    // Override the what() method to return our message
    [[nodiscard]] const char* what() const noexcept override{
      return ("Semantic Error:\n\t\t" + message).c_str();
    }
};


#endif //CCOMPILER_SEMANTICEXCEPTION_H
