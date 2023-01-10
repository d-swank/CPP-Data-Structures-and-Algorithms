#include<iostream>
#include "ArrayStack.h"
using namespace std;

ArrayStack::ArrayStack() {
    top = -1;
}

ArrayStack::~ArrayStack(){}

bool ArrayStack::isEmpty()
{
    if (top == -1) 
        return true; 
    else 
        return false;
}

bool ArrayStack::isFull()
{
    if (top == MAX - 1) 
        return true; 
    else 
        return false;
}

void ArrayStack::push(element d)
{
    if (isFull()) {
        throw Overflow();
    }
    else { 
        top++; 
        data[top] = d; 
    }
}

float ArrayStack::pop()
{
    if (isEmpty()) {
        throw Underflow();
    }
    else { 
        data[top--];  
    }
}

float ArrayStack::peek()
{
    if (isEmpty()) {
        throw Underflow();
    }
    else { 
        top = data[top]; 
    }
}

int getPrecedence(char operation){
    
    switch (operation){
    case '+':
    case '-': return 1;
    case '*':
    case '/': return 2;
    default: return -1;
    }
}

double applyOperation(double value1, double value2, char operation){

    switch (operation) {
    case '+': return value1 + value2;
    case '-': return value1 - value2;
    case '*': return value1 * value2;
    }
    return value1 / value2;
}

double evalExpression(const char* exp) {
  
    ArrayStack Operand;
    ArrayStack Operator;
    int i;

    for (i = 0; i < strlen(exp); i++) {
  
        if (exp[i] == ' ')
            continue;
        
        else if (exp[i] == '(') {
            
            Operator.push(exp[i]);
        }

        else if (isdigit(exp[i])) {
            float value = 0;
            
            while (i < strlen(exp) && isdigit(exp[i])){
                value = value * 10 + (exp[i] - '0');
                i++;
            }

            float count = 1;
            float doubleValue = 0;
            
            if (i < strlen(exp) && exp[i] == '.'){
                i++;

                while (i < strlen(exp) && isdigit(exp[i])){

                    doubleValue = doubleValue * 10 + (exp[i] - '0');
                    i++;
                    count = count * 10;
                }

                doubleValue = doubleValue / count;
                value = value + doubleValue;
            }

            Operand.push(value);
            i--;
        }
        
        else if (exp[i] == ')'){

            while (!Operator.isEmpty() && Operator.peek() != '('){
                float value1 = Operand.peek();
                Operand.pop();

                float value2 = Operand.peek();
                Operand.pop();

                char op = Operator.peek();
                Operator.pop();

                Operand.push(applyOperation(value1, value2, op));
            }

            if (!Operator.isEmpty())
                Operator.pop();
        }
        
        else{
            while (!Operator.isEmpty() && getPrecedence(Operator.peek()) >= getPrecedence(exp[i])) {
                float value1 = Operand.peek();
                Operand.pop();

                float value2 = Operand.peek();
                Operand.pop();

                char op = Operator.peek();
                Operator.pop();

                Operand.push(applyOperation(value1, value2, op));
            }
            Operator.push(exp[i]);
        }
    }   

    while (!Operator.isEmpty()) {
        float value1 = Operand.peek();
        Operand.pop();
        
        float value2 = Operand.peek();
        Operand.pop();

        char op = Operator.peek();
        Operator.pop();
        
        if (op == '/' && value2 == 0)
            cerr << "Invalid Expression: Cannot Divide by 0!\t";    

        Operand.push(applyOperation(value1, value2, op));
    }
    return Operand.peek();
}

int main() {
    
    try {
        cout << "\n";
        cout << "Calculated Expression divided by 0: " << evalExpression("5 / 0");
    }
    catch (ArrayStack::Underflow) {
        cerr << "Underflow error: Empty Stack. \n";
    }

    try {
        cout << "\n";
        cout << "Calculated Expression divided by 0: " << evalExpression("3.5 + 20/4");
    }
    catch (ArrayStack::Overflow) {
        cerr << "Overflow error: Full Stack. \n";
    }

    return 0;
}