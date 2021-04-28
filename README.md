# Проектирование компиляторов
## Лабораторные работы
* ### ЛР1 - Парсер регулярных выражений
 
  #### Вариант 4
  
  Реализовать программу, которая в качестве входа принимает произвольное регулярное выражение, и выполняет 
  следующие преобразования:
  1) По регулярному выражению строит НКА.
  2) По НКА строит эквивалентный ему ДКА. 
  3) По ДКА строит эквивалентный ему КА, имеющий наименьшее возможное количество состояний. 
  Указание. Воспользоваться алгоритмом http://neerc.ifmo.ru/wiki/index.php?title=Алгоритм_Бржозовского
  4) Моделирует минимальный КА для входной цепочки из терминалов исходной грамматики.

* ### ЛР2 - Преобразование грамматик (удаление левой рекурсии и eps-правил)

  #### Общее задание
  Постройте программу, которая в качестве входа принимает приведенную КС-грамматику G = (N, T, P, S) и 
  преобразует ее в эквивалентную КС-грамматику G' без левой рекурсии
  
  #### Вариант 3. Преобразование в грамматику без ε-правил.
  Определение. Назовем КС-грамматику G = (N, T, P, S) грамматикой без -правил (или неукорачивающей), 
  если либо
  1. P не содержит ε-правил, либо
  2. есть точно одно ε-правило S – > ε и S не встречается в правых частях остальных правил из Р. 
  
  Постройте программу, которая в качестве входа принимает произвольную КС-грамматику    G = (N, T, P, S) и 
  преобразует ее в эквивалентную КС-грамматику G' = (N', T', P', S') без ε-правил.
  Указания. Воспользоваться алгоритмом 2.10 (АХО А., УЛЬМАН Дж. Теория синтаксического анализа, перевода и компиляции: В 2-х томах. Т.1.: Синтаксический анализ. - М.: Мир, 1978.). 
  
* ### ЛР3 - Синтаксический разбор с использованием метода рекурсивного спуска
  #### Вариант 1. Грамматика G1
  Рассматривается грамматика выражений отношения с правилами
  
  ```
  <выражение> ->
    <простое выражение> | 
    <простое выражение> <операция отношения> <простое выражение>
  
  <простое выражение> ->
    <терм> | 
    <знак> <терм> | 
    <простое выражение> <операция типа сложения> <терм>
  
  <терм> ->
    <фактор> | 
    <терм> <операция типа умножения> <фактор>
  
  <фактор> ->
    <идентификатор> | 
    <константа> | 
    ( < простое выражение > ) | 
    not <фактор>
  
  <операция отношения> ->
    = | <> | < | <= | > | >=
  
  <знак> -> 
    + | -
  
  <операция типа сложения> -> 
    + | - | or
  
  <операция типа умножения> -> 
    * | / | div | mod | and
  ```
  
  Замечания.
  1. Нетерминалы <идентификатор> и <константа> - это лексические единицы (лексемы), которые
    оставлены неопределенными, а при выполнении лабораторной работы можно либо рассматривать их
    как терминальные символы, либо определить их по своему усмотрению и добавить эти определения.
  2. Терминалы not, or, div, mod, and - ключевые слова (зарезервированные).
  3. Терминалы ( ) - это разделители и символы пунктуации.
  4. Терминалы = <> < <= > >= + - * / - это знаки операций.
  5. Нетерминал <выражение> - это начальный символ грамматики.

  #### Задание на лабораторную работу
  Дополнить грамматику блоком, состоящим из последовательности операторов присваивания. Для реализации
  предлагаются два варианта расширенной грамматики.
  ##### Вариант в стиле Алгол-Паскаль.
  ```
  <программа> -> 
    <блок>
    
  <блок> ->
    begin <список операторов> end
    <список операторов>
    <оператор> | <список операторов> ; <оператор>
    
  <оператор> ->
    <идентификатор> = <выражение>
  ```
 
  ##### Вариант в стиле Си.
  ```
  <программа> -> 
    <блок>
    
  <блок> ->
    { <список операторов> }
    <список операторов>
    <оператор> <хвост>
    
  <хвост> ->
    ; <оператор> <хвост> | ε
  ```
  
  Первый вариант содержит левую рекурсию, которая должна быть устранена. Второй вариант не содержит
  левую рекурсию, но имеет ε-правило. В обоих вариантах точка с запятой (;) ставится между операторами.
  Теперь начальным символом грамматики становится нетерминал <программа>. Оба варианта содержат
  цепное правило <программа> -> <блок>. Можно начальным символом грамматики назначить нетерминал
  <блок>. А можно <блок> считать оператором, т. е.
  ```<оператор> -> <идентификатор> = <выражение> | <блок>```
  
  В последнем случае возможна конструкция с вложенными блоками. Если между символом присваивания (=) и
  символом операции отношения (=) возникает конфликт, то можно для любого из них ввести новое
  изображение, например, :=, <-, == и т. п.
  
  Для модифицированной грамматики написать программу нисходящего синтаксического анализа с
  использованием метода рекурсивного спуска.
