package analysis

import grammar._
import scala.collection.mutable.Stack
import java.{util => ju}

class Parser(val grammar: Grammar, val table: ControlTable) {
  def parse(input: List[GrammarSymbol]) {
    val stack = Stack[GrammarSymbol](table.boarder)
    val chain = input :+ table.boarder
    var pos = 0

    def shift(): Unit = {
      stack.push(chain(pos))
      pos += 1
    }

    def conv(): Unit = {
      var rhs = stack.pop() :: Nil

      while (
        stack.top.stype == SymbolType.NonTerm ||
        !rhs.find(s => s.stype == SymbolType.Term).isDefined ||
        table.table(
          (stack.top, rhs.findLast(s => s.stype == SymbolType.Term).get)
        ) == PrecedenceType.Neighbors
      ) {
        rhs = rhs :+ stack.pop()
      }

      println("conv: ", rhs)

      val rule = grammar.rules.find(r => r.rhs == rhs)

      if (!rule.isDefined) {
        throw new NoSuchElementException("No matching rule for current base")
      }

      stack.push(rule.get.lhs.head)
    }

    while (true) {
      val s = stack.find(s => s.stype == SymbolType.Term).get
      if (s == table.boarder && chain(pos) == table.boarder) return

      println("pair: ", (s, chain(pos)))

      table.table((s, chain(pos))) match {
        case PrecedenceType.Neighbors | PrecedenceType.Precedes => shift()
        case PrecedenceType.Follows                             => conv()
      }

    }
  }
}
