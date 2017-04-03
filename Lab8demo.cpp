/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   main.cpp
 * Author: Theo Choma
 *
 *
 */

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>



using namespace std;

class message{

    protected:
        string msg;
    public:
        message();
        message(string);
        virtual ~message();
        virtual void print();

};


message::message(){
    cout<<"Please input a message to translate: "<<endl;
    cin>>msg;
}

message::message(string input){
    msg = input;
}

message::~message(){
	//cout << "\nBase Destructor" << endl;
}

void message::print(){
    cout << msg <<endl;
}


class morseCodeMessage:public message{
    public:
        string tran_msg;
        int index;
        morseCodeMessage();
        morseCodeMessage(string);
        ~morseCodeMessage();
        void translate(string message1);
        void print();
};

morseCodeMessage::morseCodeMessage() : message(){
    translate(msg);
}

morseCodeMessage::morseCodeMessage(string input) : message(input){
    msg = input;
    translate(msg);
}

morseCodeMessage::~morseCodeMessage(){
	//cout << "\nMorse Destructor" << endl;
}

void morseCodeMessage::print(){
    cout << msg << endl;
    cout << tran_msg << endl;
}


void morseCodeMessage::translate(string message1) {
    //translate english to morse using a morse code table
	string morseTable[] = {".-", "-...", "-.-.", "-..", ".", "..-.",
		"--.", "....", "..", ".---", "-.-", ".-..", "--", "-.", "---",
		".--.", "--.-", ".-.", "...", "-", "..-", "...-", ".--", "-..-",
		"-.--", "--.."};
		char ch;
		string output = "";

		for(unsigned int i=0; i < message1.length(); i++)
		{
			ch = message1[i];
			ch = toupper(ch);
			output += morseTable[ch - 'A']; //A is the first value of the array; by subtracting, it's finding the appropriate morse code value for each letter
			output += " ";
		}
		tran_msg = output;
}



class messageStack{
public:
    message *ptrstack[10];
    messageStack(message);
    ~messageStack();
    void push(message current_obj);
    void pop();
    void printStack();
    int stack_top;
    int numobj;
};

messageStack::messageStack(message init){
    //cout<<"stack constructor"<<endl;
    ptrstack[0] = new message(init);
    //ptrstack[0] = &init;

    numobj= 1;
    stack_top = 1;


}
messageStack::~messageStack(){
	//cout << "\nStack Destructor" << endl;
        for(int i = 0; i < numobj; i++)
	{
		delete ptrstack[i];
	}
}


void messageStack::push(message current_obj){
    ptrstack[stack_top] = new message(current_obj);
	//ptrstack[stack_top] = &current_obj;
    numobj++;
    stack_top++;
}

void messageStack::pop(){
    //cout<<"begin popping"<<endl;
    delete ptrstack[stack_top-1];
    stack_top--;
    numobj--;
}

void messageStack::printStack(){
    //print all messages from top to bottom of stack
	//cout<<"print stack fn"<< endl;
	for(int i = 0; i < numobj; i++)
	{
		cout<<"Message no. " << i <<endl;
		ptrstack[i]->print();
	}
}

int main(int argc, char** argv) {

    message msg1("test");
    msg1.print();
    morseCodeMessage msg2("Helloworld");
    msg2.print();
    message msg3("Test2");
    msg3.print();

    cout<<endl;
    messageStack stack(msg1);
    stack.push(msg2);
    stack.push(msg3);
    stack.printStack();
    stack.pop();
    cout<<endl;
    stack.printStack();


    cout<<endl<<"exit"<<endl;
    return 0;
}

