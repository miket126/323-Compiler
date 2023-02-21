#include <fstream>
#include <iostream>
#include <vector>
#include <string.h>

void lexer(std::string& token, bool& skip, std::vector<char>&lexeme, bool& done, std::ifstream& file) {
    char c;



    
    done = false;
    
    while(!done) {

        file.get(c);
        if (c != ' ') {lexeme.push_back(c);}
        else if (c == ' ' && lexeme.size() != 0) {done = true;}

        //comment
        std::string comment(lexeme.begin(), lexeme.end());
        if (comment == "[*") {std::cout << "skip\n"; skip = true;}
        else if (comment == "*]") {std::cout << "doneskip\n"; skip = false; lexeme.clear();}
        if (c == ' ' && skip) lexeme.clear();

        if (file.eof()) {lexeme.pop_back(); done = true;}
    }

    




    token = "Working";
    

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
    //char *lexeme = new char[BUFSIZ];
    std::vector<char> lexeme;
    int state = 1;
    
    int i = 0;
    bool skip = false;
    bool done = false;

    if (!file.is_open()) {
      std::cerr << "\n\nWarning, could not open file '" << filename << "'\n\n";
      exit(-1);
    }

    std::cout << "Token\t\t\tLexeme\n"; 
        //char c;


    while (!file.eof()) {
            //file.get(c);
            lexer(token,skip,lexeme,done,file);
            if (!skip && (lexeme.size() != 0) && done) {
                std::cout << token << "\t\t\t"; 
                for (auto s : lexeme) std::cout << s;
                std::cout << std::endl;
                lexeme.clear();
            }
    }

    

    
    
    

    file.close();
    return 0;
}