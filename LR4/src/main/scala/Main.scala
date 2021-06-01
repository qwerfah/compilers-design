import xml._
import grammar._
import analysis._

object Main extends App {
  val reader = new XmlReader("adduced_grammar.xml")
  val grammar: Grammar = reader.parse()

  println(grammar)

  val list = List(1, 2, 3) :: List(4, 5, 6) :: Nil

  println(list.reduce((a, b) => a ::: b))

  val table = new ControlTable(grammar)
}
