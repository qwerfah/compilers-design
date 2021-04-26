package parser

/** Result of pasing operation (contains parse tree or pasing errors).
  * 
  * @param isSuccess Shows whether the result of parsing operation is parse tree or error.
  * @param tree Parse tree which built as a result of parseing operation.
  * @param message Error message (in case of error).
  * @param inner Inner results that contain inner errors.
  */
class ParseResult(
    val isSuccess: Boolean = true, 
    val tree: Option[Node] = None,
    val message: String = "",  
    val inner: Option[ParseResult] = None) {

    /** Constructor for error result of parsing operation.
      *
      * @param message Error message.
      * @param inner Inner errors.
      */
    def this(message: String, inner: Option[ParseResult]) {
        this(false, None, message, inner)
    }

    /** Constructor for error result without inner errors.
      *
      * @param message Error message.
      */
    def this(message: String) {
        this(false, None, message, None)
    }
}