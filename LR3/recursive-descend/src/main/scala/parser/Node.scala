package parser

import grammar.GrammarSymbol
import grammar.Grammar
import grammar.SymbolType

/** Describes node of parse tree.
  *
  * @param id Id of parse tree node.
  * @param symbol symbol (terminal or nonterminal), decribed by this node.
  * @param childs child nodes of this node in parse tree.
  */
class Node(val symbol: GrammarSymbol, val childs: Option[List[Node]] = None) {
  private val _id: Symbol = Symbol(symbol.name)
  def id = _id

  /** Constructor for tree leaf without childs.
    *
    * @param symbol Symbol represented by this node.
    */
  def this(symbol: GrammarSymbol) {
    this(symbol, None)
  }

  /** Constructor for tree leaf without childs.
    *
    * @param name Name of symbol represented by this node
    * (default nonterminal without spell).
    */
  def this(name: String) {
    this(new GrammarSymbol(name), None)
  }

  def this(name: String, spell: String) {
    this(new GrammarSymbol(name, Option(spell), SymbolType.Term), None)
  }

  /** Constructor for tree node with childs.
    *
    * @param symbol Symbol represented by this node.
    * @param childs Child nodes list.
    */
  def this(symbol: GrammarSymbol, childs: List[Node]) {
    this(symbol, Option(childs))
  }

  /** Constructor for tree node with childs.
    *
    * @param name Name of symbol represented by this node.
    * @param childs Child nodes list.
    */
  def this(name: String, childs: List[Node]) {
    this(new GrammarSymbol(name), Option(childs))
  }
}
