package analysis

import java.io.FileReader
import java.io.File

import grammar._
import data._

/** Lexer that splits input file into token list.
  *
  * @param string Name of input file with code.
  */
class Lexer(filename: String) {
  if (filename == null || filename.isBlank()) {
    throw new Exception("Invalid input string")
  }

  /** Split input file into token list.
    *
    * @return List of tokens.
    */
  def getTokens(): List[String] = {
    val source = scala.io.Source.fromFile(filename)
    val lines =
      try source.mkString
      finally source.close()

    lines.split("( +)|(\n)").toList
  }
}
