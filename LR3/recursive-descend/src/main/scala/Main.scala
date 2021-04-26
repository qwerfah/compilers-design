import parser._

object Main extends App {
    val parser: Parser = new Parser("" :: Nil)
    println(parser.parse.isSuccess)
}