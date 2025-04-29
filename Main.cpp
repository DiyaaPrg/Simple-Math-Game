#include <iostream>
#include <cstdlib>

using namespace std;

enum enQuestionLevels {Easy = 1, Med = 2, Hard = 3, Mixlevel = 4};

enum enOperationType {Add = 1, Sub = 2, Mul = 3, Div = 4, Mix = 5};

enum enRightOrWrong {Right = 1, Wrong = 2};

struct strGameResults {
    short NumberofQuestions = 0;
    enOperationType OpType;
    string level;
    short NumberofRightAnswers = 0;
    short NumberofWrongAnswers = 0;
    string finalresult;
    string operationtype;
};


int ReadNumberInRange(string message, int Least_num, int Most_num)
{
    int number = 0;
    do {
        cout << message;
        cin >> number;
    } while (number < Least_num || number > Most_num);

    return number;
}

int RandomNumber(int From, int To)
{
    int randnum = rand() % (To - From + 1) + From;
    return randnum;
}

short ReadHowManyQuestions()
{
    short number = ReadNumberInRange("How Many Questions do you want to answer? ", 1, 10);
    return number;
}

void ClearScreen()
{
    system("cls");
    system("color 0F");
}

void FillTwoNumbers(enQuestionLevels level, int &num1, int &num2)
{
    switch (level)
    {
    case(enQuestionLevels::Easy):
    {
        num1 = RandomNumber(1, 10);
        num2 = RandomNumber(1, 10);
        break;
    }

    case(enQuestionLevels::Med):
    {
        num1 = RandomNumber(10, 100);
        num2 = RandomNumber(10, 100);
        break;
    }
    case(enQuestionLevels::Hard):
    {
        num1 = RandomNumber(100, 1000);
        num2 = RandomNumber(100, 1000);
        break;
    }
    case(enQuestionLevels::Mixlevel):
    {
        num1 = RandomNumber(1, 1000);
        num2 = RandomNumber(1, 1000);
        break;
    }
    }
}

int CalculateTwoNumbers(enOperationType optype, int num1, int num2)
{

    switch (optype)
    {
    case(enOperationType::Add):
        return (num1 + num2);

    case(enOperationType::Sub):
        return (num1 - num2);

    case(enOperationType::Mul):
        return (num1 * num2);

    case(enOperationType::Div):
        return (num1 / num2);

    }

    
   
}

string ReturnOperationString(enOperationType optype)
{
    switch (optype)
    {
    case(enOperationType::Add):
        return "+";

    case(enOperationType::Sub):
        return "-";

    case(enOperationType::Mul):
        return "*";

    case(enOperationType::Div):
        return "/";
    case(enOperationType::Mix):
        return "Mix";
    default:

        return "Unknown";
    }
}

string ReturnLevelString(enQuestionLevels level)
{
        switch (level)
        {
        case(enQuestionLevels::Easy):
            return "Easy";
        case(enQuestionLevels::Med):
            return "Med";
        case(enQuestionLevels::Hard):
            return "Hard";
        case(enQuestionLevels::Mixlevel):
            return "Mix";
        default:
            return "Unknown";
        }
}

int ChooseOperation(short opType)
{
    // this function works when user want mix operations 
    int rand_num = RandomNumber(1, 4);
    if (opType == 5)
        return rand_num;
    else
        return opType;
} 

enRightOrWrong PrintOperation(int num1, int num2, enOperationType optype, int right_answer)
{
    string operationType = ReturnOperationString(optype);
    cout << "\n" << num1;
    cout << "\n" << operationType; 
    cout << "\n" << num2;
    cout << "\n" << "__________________\n";
    int user_answer = ReadNumberInRange("", -100, 10000000);

    if (user_answer == right_answer)
        return enRightOrWrong::Right;
    else
        return enRightOrWrong::Wrong;
}

void ChangeScreentoGrayorRed(enRightOrWrong answer)
{
    if (answer == enRightOrWrong::Right)
        system("color 2F");
    else
        system("color 4F");

}

void PrintWrongorCorrect(enRightOrWrong answer, int correctanswer)
{
    if (answer == enRightOrWrong::Right)
    {
        cout << "\n" << "Right Answer :-)";

    }
    else
    {
        cout << "\n" << "Wrong Answer :-(\n";
        cout << "The Right Answer is: " << correctanswer << endl;
    }
    cout << "\n\n";
    ChangeScreentoGrayorRed(answer);


}

string PassOrFail(strGameResults &g_results)
{
    if (g_results.NumberofRightAnswers > g_results.NumberofWrongAnswers)
        return "Pass :-)";
    else
        return "Fail :-(";
}

void FillGameResults(strGameResults &g_results, enOperationType optype, short num_questions, enQuestionLevels level)
{
    g_results.NumberofQuestions = num_questions;
    g_results.OpType = optype;
    g_results.finalresult = PassOrFail(g_results);
    g_results.level = ReturnLevelString(level);
    g_results.operationtype = ReturnOperationString(optype);
}

strGameResults PlayGame(short NumberofQuestions)
{
    short Questionlevels = ReadNumberInRange("Enter Questions levels [1] Easy, [2] Med, [3] Hard, [4] Mix: ", 1, 4);  
    short OperationType  = ReadNumberInRange("Enter Operation type [1] Add, [2] Sub, [3] Mul, [4] Div, [5] Mix: ", 1, 5); 
    short user_operation_type = OperationType;

    strGameResults game_results;

    for (int i = 1; i <= NumberofQuestions; ++i)
    {

        cout << "\n\nQuestion[" << i << "/" << NumberofQuestions << "]\n";

        int number1 = 0, number2 = 0;
        FillTwoNumbers(enQuestionLevels(Questionlevels), number1, number2);
        
        if (user_operation_type == 5)
            OperationType = ChooseOperation(user_operation_type);
        

        int result = CalculateTwoNumbers(enOperationType(OperationType), number1, number2);

        enRightOrWrong Answer =  PrintOperation(number1, number2, enOperationType(OperationType), result);

        PrintWrongorCorrect(Answer, result);

        if (Answer == enRightOrWrong::Right)
            game_results.NumberofRightAnswers++;
        else
            game_results.NumberofWrongAnswers++;
    }
    FillGameResults(game_results, enOperationType(user_operation_type), NumberofQuestions, enQuestionLevels(Questionlevels));

    return game_results;

}

void PrintGameResults(strGameResults g_results)
{
    cout << "_____________________________\n";
    cout << "Final Result is: " << g_results.finalresult << "\n";
    cout << "_____________________________\n";
    cout << "Number of Questions: " << g_results.NumberofQuestions << "\n";
    cout << "Questions Levels   : " << g_results.level << "\n";
    cout << "Op Type            : " << g_results.operationtype << "\n";
    cout << "Number of Right Answers: " << g_results.NumberofRightAnswers << "\n";
    cout << "Number of Wrong Answers: " << g_results.NumberofWrongAnswers << "\n";
    cout << "_____________________________" <<endl;

}


void StartGame()
{
    char answer = 'Y';
    do {
        ClearScreen();

        strGameResults Results;
        Results = PlayGame(ReadHowManyQuestions());
       
        PrintGameResults(Results);


        cout << "\nDo you want to continue playing (Y/N): ";
        cin >> answer;

    } while (answer == 'y' || answer == 'Y');



}


int main()
{
    srand((unsigned)time(NULL));

    StartGame();






    return 0;
}
  

