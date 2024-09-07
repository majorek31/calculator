#include <iostream>
#include <chrono>
#include <iomanip>
#include "Lexer.h"
#include "Parser.h"

int main()
{
    std::cout << "Basic expression evaluator by https://github.com/majorek31\n";
    std::string input;
    while (true)
    {
        std::cout << "Enter math expression: "; std::getline(std::cin, input);
        Lexer lexer;
        if (!lexer.Parse(input))
        {
            std::cout << "Lexical analysis failed! Found " << lexer.GetErrors().size() << " errors: \n";
            for (const auto& error : lexer.GetErrors())
            {
                std::cout << "\tInvalid Character ('" << error.What << "') at: " << error.Where << "\n";
            }
            continue;
        }
        std::cout << "Displaing lexical analysis results: \n";
        for (const auto& token : lexer.GetTokens())
        {
            std::cout << "\tToken Type: " << Token::TokenTypeToString(token.Type);
            if (token.Type == Token::TokenType::NUMBER)
                std::cout << " | Data: " << token.Data << "\n";
            else std::cout << "\n";
        }
        std::cout << lexer.GetTokens().size() << " tokens has been registered!\n";
        Parser parser(lexer.GetTokens());
        auto start = std::chrono::high_resolution_clock::now();
        parser.Compile();
        double result = parser.Evaluate();
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
        std::cout << "Result of calculation: " << std::setprecision(9) << result << " in " << duration << "ns" << " (compilation and evaluation)" << "\n";
    }
}