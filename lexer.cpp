#include <iostream>
#include <fstream>
#include <string.h>

void lexer(std::string& token, char lexeme[BUFSIZ],std::ifstream& file) {

    int dfsm[9][4];

    dfsm[0][0] = 3;
    dfsm[0][1] = 2;
    dfsm[0][2] = 9;
    dfsm[0][3] = 9;

    dfsm[1][0] = 9;
    dfsm[1][1] = 2;
    dfsm[1][2] = 9;
    dfsm[1][3] = 4;

    dfsm[2][0] = 5;
    dfsm[2][1] = 6;
    dfsm[2][2] = 7;
    dfsm[2][3] = 9;

    dfsm[3][0] = 9;
    dfsm[3][1] = 8;
    dfsm[3][2] = 9;
    dfsm[3][3] = 9;

    dfsm[4][0] = 5;
    dfsm[4][1] = 6;
    dfsm[4][2] = 7;
    dfsm[4][3] = 9;

    dfsm[5][0] = 5;
    dfsm[5][1] = 6;
    dfsm[5][2] = 7;
    dfsm[5][3] = 9;

    dfsm[6][0] = 5;
    dfsm[6][1] = 6;
    dfsm[6][2] = 7;
    dfsm[6][3] = 9;

    dfsm[7][0] = 9;
    dfsm[7][1] = 8;
    dfsm[7][2] = 9;
    dfsm[7][3] = 9;
    
    dfsm[8][0] = 9;
    dfsm[8][1] = 9;
    dfsm[8][2] = 9;
    dfsm[8][3] = 9;




    file.getline(lexeme, BUFSIZ, ' ');

    


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
    char lexeme[BUFSIZ];

    if (!file.is_open()) {
      std::cerr << "\n\nWarning, could not open file '" << filename << "'\n\n";
      exit(-1);
    }

    std::cout << "token\t\t\tlexeme\n"; 

    while (!file.eof()) {
        lexer(token,lexeme,file);
        std::cout << token << "\t\t\t" << lexeme << std::endl;
    }


    return 0;
}