package grammar

/** Describes context-free grammar which represents a tuple of four elements.
  *
  * @param terms Set of terminal symbols.
  * @param nonTerms Set of nonterminal symbols.
  * @param rules Set of production rules.
  * @param axiom Start symbol of grammar.
  */
class Grammar(
    val terms: Set[Symbol], 
    val nonTerms: Set[Symbol], 
    val rules: Set[Rule], 
    val axiom: Symbol) {

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
}