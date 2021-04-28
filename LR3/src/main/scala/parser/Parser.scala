package parser

import scala.util.matching.Regex
import grammar._
import java.security.DrbgParameters.Reseed

/** Perform parseing of input token stream and build
  * parse tree according to the specified grammar rules.
  *
  * @param tokens Input token stream.
  */
class Parser(val tokens: List[String]) {
  if (tokens == null || tokens.isEmpty)
    throw new Exception("Invalid token stream")

  /** Launch parsing process for current token stream.
    *
    * @return Parse result which contains parse tree or parsing errors.
    */
  def parse(pos: Int = 0): ParseResult = {
    val result = parseBlock(pos)

    if (result.isSuccess) {
      result
    } else {
      new ParseResult(
        s"Position ${pos}: error while parsing program - block expected",
        pos,
        result
      )
    }
  }

  /** Parse code block from token stream according to the grammar rule:
    * block : '{' operator_list '}';
    *
    * @param pos Position from which parsing begins.
    * @return Parse result which contains parse tree or parsing errors.
    */
  private def parseBlock(pos: Int): ParseResult = {
    if (tokens(pos) == "{") {
      val result = parseOperatorList(pos + 1)

      if (result.isSuccess) {
        if (tokens(result.pos) == "}") {
          new ParseResult(
            new Node(
              "block",
              new Node("{") :: result.tree.get :: new Node("}") :: Nil
            ),
            result.pos + 1
          )
        } else {
          new ParseResult(
            s"Position ${result.pos}: error while parsing block - '}' expected",
            result.pos
          )
        }
      } else {
        new ParseResult(
          s"Position ${pos + 1}: error while parsing block",
          pos + 1,
          result
        )
      }
    }

    new ParseResult(
      s"Position ${pos}: error while parsing block - '{' expected",
      pos
    )
  }

  /** Parse operator list from token stream according to the grammar rule:
    * operator_list : operator tail;
    *
    * @param pos Position from which parsing begins.
    * @return Parse result which contains parse tree or parsing errors.
    */
  private def parseOperatorList(pos: Int): ParseResult = {
    val opResult = parseOperator(pos)

    if (opResult.isSuccess) {
      val tailResult = parseTail(opResult.pos)

      if (tailResult.isSuccess) {
        new ParseResult(
          new Node(
            "operator_list",
            opResult.tree.get :: tailResult.tree.get :: Nil
          ),
          tailResult.pos
        )
      } else {
        new ParseResult(
          s"Position ${opResult.pos}: error while parsing operator list - tail expected",
          opResult.pos,
          tailResult
        )
      }
    }

    new ParseResult(
      s"Position ${pos}: error while parsing operator list - operator expected",
      pos,
      opResult
    )
  }

  /** Parse operator from token stream according to the grammar rule:
    * operator_list : operator tail;
    *
    * @param pos Position from which parsing begins.
    * @return Parse result which contains parse tree or parsing errors.
    */
  private def parseOperator(pos: Int): ParseResult = {
    val idResult = parseId(pos)

    if (idResult.isSuccess) {
      if (tokens(idResult.pos) == "=") {
        val exprResult = parseExpr(idResult.pos + 1)

        if (exprResult.isSuccess) {
          new ParseResult(
            new Node(
              "operator",
              idResult.tree.get :: new Node("=") :: exprResult.tree.get :: Nil
            ),
            exprResult.pos
          )
        } else {
          new ParseResult(
            s"Position ${idResult.pos + 1}: error while parsing operator - expression expected",
            idResult.pos + 1,
            exprResult
          )
        }
      } else {
        new ParseResult(
          s"Position ${idResult.pos + 1}: error while parsing operator - '=' expected",
          idResult.pos
        )
      }
    }

    new ParseResult(
      s"Position ${pos}: error while parsing operator - identifier expected",
      pos,
      idResult
    )
  }

  /** Parse operator list tail from token stream according to the grammar rule:
    * operator_list : operator tail;
    *
    * @param pos Position from which parsing begins.
    * @return Parse result which contains parse tree or parsing errors.
    */
  private def parseTail(pos: Int): ParseResult = {
    if (tokens(pos) == ";") {
      val result = parseOperatorList(pos + 1)

      if (result.isSuccess) {
        new ParseResult(
          new Node("tail", result.tree.get.childs.get),
          result.pos
        )
      } else {
        new ParseResult(
          s"Position ${pos + 1}: error while parsing tail - operator expected",
          pos + 1,
          result
        )
      }
    }

    // Tail allowed to be empty
    new ParseResult(new Node("eps"), pos)
  }

  /** Parse expression from token stream according to the grammar rule:
    * expr : simple_expr | simple_expr rel_op simple_expr;
    *
    * @param pos Position from which parsing begins.
    * @return Parse result which contains parse tree or parsing errors.
    */
  private def parseExpr(pos: Int): ParseResult = {
    val parser = new Parser(tokens.drop(pos))
    var result: ParseResult = parser.parse()
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
    * @param pos Position from which parsing begins.
    * @return Parse result which contains parse tree or parsing errors.
    */
  private def parseSimpleExpr(pos: Int): ParseResult = {
    new ParseResult
  }

  /** Parse term from input token stream according to the grammar rule:
    * term : factor | term mul_op factor;
    *
    * @param pos Position from which parsing begins.
    * @return Parse result which contains parse tree or parsing errors.
    */
  private def parseTerm(pos: Int): ParseResult = {
    new ParseResult
  }

  /** Parse factor from input token stream according to the grammar rule:
    * factor : id | const | '(' simple_expr ')' | 'not' factor;
    *
    * @param pos Position from which parsing begins.
    * @return Parse result which contains parse tree or parsing errors.
    */
  private def parseFactor(pos: Int): ParseResult = {
    new ParseResult
  }

  /** Parse sign from input token stream according to the grammar rule:
    * sign :'+' | '-';
    *
    * @param pos Position from which parsing begins.
    * @return Parse result which contains parse tree or parsing errors.
    */
  private def parseSign(pos: Int): ParseResult = {
    val signRegex: Regex = "+|-".r

    if (signRegex.matches(tokens(pos))) {
      new ParseResult(new Node("sign", new Node(tokens(pos)) :: Nil), pos + 1)
    } else {
      new ParseResult(s"Position $pos: sign expected", pos)
    }
  }

  /** Parse relation operation from input
    * token stream according to the grammar rule:
    * rel_op : '=' | '<>' | '<' | '<=' | '>' | '>=';
    *
    * @param pos Position from which parsing begins.
    * @return Parse result which contains parse tree or parsing errors.
    */
  private def parseRelOp(pos: Int): ParseResult = {
    val relOpRegex: Regex = "=|<>|<|<=|>|>=".r

    if (relOpRegex.matches(tokens(pos))) {
      new ParseResult(new Node("rel_op", new Node(tokens(pos)) :: Nil), pos + 1)
    } else {
      new ParseResult(s"Position $pos: relation operation expected", pos)
    }
  }

  /** Parse sum operation from input token stream according to the grammar rule:
    * sum_op : '+' | '-' | 'or';
    *
    * @param pos Position from which parsing begins.
    * @return Parse result which contains parse tree or parsing errors.
    */
  private def parseSumOp(pos: Int): ParseResult = {
    val sumOpRegex: Regex = "\\+|-|or".r

    if (sumOpRegex.matches(tokens(pos))) {
      new ParseResult(new Node("sum_op", new Node(tokens(pos)) :: Nil), pos + 1)
    } else {
      new ParseResult(s"Position $pos: sum operation expected", pos)
    }
  }

  /** Parse multiplication operation from input
    * token stream according to the grammar rule:
    * mul_op : '*' | '/' | 'div' | 'mod' | 'and';
    *
    * @param pos Position from which parsing begins.
    * @return Parse result which contains parse tree or parsing errors.
    */
  private def parseMulOp(pos: Int): ParseResult = {
    val mulOpRegex: Regex = "\\*|/|div|mod|and".r

    if (mulOpRegex.matches(tokens(pos))) {
      new ParseResult(new Node("mul_op", new Node(tokens(pos)) :: Nil), pos + 1)
    } else {
      new ParseResult(s"Position $pos: multiplication operation expected", pos)
    }
  }

  /** Parse identifier from input token stream according to the grammar rule:
    * id : 'a' .. 'z' +;
    *
    * @param pos Position from which parsing begins.
    * @return Parse result which contains parse tree or parsing errors.
    */
  private def parseId(pos: Int): ParseResult = {
    val idRegex: Regex = "[_a-zA-Z][_a-zA-Z0-9]{0,30}".r

    if (idRegex.matches(tokens(pos))) {
      new ParseResult(new Node("id", new Node(tokens(pos)) :: Nil), pos + 1)
    } else {
      new ParseResult(s"Position $pos: invalid identifier", pos)
    }
  }

  /** Parse constant from input token stream according to the grammar rule:
    * const : '0' .. '9' +;
    *
    * @param pos Position from which parsing begins.
    * @return Parse result which contains parse tree or parsing errors.
    */
  private def parseConst(pos: Int): ParseResult = {
    new ParseResult
  }
}
