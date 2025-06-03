#include <random>
#include <iostream>
#include <string>

// Amount of questions
constexpr int AMOUNT_OF_QUESTIONS = 3;
constexpr int NUMBER_LIMIT = 10;

// Question struct
struct Question {
    std::pair<int, int> numbers;
    int add() { return numbers.first + numbers.second; }
    Question(int num1, int num2) : numbers(num1, num2) {}
};

// Function declarations
Question make_question(std::random_device& rd);

int main() {
    std::cout << "Generating questions...\n\n";
    std::random_device rd;
    std::vector<Question> questions;
    for (int questions_initialised = 0; questions_initialised < AMOUNT_OF_QUESTIONS; questions_initialised++) {
        questions.emplace_back(make_question(rd));
    }
    int questionsDone = 0;
    int score;
    for (Question question : questions) {
        std::cout << "Question " << ++questionsDone << std::string(score, '!') << "\n";
        std::cout << "What is " << question.numbers.first << " + " << question.numbers.second << "? ";
        std::string inputted;
        std::cin >> inputted;
        int answer;
        try {
            answer = std::stoi(inputted);
        }
        catch (std::invalid_argument e) {
            std::cout << "WRONG! You inputted something wrong...\nTechnical details: Type: std::invalid_argument, What: " << e.what() << "\n\n";
            continue;
        }

        if (answer == question.add()) {
            std::cout << "CORRECT! Well done!\n\n";
            score++;
        }
        else {
            std::cout << "WRONG! Better luck next time!\n\n";
        }
    }
    std::cout << "COMPLETED!\n" << "Your final score is: " << score << std::string(score, '!') << "\n" << std::flush;
    return 0;
}


Question make_question(std::random_device& rd) {
    std::mt19937 num1(rd()); std::mt19937 num2(rd()); // Generate 2 random 32-bit numbers
    std::uniform_int_distribution<> limitNum(1, NUMBER_LIMIT);
    return Question(limitNum(num1), limitNum(num2)); // Limit the numbers to a range of 1-[limit] then return them
}
