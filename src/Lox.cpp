#include "Lox.hpp"
#include "Scanner.hpp"

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iterator>

bool Lox::hadError = false;

int Lox::main(int argc, char* argv[]) {

    if (argc > 2) {
        std::cerr << "Usage: lox [script]\n";
        return 64;
    }

    if (argc == 2) {
        runFile(argv[1]);
    } else {
        runPrompt();
    }

    return 0;
}

void Lox::runFile(const std::string& path) {

    std::ifstream file(path);

    if (!file) {
        std::cerr
            << "Could not open file: "
            << path << '\n';

        return;
    }

    std::string source(
        (std::istreambuf_iterator<char>(file)),
        std::istreambuf_iterator<char>()
    );

    run(source);

    if (hadError) {
        std::exit(65);
    }
}

void Lox::runPrompt() {

    std::string line;

    while (true) {

        std::cout << "> ";

        if (!std::getline(std::cin, line)) {
            break;
        }

        run(line);

        hadError = false;
    }
}

void Lox::run(const string& source) {

    Scanner scanner(source);

    vector<Token> tokens = scanner.scanTokens();

    for (const Token& token : tokens) {
        cout << token.toString() << '\n';
    }
}

void Lox::error(
    int line,
    const std::string& message
) {
    report(line, "", message);
}

void Lox::report(
    int line,
    const std::string& where,
    const std::string& message
) {

    std::cerr
        << "[line " << line << "] Error"
        << where
        << ": " << message
        << '\n';

    hadError = true;
}