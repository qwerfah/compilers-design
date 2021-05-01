grammar Grammar;

program : block;

block : '{' operator_list '}';

operator_list : operator tail;

tail : ';' operator tail | ; 

operator : id '=' expr;

expr : simple_expr | simple_expr rel_op simple_expr;

simple_expr : term | sign term | term simpe_expr' | sign term simple_expr';

simple_expr' : sum_op term | sum_op term simple_expr';

term : factor | factor term';

term' : mul_op factor | mul_op factor term';

factor : id | const | '(' simple_expr ')' | 'not' factor;

sign :'+' | '-';

rel_op : '=' | '<>' | '<' | '<=' | '>' | '>=';

sum_op : '+' | '-' | 'or';

mul_op : '*' | '/' | 'div' | 'mod' | 'and';

id : 'a' .. 'z' +;

const : '0' .. '9' +;

