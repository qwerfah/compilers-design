grammar Grammar;

program : block;

block : '{' operator_list '}';

operator_list : operator tail;

tail : ';' operator tail | ; 

operator : id '=' expr;

<<<<<<< HEAD:LR3/left_factorized.g4
expr : simple_expr expr#0;

expr#0 : rel_op simple_expr | ;

simple_expr : term simpe_expr';
=======
expr : simple_expr expr_a;

expr_a : rel_op simple_expr | ;
>>>>>>> 3881ef6f6a5a8c328492b2183e5651aeda67b25f:LR3/Grammar.g4

simple_expr : term | sign term | term simple_expr_a | sign term simple_expr_a;

simple_expr_a : sum_op term | sum_op term simple_expr_a;

term : factor | factor term_a;

term_a : mul_op factor | mul_op factor term_a;

factor : id | const | '(' simple_expr ')' | 'not' factor;

sign :'+' | '-';

rel_op : '=' | '<>' | '<' | '<=' | '>' | '>=';

sum_op : '+' | '-' | 'or';

mul_op : '*' | '/' | 'div' | 'mod' | 'and';

id : 'a' .. 'z' +;

const : '0' .. '9' +;

