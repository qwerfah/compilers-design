package parser

import scala.util.matching.Regex
import grammar._

/** Perform parseing of input token stream and build 
  * parse tree according to the specified grammar rules.
  *
  * @param tokens Input token stream.
  */
class Parser(val tokens: List[String]) {
    if (tokens == null || tokens.isEmpty) throw new Exception("Invalid token stream")

    private var pos: Int = 0

    /** Launch parsing process for current token stream.
      *
      * @return Parse result which contains parse tree or parsing errors.
      */
    def parse: ParseResult = {
        val result = parseExpr
        if (result.isSuccess) result
        else {
            new ParseResult(s"Position $pos: error while parsing expression", Option(result))
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
                if (result.isSuccess) result 
                else {
                    new ParseResult(s"Position $pos: second simple expression required", Option(result))
                }
            }
        }
        else {
            new ParseResult(s"Position $pos: simple expression required", Option(result))
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
        new ParseResult
    }

    /** Parse relation operation from input 
      * token stream according to the grammar rule:
      * rel_op : '=' | '<>' | '<' | '<=' | '>' | '>=';
      *
      * @return Parse result which contains parse tree or parsing errors.
      */
    def parseRelOp: ParseResult = {
        new ParseResult
    }

    /** Parse sum operation from input token stream according to the grammar rule:
      * sum_op : '+' | '-' | 'or';
      *
      * @return Parse result which contains parse tree or parsing errors.
      */
    def parseSumOp: ParseResult = {
        new ParseResult
    }

    /** Parse multiplication operation from input 
      * token stream according to the grammar rule:
      * mul_op : '*' | '/' | 'div' | 'mod' | 'and';
      *
      * @return Parse result which contains parse tree or parsing errors.
      */
    def parseMulOp: ParseResult = {
        new ParseResult
    }

    /** Parse identifier from input token stream according to the grammar rule:
      * id : 'a' .. 'z' +;
      *
      * @return Parse result which contains parse tree or parsing errors.
      */
    def parseId: ParseResult = {
        new ParseResult
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