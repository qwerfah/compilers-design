package grammar

import scala.util.matching.Regex

class ParseResult(val isSuccess: Boolean = true, val message: String = "", val inner: Option[ParseResult] = None)

class Parser(val tokens: List[String]) {
    if (tokens == null || tokens.isEmpty) throw new Exception("Invalid token stream")

    private var pos: Int = 0

    // Parse input token stream to validate it
    def parse: ParseResult = {
        val result = parseExpr
        if (result.isSuccess) result
        else {
            new ParseResult(false, s"Position $pos: error while parsing expression", Option(result))
        }
    }

    // expr : simple_expr | simple_expr rel_op simple_expr
    def parseExpr: ParseResult = {
        var result: ParseResult = parseSimpleExpr
        if (result.isSuccess) {
            result = parseRelOp
            if (result.isSuccess) {
                result = parseSimpleExpr
                if (result.isSuccess) result 
                else {
                    new ParseResult(false, s"Position $pos: second simple expression required", Option(result))
                }
            }
        }
        else {
            new ParseResult(false, s"Position $pos: simple expression required", Option(result))
        }
        
        new ParseResult
    }

    // simple_expr : term | sign term | simple_expr sum_op term
    def parseSimpleExpr: ParseResult = {
        new ParseResult
    }

    // term : factor | term mul_op factor
    def parseTerm: ParseResult = {
        new ParseResult
    }

    // factor : id | const | '(' simple_expr ')' | 'not' factor
    def parseFactor: ParseResult = {
        new ParseResult
    }

    // sign :'+' | '-'
    def parseSign: ParseResult = {
        new ParseResult
    }

    // rel_op : '=' | '<>' | '<' | '<=' | '>' | '>='
    def parseRelOp: ParseResult = {
        new ParseResult
    }

    // sum_op : '+' | '-' | 'or'
    def parseSumOp: ParseResult = {
        new ParseResult
    }

    // mul_op : '*' | '/' | 'div' | 'mod' | 'and'
    def parseMulOp: ParseResult = {
        new ParseResult
    }

    // id : 'a' .. 'z' +
    def parseId: ParseResult = {
        new ParseResult
    }

    // const : '0' .. '9' +
    def parseConst: ParseResult = {
        new ParseResult
    }
}