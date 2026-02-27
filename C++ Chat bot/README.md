# 🤖 C++ Console Chat Bot

A modern, colorful, pattern-matching chatbot that runs entirely in your terminal — written in **C++17**.

> Originally created by **Yunus Emre Vurgun** (2022) — modernized & enhanced (2026).

---

## ✨ Features

| Feature | Description |
|---------|-------------|
| 💬 **Natural Chat** | Greetings, small talk, questions about the bot |
| 🧮 **Calculator** | Full arithmetic: `+` `-` `*` `/` with decimals |
| 😂 **Jokes** | Random programming jokes |
| 🧠 **Fun Facts** | Random tech & computing facts |
| 🕐 **Date & Time** | Current date and time display |
| 🪙 **Coin Flip** | Random heads or tails |
| 🎲 **Dice Roll** | Roll a 6-sided die |
| 🔄 **String Reverse** | Reverse any text |
| 📝 **Word Count** | Count words in a sentence |
| 📜 **History** | View your conversation history |
| ⏱️ **Uptime** | Session duration tracker |
| 🎨 **Colorful UI** | ANSI-colored terminal interface |

---

## 🚀 Quick Start

### Prerequisites

- A C++17 compatible compiler (`g++` 7+ or `clang++` 5+)
- A terminal that supports ANSI escape codes (most modern terminals)

### Build & Run

```bash
# Using Make
make
./chatbot

# Or compile directly
g++ -std=c++17 -Wall -O2 -o chatbot chat.cpp
./chatbot

# Build and run in one step
make run
```

### Clean

```bash
make clean
```

---

## 📋 Commands

| Command | What it does |
|---------|-------------|
| `help` / `manual` | Show all available commands |
| `calc` / `math` | Enter calculator mode |
| `joke` | Get a random programming joke |
| `fact` | Learn a random fun fact |
| `time` / `date` | Show current date & time |
| `flip` | Flip a coin |
| `roll` | Roll a dice |
| `reverse <text>` | Reverse the given text |
| `count <text>` | Count words in the text |
| `history` | Show conversation history |
| `uptime` | Show session duration |
| `clear` | Clear the screen |
| `bye` / `exit` | End the conversation |

You can also just chat naturally — try saying `hi`, `how are you?`, `what is c++?`, and more!

---

## 🏗️ Architecture

The bot uses a clean **class-based architecture** with:

- **`std::unordered_map`** for O(1) response lookups
- **Alias system** mapping alternative phrasings to canonical keys
- **Partial matching** as a fallback for unrecognized input
- **No recursion** — safe iterative main loop (no stack overflow risk)
- **Modern C++17** — `std::string`, `<algorithm>`, `<chrono>`, `<random>`, structured bindings

---

## 📄 License

See [LICENSE](../LICENSE) for details.

---

*Built with ❤️ and C++*
