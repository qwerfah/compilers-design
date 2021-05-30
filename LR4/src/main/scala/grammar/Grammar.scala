package grammar

/** Specifies context-free grammar which represents a tuple consisnts of four elements.
  *
  * @param terms Set of terminal symbols.
  * @param nonTerms Set of nonterminal symbols.
  * @param rules Set of production rules.
  * @param axiom Start symbol of grammar.
  */
class Grammar(
    val terms: Set[GrammarSymbol],
    val nonTerms: Set[GrammarSymbol],
    val rules: Set[GrammarRule],
    val axiom: GrammarSymbol
) {
  if (terms == null || terms.isEmpty) {
    throw new Exception("Invalid terms list")
  }

  if (nonTerms == null || nonTerms.isEmpty) {
    throw new Exception("Invalid nonterms list")
  }

  if (rules == null || rules.isEmpty) {
    throw new Exception("Invalid rules list")
  }

  if (axiom == null) {
    throw new Exception("Invalid axiom")
  }

  override def toString(): String = {
    "NONTERMINALS:\n" + nonTerms +
      "\nTERMINALS:'n" + terms +
      "\nRULES:\n" + rules +
      "\nAXIOM: " + axiom
  }
}
