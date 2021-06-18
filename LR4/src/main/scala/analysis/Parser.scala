package analysis

import grammar._
import scala.collection.mutable.Stack
import java.{util => ju}

class Parser(val grammar: Grammar, val table: ControlTable) {
  def parse(input: List[GrammarSymbol]): List[GrammarSymbol] = {
    val stack = Stack[GrammarSymbol](table.boarder)
    val chain = input :+ table.boarder
    var pos = 0
    var postfix = List[GrammarSymbol]()

    def matchRule(rhs: List[GrammarSymbol])(rule: GrammarRule): Boolean = {
      val f1 = rhs.filter(s => s.stype == SymbolType.Term)
      val f2 = rule.rhs.filter(s => s.stype == SymbolType.Term)

      return f1 == f2
    }

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
          stack.top,
          (rhs.findLast(s => s.stype == SymbolType.Term).get)
        ) == PrecedenceType.Neighbors
      ) {
        rhs = stack.pop() +: rhs
      }

      println("conv: ", rhs)

      val rule = grammar.rules.find(matchRule(rhs) _)

      if (!rule.isDefined) {
        throw new NoSuchElementException(s"No matching rule for base ${rhs}")
      }

      postfix = postfix ::: rhs.filter(s => s.stype == SymbolType.Term)

      stack.push(rule.get.lhs.head)
    }

    while (true) {
      val s = stack.find(s => s.stype == SymbolType.Term).get
      if (s == table.boarder && chain(pos) == table.boarder) return postfix

      println("pair: ", (s, chain(pos)), table.table((s, chain(pos))))

      table.table((s, chain(pos))) match {
        case PrecedenceType.Neighbors | PrecedenceType.Precedes => shift()
        case PrecedenceType.Follows                             => conv()
      }

    }

    return postfix
  }
}
