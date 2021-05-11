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
  def program(pos: Int): ParseResult = {
    val result = block(pos)

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
  def block(pos: Int): ParseResult = {
    if (tokens(pos) == "{") {
      val result = operatorList(pos + 1)

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
  def operatorList(pos: Int): ParseResult = {
    val opResult = operator(pos)

    if (opResult.isSuccess) {
      val tailResult = tail(opResult.pos)

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
          s"Position ${opResult.pos}: error while " +
            s"parsing operator list - tail expected",
          opResult.pos,
          tailResult
        )
      }
    }

    new ParseResult(
      s"Position ${pos}: error while " +
        s"parsing operator list - operator expected",
      pos,
      opResult
    )
  }

  /** Parse operator from token stream according to the grammar rule:
    * operator : id = expr | block;
    *
    * @param pos Position from which parsing begins.
    * @return Parse result which contains parse tree or parsing errors.
    */
  def operator(pos: Int): ParseResult = {
    val idResult = id(pos)

    if (idResult.isSuccess) {
      if (tokens(idResult.pos) == "=") {
        val exprResult = expr(idResult.pos + 1)

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
            s"Position ${idResult.pos + 1}: error while " +
              s"parsing operator - expression expected",
            idResult.pos + 1,
            exprResult
          )
        }
      } else {
        new ParseResult(
          s"Position ${idResult.pos + 1}: error while " +
            s"parsing operator - '=' expected",
          idResult.pos
        )
      }
    } else {
      val blockResult = block(pos)

      if (blockResult.isSuccess) {
        new ParseResult(
          new Node(
            "operator",
            blockResult.tree.get :: Nil
          ),
          blockResult.pos
        )
      }
    }

    new ParseResult(
      s"Position ${pos}: error while " +
        s"parsing operator - identifier or nested block expected",
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
  def tail(pos: Int): ParseResult = {
    if (tokens(pos) == ";") {
      val result = operatorList(pos + 1)

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
  def expr(pos: Int): ParseResult = {
    val parsers =
      new Parser(tokens.drop(pos), "expr_var1") ::
        new Parser(tokens.drop(pos), "expr_var2") ::
        Nil

    // Recursive descend with rollback
    for (parser <- parsers) {
      val result = parser.parse()

      if (result.isSuccess) {
        result
      }
    }

    new ParseResult(
      s"Position $pos: error while parsing " +
        s"simple expression - simple_expr expected",
      pos
      // Which one of copies results should be returned as inner
    )
  }

  private def expr_var1(pos: Int): ParseResult = {
    val result = simpleExpr(pos)

    if (result.isSuccess) {
      new ParseResult(
        new Node("expr", result.tree.get :: Nil),
        result.pos
      )
    }

    new ParseResult(
      s"Position $pos: error while parsing " +
        s"expression - simple_expr expected",
      pos,
      result
    )
  }

  private def expr_var2(pos: Int): ParseResult = {
    val selResult = simpleExpr(pos)

    if (selResult.isSuccess) {
      val relOpResult = relOp(selResult.pos)

      if (relOpResult.isSuccess) {
        val serResult = simpleExpr(relOpResult.pos)

        if (serResult.isSuccess) {
          new ParseResult(
            new Node(
              "expr",
              selResult.tree.get :: relOpResult.tree.get :: serResult.tree.get :: Nil
            ),
            serResult.pos
          )
        } else {
          new ParseResult(
            s"Position ${relOpResult.pos}: error while " +
              s"parsing expression - simple expression expected",
            relOpResult.pos,
            serResult
          )
        }
      } else {
        new ParseResult(
          s"Position ${selResult.pos}: error while " +
            s"parsing expression - relation operation expected",
          selResult.pos,
          relOpResult
        )
      }
    }

    new ParseResult(
      s"Position $pos: error while parsing " +
        s"expression - simple expression expected",
      pos,
      selResult
    )
  }

  /** Parse simple expression from token stream accoridng to the grammar rule:
    * simple_expr : simple_expr : term | sign term | term simple_expr#0 | sign term simple_expr#0 ;
    *
    * @param pos Position from which parsing begins.
    * @return Parse result which contains parse tree or parsing errors.
    */
  def simpleExpr(pos: Int): ParseResult = {
    val parsers =
      new Parser(tokens.drop(pos), "simpleExpr_var1") ::
        new Parser(tokens.drop(pos), "simpleExpr_var2") ::
        new Parser(tokens.drop(pos), "simpleExpr_var3") ::
        new Parser(tokens.drop(pos), "simpleExpr_var4") ::
        Nil

    // Recursive descend with rollback
    for (parser <- parsers) {
      val result = parser.parse()

      if (result.isSuccess) {
        result
      }
    }

    new ParseResult(
      s"Position $pos: error while parsing " +
        s"simple expression - term or sign expected",
      pos
    )
  }

  /** Parse simple expression from token stream accoridng to the grammar rule:
    * simple_expr : term;
    *
    * @param pos Position from which parsing begins.
    * @return Parse result which contains parse tree or parsing errors.
    */
  private def simpleExpr_var1(pos: Int): ParseResult = {
    val result = term(pos)

    if (result.isSuccess) {
      new ParseResult(
        new Node("simple_expr", result.tree.get :: Nil),
        result.pos
      )
    }

    new ParseResult(
      s"Position $pos: error while parsing " +
        s"simple expression - term expected",
      pos
    )
  }

  /** Parse simple expression from token stream accoridng to the grammar rule:
    * simple_expr : sign term;
    *
    * @param pos Position from which parsing begins.
    * @return Parse result which contains parse tree or parsing errors.
    */
  private def simpleExpr_var2(pos: Int): ParseResult = {
    val signResult = sign(pos)

    if (signResult.isSuccess) {
      val termResult = term(signResult.pos)

      if (termResult.isSuccess) {
        new ParseResult(
          new Node(
            "simple_expr",
            signResult.tree.get :: termResult.tree.get :: Nil
          ),
          termResult.pos
        )
      } else {
        new ParseResult(
          s"Position ${signResult.pos}: error while parsing " +
            s"simple expression - term expected",
          signResult.pos,
          termResult
        )
      }
    }

    new ParseResult(
      s"Position $pos: error while parsing " +
        s"simple expression - sign expected",
      pos
    )
  }

  /** Parse simple expression from token stream accoridng to the grammar rule:
    * simple_expr : term simple_expr#0 ;
    *
    * @param pos Position from which parsing begins.
    * @return Parse result which contains parse tree or parsing errors.
    */
  private def simpleExpr_var3(pos: Int): ParseResult = {
    val termResult = term(pos)

    if (termResult.isSuccess) {
      val seResult = simpleExpr_0(termResult.pos)

      if (seResult.isSuccess) {
        new ParseResult(
          new Node(
            "simple_expr",
            termResult.tree.get :: seResult.tree.get :: Nil
          ),
          seResult.pos
        )
      } else {
        new ParseResult(
          s"Position ${termResult.pos}: error while parsing simple " +
            s"expression - simple_expr#0 expected",
          termResult.pos,
          seResult
        )
      }
    }

    new ParseResult(
      s"Position $pos: error while parsing " +
        s"simple expression - term expected",
      pos,
      termResult
    )
  }

  /** Parse simple expression from token stream accoridng to the grammar rule:
    * simple_expr : sign term simple_expr#0 ;
    *
    * @param pos Position from which parsing begins.
    * @return Parse result which contains parse tree or parsing errors.
    */
  private def simpleExpr_var4(pos: Int): ParseResult = {
    val signResult = sign(pos)

    if (signResult.isSuccess) {
      val termResult = term(signResult.pos)

      if (termResult.isSuccess) {
        val seResult = simpleExpr_0(termResult.pos)

        if (seResult.isSuccess) {
          new ParseResult(
            new Node(
              "simple_expr",
              signResult.tree.get ::
                termResult.tree.get ::
                seResult.tree.get :: Nil
            ),
            seResult.pos
          )
        } else {
          new ParseResult(
            s"Position ${termResult.pos}: error while parsing " +
              s"simple expression - simple_expr#0 expected",
            termResult.pos,
            seResult
          )
        }
      } else {
        new ParseResult(
          s"Position ${signResult.pos}: error while parsing " +
            s"simple expression - term expected",
          signResult.pos,
          termResult
        )
      }
    }

    new ParseResult(
      s"Position $pos: error while parsing " +
        s"simple expression - sign expected",
      pos,
      signResult
    )
  }

  /** Parse additional nonterminal sim[ple_expr#0
    * from input token stream according to the grammar rule:
    * simple_expr#0 : sum_op term simple_expr#3;
    *
    * @param pos Position from which parsing begins.
    * @return Parse result which contains parse tree or parsing errors.
    */
  private def simpleExpr_0(pos: Int): ParseResult = {
    val sumOpResult = sumOp(pos)

    if (sumOpResult.isSuccess) {
      val termResult = term(sumOpResult.pos)

      if (termResult.isSuccess) {
        val seResult = simpleExpr_3(termResult.pos)

        if (seResult.isSuccess) {
          new ParseResult(
            new Node(
              "simple_expr#0",
              sumOpResult.tree.get ::
                termResult.tree.get ::
                seResult.tree.get :: Nil
            ),
            seResult.pos
          )
        } else {
          new ParseResult(
            s"Position ${termResult.pos}: error while parsing " +
              s"simple_expr#0 - simple_expr#3 expected",
            termResult.pos,
            seResult
          )
        }
      } else {
        new ParseResult(
          s"Position ${sumOpResult.pos}: error while parsing " +
            s"simple_expr#0 - term expected",
          sumOpResult.pos,
          termResult
        )
      }
    }

    new ParseResult(
      s"Position $pos: error while parsing " +
        s"simple_expr#0 - sum operation expected",
      pos,
      sumOpResult
    )
  }

  /** Parse additional nonterminal simple_expr#1
    * from input token stream according to the grammar rule:
    * simple_expr#1 : simple_expr#0 | ;
    *
    * @param pos Position from which parsing begins.
    * @return Parse result which contains parse tree or parsing errors.
    */
  private def simpleExpr_1(pos: Int): ParseResult = {
    val result = simpleExpr_0(pos)

    if (result.isSuccess) {
      new ParseResult(
        new Node("simple_expr#1", result.tree.get :: Nil),
        result.pos
      )
    }

    new ParseResult(
      new Node("simple_expr#1"),
      pos
    )
  }

  /** Parse additional nonterminal simple_expr#2
    * from input token stream according to the grammar rule:
    * simple_expr#2 : simple_expr#0 | ;
    *
    * @param pos Position from which parsing begins.
    * @return Parse result which contains parse tree or parsing errors.
    */
  private def simpleExpr_2(pos: Int): ParseResult = {
    val result = simpleExpr_0(pos)

    if (result.isSuccess) {
      new ParseResult(
        new Node("simple_expr#2", result.tree.get :: Nil),
        result.pos
      )
    }

    new ParseResult(
      new Node("simple_expr#2"),
      pos
    )
  }

  /** Parse additional nonterminal simple_expr#3
    * from input token stream according to the grammar rule:
    * simple_expr#3 : simple_expr#0 | ;
    *
    * @param pos Position from which parsing begins.
    * @return Parse result which contains parse tree or parsing errors.
    */
  private def simpleExpr_3(pos: Int): ParseResult = {
    val result = simpleExpr_0(pos)

    if (result.isSuccess) {
      new ParseResult(
        new Node("simple_expr#3", result.tree.get :: Nil),
        result.pos
      )
    }

    new ParseResult(
      new Node("simple_expr#3"),
      pos
    )
  }

  /** Parse term from input token stream according to the grammar rule:
    * term : factor | term mul_op factor;
    *
    * @param pos Position from which parsing begins.
    * @return Parse result which contains parse tree or parsing errors.
    */
  private def term(pos: Int): ParseResult = {
    val factorResult = factor(pos)

    if (factorResult.isSuccess) {
      val termResult = term_1(factorResult.pos)

      if (termResult.isSuccess) {
        new ParseResult(
          new Node("term", factorResult.tree.get :: termResult.tree.get :: Nil),
          termResult.pos
        )
      } else {
        new ParseResult(
          s"Position $pos: error while parsing " +
            s"term - term#1 expected",
          factorResult.pos,
          termResult
        )
      }
    }

    new ParseResult(
      s"Position $pos: error while parsing " +
        s"term - factor expected",
      pos,
      factorResult
    )
  }

  private def term_0(pos: Int): ParseResult = {
    val mulOpResult = mulOp(pos)

    if (mulOpResult.isSuccess) {
      val factorResult = factor(mulOpResult.pos)

      if (factorResult.isSuccess) {
        val termResult = term_2(factorResult.pos)

        if (factorResult.isSuccess) {
          new ParseResult(
            new Node(
              "term#0",
              mulOpResult.tree.get ::
                factorResult.tree.get ::
                termResult.tree.get :: Nil
            ),
            termResult.pos
          )
        } else {
          new ParseResult(
            s"Position ${factorResult.pos}: error while parsing " +
              s"term#0 - term#2 expected",
            factorResult.pos,
            termResult
          )
        }
      } else {
        new ParseResult(
          s"Position ${mulOpResult.pos}: error while parsing " +
            s"term#0 - factor expected",
          mulOpResult.pos,
          factorResult
        )
      }
    }

    new ParseResult(
      s"Position $pos: error while parsing " +
        s"term#0 - multiplication operation expected",
      pos,
      mulOpResult
    )
  }

  private def term_1(pos: Int): ParseResult = {}

  private def term_2(pos: Int): ParseResult = {}

  /** Parse factor from input token stream according to the grammar rule:
    * factor : id | const | '(' simple_expr ')' | 'not' factor;
    *
    * @param pos Position from which parsing begins.
    * @return Parse result which contains parse tree or parsing errors.
    */
  private def factor(pos: Int): ParseResult = {
    new ParseResult
  }

  /** Parse sign from input token stream according to the grammar rule:
    * sign :'+' | '-';
    *
    * @param pos Position from which parsing begins.
    * @return Parse result which contains parse tree or parsing errors.
    */
  private def sign(pos: Int): ParseResult = {
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
  private def relOp(pos: Int): ParseResult = {
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
  private def sumOp(pos: Int): ParseResult = {
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
  private def mulOp(pos: Int): ParseResult = {
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
  private def id(pos: Int): ParseResult = {
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
  private def const(pos: Int): ParseResult = {
    new ParseResult
  }
}
