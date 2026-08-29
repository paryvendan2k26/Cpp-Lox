#pragma once

#include <string>

class Lox {
public:
    static int main(int argc, char* argv[]);

private:
    static bool hadError;

    static void runFile(const std::string& path);
    static void runPrompt();
    static void run(const std::string& source);

    static void error(
        int line,
        const std::string& message
    );

    static void report(
        int line,
        const std::string& where,
        const std::string& message
    );

    friend class Scanner;
    friend class Parser;
};