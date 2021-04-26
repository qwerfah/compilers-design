import parser._
import grammar._

object Main extends App {
    val node1 = new Node(new GrammarSymbol("A"))
    val node2 = new Node(new GrammarSymbol("B"))
    val node3 = new Node(new GrammarSymbol("C"))
    val node4 = new Node(new GrammarSymbol("D"), Option(node1 :: Nil))
    val node5 = new Node(new GrammarSymbol("E"), Option(node2 :: node3 :: Nil))
    val node6 = new Node(new GrammarSymbol("S"), Option(node4 :: node5 :: Nil))

    val serializer = new TreeSerializer("file.dot")
    try {
        serializer.serialize(node6)
        println("Success")
    } catch {
        case e: Exception => println("Error")
    }
}