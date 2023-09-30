#include <NFA.h>
#include <NFA_to_DFA.h>
#include <REGTree.h>
#include <REG_to_NFA.h>

#include <cassert>
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

int main() {
  std::string regexp = "ab*+c";
  REGTree regtree(regexp);
  NFA nfa = GetNFAFromREG(regtree);
  nfa = GetNFAWithNoEpsilons(nfa);
  try {
    //
    // NFA to DFA conversion test
    DFA dfa = ConvertNFAtoDFA(nfa);

    assert(!dfa.IsFinal());
    assert(!dfa.Input("a"));

    // ab, abb, abbb are accepted by DFA
    assert(dfa.Input("b"));
    assert(dfa.Input("b"));
    assert(dfa.Input("b"));
    assert(dfa.IsFinal());

    dfa.Reset();
    // c is accepted by DFA
    assert(dfa.Input("c"));

    // cb is not accepted by DFA
    assert(!dfa.Input("b"));


    return 0;
  } catch (const std::exception& e) {
    std::cout << "FAILED with error " << ' ' << e.what() << '\n';
    return 1;
  }
}