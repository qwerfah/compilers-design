package grammar

/** Grammar symbol (terminal or nonterminal).
  *
  * @param name Symbol name (using in  parsing process).
  * @param spell Symbiol spell (using in input token stream).
  * @param stype Symbol type.
  */
class GrammarSymbol(
    val name: String,
    val spell: Option[String] = None,
    val stype: SymbolType.SymbolType = SymbolType.Term
) {

  if (name == null || name.isBlank()) {
    throw new Exception("Invalid name")
  }

  if (stype == null) {
    throw new Exception("Invalid symbol type")
  }
}
