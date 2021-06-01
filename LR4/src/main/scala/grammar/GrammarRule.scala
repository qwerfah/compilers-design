package grammar

/** Specifies rule of context-free grammar with one nonterminal in
  * left-hand side and some symbol sequence in right-hand side.
  *
  * @param lhs Left-hand side of the rule.
  * @param rhs Right-hand-side of the rule.
  */
class GrammarRule(val lhs: List[GrammarSymbol], val rhs: List[GrammarSymbol])
    extends Ordered[GrammarRule] {
  if (lhs == null || lhs.isEmpty || lhs.length != 1) {
    throw new Exception("Invalid left-hand side of the rule")
  }

  if (rhs == null) {
    throw new Exception("Invalid right-hand side of the rule")
  }

  override def toString(): String = s"${lhs.head} -> ${rhs}\n"

  override def compare(that: GrammarRule): Int = {
    val thisSymbols = lhs ::: rhs
    val thatSymbols = that.lhs ::: that.rhs

    val result = thisSymbols
      .zip(thatSymbols)
      .dropWhile(pair => pair._1.compare(pair._2) == 0)

    if (result.isEmpty) {
      thisSymbols.length - thatSymbols.length
    } else {
      result.head._1.compare(result.head._2)
    }
  }

}
