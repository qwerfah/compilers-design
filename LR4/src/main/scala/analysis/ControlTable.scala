package analysis

import grammar._
import scala.collection.immutable.SortedSet

import PrecedenceType._

/** Specifies control table for table-driven
  * syntax analysis algorithm of operator precedence.
  * @param grammar Operator precedence grammar.
  */
class ControlTable(val grammar: Grammar) {
  type RawTable = Map[(GrammarSymbol, GrammarSymbol), PrecedenceType]
  type ExtremeSymbolTable =
    Map[GrammarSymbol, (Set[GrammarSymbol], Set[GrammarSymbol])]

  val table: Map[(GrammarSymbol, GrammarSymbol), PrecedenceType] =
    buildControlTable()

  /** Build control table for all terminal symbols based on grammar data.
    * @return Raw representation of control table (map).
    */
  private def buildControlTable(): RawTable = {
    val extremeTable = buildExtremeTerminalTable()
    var controlTable =
      Map[(GrammarSymbol, GrammarSymbol), PrecedenceType.PrecedenceType]()

    /** Get terminal symbol following specified terminal.
      * @param term Terminal ыньищд to search for next.
      * @param rule Grammar rule that presumably contains required symbols.
      * @return Required terminal symbol or none if not found.
      */
    def getNextTerm(
        term: GrammarSymbol
    )(rule: GrammarRule): Option[GrammarSymbol] = {
      if (!rule.rhs.contains(term)) return None

      val ind = rule.rhs.indexOf(term)

      return if (
        rule.rhs.isDefinedAt(ind + 1) &&
        rule.rhs(ind + 1).stype == SymbolType.Term
      ) Option(rule.rhs(ind + 1))
      else if (
        rule.rhs.isDefinedAt(ind + 2) &&
        rule.rhs(ind + 2).stype == SymbolType.Term
      ) Option(rule.rhs(ind + 2))
      else None
    }

    /** Get nonterminal symbol following or precedes specified terminal.
      *
      * @param term Terminal symbol to search for next.
      * @param rule Grammar rule that presumably contains required symbols.
      * @return Required nonterminal symbol or none if not found.
      */
    def getNonterm(
        term: GrammarSymbol,
        offset: Int
    )(rule: GrammarRule): Option[GrammarSymbol] = {
      if (!rule.rhs.contains(term)) return None

      val ind = rule.rhs.indexOf(term)

      return if (
        rule.rhs.isDefinedAt(ind + offset) &&
        rule.rhs(ind + offset).stype == SymbolType.NonTerm
      ) Option(rule.rhs(ind + offset))
      else None
    }

    for (term <- grammar.terms) {
      val neighborSymbols = grammar.rules.map(getNextTerm(term) _).flatten

      // Step 1: fill in table cells for symbols that have common basis with current
      for (symbol <- neighborSymbols) {
        controlTable += ((term, symbol) -> PrecedenceType.Neighbors)
      }

      // Step 2: fill in table cells for symbols that precedes current in some basis
      val leftmost = grammar.rules.map(getNonterm(term, 1) _).flatten
      controlTable ++= leftmost
        .map(nt => extremeTable(nt)._1)
        .flatten
        .filter(s => s.stype == SymbolType.Term)
        .map(s => (term, s) -> PrecedenceType.Precedes)

      // Step 3: fill in table cells for symbols that follows current in some basis
      val rightmost = grammar.rules.map(getNonterm(term, -1) _).flatten
      controlTable ++= rightmost
        .map(nt => extremeTable(nt)._2)
        .flatten
        .filter(s => s.stype == SymbolType.Term)
        .map(s => (s, term) -> PrecedenceType.Follows)
    }

    val start = new GrammarSymbol("start")
    val stop = new GrammarSymbol("stop")

    controlTable ++= extremeTable(grammar.axiom)._1
      .filter(s => s.stype == SymbolType.Term)
      .map(s => ((start, s) -> PrecedenceType.Precedes))

    controlTable ++= extremeTable(grammar.axiom)._2
      .filter(s => s.stype == SymbolType.Term)
      .map(s => ((s, stop) -> PrecedenceType.Follows))

    return controlTable
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
      isChanged = false

      for ((symbol, sets) <- table) {
        val leftmost1 = sets._1
          .filter(s => table.contains(s))
          .map(s => table(s)._1)
          .flatten

        val leftmost = leftmost1 ++ sets._1

        val rightmost = sets._2
          .filter(s => table.contains(s))
          .map(s => table(s)._2)
          .flatten ++ sets._2

        updatedTable += (symbol -> (leftmost, rightmost))

        isChanged =
          if (!(leftmost &~ sets._1).isEmpty || !(rightmost &~ sets._2).isEmpty)
            true
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
          r.rhs.head.stype == SymbolType.Term ||
            (r.rhs.isDefinedAt(1) &&
              r.rhs.tail.head.stype == SymbolType.Term)
        )
        .map(r =>
          if (r.rhs.head.stype == SymbolType.Term) r.rhs.head
          else r.rhs.tail.head
        )

      val rightmost = rules
        .filter(r => r.rhs.last.stype == SymbolType.Term)
        .map(r => r.rhs.last)
      termTable += (nt -> (leftmost, rightmost))
    }

    for ((symbol, sets) <- table) {
      val leftmost = sets._1
        .filter(s => termTable.contains(s))
        .map(s => termTable(s)._1)
        .flatten ++ termTable(symbol)._1

      val rightmost = sets._2
        .filter(s => termTable.contains(s))
        .map(s => termTable(s)._2)
        .flatten ++ termTable(symbol)._2

      termTable = termTable.updated(symbol, (leftmost, rightmost))
    }

    return table
  }

  override def toString(): String = {
    val (rows, cols) = {
      val (r, c) = table.keys.unzip
      (SortedSet(r.toSeq: _*).toList, SortedSet(c.toSeq: _*).toList)
    }

    ("      " +: cols).map("%5s |".format(_)).mkString + "\n" +
      rows
        .map { r =>
          "-" + "------|" * (cols.length + 1) + "\n" +
            "%5s  |".format(r.name) + cols.map { c =>
              "%4s  |".format(table.getOrElse((r, c), "--"))
            }.mkString
        }
        .mkString("\n")
  }
}
