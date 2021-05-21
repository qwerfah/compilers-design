import analysis._
import grammar._
import scala.util.matching.Regex
import data.ParseResult
import data.TreeSerializer
import scala.reflect.io.File

object Main extends App {
  val lexer = new Lexer(File(".").toAbsolute + "/code.code")
  val tokens: List[String] = lexer.getTokens()

  tokens.foreach(println(_))

  val parser = new Parser(tokens)
  val result: ParseResult = parser.parse()

  if (result.isSuccess) {
    val serializer = new TreeSerializer("tree.dot")
  } else {
    result.printErrors()
  }

}
