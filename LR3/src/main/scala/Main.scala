import analysis._
import grammar._
import scala.util.matching.Regex
import data.ParseResult
import data.TreeSerializer
import scala.reflect.io.File

object Main extends App {
  val lexer = new Lexer(File(".").toAbsolute + "/code.code")
  val tokens: List[String] = lexer.getTokens()

  println("TOKENS:")
  for (i <- tokens.indices) {
    println(s"${i}: ${tokens(i)}")
  }

  val parser = new Parser(tokens)
  println("\nPARSE:")
  val result: ParseResult = parser.parse()

  if (result.isSuccess) {
    val serializer = new TreeSerializer("tree.dot")
    serializer.serialize(result.tree.get)
  } else {
    println("\nERRORS:")
    result.printErrors()
  }
  println("\nDONE\n")
}
