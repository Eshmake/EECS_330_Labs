#ifndef __MYINFIXCALCULATOR_H__
#define __MYINFIXCALCULATOR_H__

#include <algorithm>
#include <string>

#include "MyStack_s701a908.h"
#include "MyVector_s701a908.h"

class MyInfixCalculator{

  public:
    
    MyInfixCalculator()
    {

    }

    ~MyInfixCalculator()
    {
     
    }

    double calculate(const std::string& s)
    {
        // code begins
        MyVector<std::string> infix_tokens;
        MyVector<std::string> postfix_tokens;
        tokenize(s, infix_tokens);
        infixToPostfix(infix_tokens, postfix_tokens);
        return calPostfix(postfix_tokens);
        // code ends
    }

  private:

    // returns operator precedance; the smaller the number the higher precedence
    // returns -1 if the operator is invalid
    // does not consider parenthesis
    int operatorPrec(const char c) const
    {
        switch(c)
        {
            case '*':
                return 2;
            case '/':
                return 2;
            case '+':
                return 3;
            case '-':
                return 3;
            default:
                return -1;
        }
    }

    // checks if a character corresponds to a valid parenthesis
    bool isValidParenthesis(const char c) const
    {
        switch(c)
        {
            case '(':
                return true;
            case ')':
                return true;
            default:
                return false;
        }
    }

    // checks if a character corresponds to a valid digit
    bool isDigit(const char c) const
    {
        if(c >= '0' && c <= '9')
            return true;
        return false;
    }

    // computes binary operation given the two operands and the operator in their string form
    double computeBinaryOperation(const std::string& ornd1, const std::string& ornd2, const std::string& opt) const
    {
        double o1 = std::stod(ornd1);
        double o2 = std::stod(ornd2);
        switch(opt[0])
        {
            case '+':
                return o1 + o2;
            case '-':
                return o1 - o2;
            case '*':
                return o1 * o2;
            case '/':
                return o1 / o2;
            default:
                std::cout << "Error: unrecognized operator: " << opt << std::endl;
                return 0.0;
        }
    }


    
    void tokenize(const std::string& s, MyVector<std::string>& tokens)
    {
        // code begins
        std::string num = "";
        for (int i = 0; i < s.length(); i++)
        {
            char c = s[i];
            if (c == ' '){
                continue;
            }
            if (isdigit(c) || c == '.' || (c == '-' && (i == 0 || s[i - 1] == '(' || s[i - 1] == '+' || s[i - 1] == '-' || s[i - 1] == '*' || s[i - 1] == '/'))){
                num += c;
            }
            else
            {
                if (!num.empty())
                {
                    tokens.push_back(num);
                    num = "";
                }

      
                std::string token(1, c);
                tokens.push_back(token);
            }
        }
        if (!num.empty())
            tokens.push_back(num);
        // code ends
    }

    // converts a set of infix tokens to a set of postfix tokens
    void infixToPostfix(MyVector<std::string>& infix_tokens, MyVector<std::string>& postfix_tokens)
    {
        // code begins
        MyStack<std::string> stack;
        for (int i = 0; i < infix_tokens.size(); i++){
           
            if (isdigit(infix_tokens[i][0]) || (infix_tokens[i].length() > 1 && infix_tokens[i][0] == '-')){
                postfix_tokens.push_back(infix_tokens[i]);
            }
           
            else if (infix_tokens[i] == "("){
                stack.push(infix_tokens[i]);
            }
            
            else if (infix_tokens[i] == ")"){
                while (!stack.empty() && stack.top() != "("){
                    postfix_tokens.push_back(stack.top());
                    stack.pop();
                }
               
                if (!stack.empty()) stack.pop();
            }
            
            else{
               
                while (!stack.empty() && stack.top() != "(" && operatorPrec(stack.top()[0]) <= operatorPrec(infix_tokens[i][0])){
                    postfix_tokens.push_back(stack.top());
                    stack.pop();
                }
              
                stack.push(infix_tokens[i]);
            }
        }
    
        while (!stack.empty())
        {
            postfix_tokens.push_back(stack.top());
            stack.pop();
        }
        // code ends
    }
    


    double calPostfix(const MyVector<std::string>& postfix_tokens) const
    {
        // code begins
        
        std::string operators = "+-*/";

        MyStack<std::string> stack;

        for (int i = 0; i < postfix_tokens.size(); i++){

            if (operators.find(postfix_tokens[i]) == std::string::npos){
                stack.push(postfix_tokens[i]);
            }
    
            else{
                std::string opd2 = stack.top();
                stack.pop();
                std::string opd1 = stack.top();
                stack.pop();

                stack.push(std::to_string(computeBinaryOperation(opd1, opd2, postfix_tokens[i])));
            }
        }
        return std::stod(stack.top());
        
        // code ends
    }
};

#endif // __MYINFIXCALCULATOR_H__
