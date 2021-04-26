package parser

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

    }
}