package parser

import java.io.PrintWriter
import java.io.File

/** Tree serializer which converts 
  * parse tree to DOT notation and save to file.
  *
  * @param filename File name to save serialized parse tree.
  */
class TreeSerializer(val filename: String) {
    if (filename.isBlank()) {
        throw new Exception("Invalid filename.")
    }

    def serialize(tree: Node) {
        val writer = new PrintWriter(new File(filename))

        writer.write("digraph ParseTree {\n")
        _serialize(tree, writer)
        writer.write("}\n")
        writer.close
    }

    private def _serialize(node: Node, writer: PrintWriter) {
        if (!node.childs.isDefined) return
        for (child <- node.childs.get) {
            writer.write(s""""${node.symbol.name}" -> "${child.symbol.name}"\n""")
            _serialize(child, writer)
        }
    }
}