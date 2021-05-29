package data

import data.nodes._

import grammar.GrammarSymbol

/** Result of pasing operation (contains parse tree or pasing errors).
  *
  * @param isSuccess Shows whether the result of parsing operation is parse tree or error.
  * @param tree Parse tree which built as a result of parseing operation.
  * @param pos Position after last parsed token
  *            (specifies next token to parse or token which raises the error).
  * @param message Error message (in case of error).
  * @param inner Inner results that contain inner errors.
  */
class ParseResult(
    val isSuccess: Boolean = true,
    val tree: Option[Node] = None,
    val pos: Int = 0,
    val message: Option[String] = None,
    val inner: Option[ParseResult] = None
) {

  /** Constructor for correct parse result which returns parse tree.
    *
    * @param tree Parse tree.
    */
  def this(tree: Node, pos: Int) {
    this(true, Option(tree), pos, None, None)
  }

  /** Constructor for error result of parsing operation.
    *
    * @param message Error message.
    * @param inner Inner errors.
    */
  def this(message: String, pos: Int, inner: ParseResult) {
    this(false, None, pos, Option(message), Option(inner))
  }

  /** Constructor for error result without inner errors.
    *
    * @param message Error message.
    */
  def this(message: String, pos: Int) {
    this(false, None, pos, Option(message), None)
  }

  def +(p: Int): ParseResult =
    new ParseResult(isSuccess, tree, pos + p, message, inner)

  /** Print all errors recursively.
    *
    * @param result Error parsing result.
    */
  def printErrors(result: Option[ParseResult] = None) {
    if (!result.isDefined) {
      return printErrors(Option(this))
    }

    println(result.get.message.get)

    if (result.get.inner.isDefined) {
      printErrors(result.get.inner)
    }
  }
}
