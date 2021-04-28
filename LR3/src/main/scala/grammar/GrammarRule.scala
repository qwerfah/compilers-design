package grammar

/** Describe grammar rule with one nonterminal in
  * left-hand side and some symbol chain in right-hand side.
  *
  * @param lhs Left-hand side of the rule.
  * @param rhs Right-hand-side of the rule.
  */
class GrammarRule(val lhs: List[GrammarSymbol], val rhs: List[GrammarSymbol]) {
  if (lhs == null || lhs.isEmpty) {
    throw new Exception("Invalid left-hand side of the rule")
  }

  if (rhs == null) {
    throw new Exception("Invalid right-hand side of the rule")
  }
}
