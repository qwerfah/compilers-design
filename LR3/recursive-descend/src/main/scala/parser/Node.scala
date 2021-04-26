package parser

import grammar.GrammarSymbol

/** Describes node of parse tree.
  * 
  * @param id Id of parse tree node.
  * @param symbol symbol (terminal or nonterminal), decribed by this node.
  * @param childs child nodes of this node in parse tree.
  */
class Node(val symbol: GrammarSymbol, val childs: Option[List[Node]] = None) {
  private val _id: Symbol = Symbol(symbol.name)
  def id = _id
}
