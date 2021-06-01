package analysis

import grammar._

import PrecedenceType._

/** Specifies control table for table-driven
  * syntax analysis algorithm of operator precedence.
  * @param grammar Operator precedence grammar.
  */
class ControlTable(grammar: Grammar) {
  type RawTable = Map[(GrammarSymbol, GrammarSymbol), PrecedenceType]

  val table: RawTable = buildTable()

  /** Build control table for all terminal symbols based on grammar data.
    * @return Raw representation of control table (map).
    */
  private def buildTable(): RawTable = {
    if (grammar.terms.isEmpty) {
      throw new Exception("Invalid grammar (no terminal symbols)")
    }

    grammar.terms.toList
      .combinations(2)
      .map(pair => {
        (pair.head, pair.last) -> determineRelation(pair.head, pair.last)
      })
      .toMap
  }

  /** Determine precedence relation between two terminal symbols.
    * @param term1 First terminal symbol.
    * @param term2 Second terminal symbol.
    * @return Type of precedence relation between specified symbols.
    */
  def determineRelation(
      term1: GrammarSymbol,
      term2: GrammarSymbol
  ): PrecedenceType = {

    if (isPrecedes(term1, term2)) return PrecedenceType.Precedes
    if (isFollows(term1, term2)) return PrecedenceType.Follows
    if (isNeighbors(term1, term2)) return PrecedenceType.Neighbors

    PrecedenceType.None
  }

  /** Determine whether first symbol precedes second symbol.
    * @param term1 First terminal symbol.
    * @param term2 Second terminal symbol.
    */
  private def isPrecedes(
      term1: GrammarSymbol,
      term2: GrammarSymbol
  ): Boolean = {
    // Select all rules of the form <U ->x term1 C y> where C is nonterminal
    val rules = grammar.rules.filter(rule =>
      rule.rhs.contains(term1) && rule
        .rhs(rule.rhs.indexOf(term1) + 1)
        .stype == SymbolType.NonTerm
    )

    for (rule <- rules) {
      if (isPrecedeReachable(term2, rule.rhs(rule.rhs.indexOf(term1) + 1))) {
        return true
      }
    }

    false
  }

  /** Determine whether first symbol follows second symbol.
    * @param term1 First terminal symbol.
    * @param term2 Second terminal symbol.
    */
  private def isFollows(
      term1: GrammarSymbol,
      term2: GrammarSymbol
  ): Boolean = {
    // Select all rules of the form <U ->x term1 C y> where C is nonterminal
    val rules = grammar.rules.filter(rule =>
      rule.rhs.contains(term2) && rule
        .rhs(rule.rhs.indexOf(term2) - 1)
        .stype == SymbolType.NonTerm
    )

    for (rule <- rules) {
      if (isFollowReachable(term1, rule.rhs(rule.rhs.indexOf(term2) - 1))) {
        return true
      }
    }

    false
  }

  /** Determine whether first symbol neighbors with second symbol.
    * @param term1 First terminal symbol.
    * @param term2 Second terminal symbol.
    */
  private def isNeighbors(
      term1: GrammarSymbol,
      term2: GrammarSymbol
  ): Boolean = {
    grammar.rules.exists(rule => {
      val ind1 = rule.rhs.indexOf(term1)
      val ind2 = rule.rhs.indexOf(term2)
      (ind2 - ind1 == 1) || (ind2 - ind1 == 2 && rule
        .rhs(ind1 + 1)
        .stype == SymbolType.NonTerm)
    })
  }

  /** Determines if specified terminal symbol is reachable
    * from specified nonterminal symbol for precedence.
    * @param term Terminal symbol that should be deduced.
    * @param nonterm Nonterminal symbol from which deduction starts.
    * @return
    */
  private def isPrecedeReachable(
      term: GrammarSymbol,
      nonterm: GrammarSymbol
  ): Boolean = {}

  /** Determines if specified terminal symbol is reachable
    * from specified nonterminal symbol for succession.
    * @param term Terminal symbol that should be deduced.
    * @param nonterm Nonterminal symbol from which deduction starts.
    * @return
    */
  private def isFollowReachable(
      term: GrammarSymbol,
      nonterm: GrammarSymbol
  ): Boolean = {}
}
