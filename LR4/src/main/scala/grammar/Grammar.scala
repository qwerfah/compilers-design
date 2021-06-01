package grammar

import scala.collection.immutable.SortedSet

/** Specifies context-free grammar which represents a tuple consisnts of four elements.
  *
  * @param terms Set of terminal symbols.
  * @param nonTerms Set of nonterminal symbols.
  * @param rules Set of production rules.
  * @param axiom Start symbol of grammar.
  */
class Grammar(
    val terms: SortedSet[GrammarSymbol],
    val nonTerms: SortedSet[GrammarSymbol],
    val rules: SortedSet[GrammarRule],
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
