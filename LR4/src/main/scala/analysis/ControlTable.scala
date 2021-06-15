package analysis

import grammar._

import PrecedenceType._

/** Specifies control table for table-driven
  * syntax analysis algorithm of operator precedence.
  * @param grammar Operator precedence grammar.
  */
class ControlTable(val grammar: Grammar) {
  type RawTable = Map[(GrammarSymbol, GrammarSymbol), PrecedenceType]
  type ExtremeSymbolTable =
    Map[GrammarSymbol, (Set[GrammarSymbol], Set[GrammarSymbol])]

  val table: RawTable = buildTable()

  /** Build control table for all terminal symbols based on grammar data.
    * @return Raw representation of control table (map).
    */
  private def buildControlTable(): Unit = {
    val extremeTable = buildExtremeTerminalTable()
    var controlTable = Map[(GrammarSymbol, GrammarSymbol), PrecedenceType.PrecedenceType]()
    
    def getNextTerm(term: GrammarSymbol)(rule: GrammarRule): Option[GrammarSymbol] = {
      if (!rule.rhs.contains(term)) return None
      
      val ind = rule.rhs.indexOf(term)

      return if (rule.rhs.isDefinedAt(ind + 1) && 
                 grammar.terms.contains(rule.rhs(ind + 1))) Option(rule.rhs(ind + 1))
        else if (rule.rhs.isDefinedAt(ind + 2) && 
                 grammar.terms.contains(rule.rhs(ind + 2))) Option(rule.rhs(ind + 2))
        else None
    }
    
    def getNextNonterm(term: GrammarSymbol)(rule: GrammarRule): Option[GrammarSymbol] = {
      if (!rule.rhs.contains(term)) return None
      
      val ind = rule.rhs.indexOf(term)
      
      return if (rule.rhs.isDefinedAt(ind + 1) && 
                 grammar.nonTerms.contains(rule.rhs(ind + 1))) Option(rule.rhs(ind + 1))
        else None
    }

    for (term <- grammar.terms) {
      val neighborSymbols = grammar.rules.map(getNextTerm(term) _).flatten
      
      for (symbol <- neighborSymbols) {
        controlTable += ((term, symbol) -> PrecedenceType.Neighbors)
      }
      
      val nonterms = grammar.rules.map(getNextNonterm(term) _).flatten
    }
  }

  /** Build extreme (leftmost and rightmost) nonterminal symbols table.
    * @return Extreme nonterminal symbols table.
    */
  def buildExtremeNonterminalTable(): ExtremeSymbolTable = {
    var table = Map[GrammarSymbol, (Set[GrammarSymbol], Set[GrammarSymbol])]()

    for (nt <- grammar.nonTerms) {
      val rules = grammar.rules.filter(r => r.lhs.contains(nt))
      val pair =
        (rules.map(r => r.rhs.head).toSet, rules.map(r => r.rhs.last).toSet)
      table = table + (nt -> pair)
    }

    var isChanged = true

    while (isChanged) {
      var updatedTable =
        Map[GrammarSymbol, (Set[GrammarSymbol], Set[GrammarSymbol])]()

      for (str <- table) {
        val leftmost = str._2._1
          .filter(s => table.contains(s))
          .map(s => table(s)._1)
          .flatten ++ str._2._1
        
        val rightmost = str._2._2
          .filter(s => table.contains(s))
          .map(s => table(s)._2)
          .flatten ++ str._2._2
        
        updatedTable = updatedTable + (str._1 -> (leftmost, rightmost))
        
        isChanged = if (
          !(leftmost &~ str._2._1).isEmpty || !(rightmost &~ str._2._2).isEmpty
        ) true
        else isChanged
      }

      table = updatedTable
    }

    return table
  }

  /** Build extreme (leftmost and rightmost) terminal symbols table.
    * @return Extreme terminal symbols table.
    */
  def buildExtremeTerminalTable(): ExtremeSymbolTable = {
    val table = buildExtremeNonterminalTable()
    var termTable =
      Map[GrammarSymbol, (Set[GrammarSymbol], Set[GrammarSymbol])]()

    for (nt <- grammar.nonTerms) {
      val rules = grammar.rules.filter(r => r.lhs.contains(nt))

      val leftmost = rules
        .filter(r =>
          grammar.terms.contains(r.rhs.head) || 
          grammar.terms.contains(r.rhs.tail.head)
        )
        .map(r =>
          if (grammar.terms.contains(r.rhs.head)) r.rhs.head
          else r.rhs.tail.head
        )
      
      val rightmost = rules.filter(r => grammar.terms.contains(r.rhs.last)).map(r => r.rhs.last)
      termTable += (nt -> (leftmost, rightmost))
    }
    
    for (str <- table) {
      val leftmost = str._2._1
        .filter(s => table.contains(s))
        .map(s => termTable(s)._1)
        .flatten ++ termTable(str._1)._1

      val rightmost = str._2._2
        .filter(s => table.contains(s))
        .map(s => termTable(s)._2)
        .flatten ++ termTable(str._1)._2

      termTable = termTable + (str._1 -> (leftmost, rightmost))
    }
    
    return table
  }
}
