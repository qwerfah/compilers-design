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
  val res = parser.parse(
    new GrammarSymbol("id") ::
      new GrammarSymbol("+") ::
      // new GrammarSymbol("(") ::
      new GrammarSymbol("const") ::
      new GrammarSymbol("==") ::
      new GrammarSymbol("id") ::
      // new GrammarSymbol(")") ::
      Nil
  )

  res.foreach(s => print(s"${s.name} "))
}
