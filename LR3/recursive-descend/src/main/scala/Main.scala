import parser._
import grammar._
import scala.util.matching.Regex

object Main extends App {
  val idRegex: Regex = "=|<>|<|<=|>|>=".r

  if (idRegex.matches("<=")) {
    println("Valid identifier")
  } else {
    println("Invalid identifier")
  }
}
