package parser

import java.io.PrintWriter
import java.io.File

/** Tree serializer which converts
  * parse tree to DOT notation and saves to file.
  *
  * @param filename File name to save serialized parse tree.
  */
class TreeSerializer(val filename: String) {
  if (filename.isBlank()) {
    throw new Exception("Invalid filename.")
  }

  private val _writer = new PrintWriter(new File(filename))

  /** Serialize parse tree to file in DOT notation.
    *
    * @param tree Parse tree to serialize.
    */
  def serialize(tree: Node) {
    _writer.write("digraph ParseTree {\n")
    _serialize(tree)
    _writer.write("}\n")
    _writer.close
  }

  /** Recursive tree serialization from node to its childs.
    *
    * @param node Current serializable node.
    */
  private def _serialize(node: Node) {
    if (!node.childs.isDefined) return
    for (child <- node.childs.get) {
      _writer.write(s""""${node.symbol.name}" -> "${child.symbol.name}"\n""")
      _serialize(child)
    }
  }
}
