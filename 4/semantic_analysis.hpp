#include "ast.hpp"
#include <stack>
#include <unordered_map>

using namespace std;

class SemanticAnalyzer {
public:
    SemanticAnalyzer() {
        symbol_table = stack<unordered_map<string, string>>();
    }
    bool analyze(ASTProgram* p);

private:
    stack<unordered_map<string, string>> symbol_table;
    bool find(string variable);
    bool find_all(string variable);
    void SemanticAnalyzer::enter_scope();
    void SemanticAnalyzer::exit_scope();
    void SemanticAnalyzer::add_variable(string variable, string type);
};