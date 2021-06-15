package grammar

/** Specifies grammar symbol.
  *
  * @param name Symbol name (Nonterminal name using
  * in  parsing process or terminal spelling in code).
  * @param stype Symbol type (Terminal, nonterminal or eps - empty sequence).
  */
class GrammarSymbol(
    val name: String,
    val stype: SymbolType.SymbolType = SymbolType.Term
) extends Ordered[GrammarSymbol] {

  if (name == null || name.isBlank()) {
    throw new Exception("Invalid name")
  }

  if (stype == null) {
    throw new Exception("Invalid symbol type")
  }

  override def toString(): String = name // s"< ${name} : ${stype} >\n"

  override def compare(that: GrammarSymbol): Int = name.compare(that.name)
}
