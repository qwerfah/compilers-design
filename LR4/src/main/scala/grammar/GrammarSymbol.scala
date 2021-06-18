package grammar

import scala.util.matching.Regex

/** Specifies grammar symbol.
  *
  * @param name Symbol name (Nonterminal name using
  * in  parsing process or terminal spelling in code).
  * @param stype Symbol type (Terminal, nonterminal or eps - empty sequence).
  * @param regex Regular expression that input token mush match with to be current symbol.
  */
class GrammarSymbol(
    val name: String,
    val stype: SymbolType.SymbolType = SymbolType.Term,
    val regex: Option[Regex] = None,
    val spell: Option[String] = None
) extends Ordered[GrammarSymbol] {

  if (name == null || name.isBlank()) {
    throw new Exception("Invalid name")
  }

  if (stype == null) {
    throw new Exception("Invalid symbol type")
  }

  override def toString(): String = name // s"< ${name} : ${stype} >\n"

  override def compare(that: GrammarSymbol): Int = name.compare(that.name)

  override def hashCode(): Int = name.hashCode()

  override def equals(x: Any): Boolean = x match {
    case s: GrammarSymbol => name.equals(s.name)
    case _                => false
  }
}
