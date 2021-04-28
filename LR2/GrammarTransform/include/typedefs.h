#pragma once

#include <vector>
#include <map>
#include <set>
#include <memory>

class Symbol;
class Rule;
class Grammar;
class GrammarTransform;

using symbol_ptr = std::shared_ptr<Symbol>;
using rule_ptr = std::shared_ptr<Rule>;
using grammar_ptr = std::shared_ptr<Grammar>;
using symbol_iterator = std::vector<std::shared_ptr<Symbol>>::iterator;
using transform_ptr = std::shared_ptr<GrammarTransform>;
using const_symbol_iterator = std::vector<std::shared_ptr<Symbol>>::const_iterator;
using symbol_vector = std::vector<std::shared_ptr<Symbol>>;
using symbol_set = std::set<std::shared_ptr<Symbol>>;
using rule_vector = std::vector<std::shared_ptr<Rule>>;
using rule_set = std::set<std::shared_ptr<Rule>>;
using transform_map = std::map<std::string, std::shared_ptr<GrammarTransform >>;
using index_vector = std::vector<size_t>;
using index_combination_vector = std::vector<std::vector<size_t>>;
