import xml._
import grammar._
import analysis._

import scala.io.StdIn.readLine
import scala.util.parsing.json.Lexer

object Main extends App {
  val regex = "^(?!(?:for|while|do)$)[_a-zA-Z][_a-zA-Z0-9]{0,30}".r
  println(regex.matches("_while"))

  val reader = new XmlReader("adduced_grammar.xml")
  val grammar: Grammar = reader.parse()

  println(grammar)

  val table = new ControlTable(grammar)

  println
  println(table)

  val parser = new Parser(grammar, table)
  val input = "\"str\" + ( 56 - ( ( 78 or 12 ) * 22 ) ) * 11"
  val lexer = new SimpleLexer(grammar)
  var tokens: List[GrammarSymbol] = null

  try {
    tokens = lexer.getTokens(input)
  } catch {
    case e: Exception =>
      println(s"Can't transform input to token stream ${e.getMessage()}")
  }

  if (tokens != null) {
    try {
      println
      parser.parse(tokens).foreach(s => print(s"${s.spell.get} "))
    } catch {
      case _: Exception => println("Invalid input expression")
    }
  }
}
