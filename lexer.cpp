#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cctype>
#include <algorithm>
#include <iomanip>
#include <cstring>

std::string token;
std::vector<char> lexeme;
int state = 1;
bool skip = true;
std::string test;
//char test[BUFSIZ];
//const char* test = str.c_str();
bool done = false;
bool unknown = false;
char c;
char s;

std::vector <char> opsep = {'=','!','>','<','+','-','*','/','#','(',')','{','}',';',','};
std::vector <std::string> keyword = {"int","bool","real","if","fi","else","return","put","get","while","endwhile","true","false","function"};
std::vector <char> num = {'0','1','2','3','4','5','6','7','8','9'};



//std::vector <std::auto> reloptest = {'==','!=','>','<','<=','=>'};

//void lexer(std::string& token, std::vector<char>& lexeme, std::ifstream& file, int& state, bool& skip) {

void lexer(std::ifstream& file) {
    
    int dfsm[10][5];

    // All 3 in 1, int real identifer dfsm
    dfsm[1][1] = 3;
    dfsm[1][2] = 2;
    dfsm[1][3] = 9;
    dfsm[1][4] = 9;

    dfsm[2][1] = 9;
    dfsm[2][2] = 2;
    dfsm[2][3] = 9;
    dfsm[2][4] = 4;

    dfsm[3][1] = 5;
    dfsm[3][2] = 6;
    dfsm[3][3] = 7;
    dfsm[3][4] = 9;

    dfsm[4][1] = 9;
    dfsm[4][2] = 8;
    dfsm[4][3] = 9;
    dfsm[4][4] = 9;

    dfsm[5][1] = 5;
    dfsm[5][2] = 6;
    dfsm[5][3] = 7;
    dfsm[5][4] = 9;

    dfsm[6][1] = 5;
    dfsm[6][2] = 6;
    dfsm[6][3] = 7;
    dfsm[6][4] = 9;

    dfsm[7][1] = 5;
    dfsm[7][2] = 6;
    dfsm[7][3] = 7;
    dfsm[7][4] = 9;

    dfsm[8][1] = 9;
    dfsm[8][2] = 8;
    dfsm[8][3] = 9;
    dfsm[8][4] = 9;

    dfsm[9][1] = 9;
    dfsm[9][2] = 9;
    dfsm[9][3] = 9;
    dfsm[9][4] = 9;

    test.clear();
    skip = true;
    unknown = false;
    done = false;
    lexeme.clear();
    state = 1;
    if (file.eof()) return;           

    //Parsing character
    while (!done) {
                
        file.get(s);
        //if (isspace(s) && lexeme.size() == 0) continue;
        if (file.eof()) return;
        if (isspace(s) && lexeme.size() != 0) break;
        


        c = tolower(s);
        switch (c)
        {
        case '=':
            lexeme.push_back(c);
            token = "Operator";
            done = true;

            //check next char for special case
            file.get(c);
            if (c == '=' || c == '>') lexeme.push_back(c);
            else file.unget();            
            break;

        case '!':
            lexeme.push_back(c);
            file.get(c);
            if (c == '=') {lexeme.push_back(c); token = "Operator"; done = true;}
            else {unknown = true; file.unget();}
            break;

        case '<':
            lexeme.push_back(c);
            token = "Operator";
            done = true;

            //check next char for special case
            file.get(c);
            if (c == '=') lexeme.push_back(c);
            else file.unget();
            break;

        case '>':
        case '+':
        case '-':
        case '/':
            lexeme.push_back(c);
            token = "Operator";
            done = true;
            break;

        case '*':
            lexeme.push_back(c);
            token = "Operator";
            done = true;

            /*
            //check next char for special case
            file.get(c);
            if (c == ']') {
                file.get(c);
                if (file.eof()) {done = true; break;}
                else {lexeme.clear(); skip = false; file.unget();}
            }
            else {file.unget();}
            */
            
            break;
        
        case '#':
        case '(':
        case ')':
        case '{':
        case '}':
        case ';':
        case ',':
            lexeme.push_back(c); 
            token = "Separator"; 
            done = true; 
            break;

        case 'a':
        case 'b':
        case 'c':
        case 'd':
        case 'e':
        case 'f':
        case 'g':
        case 'h':
        case 'i':
        case 'j':
        case 'k':
        case 'l':
        case 'm':
        case 'n':
        case 'o':
        case 'p':
        case 'q':
        case 'r':
        case 's':
        case 't':
        case 'u':
        case 'v':
        case 'w':
        case 'x':
        case 'y':
        case 'z':
            lexeme.push_back(c);
            state = dfsm[state][1]; 
            if (state == 3 || 5) token = "Identifier";

            //check next char for special case
            file.get(c);
            if (std::find(opsep.begin(), opsep.end(), c) != opsep.end()) done = true;
            else if (file.eof()) {done = true; break;}
            file.unget();
            break;

        case '_':
            lexeme.push_back(c);
            state = dfsm[state][3];
            if (state == 7) token = "Identifier";
            else if (lexeme.size() == 1) unknown = true;

            //check next char for special case
            file.get(c);
            if (std::find(opsep.begin(), opsep.end(), c) != opsep.end()) done = true;
            else if (file.eof()) {done = true; break;}
            file.unget();
            break;

        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            lexeme.push_back(c);
            state = dfsm[state][2]; 
            if (state == 2) token = "Integer";
            else if (state == 8) token = "Real";
            else if (state == 6) token = "Identifier";

            //check next char for special case
            file.get(c);
            if (std::find(opsep.begin(), opsep.end(), c) != opsep.end()) done = true;
            else if (file.eof()) {done = true; break;}
            file.unget();
            break;

        case '.':
            lexeme.push_back(c);
            state = dfsm[state][4];
            if (lexeme.size() == 1) unknown = true;

            //check next char for special case
            file.get(c);
            if (std::find(num.begin(), num.end(), c) == num.end()) {
                unknown = true;
                if (file.eof()) {done = true; break;}
            }
            file.unget();
            break;

        //comment
        case '[':
            file.get(c);
            if (c == '*') {
                while(skip) {
                    file.get(c);
                    if (c == '*') {
                        file.get(c);
                        if (c == ']') break;
                    }
                }
            }
            //else {lexeme.push_back('['); file.unget(); unknown = true;}
            break;

        case ' ':
            break;

        default:
            if(!isspace(c)) {
                lexeme.push_back(c); unknown = true;
                //check next char for special case
                file.get(c);
                if (std::find(opsep.begin(), opsep.end(), c) != opsep.end()) done = true;
                else if (file.eof()) {done = true; break;}
                file.unget();
            }
            break;
        }
    }

    //if (file.eof()) return;
    // check for keyword
    std::string temp(lexeme.begin(), lexeme.end());
    test = temp;
    if (std::find(keyword.begin(), keyword.end(), temp) != keyword.end()) token = "Keyword";
    else if ((state == 9) || unknown) token = "Unknown";

    std::cout << "\n\n\n";
    std::cout << std::left << std::setw(15) << token;
    for (auto x : lexeme) std::cout << x;
    std::cout << std::endl;
    
}




void Rat32S(std::ifstream& file);

void ofd(std::ifstream& file);

void funcdef(std::ifstream& file);

void funcsuf(std::ifstream& file);

void func(std::ifstream& file);

void opl(std::ifstream& file);

void paramlist(std::ifstream& file);

void paramsuf(std::ifstream& file);

void param(std::ifstream& file);

void qualifier(std::ifstream& file);

void body(std::ifstream& file);

void odl(std::ifstream& file);

void declist(std::ifstream& file);

void decsuf(std::ifstream& file);

void dec(std::ifstream& file);

void ids(std::ifstream& file);

void idsuffix(std::ifstream& file);

void statementlist(std::ifstream& file);

void statementsuf(std::ifstream& file); 

void statement(std::ifstream& file);

void comp(std::ifstream& file);

void assign(std::ifstream& file);

void if_(std::ifstream& file);

void ifsuf(std::ifstream& file);

void return_(std::ifstream& file);

void returnsuf(std::ifstream& file);

void print_(std::ifstream& file);

void scan(std::ifstream& file);

void while_(std::ifstream& file);

void cond(std::ifstream& file);

void relop(std::ifstream& file);

void exp(std::ifstream& file);

void exprime(std::ifstream& file);

void term(std::ifstream& file);

void termprime(std::ifstream& file);

void factor(std::ifstream& file);

void primary(std::ifstream& file);

void identifiersuf(std::ifstream& file);

/*
void (std::ifstream& file);
*/
void removebom(std::ifstream& file) {
    char b;
    
    file.get(b);
    if (b == (char)0xEF) {
        file.get(b);
        if (b == (char)0xBB) file.get(b);
        else file.unget();

        if (b == (char)0xBF) return;
        else file.unget();
    }
    else file.unget();

    
}

int main(int argc, const char * argv[])
{
    if (argc != 2) {
        std::cerr << "Usage: ./lexer.exe infile_name.txt > outfile_name.txt\n\n";
        exit(-2);
    }

    std::string filename = argv[1];
    std::ifstream file(filename);


    if (!file.is_open()) {
      std::cerr << "\n\nWarning, could not open file '" << filename << "'\n\n";
      exit(-1);
    }

    removebom(file);


    std::cout << std::left << std::setw(15) << "Token" << "Lexeme\n";

    while (!file.eof()) {
        Rat32S(file);
    }

    /*
    while (!file.eof()) {
        lexer(token, lexeme, file, state, skip);
        if (lexeme.size() != 0 && !skip) {
            std::cout << std::left << std::setw(15) << token;
            for (auto s : lexeme) std::cout << s;
            std::cout << std::endl;           
        }
    }

    */ 
    
    file.close();
    return 0;
}



void Rat32S(std::ifstream& file) {
    
    lexer(file);

    
    
    
    if (test == "function") {std::cout << "<Rat23S> -> 	<Opt Function Definition> # <Opt Declaration List> # <Statement List>\n";}
    
    ofd(file);

    //lexer(file);
    if (test == "#") {    std::cout << "<Rat23S> -> 	<Opt Function Definition> # <Opt Declaration List> # <Statement List>\n";
lexer(file); 

        if (test == "int" || test == "bool" || test == "real" ) {std::cout << "<Rat23S> -> 	<Opt Function Definition> # <Opt Declaration List> # <Statement List>\n";}
         odl(file);}
    else {std::cout << "Expected #\n"; lexer(file);}
    //lexer(file);


    if (test == "#") {    std::cout << "<Rat23S> -> 	<Opt Function Definition> # <Opt Declaration List> # <Statement List>\n";
lexer(file); std::cout << "<Rat23S> -> 	<Opt Function Definition> # <Opt Declaration List> # <Statement List>\n";statementlist(file);}
    else {std::cout << "Expected #\n"; lexer(file);}

    if (!file.eof()) std::cout << "Expected EOF marker\n";
    std::cout << "                                                     End Of File\n";
}


void ofd(std::ifstream& file) {
    //std::cout << "<Opt Function Definitions> 	-> 	<Function Definitions> | <Empty>\n";
    if (test == "function") {std::cout << "<Opt Function Definitions> 	-> 	<Function Definitions> | <Empty>\n";funcdef(file);}
    //return;
    //else std::cout << "<Opt Function Definitions> 	-> 	<Function Definitions> | <Empty>\n";
}

void funcdef(std::ifstream& file) {

    if (test == "function") {
        
        }
    //else {std::cout << "Expected function\n"; lexer(file);}


    std::cout << "<Function Definitions>		->	<Function> <Function Suffix>\n";
        func(file);
    


    if (test == "function")
    {std::cout << "<Function Definitions>		->	<Function> <Function Suffix>\n";}
    funcsuf(file);
    //lexer(file);
}

void funcsuf(std::ifstream& file) {
    //std::cout << "<Function Suffix>			->	<Function Definitions> | <empty>\n";
    if (test == "function") {std::cout << "<Function Suffix>			->	<Function Definitions> | <empty>\n";funcdef(file);}
    //return;
    //else std::cout << "<Function Suffix>			->	<Function Definitions> | <empty>\n";
    //lexer(file);
}

void func(std::ifstream& file) {
    if (test == "function") {
        std::cout << "<Function>				-> 	function <Identifier> (<Opt Parameter List>) <Opt Declaration List> <Body>\n";
        lexer(file);
    }
    else {std::cout << "Expected function\n"; lexer(file);}

    if (token == "Identifier") {
        std::cout << "<Function>				-> 	function <Identifier> (<Opt Parameter List>) <Opt Declaration List> <Body>\n";
    lexer(file);
    }
    else {std::cout << "Expected Identifier\n"; lexer(file);}

    if (test == "(") {
                std::cout << "<Function>				-> 	function <Identifier> (<Opt Parameter List>) <Opt Declaration List> <Body>\n";

        lexer(file);
        
        
    }
    else {std::cout << "Expected (\n"; lexer(file);}

    if (token == "Identifier") {std::cout << "<Function>				-> 	function <Identifier> (<Opt Parameter List>) <Opt Declaration List> <Body>\n";}
    opl(file);

    if (test == ")") {
                    std::cout << "<Function>				-> 	function <Identifier> (<Opt Parameter List>) <Opt Declaration List> <Body>\n";

        lexer(file);
    }
    else {std::cout << "Expected )\n"; lexer(file);}

    if (test == "int" || test == "bool" || test == "real" ) {std::cout << "<Function>				-> 	function <Identifier> (<Opt Parameter List>) <Opt Declaration List> <Body>\n";}
    odl(file);

    std::cout << "<Function>				-> 	function <Identifier> (<Opt Parameter List>) <Opt Declaration List> <Body>\n";
    body(file);
    //lexer(file);
}

void opl(std::ifstream& file) {
    if (token == "Identifier") {    std::cout << "<Opt Parameter List>		-> 	<Parameter List> | <Empty>\n";
paramlist(file);}
//return;
    
    //lexer(file);
}

void paramlist(std::ifstream& file) {

    if (token == "Identifier") {
        
    }
    //else {std::cout << "Expected Identifier\n"; lexer(file);}
        
    std::cout << "<Parameter List>			->	<Parameter>	<Parameter Suffix>\n";
        param(file);
    
    if (test == ",")
    {std::cout << "<Parameter List>			->	<Parameter>	<Parameter Suffix>\n";}
    paramsuf(file);
    //lexer(file);
}

void paramsuf(std::ifstream& file) {
    //std::cout << "<Parameter Suffix>			->  ,<Parameter List> | <empty>\n";
    if (test == ",") {
            std::cout << "<Parameter Suffix>			->  ,<Parameter List> | <empty>\n";

        lexer(file);
        std::cout << "<Parameter Suffix>			->  ,<Parameter List> | <empty>\n";
        paramlist(file);
    }
    

    //return;
    //else {std::cout << "<Parameter Suffix>			->  ,<Parameter List> | <empty>\n";}
    //lexer(file);
}

void param(std::ifstream& file) {
    if (token == "Identifier") {
        
    }
    //else {std::cout << "Expected Identifier\n"; lexer(file);}
    std::cout << "<Parameter>					->	<IDs> <Qualifier>\n";
    ids(file);
    
    if (test == "int" || test == "bool" || test == "real" ) {}
    //else {std::cout << "Expected: int   |    bool   |  real\n";lexer(file);}
    std::cout << "<Parameter>					->	<IDs> <Qualifier>\n";
    qualifier(file);
    
    //lexer(file);
}

void qualifier(std::ifstream& file) {
    if (test == "int" || test == "bool" || test == "real" ) {
        std::cout << "<Qualifier> -> int   |    bool   |  real\n";
        //lexer(file);
    }
    else {std::cout << "Expected: int   |    bool   |  real\n";}


    lexer(file);
}


void body(std::ifstream& file) {
    if (test == "{") {
        std::cout << "<Body>						->	{ <Statement List> }\n";
        lexer(file);
        
    }
    else {std::cout << "Expected {\n"; lexer(file);}

    std::cout << "<Body>						->	{ <Statement List> }\n";
    statementlist(file);


        if (test == "}") {std::cout << "<Body>						->	{ <Statement List> }\n";}
        else std::cout << "Expected }\n";         
        lexer(file);
}

void odl(std::ifstream& file) {
    //std::cout << " <Opt Declaration List>		->	<Declaration List> | <Empty>\n";
    if (test == "int" || test == "bool" || test == "real" ) {
        std::cout << "<Opt Declaration List>		->	<Declaration List> | <Empty>\n"; declist(file);}
    //else std::cout << " <Opt Declaration List>		->	<Declaration List> | <Empty>\n"; 
    //return;
    //lexer(file);
}

void declist(std::ifstream& file) {

    //if (test == "int" || "bool" || "real" ) {}
    // else {std::cout << "Expected: int   |    bool   |  real\n";lexer(file);}
    std::cout << "<Declaration List>			-> 	<Declaration>; <Declaration List Suffix>\n";
    dec(file);


    if (test == ";")     std::cout << "<Declaration List>			-> 	<Declaration>; <Declaration List Suffix>\n";
    else std::cout << "Expected ;\n";

    lexer(file); 

    //if (test == std::string("int") || test == std::string("bool") || test == std::string("real"))
    if (test == "int" || test == "bool" || test == "real")
    {std::cout << "<Declaration List>			-> 	<Declaration>; <Declaration List Suffix>HHHHHHHHHHHHHHHHHHHHHHH\n";}
    //else return;
    
    decsuf(file);
    
}

void decsuf(std::ifstream& file) {
    //std::cout << "<Declaration List Suffix> 	->  <Declaration List>  |  <empty>\n";
    if (test == "int" || test == "bool" || test == "real" ) {std::cout << "<Declaration List Suffix> 	->  <Declaration List>  |  <empty>\n";declist(file);}
    //else std::cout << "<Declaration List Suffix> 	->  <Declaration List>  |  <empty>\n";
    //lexer(file);
    //return;
}

void dec(std::ifstream& file) {

    //if (test == "int" || "bool" || "real" ) {}
    //else {std::cout << "Expected: int   |    bool   |  real\n";lexer(file);}

    std::cout << "<Declaration>				-> 	<Qualifier> <IDs>\n";
    qualifier(file);
    
    std::cout << "<Declaration>				-> 	<Qualifier> <IDs>\n";
        ids(file);
    //if (token == "Identifier") {}
    //else {std::cout << "Expected Identifier\n"; lexer(file);}
    //std::cout << "<Declaration>				-> 	<Qualifier> <IDs>\n";
    
    //lexer(file);
}

void ids(std::ifstream& file) {
    if (token == "Identifier") {
        std::cout << "<IDs>						->	<Identifier> <IDs Suffix>\n";
        lexer(file);
        
    }
    else {std::cout << "Expected Identifier\n"; lexer(file);}


    if (test == ",") {std::cout << "<IDs>						->	<Identifier> <IDs Suffix>\n";}
    idsuffix(file);
}

void idsuffix(std::ifstream& file) {
    //std::cout << "<IDs Suffix>				->  ,<IDs>  |  <empty>\n";
    if (test == ",") {
            std::cout << "<IDs Suffix>				->  ,<IDs>  |  <empty>\n";

        lexer(file);
        std::cout << "<IDs Suffix>				->  ,<IDs>  |  <empty>\n";
        ids(file);
    }
    //else {std::cout << "Expected ,\n"; lexer(file);}
    //return;
    
}

void statementlist(std::ifstream& file) {

    if ((token == "Identifier") || (test == "{" || "if" || "return" || "put" || "get" || "while")) {
        }
    //else {std::cout << "Expected { | Identifier | if | return | put | get | while\n"; lexer(file);}
    std::cout << "<Statement List>			->	<Statement>	<Statement List Suffix>\n";statement(file);

    if (token == "Identifier" || test == "{" || test == "if" || test == "return" || test == "put" || test == "get" || test == "while")
        {std::cout << "<Statement List>			->	<Statement>	<Statement List Suffix>\n";}
    statementsuf(file);
    //lexer(file);
}

void statementsuf(std::ifstream& file) {
    //std::cout << "<Statement List Suffix>  	->  <Statement List>  |  <empty>\n";
    if (token == "Identifier" || test == "{" || test == "if" || test == "return" || test == "put" || test == "get" || test == "while") {
        std::cout << "<Statement List Suffix>  	->  <Statement List>  |  <empty>\n";statementlist(file);}
    //else lexer(file);
    //lexer(file);
}   

void statement(std::ifstream& file) {
    //lexer(file);
    if (token == "Identifier" || test == "{" || test == "if" || test == "return" || test == "put" || test == "get" || test == "while") {
        std::cout << "<Statement>				->	<Compound>	|	<Assign>	|	<If>	|	<Return>	|	<Print>	|	<Scan>	|	<While>\n";
        if (test == "{") comp(file);
        else if (token == "Identifier") assign(file);
        else if (test == "if") if_(file);
        else if (test == "return") return_(file);
        else if (test == "put") print_(file);
        else if (test == "get") scan(file);
        else if (test == "while") while_(file);
    }
    else {std::cout << "Expected { | Identifier | if | return | put | get | while\n"; lexer(file);}
}

void comp(std::ifstream& file) {
    if (test == "{") {
        std::cout << "<Compound>					->	{ <Statement List> }\n";
        lexer(file);
        
    }
    else {std::cout << "Expected {\n"; lexer(file);}
    
    std::cout << "<Compound>					->	{ <Statement List> }\n";
        statementlist(file);

        if (test == "}") {
                    std::cout << "<Compound>					->	{ <Statement List> }\n";
            lexer(file);
        }
        else {std::cout << "Expected }\n"; lexer(file);} 
}

void assign(std::ifstream& file) {
    if (token == "Identifier") std::cout << "<Assign>					->	<Identifier> = <Expression>;\n";
    else std::cout << "Expected Identifier\n";

    lexer(file);
    if (test == "=") {std::cout << "<Assign>					->	<Identifier> = <Expression>;\n";lexer(file);
    }
    else {std::cout << "Expected =\n"; lexer(file);}

    std::cout << "<Assign>					->	<Identifier> = <Expression>;\n"; exp(file);

    //lexer(file);
    if (test == ";") {std::cout << "<Assign>					->	<Identifier> = <Expression>;\n";lexer(file);}
    else {std::cout << "Expected ;\n"; lexer(file);}

    //lexer(file);
}

void if_(std::ifstream& file) {
    if (test == "if") std::cout << "<If>						-> 	if(<Condition>)<Statement> <If Suffix>\n";
    else {std::cout << "Expected if\n";}
    
    lexer(file);
    if (test == "(") {std::cout << "<If>						-> 	if(<Condition>)<Statement> <If Suffix>\n";lexer(file);
    }
    else {std::cout << "Expected (\n"; lexer(file);}

    std::cout << "<If>						-> 	if(<Condition>)<Statement> <If Suffix>\n"; cond(file);

    if (test == ")") {std::cout << "<If>						-> 	if(<Condition>)<Statement> <If Suffix>\n";lexer(file);
    }
    else {std::cout << "Expected )\n"; lexer(file);}


    std::cout << "<If>						-> 	if(<Condition>)<Statement> <If Suffix>\n"; statement(file);
    std::cout << "<If>						-> 	if(<Condition>)<Statement> <If Suffix>\n"; ifsuf(file);
    //lexer(file);
}

void ifsuf(std::ifstream& file) {
    //std::cout << "<If Suffix>				->  fi  |  else <Statement> fi\n";
    if (test == "fi") {std::cout << "<If Suffix>				->  fi  |  else <Statement> fi\n";lexer(file);}
    else if (test == "else") {
        std::cout << "<If Suffix>				->  fi  |  else <Statement> fi\n";
        lexer(file); 
        std::cout << "<If Suffix>				->  fi  |  else <Statement> fi\n";
        statement(file);
        if (test == "fi") {std::cout << "<If Suffix>				->  fi  |  else <Statement> fi\n";lexer(file);}
        else {std::cout << "Expected fi\n"; lexer(file);}

    }
    else {std::cout << "Expected fi | else\n"; lexer(file);}
    
}

void return_(std::ifstream& file) {
    if (test == "return") {
        std::cout << "<Return>					->	return <Return Suffix>\n";
        lexer(file);        
        
        
    }
    else {std::cout << "Expected return\n"; lexer(file);}

    std::cout << "<Return>					->	return <Return Suffix>\n";
        returnsuf(file);
    
}

void returnsuf(std::ifstream& file) {
    //std::cout << "<Return Suffix>			->  ;  |  <Expression>;\n";
    if (test == ";") {    std::cout << "<Return Suffix>			->  ;  |  <Expression>;\n";
lexer(file);}
    //if ((token == "Identifier" || "Real" || "Integer") || (test == "(" || "true" || "false" || "-"))
    else     {
        std::cout << "<Return Suffix>			->  ;  |  <Expression>;\n";
        exp(file);

        if (test == ";") {    std::cout << "<Return Suffix>			->  ;  |  <Expression>;\n";
        lexer(file);}
        else {std::cout << "Expected ;\n"; lexer(file);}

        
        }
        
    
    //std::cout << "Expected Identifier | Real | Integer | ( | true | false | - | ; |\n";
    //else { lexer(file);}
    //lexer(file);
}

void print_(std::ifstream& file) {
    if (test == "put") std::cout << "<Print>					->	put(<Expression>);\n";
    else std::cout << "Expected put\n";
    lexer(file);

    if (test == "(") {std::cout << "<Print>					->	put(<Expression>);\n";lexer(file); }
    else {std::cout << "Expected (\n"; lexer(file);}
    //lexer(file);
    std::cout << "<Print>					->	put(<Expression>);\n";exp(file);

    if (test == ")") {std::cout << "<Print>					->	put(<Expression>);\n";lexer(file);}
    else {std ::cout << "Expected )\n"; lexer(file);}
    
    if (test == ";") {std::cout << "<Print>					->	put(<Expression>);\n";lexer(file);}
    else {std::cout << "Expected ;\n"; lexer(file);}

    //lexer(file);
}

void scan(std::ifstream& file) {
    if (test == "get") std::cout << "<Scan>						->	get(<IDs>);\n";
    else std::cout << "Expected get\n";
    lexer(file);

    if (test == "(") {std::cout << "<Scan>						->	get(<IDs>);\n";lexer(file); }
    else {std::cout << "Expected (\n"; lexer(file);}
    //lexer(file);
    std::cout << "<Scan>						->	get(<IDs>);\n";ids(file);

    if (test == ")") {std::cout << "<Scan>						->	get(<IDs>);\n";lexer(file);}
    else {std::cout << "Expected )\n"; lexer(file);}

    if (test == ";") {std::cout << "<Scan>						->	get(<IDs>);\n";lexer(file);}
    else {std::cout << "Expected ;\n"; lexer(file);}

    //lexer(file);
}

void while_(std::ifstream& file) {
    if (test == "while") std::cout << "<While>					->	while(<Condition>) <Statement> endwhile\n";
    else std::cout << "Expected while\n";
    lexer(file);

    if (test == "(") {std::cout << "<While>					->	while(<Condition>) <Statement> endwhile\n";lexer(file); }
    else {std::cout << "Expected (\n"; lexer(file);}

    std::cout << "<While>					->	while(<Condition>) <Statement> endwhile\n";cond(file);

    //lexer(file);
    if (test == ")") {std::cout << "<While>					->	while(<Condition>) <Statement> endwhile\n";lexer(file); }
    else {std::cout << "Expected )\n"; lexer(file);}

    std::cout << "<While>					->	while(<Condition>) <Statement> endwhile\n";statement(file);
    //lexer(file);
    if (test == "endwhile") {std::cout << "<While>					->	while(<Condition>) <Statement> endwhile\n";lexer(file);}
    else {std::cout << "Expected endwhile\n"; lexer(file);}
    //lexer(file);
}

void cond(std::ifstream& file) {
    if ((token == "Identifier" || "Real" || "Integer") || (test == "(" || test == "true" || test == "false" || test == "-"))    {}
    //else {std::cout << "Expected Identifier | Real | Integer | ( | true | false | - |\n"; lexer(file);}
    std::cout << "<Condition>				->	<Expression> <Relop> <Expression>\n";
exp(file);


    if (test == "==" || test == "!=" || ">" || "<" || "<=" || "=>") {
        
    }
    //else {std::cout << "Expected ==   |   !=    |   >     |   <    |  <=   |    =>\n"; lexer(file);}
    std::cout << "<Condition>				->	<Expression> <Relop> <Expression>\n";relop(file);
        

    if ((token == "Identifier" || "Real" || "Integer") || (test == "(" || test == "true" || test == "false" || test == "-"))    {}
    //else {std::cout << "Expected Identifier | Real | Integer | ( | true | false | - |\n"; lexer(file);}
    std::cout << "<Condition>				->	<Expression> <Relop> <Expression>\n";
exp(file);
    

    
    //lexer(file);
}

void relop(std::ifstream& file) {
    if (test == "==" || test == "!=" || test == ">" || test == "<" || test == "<=" || test == "=>") {
        std::cout << "<Relop> ->        ==   |   !=    |   >     |   <    |  <=   |    => \n";
    }
    else std::cout << "Expected ==   |   !=    |   >     |   <    |  <=   |    =>\n";

    lexer(file);
}

void exp(std::ifstream& file) {
    if ((token == "Identifier" || "Real" || "Integer") || (test == "(" || "true" || "false" || "-"))    {}
    //else {std::cout << "Expected Identifier | Real | Integer | ( | true | false | - |\n"; lexer(file);}
    std::cout << "<Expression>				->	<Term> <Expression Prime>\n";
term(file);

    if (test == "+" || test == "-")
    {std::cout << "<Expression>				->	<Term> <Expression Prime>\n";}
    exprime(file);
    //lexer(file);
}

void exprime(std::ifstream& file) {
    //std::cout << "<Expression Prime>			->  +<Term> <Expression Prime> | -<Term><Expression Prime>  |  <empty>\n";
    if (test == "+" || test == "-") {
        std::cout << "<Expression Prime>			->  +<Term> <Expression Prime> | -<Term><Expression Prime>  |  <empty>\n";lexer(file);    
        std::cout << "<Expression Prime>			->  +<Term> <Expression Prime> | -<Term><Expression Prime>  |  <empty>\n";
 term(file);    
 
    if (test == "+" || test == "-")
 {std::cout << "<Expression Prime>			->  +<Term> <Expression Prime> | -<Term><Expression Prime>  |  <empty>\n";}
 exprime(file);}
    //else std::cout << "Expected + | -\n";
    //else     std::cout << "<Expression Prime>			->  +<Term> <Expression Prime> | -<Term><Expression Prime>  |  <empty>\n";
//lexer(file);}
}

void term(std::ifstream& file) {
    if ((token == "Identifier" || token == "Real" || token == "Integer") || (test == "(" || test == "true" || test == "false" || test == "-"))    {}
    //else {std::cout << "Expected Identifier | Real | Integer | ( | true | false | - |\n"; lexer(file);}
    std::cout << "<Term>						->	<Factor> <Term Prime>\n";
factor(file);
    
    if (test == "*" || test == "/") {std::cout << "<Term>						->	<Factor> <Term Prime>\n";}
    termprime(file);
    //lexer(file);
}

void termprime(std::ifstream& file) {
    //std::cout << "<Term Prime>				->  *<Factor><Term Prime>  |  /<Factor><Term Prime>  |  <empty>\n";
    if (test == "*" || test == "/") {
        std::cout << "<Term Prime>				->  *<Factor><Term Prime>  |  /<Factor><Term Prime>  |  <empty>\n";lexer(file);    
    std::cout << "<Term Prime>				->  *<Factor><Term Prime>  |  /<Factor><Term Prime>  |  <empty>\n";
 factor(file);    
 
 if (test == "*" || test == "/") {std::cout << "<Term Prime>				->  *<Factor><Term Prime>  |  /<Factor><Term Prime>  |  <empty>\n";}
 
 termprime(file);}
    //else std::cout << "Expected + | -\n";
    //else     std::cout << "<Term Prime>				->  *<Factor><Term Prime>  |  /<Factor><Term Prime>  |  <empty>\n";
//lexer(file);}
}

void factor(std::ifstream& file) {
    //std::cout << "<Factor>					->	-<Primary>	 |	<Primary>\n";
    if (test == "-") {std::cout << "<Factor>					->	-<Primary>	 |	<Primary>\n";
 lexer(file);std::cout << "<Factor>					->	-<Primary>	 |	<Primary>\n";primary(file);    }
 //if ((token == "Identifier" || "Real" || "Integer") || (test == "(" || "true" || "false"))
    else     {std::cout << "<Factor>					->	-<Primary>	 |	<Primary>\n";
primary(file);}
    
    //else {std::cout << "Expected Identifier | Real | Integer | ( | true | false | - |\n"; lexer(file);}
    //lexer(file);
}

void primary(std::ifstream& file) {
    if ((token == "Identifier" || token == "Real" || token == "Integer") || (test == "(" || test == "true" || test == "false")) {
        std::cout << "<Primary>    ->    <Identifier> <Identifier Suffix> |  <Integer>    |   ( <Expression> )   |   <Real>  |   true   |  false\n";
        if (token == "Identifier") {
            lexer(file);
            
            if (test == "(") {
            std::cout << "<Primary>    ->    <Identifier> <Identifier Suffix> |  <Integer>    |   ( <Expression> )   |   <Real>  |   true   |  false\n";} identifiersuf(file);}


        else if (test == "(") {lexer(file);
            std::cout << "<Primary>    ->    <Identifier> <Identifier Suffix> |  <Integer>    |   ( <Expression> )   |   <Real>  |   true   |  false\n";
            exp(file);
            if (test == ")")        std::cout << "<Primary>    ->    <Identifier> <Identifier Suffix> |  <Integer>    |   ( <Expression> )   |   <Real>  |   true   |  false\n";
            else std::cout << "Expected )\n";
            lexer(file);
        }
        else lexer(file);
    }
    else {std::cout << "Expected Identifier | Real | Integer | ( | true | false\n"; lexer(file);}
    //lexer(file);
}

void identifiersuf(std::ifstream& file) {
    //std::cout << "<Identifier Suffix>  ->    ( <IDs> )   | <Empty>\n";
    if (test == "(") {
        std::cout << "<Identifier Suffix>  ->    ( <IDs> )   | <Empty>\n";
        lexer(file);

        std::cout << "<Identifier Suffix>  ->    ( <IDs> )   | <Empty>\n";    
    ids(file);

        if (test == ")") {    std::cout << "<Identifier Suffix>  ->    ( <IDs> )   | <Empty>\n";
        lexer(file);}
        else {std::cout << "Expected )\n"; lexer(file);}

    }
    //else {std::cout << "Expected (\n"; lexer(file);}
    

    
    //else {    std::cout << "<Identifier Suffix>  ->    ( <IDs> )   | <Empty>\n";}
    //lexer(file);

}