#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <regex>
#include <stack>
#include <bits/stdc++.h>
using namespace std;

class Tape {
public:
    int currentPosition = 0;
    vector<char> positiveTape;
    vector<char> negativeTape;

    char& get(int index) {
        vector<char>& halfTape = index >= 0 ? positiveTape : negativeTape;
        int absIndex = abs(index);
        if (halfTape.size() <= absIndex) {
            halfTape.resize(absIndex + 1);
        }
        return halfTape[absIndex];
    }

    int getMinPosition() {
        while (!negativeTape.empty()) {
            if (negativeTape.back() != 0) {
                return -static_cast<int>(negativeTape.size()) + 1;
            }
            negativeTape.pop_back();
        }
        for (size_t i = 0; i < positiveTape.size(); ++i) {
            if (positiveTape[i] != 0) {
                return i;
            }
        }
        return 114514;
    }

    int getMaxPosition() {
        while (!positiveTape.empty()) {
            if (positiveTape.back() != 0) {
                return positiveTape.size() - 1;
            }
            positiveTape.pop_back();
        }
        for (size_t i = 1; i < negativeTape.size(); ++i) {
            if (negativeTape[i] != 0) {
                return -i;
            }
        }
        return -114514;
    }

    void initialize(const string& str) {
        positiveTape.assign(str.begin(), str.end());
    }

    char& current() {
        return get(currentPosition);
    }

    void move(int direction) {
        currentPosition += direction;
    }

    int digit(int number) {
        return to_string(abs(number)).length();
    }

    void printHead() {
        int minPos = min(currentPosition, getMinPosition());
        int maxPos = max(currentPosition, getMaxPosition());
        for (int i = minPos; i <= maxPos; ++i) {
            cout << left << setw(digit(i) + 1) << (i == currentPosition ? '^' : ' ');
        }
        cout << endl;
    }

    void printIndex() {
        int minPos = min(currentPosition, getMinPosition());
        int maxPos = max(currentPosition, getMaxPosition());
        int i = minPos;
        do {
            cout << abs(i) << ' ';
        } while (++i <= maxPos);
        cout << endl;
    }

    void printTape() {
        int minPos = min(currentPosition, getMinPosition());
        int maxPos = max(currentPosition, getMaxPosition());
        for (int i = minPos; i <= maxPos; ++i) {
            cout << left << setw(digit(i) + 1) << (get(i) ? get(i) : '_');
        }
        cout << endl;
    }

    void printResult() {
        int minPos = getMinPosition();
        int maxPos = getMaxPosition();
        for (int i = minPos; i <= maxPos; ++i) {
            cout << (get(i) ? get(i) : '_');
        }
        cout << endl;
    }
};

class PDA {
public:
    std::vector<std::string> states;         // 状态集 Q
    std::vector<std::string> inputSymbols;   // 输入符号集 Σ
    std::vector<std::string> stackSymbols;    // 栈符号集 Γ
    std::string initialState;                 // 初始状态 q0
    std::string stackStartSymbol;             // 栈起始符号 z0
    std::vector<std::string> finalStates;     // 终结状态集 F
    std::vector<std::string> transitions;     // 转移函数 δ

    void print() {
        std::cout << "States: ";
        for (const auto& state : states) std::cout << state << " ";
        std::cout << "\nInput Symbols: ";
        for (const auto& symbol : inputSymbols) std::cout << symbol << " ";
        std::cout << "\nStack Symbols: ";
        for (const auto& symbol : stackSymbols) std::cout << symbol << " ";
        std::cout << "\nInitial State: " << initialState;
        std::cout << "\nStack Start Symbol: " << stackStartSymbol;
        std::cout << "\nFinal States: ";
        for (const auto& state : finalStates) std::cout << state << " ";
        std::cout << "\nTransitions: \n";
        for (const auto& transition : transitions) std::cout << transition << "\n";
    }
    int simulate(const std::string& input, bool verbose){
        if(verbose){
            cout << "Input: " << input << endl;
        }
        for (size_t i = 0; i < input.size(); ++i) {
            // std::cout << "Current character: '" << input[i] << "' (ASCII: " << static_cast<int>(input[i]) << ")" << std::endl;
            // for (const auto& symbol : inputSymbols) {
            //     std::cout << "Symbol: '" << symbol << "' (ASCII: ";
            //     for (char ch : symbol) {
            //         std::cout << static_cast<int>(ch) << " "; // 输出每个字符的 ASCII 码
            //     }
            //     std::cout << ")" << std::endl;
            // }
            if (std::find(inputSymbols.begin(), inputSymbols.end(), std::string(1, input[i])) == inputSymbols.end()) {
                if(verbose){
                    std::cerr << "==================== ERR ==================== \n";
                    std::cerr << "error: '" << input[i] << "' was not declared in the set of input symbols\n";
                    std::cerr << "Input: " << input << "\n";

                    // 打印指示符，确保与非法字符对齐
                    std::cerr << std::string(7, ' ') << std::string(i, ' ') << "^\n"; // 9个空格 + i个空格
                    std::cerr << "==================== END ==================== \n";
                }
                return -1; 
            }
        }
        if(verbose){
            std::cout << "==================== RUN ==================== \n";
        }
        std::stack<std::string> stack; // 使用 STL 栈
        stack.push(stackStartSymbol); // 初始化栈
        std::string currentState = initialState; // 当前状态
        size_t inputIndex = 0; // 输入字符串的索引
        while(true){
            std::string currentInputSymbol = (inputIndex < input.size()) ? std::string(1, input[inputIndex]) : "_"; // 当前输入符号，空符号用 "_" 表示
            std::string currentStackTop = stack.empty() ? "_" : stack.top(); // 当前栈顶符号，空栈用 "_" 表示
            
            if (std::find(inputSymbols.begin(), inputSymbols.end(), currentInputSymbol) == inputSymbols.end() && currentInputSymbol != "_") {
                return -1; // 如果当前输入字符不在输入符号集中，直接拒绝
            }

            bool transitionFound = false;
            bool inputIsEmpty = false; //判断选定的inputSymbol是否为空

            //cout << currentInputSymbol << " " << currentState << "    :";

            for (const auto& transition : transitions) {
                std::istringstream iss(transition);
                std::string oldState, inputSymbol, stackTopSymbol, newState, stackSequence;

                // 解析转移
                iss >> oldState >> inputSymbol >> stackTopSymbol >> newState >> stackSequence;

                // 检查转移条件
                if (oldState == currentState && (inputSymbol == currentInputSymbol || inputSymbol == "_") && (stackTopSymbol == currentStackTop || stackTopSymbol == "_")) {
                    if(inputSymbol == "_"){
                        inputIsEmpty = true;
                    }
                    transitionFound = true;
                    currentState = newState; // 更新状态
                    //cout << transition << endl;
                    if (stackTopSymbol != "_") {
                        stack.pop(); // 弹出栈顶符号
                    }
                    // 将新栈序列推入栈中（逆序推入）
                    for (int i = stackSequence.size() - 1; i >= 0; --i) {
                        if (stackSequence[i] != '_') { // 忽略空符号
                            stack.push(std::string(1, stackSequence[i]));
                        }
                    }
                    break; // 找到转移后跳出循环
                }
            }
            if (!transitionFound) {
                break;
            }
            if (verbose) {
                std::cout << "state : " << currentState << "\n";
                std::cout << "stack：";
                std::stack<std::string> tempStack = stack; // 创建一个临时栈以打印内容
                std::string stackContents;
                while (!tempStack.empty()) {
                    stackContents = tempStack.top() + stackContents; // 从底到顶
                    tempStack.pop();
                }
                std::cout << stackContents << "\n";
                std::cout << "--------------------------------------------- \n";
            }
            if (inputIndex < input.size() && !inputIsEmpty) {
                inputIndex++;
            }

        }
        if(std::find(finalStates.begin(), finalStates.end(), currentState) != finalStates.end() && stack.empty() && inputIndex == input.size()){
            return 1;
        }
        else{
            return 0;
        }
    }
};



void reportError(const std::string& message, int lineNumber) {
    std::cerr << "Error on line " << lineNumber << ": " << message << std::endl;
    std::exit(1);
}

void judge_(bool condition, const std::string& message, int lineNumber) {
    if (!condition) {
        //reportError(message, lineNumber);
        cerr << "syntax error" << endl;
        ::exit(1);
    }
}

void loadPDAFromFile(const std::string& filename, PDA& pda) {
    std::ifstream file(filename);
    std::string line;
    int lineNumber = 1;

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        line.erase(0, line.find_first_not_of(" \t")); // Trim leading whitespace
        line.erase(line.find_last_not_of(" \t") + 1); // Trim trailing whitespace

        size_t commentPosition = line.find(';');
        if (commentPosition != std::string::npos) line.erase(commentPosition);

        if (line.empty()) {
            lineNumber++;
            continue;
        }

        if (line[0] == '#') {
            if (line.find("#Q =") == 0) {
                judge_(line.length() >= 7, "Invalid state declaration format", lineNumber);
                std::string statesLine = line.substr(5);
                judge_(statesLine.front() == '{' && statesLine.back() == '}', "States must be enclosed in braces", lineNumber);
                statesLine.erase(0, 1);
                statesLine.pop_back();
                std::stringstream ss(statesLine);
                std::string state;
                while (std::getline(ss, state, ',')) {
                    pda.states.push_back(state);
                }
            }
            else if (line.find("#S =") == 0) {
                judge_(line.length() >= 7, "Invalid input symbol declaration format", lineNumber);
                std::string symbolsLine = line.substr(5);
                judge_(symbolsLine.front() == '{' && symbolsLine.back() == '}', "Input symbols must be enclosed in braces", lineNumber);
                symbolsLine.erase(0, 1);
                symbolsLine.pop_back();
                std::stringstream ss(symbolsLine);
                std::string symbol;
                while (std::getline(ss, symbol, ',')) {
                    pda.inputSymbols.push_back(symbol);
                }
            }
            else if (line.find("#G =") == 0) {
                judge_(line.length() >= 7, "Invalid stack symbol declaration format", lineNumber);
                std::string symbolsLine = line.substr(5);
                judge_(symbolsLine.front() == '{' && symbolsLine.back() == '}', "Stack symbols must be enclosed in braces", lineNumber);
                symbolsLine.erase(0, 1);
                symbolsLine.pop_back();
                std::stringstream ss(symbolsLine);
                std::string symbol;
                while (std::getline(ss, symbol, ',')) {
                    pda.stackSymbols.push_back(symbol);
                }
            }
            else if (line.find("#q0 =") == 0) {
                judge_(line.length() > 6, "Initial state must be specified", lineNumber);
                pda.initialState = line.substr(6);
            }
            else if (line.find("#z0 =") == 0) {
                judge_(line.length() > 6, "Stack start symbol must be specified", lineNumber);
                pda.stackStartSymbol = line.substr(6);
            }
            else if (line.find("#F =") == 0) {
                judge_(line.length() >= 7, "Invalid final state declaration format", lineNumber);
                std::string statesLine = line.substr(5);
                judge_(statesLine.front() == '{' && statesLine.back() == '}', "Final states must be enclosed in braces", lineNumber);
                statesLine.erase(0, 1);
                statesLine.pop_back();
                std::stringstream ss(statesLine);
                std::string state;
                while (std::getline(ss, state, ',')) {
                    pda.finalStates.push_back(state);
                }
            }
            else {
                reportError("Unknown declaration", lineNumber);
            }
        }
        else {
            // Assume it's a transition
            std::stringstream ss(line);
            std::string oldState, inputSymbol, oldStackSymbol, newState, stackSequence;
            ss >> oldState >> inputSymbol >> oldStackSymbol >> newState >> stackSequence;
            judge_(!oldState.empty() && !newState.empty(), "Invalid transition format", lineNumber);
            pda.transitions.push_back(line);
        }

        lineNumber++;
    }

    file.close();
}

class TM {
public:
    class Rule;
    bool isVerbose; // 是否为详细模式
    string fileName; // 文件名
    vector<string> states; // 状态集
    unordered_map<string, int> stateLookupTable; // 状态查找表
    unordered_set<char> inputSymbols; // 输入符号集
    unordered_set<char> tapeSymbols; // 磁带符号集
    int currentState; // 当前状态
    unordered_set<int> finalStates; // 终结状态集
    int numberOfTapes; // 磁带数量
    vector<Tape> tapeCollection; // 磁带集合
    vector<vector<Rule>> transitionRules; // 转移规则集合

    void printTuringMachine(int step) {
        cout << left << setw(6 + digit(numberOfTapes)) << "Step" << ": " << step << endl;
        cout << left << setw(6 + digit(numberOfTapes)) << "State" << ": " << states[currentState] << endl;
        for (int i = 0; i < numberOfTapes; ++i) {
            cout << "Index" << left << setw(1 + digit(numberOfTapes)) << i << ": ";
            tapeCollection[i].printIndex();
            cout << "Tape" << left << setw(2 + digit(numberOfTapes)) << i << ": ";
            tapeCollection[i].printTape();
            cout << "Head" << left << setw(2 + digit(numberOfTapes)) << i << ": ";
            tapeCollection[i].printHead();
        }
        cout << "---------------------------------------------" << endl;
    }

    void executeTuringMachine() {
        int step = 0;
        if (isVerbose) printTuringMachine(step);
        while (true) {
            bool ruleApplied = false;
            for (auto& rule : transitionRules[currentState]) {
                if (rule.match()) {
                    ruleApplied = true;
                    rule.apply();
                    break;
                }
            }
            if (!ruleApplied) {
                break;
            }
            ++step;
            if (isVerbose) printTuringMachine(step);
        }
    }

    vector<string> splitString(const string& input) {
        vector<string> result;
        stringstream ss(input);
        string item;
        while (getline(ss, item, ',')) {
            if (!item.empty()) {
                result.push_back(item);
            }
        }
        return result;
    }

    void judge_(bool condition) {
        if (!condition) {
            cerr << "syntax error" << endl;
            ::exit(1);
        }
    }

    void readFile() {
        ifstream fileStream(fileName);

        pair<string, int> stateDeclaration, inputSymbolDeclaration, tapeSymbolDeclaration, startStateDeclaration, finalStateDeclaration;
        vector<pair<string, int>> transitionData;

        int lineNumber = 1;

        string line;
        while (getline(fileStream, line)) {

            stringstream ss(line);
            getline(ss >> ws, line);

            size_t commentPosition = line.find(';');
            if (commentPosition != string::npos) line.erase(commentPosition);

            while (!line.empty() && isspace(line.back())) line.pop_back();
            if (line.empty()) continue;

            if (line[0] == '#') {
                pair<string, int> *part = nullptr;

                judge_(line.length() >= 6);

                if (line[1] == 'Q') {
                    part = &stateDeclaration;
                } 
                else if (line[1] == 'S') {
                    part = &inputSymbolDeclaration;
                } 
                else if (line[1] == 'G') {
                    part = &tapeSymbolDeclaration;
                } 
                else if (line[1] == 'F') {
                    part = &finalStateDeclaration;
                } 
                else if (line[1] == 'B') {
                    judge_(line == "#B = _");
                } 
                else if (line[1] == 'N') {
                    judge_(line.substr(0, 5) == "#N = ");
                    numberOfTapes = stoi(line.substr(5));
                    judge_(numberOfTapes > 0);
                    judge_(line.substr(5) == to_string(numberOfTapes));
                } 
                else if (line[1] == 'q') {
                    judge_(line.length() >= 7 && line.substr(0, 6) == "#q0 = ");
                    startStateDeclaration.first = line.substr(6);
                    startStateDeclaration.second = lineNumber;
                } 
                else {
                    judge_(false);
                }

                if (part) {
                    judge_(line.length() >= 7 && line.substr(2, 4) == " = {" && line.back() == '}');
                    part->first = line.substr(6, line.length() - 7);
                    part->second = lineNumber;
                }
            } 
            else {
                transitionData.emplace_back(line, lineNumber);
            }

            lineNumber++;
        }

        // 初始化状态、输入符号、磁带符号、以及转移规则的处理
        tapeCollection.resize(numberOfTapes);

        for (const auto& stateStr : splitString(stateDeclaration.first)) {
            for (char ch : stateStr) {
                judge_(isalnum(ch) || ch == '_');
            }
            judge_(!stateLookupTable.count(stateStr));
            states.push_back(stateStr);
            stateLookupTable[stateStr] = states.size() - 1;
        }

        transitionRules.resize(states.size());

        for (const auto& tapeSymStr : splitString(tapeSymbolDeclaration.first)) {
            judge_(tapeSymStr.length() == 1);
            char ch = tapeSymStr[0];
            judge_(ch != ' ' && ch != ',' && ch != ';' && ch != '{' && ch != '}' && ch != '*');
            judge_(!tapeSymbols.count(ch));
            tapeSymbols.insert(ch);
        }

        judge_(tapeSymbols.count('_'));

        for (const auto& inputSymStr : splitString(inputSymbolDeclaration.first)) {
            judge_(inputSymStr.length() == 1);
            char ch = inputSymStr[0];
            judge_(ch != ' ' && ch != ',' && ch != ';' && ch != '{' && ch != '}' && ch != '*' && 
                  ch != '_');
            judge_(tapeSymbols.count(ch));
            judge_(!inputSymbols.count(ch));
            inputSymbols.insert(ch);
        }

        for (const auto& finalStateStr : splitString(finalStateDeclaration.first)) {
            judge_(stateLookupTable.count(finalStateStr));
            judge_(!finalStates.count(stateLookupTable[finalStateStr]));
            finalStates.insert(stateLookupTable[finalStateStr]);
        }

        judge_(stateLookupTable.count(startStateDeclaration.first));

        currentState = stateLookupTable[startStateDeclaration.first];

        for (auto& transitionStr : transitionData) {
            Rule rule(transitionStr.first, transitionStr.second, *this);
            transitionRules[rule.oldStatus()].push_back(rule);
        }
    }

    int digit(int number) {
        return to_string(abs(number)).length();
    }

public:
    TM(bool verbose, string filename) : isVerbose(verbose), fileName(filename) {}

    void run(string input) {
        readFile();
        for (int i = 0, j = input.length(); i < j; i++) {
            if (!inputSymbols.count(input[i])) {
                if (isVerbose) {
                    cerr << "Input: " << input << endl;
                    cerr << "==================== ERR ====================" << endl;
                    cerr << "error: '" << input[i] << "' was not declared in the set of input symbols"
                         << endl;
                    cerr << "Input: " << input << endl;
                    cerr << right << setw(8 + i) << '^' << endl;
                    cerr << "==================== END ====================" << endl;
                } else {
                    cerr << "illegal input" << endl;
                }
                return;
            }
        }
        tapeCollection[0].initialize(input);
        if (isVerbose) {
            cout << "Input: " << input << endl;
            cout << "==================== RUN ====================" << endl;
        }
        executeTuringMachine();
        if (isVerbose) {
            cout << "Result: ";
            tapeCollection[0].printResult();
            cout << "==================== END ====================" << endl;
        } else tapeCollection[0].printResult();
    }

    class Rule {
    private:
        int fromState, toState;
        string oldSymbol, newSymbol, movement;
        TM& turingMachine;

    public:
        Rule(const string& str, int line, TM& tm) : turingMachine(tm) {
            stringstream buf(str);
            string status1, status2;
            buf >> status1 >> oldSymbol >> newSymbol >> movement >> status2;
            fromState = turingMachine.stateLookupTable[status1];
            toState = turingMachine.stateLookupTable[status2];
            for (size_t i = 0; i < oldSymbol.length(); ++i) {
                if (oldSymbol[i] == '_') oldSymbol[i] = 0;
                if (newSymbol[i] == '_') newSymbol[i] = 0;
            }
        }

        int oldStatus() {
            return fromState;
        }

        bool match() {
            int i = 0;
            while (i < turingMachine.numberOfTapes) {
                char symbol = turingMachine.tapeCollection[i].current();
                if ((oldSymbol[i] == '*' && symbol == 0) || (oldSymbol[i] != '*' && oldSymbol[i] != symbol)) {
                    return false;
                }
                i++;
            }
            return true;
        }

        void apply() {
            int i = 0;
            while (i < turingMachine.numberOfTapes) {
                if (newSymbol[i] != '*') {
                    turingMachine.tapeCollection[i].current() = newSymbol[i];
                }
                switch (movement[i]) {
                case 'l': turingMachine.tapeCollection[i].move(-1); break;
                case 'r': turingMachine.tapeCollection[i].move(1); break;
                }
                i++;
            }
            turingMachine.currentState = toState;
        }
    };
};



bool isTMFile(const std::string& filename) {
    std::regex tmRegex(".*\\.tm$", std::regex_constants::ECMAScript);
    return std::regex_match(filename, tmRegex);
}
bool isPDAFile(const std::string& filename) {
    std::regex tmRegex(".*\\.pda$", std::regex_constants::ECMAScript);
    return std::regex_match(filename, tmRegex);
}
void printHelp() {
    cout << "usage:   fla [-h|--help] <pda> <input> " << endl;
    cout << "         fla [-v|--verbose] [-h|--help] <tm> <input> " << endl;
}
int main(int argc, char* argv[]){
    bool verbose_mode = false;
    bool is_pda = false;
    string pda_path;
    bool is_tm = false;
    string tm_path;
    string pattern;
    
    if(argc == 1){
        return 1;
    }
    
    for (int i = 1; i < argc; ++i) { 
        string arg_ = argv[i];

        if (arg_ == "-h" || arg_ == "--help") {
            printHelp();
            return 0;
        } else if (arg_ == "-v" || arg_ == "--verbose") {
            verbose_mode = true;
        } else if (isPDAFile(arg_)) {
            is_pda = true;
            pda_path = arg_;
        } else if (isTMFile(arg_)) {
            is_tm = true;
            tm_path = arg_;
        } else {
            pattern = arg_;
        }
    }

    // cout << "Verbose mode: " << verbose_mode << endl;
    // cout << "Is PDA: " << is_pda << " Path: " << pda_path << endl;
    // cout << "Is TM: " << is_tm << " Path: " << tm_path << endl;
    // cout << "Pattern: " << pattern << endl;

    if(is_pda){
        PDA pda_;
        loadPDAFromFile(pda_path, pda_);
        //pda_.print();
        int ans = pda_.simulate(pattern, verbose_mode);
        if(ans == 1){
            cout << "true" << endl;
            if(verbose_mode){
                cout << "==================== END ====================\n";
            }
        }
        else if(ans == 0){
            cout << "false" << endl;
            if(verbose_mode){
                cout << "==================== END ====================\n";
            }
        }
        else{
            cerr << "illegal input" << endl;
            return 1;
        }
    }
    else if(is_tm){
        TM tm_(verbose_mode, tm_path);
        tm_.run(pattern);
    }

    return 0;
}
