package data.nodes

import grammar.GrammarSymbol
import grammar.Grammar
import grammar.SymbolType

/** Describes node of parse tree.
  *
  * @param id Id of parse tree node.
  * @param symbol symbol (terminal or nonterminal), decribed by this node.
  * @param childs child nodes of this node in parse tree.
  */
abstract class Node(
    val name: String,
    val childs: Option[List[Node]] = None
) {
  private val _id: Symbol = Symbol(name)
  def id = _id

  /** Constructor for tree leaf without childs.
    *
    * @param name Name of symbol represented by this node
    * (default nonterminal without spell).
    */
  def this(name: String) {
    this(name, None)
  }
}

/** Describes factor.
  *
  * @param symbol Node name (grammar symbol name).
  * @param childs child nodes of this node in parse tree.
  */
class Factor(name: String, childs: List[Node])
    extends Node(name, Option(childs))

/** Describes tail.
  *
  * @param name Node name (grammar symbol name).
  * @param childs Child nodes of this node in parse tree.
  */
class Tail(name: String, childs: List[Node]) extends Node(name, Option(childs))

/** Describes operator.
  *
  * @param name Node name (grammar symbol name).
  * @param childs Child nodes of this node in parse tree.
  */
class Operator(name: String, childs: List[Node])
    extends Node(name, Option(childs))

/** Describes program.
  *
  * @param name Node name (grammar symbol name).
  * @param childs Child nodes of this node in parse tree.
  */
class Programm(name: String, childs: List[Node])
    extends Node(name, Option(childs))

/** Describes block.
  *
  * @param name Node name (grammar symbol name).
  * @param childs Child nodes of this node in parse tree.
  */
class Block(name: String, childs: List[Node]) extends Node(name, Option(childs))

/** Describes expression.
  *
  * @param name Node name (grammar symbol name).
  * @param childs Child nodes of this node in parse tree.
  */
class Expr(name: String, childs: List[Node]) extends Node(name, Option(childs))

/** Describes simple expression.
  *
  * @param name Node name (grammar symbol name).
  * @param childs Child nodes of this node in parse tree.
  */
class SimpleExpr(name: String, childs: List[Node])
    extends Node(name, Option(childs))

/** Describes additional simple expression.
  *
  * @param name Node name (grammar symbol name).
  * @param childs Child nodes of this node in parse tree.
  */
class SimpleExpr0(name: String, childs: List[Node])
    extends Node(name, Option(childs))

/** Describes term.
  *
  * @param name Node name (grammar symbol name).
  * @param childs Child nodes of this node in parse tree.
  */
class Term(name: String, childs: List[Node]) extends Node(name, Option(childs))

/** Describes additional term.
  *
  * @param name Node name (grammar symbol name).
  * @param childs Child nodes of this node in parse tree.
  */
class Term0(name: String, childs: List[Node]) extends Node(name, Option(childs))

/** Describes operator list in block.
  *
  * @param name Node name (grammar symbol name).
  * @param childs Child nodes of this node in parse tree.
  */
class OperatorList(name: String, childs: List[Node])
    extends Node(name, Option(childs))

/** Describes relation operation.
  *
  * @param name Node name (grammar symbol name).
  * @param childs Child nodes of this node in parse tree.
  */
class RelOp(name: String, childs: List[Node]) extends Node(name, Option(childs))

/** Describes multiplication operation.
  *
  * @param name Node name (grammar symbol name).
  * @param childs Child nodes of this node in parse tree.
  */
class MulOp(name: String, childs: List[Node]) extends Node(name, Option(childs))

/** Describes sum operation.
  *
  * @param name Node name (grammar symbol name).
  * @param childs Child nodes of this node in parse tree.
  */
class SumOp(name: String, childs: List[Node]) extends Node(name, Option(childs))

/** Describes number sign.
  *
  * @param name Node name (grammar symbol name).
  * @param childs Child nodes of this node in parse tree.
  */
class Sign(name: String, childs: List[Node]) extends Node(name, Option(childs))

/** Describes variable identifier.
  *
  * @param name Node name (grammar symbol name).
  * @param childs Child nodes of this node in parse tree.
  */
class Ident(name: String, childs: List[Node]) extends Node(name, Option(childs))

/** Describes numeric, char or string literal.
  *
  * @param name Node name (grammar symbol name).
  * @param childs Child nodes of this node in parse tree.
  */
class Const(name: String, childs: List[Node]) extends Node(name, Option(childs))

class Terminal(name: String) extends Node(name)
