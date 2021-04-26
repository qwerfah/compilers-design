package parser

import grammar.Symbol

/** Describes node of parse tree.
  * 
  * @param id Id of parse tree node.
  * @param symbol symbol (terminal or nonterminal), decribed by this node.
  * @param childs child nodes of this node in parse tree.
  */
class Node(val id: Int, val symbol: Symbol, val childs: List[Node])
