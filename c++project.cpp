#include <iostream>
#include <bits/stdc++.h>
#include <string.h>
#include <fstream>

using namespace std;

string whiteSpaceRemove(string str)
{

    int start = 0, end = str.size() - 1;
    // find the first index with character
    for (int i = 0; i < str.size(); i++)
    {
        if (str[i] != ' ')
        {
            start = i;
            break;
        }
    }
    // find the last index with character
    for (int i = str.size() - 1; i >= 0; i--)
    {
        if (str[i] != ' ')
        {
            end = i;
            break;
        }
    }
    string newStr = "";
    // create new string with out white space
    for (int i = start; i <= end; i++)
    {
        newStr += str[i];
    }
    return newStr;
}

string upperCaseToLowercase(string str)
{
    string newStr = "";
    // convert upper case character in lower case charactar
    for (auto x : str)
    {
        if (isdigit(x) == false && isupper(x) == true)
        {
            x = x + 32;
        }
        newStr = newStr + x;
    }
    return newStr;
}
// create a structure of operand
struct operand
{
    string operand;
    bool validation;
};

class operandChecker
{
public:
    const vector<string> operandRegisterName = {"zero", "ra", "sp", "gp", "tp", "fp"}; // save some register name

    bool validOpeand(string str)
    {
        str = upperCaseToLowercase(str); // conver the string in lowercase chareacter
        int size = str.size();

        for (int i = 0; i < operandRegisterName.size(); i++) // searching from register vector
        {

            if (str == operandRegisterName[i])
            {
                return true;
            }
        }
        if (str[0] != 'a' && str[0] != 's' && str[0] != 't' && str[0] != 'x') // if it is a number
        {

            for (char &c : str)
            {
                if (isdigit(c) == 0)
                {
                    return false;
                }
            }
            return true;
        }

        if (str[0] == 'a' && str.size() > 1 && isdigit(str[1])) // if it is   A regiser
        {
            string newStr = str.substr(1);
            int num = stoi(newStr);
            if (num < 8)
                return true;
        }
        if (str[0] == 's' && str.size() > 1 && isdigit(str[1])) // if it is   S regiser
        {
            string newStr = str.substr(1);
            int num = stoi(newStr);
            if (num < 12)
                return true;
        }
        if (str[0] == 't' && str.size() > 1 && isdigit(str[1])) // if it is   T regiser
        {
            string newStr = str.substr(1);
            int num = stoi(newStr);
            if (num < 7)
                return true;
        }
        if (str[0] == 'x' && str.size() > 1 && isdigit(str[1])) // if it is   X regiser
        {
            string newStr = str.substr(1);
            int num = stoi(newStr);
            if (num < 32)
                return true;
        }

        return false;
    }
};

class opcode
{
public:
    const vector<string> opcode = {"add", "addi", "sub", "subi", "la", "li", "ecall"}; // save op code
    const vector<string> opcodeWithThreeOperands = {"add", "addi", "sub", "subi"};     // save op code which use 3 operands
    const vector<string> opcodeWithTwoOperands = {"la", "li"};                         // save op code which use 2 operands
    const string opcodeWithNoOperands = "ecall";                                       // save op code which use no operand

    bool validOpcode(string str) // searching it is opcode
    {
        for (int i = 0; i < opcode.size(); i++)
        {
            if (str == opcode[i])
            {
                return true;
            }
        }
        return false;
    }

    bool validOpcode(string str, int num)
    {
        str = upperCaseToLowercase(str);
        if (num == 3) // searching it is a 3 operand's opcode
        {
            for (int i = 0; i < opcodeWithThreeOperands.size(); i++)
            {
                if (str == opcodeWithThreeOperands[i])
                {
                    return true;
                }
            }
            return false;
        }
        if (num == 2) // searching it is a 2 operand's opcode
        {
            for (int i = 0; i < opcodeWithTwoOperands.size(); i++)
            {
                if (str == opcodeWithTwoOperands[i])
                {
                    return true;
                }
            }
            return false;
        }
        if (num == 0) // searching it is a  ecall opcode
        {
            if (str == opcodeWithNoOperands)
            {
                return true;
            }
        }
        return false;
    }
};

class instructioncheck
{
public:
    bool opValid;
    bool operandVaild;
    int operandNum;
    bool instruction = false;
    vector<operand> instructionOperands;
    string instructionOpcode;

    void instructionOpcodeAndOperand(vector<string> words) // store written opcode in a string and operand in vector
    {

        if (!words.empty())
        {
            if (words.size() == 1)
            {
                instructionOpcode = words[0];
                

                
            }
            else
            {
                instructionOpcode = words[0];

                for (int i = 1; i < words.size(); i++)
                {

                    instructionOperands.push_back({
                        words[i],
                    });
                }
            }
        }
    }

    void opcodeAndOrarandSeparetion(string str) // separeting op code and operand
    {

        string word = "";

        vector<string> words;
        for (auto x : str)
        {
            if (x == '#')
            {
                break;
            }
            if (x == ' ')
            {

                if (word != "")
                {
                    words.push_back(word);
                }
                word = "";
            }
            else
            {
                if (x != ',')
                {
                    word = word + x;
                }
            }
        }
        if (word != "")
        {
            words.push_back(word);
        }
        instructionOpcodeAndOperand(words);
       
    }

    void opcodeAndOrarandValidation() // cheaking the opcode and the operand are valid or not
    {
        opcode opcode;
        operandChecker operand;
        operandNum = instructionOperands.size();
        opValid = opcode.validOpcode(instructionOpcode, operandNum);
        

        for (int i = 0; i < instructionOperands.size(); i++)
        {
            instructionOperands[i].validation = operand.validOpeand(instructionOperands[i].operand);
        }
        for (int i = 0; i < instructionOperands.size(); i++)
        {
            if (!instructionOperands[i].validation)
            {
                operandVaild = false;
                break;
            }
            operandVaild = true;
        }
    }

    string validInsinstruction() // creating a instruction with valid opcode and operand
    {
        string requiredInsruction = "";

        if (!instructionOpcode.empty())
        {
            
            if (upperCaseToLowercase(instructionOpcode) == "ecall")
            {
                
                requiredInsruction = instructionOpcode;
            }
            else
            {
                requiredInsruction = instructionOpcode + " ";
            }
        }

        if (!instructionOperands.empty())
        {
            for (int i = 0; i < instructionOperands.size(); i++)
            {
                string word = "";
                if (i == operandNum - 1)
                {
                    requiredInsruction = requiredInsruction + instructionOperands[i].operand;
                    break;
                }
                word = instructionOperands[i].operand + ',';
                requiredInsruction = requiredInsruction + word + " ";
            }
        }
        return requiredInsruction;
    }

    bool instructionChecker(string str) // checking the instruction vaild or not
    {

        string requiredInsruction = "";
        opcodeAndOrarandSeparetion(str);

        opcodeAndOrarandValidation();

        if ((opValid == true && operandVaild == true) || (upperCaseToLowercase(instructionOpcode) == "ecall" && instructionOperands.empty())) // if the opcode and operand is valid creating the instruction
        {
            requiredInsruction = validInsinstruction();
        }

        

        string newStr;

        for (auto x : str) // crating the before # tag
        {
            if (x == '#')
            {
                break;
            }
            newStr = newStr + x;
        }
        
        str = whiteSpaceRemove(newStr); // removing the white space

        if (requiredInsruction == str&&requiredInsruction!=""&str!="")
        {
            instruction = true;
        }

        if (instruction == true)
        {
            cout << "valid" << endl;
            return true;
        }
        else
        {
            cout << "invalid" << endl;
            return false;
        }
    }
    void dInstructioncheck() // destructor
    {
        opValid = false;
        operandVaild = false;
        operandNum = 0;
        instruction = false;
        instructionOperands.clear();
        instructionOpcode = "";
    }
};

int main()
{

   string input;
    instructioncheck check;
    check.instructionChecker(input);
    
    ofstream finalList("finalList.txt");

    // Read from the text file
    ifstream readFile("input.txt");
    int i = 1;

    // to read the file line by line
    while (getline(readFile, input))
    {
        if (input != "")
        {
            cout << "Number " << i << " instruction : " << input << " = ";
            if (check.instructionChecker(input))
            {

                finalList << input << endl;
            }
            check.dInstructioncheck();
            i++;
        }
    }
    finalList.close();

    readFile.close();

    cout << endl;
    cout << "Valid Instruction are : " << endl;
    cout << endl;

    ifstream readfinalList("finalList.txt");
    while (getline(readfinalList, input))
    {
        if (input != "")
        {
            cout << "instruction : " << input << endl;
        }
    }
    readfinalList.close();

    return 0;
}