import xml._
import grammar._
import analysis._

object Main extends App {
  val reader = new XmlReader("adduced_grammar.xml")
  val grammar: Grammar = reader.parse()

  println(grammar)

  val table = new ControlTable(grammar)

  println
  println(table)

  val parser = new Parser(grammar, table)

  println
  parser.parse(
    new GrammarSymbol("id", SymbolType.Term) ::
      new GrammarSymbol("+") ::
      new GrammarSymbol("const", SymbolType.Term) ::
      Nil
  )
}
