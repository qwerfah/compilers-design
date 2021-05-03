package parser

import scala.util.matching.Regex
import grammar._
import java.security.DrbgParameters.Reseed
import scala.reflect.runtime.{universe => ru}

/** Perform parseing of input token stream and build
  * parse tree according to the specified grammar rules.
  *
  * @param tokens Input token stream.
  */
class Parser(
    val tokens: List[String]
) {
  if (tokens == null || tokens.isEmpty)
    throw new Exception("Invalid token stream")

  private var method: Seq[Any] => Any = null

  def this(tokens: List[String], methodName: String = "parseProgram") {
    this(tokens)

    val m = ru.runtimeMirror(getClass.getClassLoader)
    val methodSymbol = ru.typeOf[Parser].decl(ru.TermName(methodName)).asMethod
    val instanceMirror = m.reflect(this)
    val methodMirror = instanceMirror.reflectMethod(methodSymbol)

    method = methodMirror.apply(_)
  }

  /** Launch parsing process for current token stream.
    *
    * @return Parse result which contains parse tree or parsing errors.
    */
  def parse(pos: Int = 0): ParseResult =
    method(Seq(pos)).asInstanceOf[ParseResult]

  /** Parse program from rule:
    * program : block;
    *
    * @param pos Position from which parsing begins.
    * @return Parse result which contains parse tree or parsing errors.
    */
  def parseProgram(pos: Int): ParseResult = {
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
    val seResult = parseSimpleExpr(pos)

    if (seResult.isSuccess) {
      val eaResult = parseExprA(seResult.pos)

      if (eaResult.isSuccess) {
        new ParseResult(
          new Node("expr", seResult.tree.get :: eaResult.tree.get :: Nil),
          eaResult.pos
        )
      } else {
        new ParseResult(
          s"Position ${seResult.pos}: error while parsing expression - expr_a expected",
          seResult.pos,
          eaResult
        )
      }
    }

    new ParseResult(
      s"Position $pos: error while parsing expression - simple expression expected",
      pos,
      seResult
    )
  }

  /** Parse additional symbol expr_a according to the grammar rule:
    * expr_a : rel_op simple_expr | ;
    * Nonterminal expr_a added to remove ambiguity in expr rule.
    *
    * @param pos Position from which parsing begins.
    * @return Parse result which contains parse tree or parsing errors.
    */
  private def parseExprA(pos: Int): ParseResult = {
    val relOpResult = parseRelOp(pos)

    if (relOpResult.isSuccess) {
      val seResult = parseSimpleExpr(relOpResult.pos)
      if (seResult.isSuccess) {
        new ParseResult(
          new Node("expr_a", relOpResult.tree.get :: seResult.tree.get :: Nil),
          seResult.pos
        )
      } else {
        new ParseResult(
          s"Position ${relOpResult.pos}: error while parsing expr_a - simple expression expected",
          relOpResult.pos,
          seResult
        )
      }
    }

    // expr_a allowed to be empty
    new ParseResult(new Node("expr_a"), pos)
  }

  /** Parse simple expression from token stream accoridng to the grammar rule:
    * simple_expr : term | sign term | term simple_expr_a | sign term simple_expr_a;
    *
    * @param pos Position from which parsing begins.
    * @return Parse result which contains parse tree or parsing errors.
    */
  private def parseSimpleExpr(pos: Int): ParseResult = {
    val parsers =
      new Parser(tokens.drop(pos), "parseSimpleExpr_1") ::
        new Parser(tokens.drop(pos), "parseSimpleExpr_2") ::
        new Parser(tokens.drop(pos), "parseSimpleExpr_3") ::
        new Parser(tokens.drop(pos), "parseSimpleExpr_4") ::
        Nil

    for (parser <- parsers) {
      val result = parser.parse()

      if (result.isSuccess) {
        result
      }
    }

    new ParseResult(
      s"Position $pos: error while parsing simple expression - term expected",
      pos
    )
  }

  /** Parse simple expression from token stream accoridng to the grammar rule:
    * simple_expr : term;
    *
    * @param pos Position from which parsing begins.
    * @return Parse result which contains parse tree or parsing errors.
    */
  private def parseSimpleExpr_1(pos: Int): ParseResult = {
    new ParseResult
  }

  /** Parse simple expression from token stream accoridng to the grammar rule:
    * simple_expr : sign term;
    *
    * @param pos Position from which parsing begins.
    * @return Parse result which contains parse tree or parsing errors.
    */
  private def parseSimpleExpr_2(pos: Int): ParseResult = {
    new ParseResult
  }

  /** Parse simple expression from token stream accoridng to the grammar rule:
    * simple_expr : term simple_expr_a;
    *
    * @param pos Position from which parsing begins.
    * @return Parse result which contains parse tree or parsing errors.
    */
  private def parseSimpleExpr_3(pos: Int): ParseResult = {
    new ParseResult
  }

  /** Parse simple expression from token stream accoridng to the grammar rule:
    * simple_expr : sign term simple_expr_a;
    *
    * @param pos Position from which parsing begins.
    * @return Parse result which contains parse tree or parsing errors.
    */
  private def parseSimpleExpr_4(pos: Int): ParseResult = {
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
