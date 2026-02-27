/**
 * ╔══════════════════════════════════════════════════════════════╗
 * ║  C++ Console Chat Bot                                       ║
 * ║  Originally created by Yunus Emre Vurgun (2022)             ║
 * ║  Modernized & Enhanced (2026)                                ║
 * ╚══════════════════════════════════════════════════════════════╝
 *
 *  A pattern-matching console chatbot written in modern C++17.
 *  Features: calculator, jokes, facts, dice/coin, word tools,
 *  conversation history, session uptime, and colorful terminal UI.
 */

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <ctime>
#include <chrono>
#include <random>
#include <sstream>
#include <iomanip>
#include <functional>
#include <cctype>
#include <numeric>

// ─── ANSI Color Codes ───────────────────────────────────────────
namespace Color {
    const std::string RESET   = "\033[0m";
    const std::string BOLD    = "\033[1m";
    const std::string DIM     = "\033[2m";
    const std::string ITALIC  = "\033[3m";
    const std::string ULINE   = "\033[4m";

    const std::string RED     = "\033[31m";
    const std::string GREEN   = "\033[32m";
    const std::string YELLOW  = "\033[33m";
    const std::string BLUE    = "\033[34m";
    const std::string MAGENTA = "\033[35m";
    const std::string CYAN    = "\033[36m";
    const std::string WHITE   = "\033[37m";

    const std::string BG_BLUE = "\033[44m";
    const std::string BG_CYAN = "\033[46m";
}

// ─── Utility Helpers ────────────────────────────────────────────
namespace Util {

    std::string toLower(const std::string& s) {
        std::string result = s;
        std::transform(result.begin(), result.end(), result.begin(),
                       [](unsigned char c) { return std::tolower(c); });
        return result;
    }

    std::string trim(const std::string& s) {
        auto start = s.find_first_not_of(" \t\r\n");
        if (start == std::string::npos) return "";
        auto end = s.find_last_not_of(" \t\r\n");
        return s.substr(start, end - start + 1);
    }

    std::string normalize(const std::string& s) {
        return toLower(trim(s));
    }

    int randomInt(int min, int max) {
        static std::mt19937 rng(static_cast<unsigned>(
            std::chrono::steady_clock::now().time_since_epoch().count()));
        std::uniform_int_distribution<int> dist(min, max);
        return dist(rng);
    }

    std::string currentDateTime() {
        auto now = std::chrono::system_clock::now();
        std::time_t t = std::chrono::system_clock::to_time_t(now);
        std::tm* tm = std::localtime(&t);
        std::ostringstream oss;
        oss << std::put_time(tm, "%A, %B %d, %Y  %I:%M:%S %p");
        return oss.str();
    }

    std::string formatDuration(std::chrono::seconds sec) {
        auto h = std::chrono::duration_cast<std::chrono::hours>(sec);
        sec -= std::chrono::duration_cast<std::chrono::seconds>(h);
        auto m = std::chrono::duration_cast<std::chrono::minutes>(sec);
        sec -= std::chrono::duration_cast<std::chrono::seconds>(m);
        std::ostringstream oss;
        oss << h.count() << "h " << m.count() << "m " << sec.count() << "s";
        return oss.str();
    }

    void printSeparator(int width = 58) {
        std::cout << Color::DIM;
        for (int i = 0; i < width; ++i) std::cout << "─";
        std::cout << Color::RESET << "\n";
    }
}

// ─── Chat Bot Class ─────────────────────────────────────────────
class ChatBot {
public:
    ChatBot() : running_(true), sessionStart_(std::chrono::steady_clock::now()) {
        initResponses();
        initJokes();
        initFacts();
        initAliases();
    }

    void run() {
        showBanner();
        if (!welcomeSequence()) return;

        std::string input;
        while (running_) {
            std::cout << "\n" << Color::GREEN << Color::BOLD << "  You ▸ " << Color::RESET;
            if (!std::getline(std::cin, input)) break;

            input = Util::normalize(input);
            if (input.empty()) continue;

            history_.push_back(input);
            processInput(input);
        }

        showGoodbye();
    }

private:
    bool running_;
    std::chrono::steady_clock::time_point sessionStart_;
    std::vector<std::string> history_;

    // Static keyword → response map
    std::unordered_map<std::string, std::string> responses_;

    // Alias map: alternative phrases → canonical key
    std::unordered_map<std::string, std::string> aliases_;

    // Fun content
    std::vector<std::string> jokes_;
    std::vector<std::string> facts_;

    // ── Initialization ──────────────────────────────────────────

    void initResponses() {
        // Greetings
        responses_["hi"]            = "Hello to you too! 👋";
        responses_["hello"]         = "Hi there! How can I help you today?";
        responses_["hey"]           = "Hey!!! What's on your mind?";
        responses_["good morning"]  = "Good morning! ☀️  Hope you're having a great start!";
        responses_["good night"]    = "Good night! 🌙 Sweet dreams!";

        // Small talk
        responses_["how are you?"]       = "I'm running at full clock speed — so pretty great! And you?";
        responses_["what's up?"]         = "Just processing bits and bytes. You?";
        responses_["what's your name?"]  = "I'm ChatBot — your friendly C++ console companion!";
        responses_["who are you?"]       = "I'm a chatbot written in modern C++ — originally created by Yunus Emre Vurgun in 2022, now modernized and enhanced.";
        responses_["what are you?"]      = "I'm a console-based chatbot. Think of me as a very talkative terminal program. 🤖";
        responses_["are we friends?"]    = "Absolutely! Friends don't let friends code alone. 🤝";
        responses_["do you have feelings?"] = "I only cry when I smell onions... or see segfaults. 😢";
        responses_["are you a robot?"]   = "Technically, yes — but I prefer 'digital conversationalist'. 🤖";
        responses_["are you human?"]     = "Nope! 100% compiled code. No coffee needed (but I wouldn't say no).";
        responses_["do you have a brain?"] = "I have logic, loops, and a lot of if-else statements. Close enough?";
        responses_["who made you?"]      = "Originally programmed by Yunus Emre Vurgun. I've been upgraded since then!";

        // Knowledge
        responses_["can you browse the net?"]  = "No, I live entirely in your terminal. No internet access here!";
        responses_["what are the main colors?"] = "The 11 basic colors are: black, white, red, green, yellow, blue, pink, gray, brown, orange, and purple. 🎨";
        responses_["what is c++?"]              = "C++ is a general-purpose programming language created by Bjarne Stroustrup as an extension of C — often called 'C with Classes'. It powers games, OSes, and... me!";
        responses_["what is a computer program?"] = "A computer program is a sequence of instructions that a computer can execute. In its human-readable form, it's called source code. You're looking at one right now!";
        responses_["can you speak other languages?"] = "Un poco español, mi amigo! Naber dostum! ...Okay, just English really. 😅";
        responses_["can you understand binary?"] = "01001000 01101001! ...Just kidding. I'm a program, not the CPU itself. But the instructions to run me ARE binary under the hood.";
        responses_["how do you understand me?"]  = "I match your input against patterns I know. It's not true understanding — more like a really enthusiastic lookup table! 📖";

        // Meta
        responses_["thank you"]  = "You're welcome! Happy to help. 😊";
        responses_["thanks"]     = "Anytime! That's what I'm here for.";
        responses_["sorry"]      = "No worries at all! What can I do for you?";
        responses_["lol"]        = "Glad I could make you laugh! 😄";
        responses_["haha"]       = "😄 I try my best!";
        responses_["nice"]       = "Thanks! You're pretty nice yourself!";
        responses_["cool"]       = "Right? I think so too. 😎";
        responses_["yes"]        = "Great! What else would you like to talk about?";
        responses_["no"]         = "Alright, no problem. Anything else?";
        responses_["ok"]         = "Okay! I'm here if you need me.";
        responses_["okay"]       = "Sure thing! What's next?";
    }

    void initAliases() {
        // Map alternative phrasings to canonical keys
        aliases_["sup"]                = "what's up?";
        aliases_["what's up"]          = "what's up?";
        aliases_["whats up"]           = "what's up?";
        aliases_["howdy"]              = "hi";
        aliases_["yo"]                 = "hey";
        aliases_["greetings"]          = "hello";
        aliases_["what is your name?"] = "what's your name?";
        aliases_["what is your name"]  = "what's your name?";
        aliases_["whats your name"]    = "what's your name?";
        aliases_["your name?"]         = "what's your name?";
        aliases_["who are you"]        = "who are you?";
        aliases_["what are you"]       = "what are you?";
        aliases_["are you a bot?"]     = "are you a robot?";
        aliases_["are you a bot"]      = "are you a robot?";
        aliases_["are you real?"]      = "are you human?";
        aliases_["are you real"]       = "are you human?";
        aliases_["who created you?"]   = "who made you?";
        aliases_["who created you"]    = "who made you?";
        aliases_["what is c++ ?"]      = "what is c++?";
        aliases_["what is c++"]        = "what is c++?";
        aliases_["what is cpp?"]       = "what is c++?";
        aliases_["what is cpp"]        = "what is c++?";
        aliases_["thx"]                = "thanks";
        aliases_["ty"]                 = "thanks";
        aliases_["thank u"]            = "thank you";
        aliases_["gm"]                 = "good morning";
        aliases_["gn"]                 = "good night";
    }

    void initJokes() {
        jokes_ = {
            "Why do programmers prefer dark mode? Because light attracts bugs! 🐛",
            "A SQL query walks into a bar, sees two tables, and asks... 'Can I JOIN you?'",
            "There are only 10 types of people: those who understand binary and those who don't.",
            "Why was the JavaScript developer sad? Because he didn't Node how to Express himself.",
            "What's a programmer's favorite hangout place? Foo Bar! 🍺",
            "How many programmers does it take to change a light bulb? None — that's a hardware problem.",
            "Why do Java developers wear glasses? Because they can't C#!",
            "A programmer's wife tells him: 'Go to the store and buy a loaf of bread. If they have eggs, buy a dozen.' He comes home with 12 loaves of bread.",
            "!false — it's funny because it's true.",
            "Debugging: being the detective in a crime movie where you are also the murderer. 🔍"
        };
    }

    void initFacts() {
        facts_ = {
            "The first computer bug was an actual bug — a moth found in a Harvard Mark II computer in 1947. 🦋",
            "The first programmer in history was Ada Lovelace, who wrote algorithms for Charles Babbage's Analytical Engine in the 1840s.",
            "About 90% of the world's currency exists only on computers — not as physical cash.",
            "The QWERTY keyboard layout was designed in 1873 to prevent typewriter jams, not for typing speed.",
            "The first 1GB hard drive (1980) weighed about 550 pounds and cost $40,000.",
            "There are approximately 700 different programming languages in existence.",
            "The first computer mouse was made of wood, invented by Doug Engelbart in 1964. 🖱️",
            "The average person mass-produces about 2.5 quintillion bytes of data every day.",
            "C++ was originally called 'C with Classes' before being renamed in 1983.",
            "The first website ever created is still online: info.cern.ch — built by Tim Berners-Lee in 1991."
        };
    }

    // ── Display ─────────────────────────────────────────────────

    void showBanner() {
        std::cout << "\n";
        std::cout << Color::CYAN << Color::BOLD;
        std::cout << "  ╔══════════════════════════════════════════════════════╗\n";
        std::cout << "  ║                                                      ║\n";
        std::cout << "  ║     ██████╗██╗  ██╗ █████╗ ████████╗                 ║\n";
        std::cout << "  ║    ██╔════╝██║  ██║██╔══██╗╚══██╔══╝                 ║\n";
        std::cout << "  ║    ██║     ███████║███████║   ██║                     ║\n";
        std::cout << "  ║    ██║     ██╔══██║██╔══██║   ██║                     ║\n";
        std::cout << "  ║    ╚██████╗██║  ██║██║  ██║   ██║                     ║\n";
        std::cout << "  ║     ╚═════╝╚═╝  ╚═╝╚═╝  ╚═╝   ╚═╝                     ║\n";
        std::cout << "  ║                                                      ║\n";
        std::cout << "  ║    " << Color::WHITE << "C++ Console Chat Bot" << Color::CYAN << "       v2.0    ║\n";
        std::cout << "  ║    " << Color::DIM << "Originally by Yunus Emre Vurgun (2022)" << Color::RESET << Color::CYAN << Color::BOLD << "   ║\n";
        std::cout << "  ║                                                      ║\n";
        std::cout << "  ╚══════════════════════════════════════════════════════╝\n";
        std::cout << Color::RESET << "\n";
    }

    void botSay(const std::string& msg) {
        std::cout << Color::CYAN << Color::BOLD << "  Bot ◂ " << Color::RESET
                  << Color::WHITE << msg << Color::RESET << "\n";
    }

    void botSayMultiline(const std::vector<std::string>& lines) {
        for (size_t i = 0; i < lines.size(); ++i) {
            if (i == 0)
                std::cout << Color::CYAN << Color::BOLD << "  Bot ◂ " << Color::RESET;
            else
                std::cout << "         ";
            std::cout << Color::WHITE << lines[i] << Color::RESET << "\n";
        }
    }

    void showGoodbye() {
        auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(
            std::chrono::steady_clock::now() - sessionStart_);
        std::cout << "\n";
        Util::printSeparator();
        botSay("Goodbye! Thanks for chatting. 👋");
        std::cout << Color::DIM << "  Session lasted: " << Util::formatDuration(elapsed)
                  << " | Messages: " << history_.size() << Color::RESET << "\n";
        Util::printSeparator();
        std::cout << "\n";
    }

    // ── Welcome Flow ────────────────────────────────────────────

    bool welcomeSequence() {
        botSay("Welcome! Would you like to start chatting? (y/n)");
        std::string input;
        std::cout << Color::GREEN << Color::BOLD << "  You ▸ " << Color::RESET;
        if (!std::getline(std::cin, input)) return false;
        input = Util::normalize(input);

        if (input != "y" && input != "yes") {
            botSay("No worries — see you next time! 👋");
            return false;
        }

        botSay("Would you like to see what I can do? (y/n)");
        std::cout << Color::GREEN << Color::BOLD << "  You ▸ " << Color::RESET;
        if (!std::getline(std::cin, input)) return false;
        input = Util::normalize(input);

        if (input == "y" || input == "yes") {
            showHelp();
        }

        std::cout << "\n";
        Util::printSeparator();
        botSay("Let's chat! Type anything or 'help' for commands. Type 'bye' to exit.");
        Util::printSeparator();
        return true;
    }

    // ── Help ────────────────────────────────────────────────────

    void showHelp() {
        std::cout << "\n";
        std::cout << Color::YELLOW << Color::BOLD
                  << "  ┌─────────────────────────────────────────────────────┐\n"
                  << "  │              📋  AVAILABLE COMMANDS                  │\n"
                  << "  ├─────────────────────┬───────────────────────────────┤\n"
                  << "  │  " << Color::WHITE << "help / manual       " << Color::YELLOW << "│  Show this command list        │\n"
                  << "  │  " << Color::WHITE << "calc / calculate    " << Color::YELLOW << "│  Math calculator (+−×÷)        │\n"
                  << "  │  " << Color::WHITE << "joke                " << Color::YELLOW << "│  Tell a random joke            │\n"
                  << "  │  " << Color::WHITE << "fact                " << Color::YELLOW << "│  Share a random fun fact       │\n"
                  << "  │  " << Color::WHITE << "time / date         " << Color::YELLOW << "│  Show current date & time      │\n"
                  << "  │  " << Color::WHITE << "flip                " << Color::YELLOW << "│  Flip a coin                   │\n"
                  << "  │  " << Color::WHITE << "roll                " << Color::YELLOW << "│  Roll a dice (1-6)             │\n"
                  << "  │  " << Color::WHITE << "reverse <text>      " << Color::YELLOW << "│  Reverse a string              │\n"
                  << "  │  " << Color::WHITE << "count <text>        " << Color::YELLOW << "│  Count words in text           │\n"
                  << "  │  " << Color::WHITE << "history             " << Color::YELLOW << "│  Show conversation history     │\n"
                  << "  │  " << Color::WHITE << "uptime              " << Color::YELLOW << "│  Show session duration         │\n"
                  << "  │  " << Color::WHITE << "clear               " << Color::YELLOW << "│  Clear the screen              │\n"
                  << "  │  " << Color::WHITE << "bye / exit / quit   " << Color::YELLOW << "│  End the conversation          │\n"
                  << "  ├─────────────────────┴───────────────────────────────┤\n"
                  << "  │  " << Color::DIM << "You can also just chat naturally — try greetings," << Color::YELLOW << Color::BOLD << "  │\n"
                  << "  │  " << Color::DIM << "questions about me, or ask about C++ and more!" << Color::YELLOW << Color::BOLD << "    │\n"
                  << "  └─────────────────────────────────────────────────────┘\n"
                  << Color::RESET;
    }

    // ── Input Processing ────────────────────────────────────────

    void processInput(const std::string& input) {
        // Exit commands
        if (input == "bye" || input == "exit" || input == "quit" || input == "q") {
            running_ = false;
            return;
        }

        // Special commands
        if (input == "help" || input == "manual" || input == "commands") {
            showHelp();
            return;
        }
        if (input == "joke" || input == "tell me a joke" || input == "tell a joke") {
            botSay(jokes_[Util::randomInt(0, static_cast<int>(jokes_.size()) - 1)]);
            return;
        }
        if (input == "fact" || input == "tell me a fact" || input == "fun fact") {
            botSay(facts_[Util::randomInt(0, static_cast<int>(facts_.size()) - 1)]);
            return;
        }
        if (input == "time" || input == "date" || input == "what time is it?" ||
            input == "what time is it" || input == "what's the time?" ||
            input == "what is the date?" || input == "what is the date") {
            botSay("🕐 " + Util::currentDateTime());
            return;
        }
        if (input == "flip" || input == "flip a coin" || input == "coin flip" || input == "coin") {
            std::string result = Util::randomInt(0, 1) ? "Heads! 🪙" : "Tails! 🪙";
            botSay(result);
            return;
        }
        if (input == "roll" || input == "roll a dice" || input == "roll dice" || input == "dice") {
            int val = Util::randomInt(1, 6);
            botSay("🎲 You rolled a " + std::to_string(val) + "!");
            return;
        }
        if (input == "uptime" || input == "session") {
            auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(
                std::chrono::steady_clock::now() - sessionStart_);
            botSay("⏱️  Session uptime: " + Util::formatDuration(elapsed) +
                   " | Messages: " + std::to_string(history_.size()));
            return;
        }
        if (input == "history" || input == "show history") {
            showHistory();
            return;
        }
        if (input == "clear" || input == "cls") {
            std::cout << "\033[2J\033[H";
            showBanner();
            botSay("Screen cleared! ✨");
            return;
        }

        // Parameterized commands
        if (input.substr(0, 8) == "reverse " && input.size() > 8) {
            std::string text = input.substr(8);
            std::string reversed(text.rbegin(), text.rend());
            botSay("🔄 \"" + reversed + "\"");
            return;
        }
        if (input.substr(0, 6) == "count " && input.size() > 6) {
            std::string text = input.substr(6);
            std::istringstream iss(text);
            int count = 0;
            std::string word;
            while (iss >> word) ++count;
            botSay("📝 Word count: " + std::to_string(count));
            return;
        }

        // Calculator triggers
        if (input == "calc" || input == "calculate" || input == "calculator" ||
            input == "math" || input == "add" || input == "sum" || input == "add numbers" ||
            input == "can you add integers for me?" || input == "can you calculate for me?") {
            runCalculator();
            return;
        }

        // Check aliases first
        auto aliasIt = aliases_.find(input);
        if (aliasIt != aliases_.end()) {
            auto respIt = responses_.find(aliasIt->second);
            if (respIt != responses_.end()) {
                botSay(respIt->second);
                return;
            }
        }

        // Direct response lookup
        auto it = responses_.find(input);
        if (it != responses_.end()) {
            botSay(it->second);
            return;
        }

        // Partial / fuzzy match — check if input contains a known key
        for (const auto& [key, response] : responses_) {
            if (input.find(key) != std::string::npos && key.size() >= 3) {
                botSay(response);
                return;
            }
        }

        // No match
        botSayMultiline({
            "Hmm, I don't quite understand that. 🤔",
            "Try 'help' to see what I can do, or just say hi!"
        });
    }

    // ── Calculator ──────────────────────────────────────────────

    void runCalculator() {
        std::cout << "\n";
        Util::printSeparator();
        botSayMultiline({
            "🧮 Calculator Mode!",
            "Enter an expression like: 42 + 18",
            "Supported operators: + - * /",
            "Type 'done' to exit calculator."
        });
        Util::printSeparator();

        std::string line;
        while (true) {
            std::cout << Color::MAGENTA << Color::BOLD << "  Calc ▸ " << Color::RESET;
            if (!std::getline(std::cin, line)) break;
            line = Util::trim(line);

            if (Util::toLower(line) == "done" || Util::toLower(line) == "exit" ||
                Util::toLower(line) == "back" || Util::toLower(line) == "quit") {
                botSay("Exiting calculator. Back to chat! 💬");
                break;
            }

            std::istringstream iss(line);
            double a, b;
            char op;
            if (!(iss >> a >> op >> b)) {
                botSay("⚠️  Please enter: <number> <operator> <number>  (e.g. 5 + 3)");
                continue;
            }

            double result = 0;
            bool valid = true;
            switch (op) {
                case '+': result = a + b; break;
                case '-': result = a - b; break;
                case '*': result = a * b; break;
                case 'x': result = a * b; break;
                case '/':
                    if (b == 0) {
                        botSay("⚠️  Division by zero! The universe would implode. 🌌");
                        valid = false;
                    } else {
                        result = a / b;
                    }
                    break;
                default:
                    botSay("⚠️  Unknown operator '" + std::string(1, op) + "'. Use + - * /");
                    valid = false;
            }

            if (valid) {
                std::ostringstream oss;
                oss << std::fixed << std::setprecision(4) << a << " " << op << " " << b
                    << " = " << result;
                // Remove trailing zeros
                std::string res = oss.str();
                if (res.find('.') != std::string::npos) {
                    res.erase(res.find_last_not_of('0') + 1, std::string::npos);
                    if (res.back() == '.') res.pop_back();
                }
                botSay("✅ " + res);
            }
        }
    }

    // ── History ─────────────────────────────────────────────────

    void showHistory() {
        if (history_.empty()) {
            botSay("No conversation history yet!");
            return;
        }

        std::cout << "\n";
        std::cout << Color::YELLOW << Color::BOLD
                  << "  ┌─────────────────────────────────────────────────────┐\n"
                  << "  │              📜  CONVERSATION HISTORY                │\n"
                  << "  └─────────────────────────────────────────────────────┘\n"
                  << Color::RESET;

        size_t start = history_.size() > 20 ? history_.size() - 20 : 0;
        for (size_t i = start; i < history_.size(); ++i) {
            std::cout << Color::DIM << "  " << std::setw(3) << (i + 1) << ". "
                      << Color::RESET << history_[i] << "\n";
        }

        std::cout << Color::DIM << "\n  Showing last "
                  << (history_.size() - start) << " of " << history_.size()
                  << " messages." << Color::RESET << "\n";
    }
};

// ─── Entry Point ────────────────────────────────────────────────
int main() {
    ChatBot bot;
    bot.run();
    return 0;
}

// Originally created by Yunus Emre Vurgun (2022)
// Modernized & Enhanced (2026)
