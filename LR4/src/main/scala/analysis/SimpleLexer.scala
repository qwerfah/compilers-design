package analysis

import grammar.Grammar
import grammar.GrammarSymbol

/** Represents simple lexer that transform input
  * string to token stream according to the given grammar.
  * @param grammar
  */
class SimpleLexer(val grammar: Grammar) {

  /** Tramsform input string to token list.
    * @param input Input string.
    * @return List of tokens.
    */
  def getTokens(input: String): List[GrammarSymbol] = {
    val strings = input.split(" ")

    return strings
      .map(str =>
        new GrammarSymbol(
          grammar.terms.find(s => s.regex.get.matches(str)).get.name,
          spell = Option(str)
        )
      )
      .toList
  }
}
