#pragma once

#include <vector>
#include <map>
#include <set>
#include <memory>

class Symbol;
class Rule;
class Grammar;
class GrammarTransform;

typedef std::shared_ptr<Symbol> symbol_ptr;
typedef std::shared_ptr<Rule> rule_ptr;
typedef std::shared_ptr<Grammar> grammar_ptr;
typedef std::shared_ptr<GrammarTransform> transform_ptr;
typedef std::vector<std::shared_ptr<Symbol>>::iterator symbol_iterator;
typedef std::vector<std::shared_ptr<Symbol>>::const_iterator const_symbol_iterator;

typedef std::vector<std::shared_ptr<Symbol>> symbol_vector;
typedef std::set<std::shared_ptr<Symbol>> symbol_set;
typedef std::vector<std::shared_ptr<Rule>> rule_vector;
typedef std::map<std::string, std::shared_ptr<GrammarTransform >> transform_map;
typedef std::vector<size_t> index_vector;
typedef std::vector<std::vector<size_t>> index_combination_vector;
