package xml

import scala.reflect.io.File
import java.io.FileReader
import java.io._
import scala.xml

import grammar._

/** Xml parser for xml files with xml context-free grammar representation.
  *
  * @param filename Xml file name.
  */
class XmlReader(filename: String) {

  private val _grammar: xml.Elem =
    xml.XML.loadFile(File(".").toAbsolute + "\\resources\\" + filename)

  /** Parse xml file content to context-free grammar.
    *  @return Context-free grammar object.
    */
  def parse(): Grammar = {
    val terminals = (_grammar \ "terminalsymbols" \ "term")
      .map(term => new GrammarSymbol((term \ "@name").text, SymbolType.Term))
      .toSet

    val nonterminals = (_grammar \ "nonterminalsymbols" \ "nonterm")
      .map(nonterm =>
        new GrammarSymbol((nonterm \ "@name").text, SymbolType.NonTerm)
      )
      .toSet

    val alphabet: Set[GrammarSymbol] = terminals ++ nonterminals

    val rules = (_grammar \ "productions" \ "production")
      .map(rule => {
        val lhs = List(
          alphabet
            .find(symbol => symbol.name == (rule \ "lhs" \ "@name").text)
            .get
        )

        val rhs = (rule \ "rhs" \ "symbol")
          .map(symbol =>
            alphabet.find(s => s.name == (symbol \ "@name").text).get
          )
          .toList

        new GrammarRule(lhs, rhs)
      })
      .toSet

    val axiom = (terminals ++ nonterminals)
      .find(s => s.name == (_grammar \ "startsymbol" \ "@name").text)
      .get

    new Grammar(terminals, nonterminals, rules, axiom)
  }
}
