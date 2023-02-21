#include <iostream>
#include <fstream>
#include <string.h>
#include <set>
#include <vector>
#include <algorithm>

void lexer(std::string& token, std::vector<char> lexeme,std::ifstream& file, int& state) {
    
    int i = 0;
    int dfsm[10][5];
    char c;
    bool done = false;
    std::vector <char> opsep = {'=','!','>','<','+','-','*','#','(',')','{','}',';',',',' '};
    std::vector <std::string> keyword = {"int","bool","real","if","fi","else","return","put","get","while","endwhile","true","false"};

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

    while (!done) {
        file.get(c);
        if (c == ' ') token = "Space"; done = true; continue;
        


        switch (tolower(c))
        {
        case '=':
            lexeme.push_back(c);
            file.get(c);
            if (c == ('=' || '>')) {lexeme.push_back(c); token = "Operator"; done = true;}
            else { file.unget(); }
            break;

        case '!':
            lexeme.push_back(c);
            file.get(c);
            if (c == '=') {lexeme.push_back(c); token = "Operator"; done = true;}
            else { token = "Unknown"; file.unget();}
            break;

        case '<':
            lexeme.push_back(c);
            done = true;
            file.get(c);
            if (c == ' ') { token = "Operator"; state == 9;}
            else if (c == '=') {lexeme.push_back(c); token = "Operator"; done = true;}
            else { file.unget(); }
            break;

        case '>':
        case '+':
        case '-':
        case '*':
            lexeme.push_back(c);
            token = "Operator";
            done = true;
            break;
        
        case '#':
        case '|':
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
            state = dfsm[state][1]; 
            if (state = 3 || 5 || 6 || 7) token = "Identifier";
            lexeme.push_back(c);

            file.get(c);
            if (std::find(opsep.begin(), opsep.end(), c) != opsep.end()) { done = true; file.unget(); break; }
            else if (c == '_') { lexeme.push_back(c); state = dfsm[state][3]; }
            else if (c == '.') { lexeme.push_back(c); state = dfsm[state][4]; }
            else file.unget();
                
            break; //accepting is 3,5,6,7

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
            state = dfsm[state][2]; 
            if (state = 2) token = "Integer";
            else if (state = 8) token = "Real";
            else if (state = 6) token = "Identifier";
            lexeme.push_back(c);

            file.get(c);
            if (std::find(opsep.begin(), opsep.end(), c) != opsep.end()) { done = true; file.unget(); break; }
            else if (c == '.') { lexeme.push_back(c); state = dfsm[state][4]; }
            else file.unget();

            break; //accepting is 2,8
        
        default:
            token == "Unknown";
            done = true;
            break;
        }

        if (file.eof()) {lexeme.pop_back(); done = true;}
    }
    
    std::string comment(lexeme.begin(), lexeme.end());
    if (std::find(keyword.begin(), keyword.end(), comment) != keyword.end()) token = "Keyword";
    if (state == 9) token = "Unknown";
}


int main(int argc, const char * argv[])
{
    if (argc != 2) {
        std::cerr << "Usage: ./lexer filename\n\n";
        exit(-2);
    }

    std::string filename = argv[1];
    std::ifstream file(filename);
    std::string token;
    std::vector<char> lexeme;
    int state = 1;
    bool skip = false;

    if (!file.is_open()) {
      std::cerr << "\n\nWarning, could not open file '" << filename << "'\n\n";
      exit(-1);
    }

    std::cout << "Token\t\t\tLexeme\n"; 

    while (!file.eof()) {
        lexer(token,lexeme,file,state);
        if (lexeme.size() != 0 && token != "Space") {
            std::cout << token << "\t\t\t";
            for (auto s : lexeme) {std::cout << s;}
            std::cout << std::endl;
            lexeme.clear();
        }
        state = 1;
    }

    file.close();
    return 0;
}