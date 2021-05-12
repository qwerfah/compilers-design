package analysis

import grammar._
import data._

/** Lexer that splits input string into token list.
  *
  * @param string Input string with code.
  */
class Lexer(string: String) {
  if (string == null || string.isBlank()) {
    throw new Exception("Invalid input string")
  }

  /** Split input string into token list.
    *
    * @return List of tokens.
    */
  def getTokens(): List[String] = {
    string.split("( +)|(\n)").toList
  }
}
