package analysis

/** Specifies precedenca relation type.
  * If A and B - two grammar symbols, there are three options:
  * - A can precedes B
  * - A can folows B
  * - A can neighbors with B
  */
object PrecedenceType extends Enumeration {
  type PrecedenceType = Value
  val Precedes, Follows, Neighbors, None = Value
}
