#include <iostream>

#include "ExprLexer.h"
#include "ExprParser.h"
#include "IRVisitor.h"
#include "InterpreterVisitor.h"
#include "PrintVisitor.h"
#include "antlr4-runtime.h"

int main(int argc, const char* argv[]) {
  std::ifstream stream;
  std::string filename = "../input.txt";
  if (argc == 2) {  // custom program file
    filename = argv[1];
  }
  stream.open(filename);

  antlr4::ANTLRInputStream input(stream);
  ExprLexer lexer(&input);
  antlr4::CommonTokenStream tokens(&lexer);
  ExprParser parser(&tokens);

  ExprParser::FileContext* tree = parser.file();

  InterpreterVisitor visitor;
  PrintVisitor print_visitor;
  IRVisitor ir_visitor;
  try {
    ir_visitor.visitFile(tree);
    ir_visitor.printIR();
    ir_visitor.printIR("program.ll");
  } catch (const std::exception& ex) {
    std::cout << "Error occured in translation pass!\n"
              << ex.what() << std::endl;
  }
  return 0;
}