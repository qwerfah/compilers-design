package grammar

/** Grammar symbol type (terminal, nonterminal or empty  - eps).
  */
object SymbolType extends Enumeration {
  type SymbolType = Value
  val Term, NonTerm, Eps = Value
}
