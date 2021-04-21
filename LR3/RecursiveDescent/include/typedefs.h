#pragma once

#include <vector>
#include <map>
#include <set>
#include <memory>

class Symbol;
class Rule;
class Grammar;

typedef std::shared_ptr<Symbol> symbol_ptr;
typedef std::shared_ptr<Rule> rule_ptr;
typedef std::shared_ptr<Grammar> grammar_ptr;
typedef std::vector<std::shared_ptr<Symbol>>::iterator symbol_iterator;
typedef std::vector<std::shared_ptr<Symbol>>::const_iterator const_symbol_iterator;
typedef std::vector<std::shared_ptr<Symbol>> symbol_vector;
typedef std::set<std::shared_ptr<Symbol>> symbol_set;
typedef std::vector<std::shared_ptr<Rule>> rule_vector;
