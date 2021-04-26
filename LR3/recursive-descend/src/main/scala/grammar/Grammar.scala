package grammar

// Grammar symbol type
object SymbolType extends Enumeration {
    type SymbolType = Value
    val Term, NonTerm, Eps = Value
}

// Grammar symbol
class Symbol(val name: String, val spell: Option[String], val stype: SymbolType.SymbolType = SymbolType.Term) {
    if (name == null || name.isBlank()) throw new Exception("Invalid name")
    if (stype == null) throw new Exception("Invalid symbol type")
}

class Rule(val lhs: List[Symbol], val rhs: List[Symbol]) {
    if (lhs == null || lhs.isEmpty) throw new Exception("Invalid left-hand side of the rule")
    if (rhs == null) throw new Exception("Invalid right-hand side of the rule")
}

class Grammar(val terms: List[Symbol], val nonTerms: List[Symbol], val rules: List[Rule], val axiom: Symbol) {
    if (terms == null || terms.isEmpty) throw new Exception("Invalid terms list")
    if (nonTerms == null || nonTerms.isEmpty) throw new Exception("Invalid nonterms list")
    if (rules == null || rules.isEmpty) throw new Exception("Invalid rules list")
    if (axiom == null) throw new Exception("Invalid axiom")
}