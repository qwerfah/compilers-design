package analysis

import grammar._

import PrecedenceType._

/** Specifies control table for table-driven
  * syntax analysis algorithm of operator precedence.
  *
  * @param grammar Operator precedence grammar.
  */
class ControlTable(grammar: Grammar) {
  type RawTable = Map[(GrammarSymbol, GrammarSymbol), PrecedenceType]

  val table: RawTable =
    buildTable()

  /** Build control table for all terminal symbols based on grammar data.
    *
    *  @return Raw representation of control table (map).
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
    *
    * @param term1 First terminal symbol.
    * @param term2 Second terminal symbol.
    * @return Type of precedence relation between specified symbols.
    */
  def determineRelation(
      term1: GrammarSymbol,
      term2: GrammarSymbol
  ): PrecedenceType = {

    if (grammar.rules.exists(rule => true)) return PrecedenceType.Precedes
    if (grammar.rules.exists(rule => true)) return PrecedenceType.Follows
    if (grammar.rules.exists(rule => true)) return PrecedenceType.Neighbors

    PrecedenceType.None
  }

  /** Determine whether first symbol precedes second symbol.
    *
    * @param term1 First terminal symbol.
    * @param term2 Second terminal symbol.
    */
  private def isPrecedesRule(term1: GrammarSymbol, term2: GrammarSymbol) {
    grammar.rules.exists(rule => {
      val ind1 = rule.rhs.indexOf(term1)
      val ind2 = rule.rhs.indexOf(term2)
      (ind2 - ind1 == 1) || (ind2 - ind1 == 2 && rule
        .rhs(ind1 + 1)
        .stype == SymbolType.NonTerm)
    })
  }

  /** Determine whether first symbol follows second symbol.
    *
    * @param term1 First terminal symbol.
    * @param term2 Second terminal symbol.
    */
  private def isFollowsRule(term1: GrammarSymbol, term2: GrammarSymbol) {}

  /** Determine whether first symbol neighbors with second symbol.
    *
    * @param term1 First terminal symbol.
    * @param term2 Second terminal symbol.
    */
  private def isNeighborsRule(term1: GrammarSymbol, term2: GrammarSymbol) {}
}
