#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <boost/program_options.hpp>

#include "src/ast/prog.h"

#include "printer.h"
#include "codegen.h"
#include "algebra_simplification_opt.h"
#include "const_prop_opt.h"
#include "dead_code_opt.h"


extern "C" int yylex();
extern ASTProgram *program_ast;
/* extern int yydebug; */
int yyparse();
extern "C" FILE *yyin;

static void usage() { printf("Usage: cc <prog.c>\n"); }


using namespace boost;
using namespace boost::program_options;

class CmdOptions{
public:
    string input_file;
    string output_file;
    bool print_ast = true;

    bool opt_al_sim = true;
    bool opt_const_prop = true;
    bool opt_deadcode = true;

    explicit CmdOptions(const variables_map& vm){
      input_file = vm["in"].as<string>();
      if(vm.count("out")){
        output_file = vm["out"].as<string>();
      }else{
        output_file = vm["in"].as<string>() + ".ll";
      }

      if(vm.count("opt-al-sim"))
        opt_al_sim = vm["opt-al-sim"].as<bool>();
      if(vm.count("opt-deadcode"))
        opt_deadcode = vm["opt-deadcode"].as<bool>();
      if(vm.count("opt-const-prop"))
        opt_const_prop = vm["opt-const-prop"].as<bool>();

      if(vm.count("print-ast")){
        print_ast = vm["print-ast"].as<bool>();
      }

      if(vm.count("all-opt")) {
        if (vm["all-opt"].as<bool>()) {
          opt_al_sim = true;
          opt_deadcode = true;
          opt_const_prop = true;
        }
      }

    }
};

CmdOptions parse(int argc, char **argv) {
    options_description help("Help Options");
    help.add_options()
            ("help", "produce a help message")
            ("print-ast", value<bool>(), "Print the AST")
            ;

    options_description io("File Paths");
    io.add_options()
            ("in", value<string>(), "Input file path")
            ("out", value<string>(), "Output file path")
            ;

    options_description opt("Optimization options");
    opt.add_options()
            ("all-opt", bool_switch(), "Enable All Optimizations")
            ("opt-al-sim", bool_switch(), "Enable Algebraic Simplification")
            ("opt-const-prop", bool_switch(), "Enable Constant Propagation")
            ("opt-deadcode", bool_switch(), "Enable Deadcode elimination")
            ;

    // Declare an options description instance which will include
    // all the options
    options_description all("Allowed options");
    all.add(io).add(opt).add(help);

    variables_map vm;
    store(parse_command_line(argc, argv, all), vm);

    if(vm.count("help")){
        cout << all << endl;
        exit(0);
    }

    if(!vm.count("in")){
      cout << "Input File Not provided" << endl;
      cout << "Usage" << endl;
      cout << all << endl;
      exit(1);
    }

    return CmdOptions(vm);
}



int main(int argc, char **argv) {
  cout << *(argv+1) <<endl;
  auto options = parse(argc, argv);

  yyin = fopen(options.input_file.c_str(), "r");
  assert(yyin);

  /* yydebug = 1; */

  int ret = yyparse();
  if(ret!=0){
    cout << "Parsing Failed" << endl;
    exit(ret);
  }

  auto *printer = new Printer();
  if(options.print_ast){
    auto str = printer->visit(program_ast);
    cout << str << endl;
  }

  if(options.opt_al_sim){
    auto *algebraSimplificationOpt = new AlgebraSimplificationOpt();
    program_ast = dynamic_cast<ASTProgram *>(program_ast->accept(algebraSimplificationOpt));

    cout << "AST After Algebraic Simplification" << endl;
    if(options.print_ast){
      auto str = printer->visit(program_ast);
      cout << str << endl;
    }
  }
  
  if(options.opt_const_prop){
    auto *constPropagation = new ConstPropagationOpt();
    program_ast = dynamic_cast<ASTProgram *>(program_ast->accept(constPropagation));

    cout << "AST After Constant Propagation" << endl;
    if(options.print_ast){
      auto str = printer->visit(program_ast);
      cout << str << endl;
    }
  }

  if(options.opt_deadcode){
    auto *deadCodeOpt = new DeadCodeOpt();
    program_ast = dynamic_cast<ASTProgram *>(program_ast->accept(deadCodeOpt));

    cout << "AST After Dead Code Removal" << endl;
    if(options.print_ast){
      auto str = printer->visit(program_ast);
      cout << str << endl;
    }
  }

  auto *cg = new Codegen(options.input_file);
  cg->visit(program_ast);
//  cg->dumpCode();
  cg->dumpFile(options.output_file);

}
