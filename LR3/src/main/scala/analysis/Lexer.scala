package analysis

import grammar._
import data._

class Lexer(code: String) {
    if (code == null || code.isBlank()) {
        throw new Exception("Invalid input string")
    }

}