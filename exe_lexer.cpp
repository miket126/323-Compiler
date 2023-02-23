#include <iostream>
#include <fstream>
#include <string.h>
#include <vector>
#include <cctype>
#include <algorithm>
#include <iomanip>
#include <conio.h>

void lexer(std::string& token, std::vector<char>& lexeme, std::ifstream& file, int& state, bool& skip) {
    
    int dfsm[10][5];
    char c;
    char s;
    bool done = false;
    bool unknown = false;
    std::vector <char> opsep = {'=','!','>','<','+','-','*','/','#','(',')','{','}',';',','};
    std::vector <std::string> keyword = {"int","bool","real","if","fi","else","return","put","get","while","endwhile","true","false","function"};
    std::vector <char> num = {'0','1','2','3','4','5','6','7','8','9'};

    //=========================All 3 in 1, int real identifer dfsm====================
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

    lexeme.clear();
    state = 1;

    //==============================Parsing character=========================
    while (!done) {
        file.get(s);
        if (isspace(s) || file.eof()) break;

        c = tolower(s);
        switch (c)
        {
        case '=':
            lexeme.push_back(c);
            token = "Operator";
            done = true;

            //check next char for special case
            file.get(c);
            if (c == '=' || '>') lexeme.push_back(c);
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

            //check next char for special case
            file.get(c);
            if (c == ']') {
                file.get(c);
                if (file.eof()) {done = true; break;}
                else {lexeme.clear(); skip = false; file.unget();}
            }
            else {file.unget();}
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
            if (c == '*') skip = true;
            else lexeme.push_back('['); unknown = true;
            file.unget();
            break;
                
        default:
            if(!isspace(c)) {lexeme.push_back(c); unknown = true;}

            //check next char for special case
            file.get(c);
            if (std::find(opsep.begin(), opsep.end(), c) != opsep.end()) done = true;
            else if (file.eof()) {done = true; break;}
            file.unget();
            break;
        }
    }

    //===============check for keyword==================
    std::string checkid(lexeme.begin(), lexeme.end());
    if (std::find(keyword.begin(), keyword.end(), checkid) != keyword.end()) token = "Keyword";
    else if ((state == 9) || unknown) token = "Unknown";
}


int main(int argc, const char * argv[])
{
    if (argc != 2) {
        std::cerr << "Usage: ./lexer infile_name.txt > outfile_name.txt\n\n";
        exit(-2);
    }

    std::string filename = argv[1];
    //std::ifstream file(filename);         //remove comment while testing cpp
    std::string token;
    std::vector<char> lexeme;
    int state = 1;
    bool skip = false;


    //=======================for exe file only, comment out while testing cpp====================
    std::string infile;
    std::string outfile;
    //need to look into _getch

    std::cout << "Please enter input file with file type:   ";
    system("pause");
    getline(std::cin, infile);
    std::ifstream file(infile);
    if (!file.is_open()) {
      std::cerr << "\n\nWarning, could not open file '" << infile << "'\n\n";
      system("pause");
      exit(-1);
    }


    std::cout << "Please enter output file with file type:   ";
    system("pause");
    getline(std::cin, outfile);
    std::ofstream of(outfile);
    if (!of.is_open()) {
      std::cerr << "\n\nWarning, could not open file '" << outfile << "'\n\n";
      system("pause");
      exit(-1);
    }


    std::cout << std::left << std::setw(15) << "Token" << "Lexeme\n\n";
    //==============Start LA============ 
    while (!file.eof()) {
        lexer(token, lexeme, file, state, skip);
        if (lexeme.size() != 0 && !skip) {
            of << std::left << std::setw(15) << token;
            for (auto s : lexeme) of << s;
            of << std::endl;           
        }
    }

    of.close();

    //=======================for exe file only, comment out while testing cpp====================

    

    /*
    if (!file.is_open()) {
      std::cerr << "\n\nWarning, could not open file '" << filename << "'\n\n";
      exit(-1);
    }
    std::cout << std::left << std::setw(15) << "Token" << "Lexeme\n\n";

    while (!file.eof()) {
        lexer(token, lexeme, file, state, skip);
        if (lexeme.size() != 0 && !skip) {
            std::cout << std::left << std::setw(15) << token;
            for (auto s : lexeme) std::cout << s;
            std::cout << std::endl;           
        }
    }

    file.close();
    */





    

    system("pause");
    return 0;
}