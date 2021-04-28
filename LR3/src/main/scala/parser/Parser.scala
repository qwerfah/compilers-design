package parser

import scala.util.matching.Regex
import grammar._

/** Perform parseing of input token stream and build
  * parse tree according to the specified grammar rules.
  *
  * @param tokens Input token stream.
  */
class Parser(val tokens: List[String]) {
  if (tokens == null || tokens.isEmpty)
    throw new Exception("Invalid token stream")

  private var pos: Int = 0

  /** Launch parsing process for current token stream.
    *
    * @return Parse result which contains parse tree or parsing errors.
    */
  def parse: ParseResult = {
    val result = parseExpr
    if (result.isSuccess) {
      result
    } else {
      new ParseResult(s"Position $pos: error while parsing expression", result)
    }
  }

  /** Parse expression from token stream according to the grammar rule:
    * expr : simple_expr | simple_expr rel_op simple_expr;
    *
    * @return Parse result which contains parse tree or parsing errors.
    */
  def parseExpr: ParseResult = {
    var result: ParseResult = parseSimpleExpr
    if (result.isSuccess) {
      result = parseRelOp
      if (result.isSuccess) {
        result = parseSimpleExpr
        if (result.isSuccess) {
          new ParseResult(new Node("expr", result.tree.get :: Nil))
        } else {
          new ParseResult(
            s"Position $pos: second simple expression required",
            result
          )
        }
      }
    } else {
      new ParseResult(s"Position $pos: simple expression required", result)
    }

    new ParseResult
  }

  /** Parse simple expression from token stream accoridng to the grammar rule:
    * simple_expr : term | sign term | simple_expr sum_op term;
    *
    * @return Parse result which contains parse tree or parsing errors.
    */
  def parseSimpleExpr: ParseResult = {
    new ParseResult
  }

  /** Parse term from input token stream according to the grammar rule:
    * term : factor | term mul_op factor;
    *
    * @return Parse result which contains parse tree or parsing errors.
    */
  def parseTerm: ParseResult = {
    new ParseResult
  }

  /** Parse factor from input token stream according to the grammar rule:
    * factor : id | const | '(' simple_expr ')' | 'not' factor;
    *
    * @return Parse result which contains parse tree or parsing errors.
    */
  def parseFactor: ParseResult = {
    new ParseResult
  }

  /** Parse sign from input token stream according to the grammar rule:
    * sign :'+' | '-';
    *
    * @return Parse result which contains parse tree or parsing errors.
    */
  def parseSign: ParseResult = {
    val signRegex: Regex = "+|-".r

    if (signRegex.matches(tokens(pos))) {
      new ParseResult(new Node("sign", tokens(pos)))
    } else {
      new ParseResult(s"Position $pos: sign expected")
    }
  }

  /** Parse relation operation from input
    * token stream according to the grammar rule:
    * rel_op : '=' | '<>' | '<' | '<=' | '>' | '>=';
    *
    * @return Parse result which contains parse tree or parsing errors.
    */
  def parseRelOp: ParseResult = {
    val relOpRegex: Regex = "=|<>|<|<=|>|>=".r

    if (relOpRegex.matches(tokens(pos))) {
      new ParseResult(new Node("rel_op", tokens(pos)))
    } else {
      new ParseResult(s"Position $pos: relation operation expected")
    }
  }

  /** Parse sum operation from input token stream according to the grammar rule:
    * sum_op : '+' | '-' | 'or';
    *
    * @return Parse result which contains parse tree or parsing errors.
    */
  def parseSumOp: ParseResult = {
    val sumOpRegex: Regex = "\\+|-|or".r

    if (sumOpRegex.matches(tokens(pos))) {
      new ParseResult(new Node("sum_op", tokens(pos)))
    } else {
      new ParseResult(s"Position $pos: sum operation expected")
    }
  }

  /** Parse multiplication operation from input
    * token stream according to the grammar rule:
    * mul_op : '*' | '/' | 'div' | 'mod' | 'and';
    *
    * @return Parse result which contains parse tree or parsing errors.
    */
  def parseMulOp: ParseResult = {
    val mulOpRegex: Regex = "\\*|/|div|mod|and".r

    if (mulOpRegex.matches(tokens(pos))) {
      new ParseResult(new Node("mul_op", tokens(pos)))
    } else {
      new ParseResult(s"Position $pos: multiplication operation expected")
    }
  }

  /** Parse identifier from input token stream according to the grammar rule:
    * id : 'a' .. 'z' +;
    *
    * @return Parse result which contains parse tree or parsing errors.
    */
  def parseId: ParseResult = {
    val idRegex: Regex = "[_a-zA-Z][_a-zA-Z0-9]{0,30}".r

    if (idRegex.matches(tokens(pos))) {
      new ParseResult(new Node("id", tokens(pos)))
    } else {
      new ParseResult(s"Position $pos: invalid identifier")
    }
  }

  /** Parse constant from input token stream according to the grammar rule:
    * const : '0' .. '9' +;
    *
    * @return Parse result which contains parse tree or parsing errors.
    */
  def parseConst: ParseResult = {
    new ParseResult
  }
}
