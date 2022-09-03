// WELCOME TO AYAYRON - WHERE THE FUN TRULY INTENSIFIES

// editor.cpp
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
#include <iomanip>
#include <stack>
#include <algorithm> // for copy() and assign()
#include <iterator> // for back_inserter
using namespace std;

// global variables

int cursrow = 1;
size_t curscol = 1;
char filename[100];
vector<vector<char>> buffer;
stack <vector<vector<char>>> bufstack;
stack <vector<vector<char>>> redobufstack;
int savecount = 0;
int insertcount = 0;
int undocount = 0;
int redocount = 0;
int saveflag = 0;


void InputFileIntoVector(char* argv)
{
    ifstream file;
    file.open(argv);
    string line;
    //char c;
    while (std::getline(file, line)) 
    {
        std::vector<char> row;
        for (char &c : line)
        {
            row.push_back(c);
        }
        int x = row.size();
        for (int i = x; i < 20; i++)
        {
            row.push_back(' ');
        }
        

        buffer.push_back(row);
    }

}

// global variables
size_t windowstart = 1;
size_t windowend = 10;

void Display(char* argv)
{
    cout<<"     "<<setw(cursrow)<<"*";
    //<<"                    "<<endl;
    for (int i = cursrow; i <= 20; i++)
    {
        cout<<" ";
    }
    cout<<endl;
    cout<<"     12345678901234567890"<<endl;


    size_t i = windowstart-1;
    for (;i < buffer.size();i++) 
    {   
        if (i+1>windowend)
        {
            break;
        }
        if (curscol == i+1)
        {
            cout<<"* "<<setw(2)<<i+1<<"|";
        }
        else
        {
            cout<<"  "<<setw(2)<<i+1<<"|";
        }
        for (size_t j = 0; j < buffer[i].size(); j++)
        {
            cout<<buffer[i][j];
        }
        
            cout << '\n';
    }
    for (; i < windowend; i++)
    {   
        if (curscol == i+1)
        {
            cout<<"* "<<setw(2)<<i+1<<"|";
        }
        else
        {
            cout<<"  "<<setw(2)<<i+1<<" ";
        }
        cout<<endl;
    }

    cout<<"     12345678901234567890"<<endl;
}

void Savefile(char* argv,string word)
{

    ofstream file;
    file.open(word);
    //cout<<word<<endl;
    for (std::vector<char> &row : buffer) 
    {
        for (char &c : row) 
        {
            file << c;
        }
            file << '\n';
    }
}

void moveCursorToRight(int count)
{

    for (int i = 0; i < count; i++)
    {
 
        if (cursrow>=20)
        {
            ;
        }
        else
        {
        cursrow++;
        }
    }
    
}

void moveCursorToLeft(int count)
{
    for (int i = 0; i < count; i++)
    {
 
        if (cursrow == 1)
        {
            ;
        }
        else
        {
        cursrow--;
        }
    }
    
}

void moveCursorToUp()//int count)//, char* argv)
{
    if (curscol == 1)
    {
        ;

    }
    else if (curscol == windowstart)
    {
        windowstart--;
        windowend--;
        curscol--;
    }
    else
    {   
    curscol--;
    }
}

void moveCursorToDown()
{
    if (curscol == buffer.size())
    {
        if (curscol == windowstart)
        {
            ;
        }
        else
        {
        windowstart++;
        windowend++;
        }

    }
    else if (curscol == windowend)
    {
        windowstart++;
        windowend++;
        curscol++;
    }
    else
    {   
    curscol++;
    }
}

void Insertion(string input)
{
    int j = cursrow;
    size_t k = curscol;
    //cout<<k<<endl;
    for (size_t i = 0; i < input.size(); i++)
    {
        buffer[k-1][j-1] = input[i];
        //cout<<buffer[curscol][j];
        j++;
        // cout<<"before increment: "<<j<<endl;
        if (j > 20)
        {
            j = 1;
            k++;
        }
        if (k > buffer.size())
        {   
            if (k > 30)
            {
                break;
            }
                
            buffer.resize(k,vector<char>(20,' '));
            
        }
        // cout<<k<<endl<<j<<endl;
        // cout<<buffer.size()<<endl; 
        // cout<<cursrow<<endl;
    }

    // cout<<endl;

    // for (size_t i = 0; i < buffer.size(); i++)
    // {
    //     for (size_t j = 0; j < buffer[i].size(); j++)
    //     {
    //         cout<<buffer[i][j];
    //     }
    //     cout<<endl;
        
    // }
    

}

int main(int argc, char* argv[])
{
    //checkFile(argc,argv[1]);
    if (argc!=2)
    {   
        if (argc>2)
        {
            cout<<"Too many command-line arguments."<<endl;
            return 1;
        }
        else
        {
            cout<<"Too few command-line arguments."<<endl;
            return 1;
        }
    }

    ifstream fi;
    fi.open(argv[1]);
    if (fi.is_open())
    {
        string str;
        int count = 0;
        while (getline(fi, str))
        {
            if (str.length() >= 21)
            {
                cout<<"File "<<argv[1]<<" has at least one too long line."<<endl;
                return 2;
            }
            count++;            
        }
        if (count>30)
        {
                cout<<"File "<<argv[1]<<" has too many lines."<<endl;
                return 2;
        }

    }
    else
    {
        cout<<"Failed to open file: "<<argv[1]<<endl;
        return 2;
    }
    fi.close();

    strcpy(filename, argv[1]);
    InputFileIntoVector(filename);
    Display(argv[1]);
    stack<string> stack;
    string input;
    bufstack.push(buffer);
    label:
    cout<<"Enter command: ";
    getline(cin,input);
    cout<<endl;
    stack.push(input);
    while (input!="q")
    {
                string word = input.substr(0,1);
                if (word == "d")
                {
                    moveCursorToRight(1);
                    //ss>>word;
                    if (input.size()!= 1)
                    {
                    word = input.substr(2);
                    //cout<<word<<endl;
                    moveCursorToRight(stoi(word)-1);
                    }

                    Display(argv[1]);
                }
                else if (word == "a")
                {
                    moveCursorToLeft(1);
                    if (input.size()!= 1)
                    {
                    word = input.substr(2);
                    //cout<<word<<endl;
                    moveCursorToLeft(stoi(word)-1);
                    }
                    Display(argv[1]);
                }
                else if (word == "w")
                {
                    moveCursorToUp();//, argv[1]);
                    if (input.size()!= 1)
                    {
                    word = input.substr(2);
                    for (int i = 0; i < stoi(word)-1; i++)
                    {
                        moveCursorToUp();//,argv[1])
                    }
                    
                    }
                    Display(argv[1]);    
                }        
                else if (word == "s")
                {   
                    if (input[1]=='a')
                    {
                        word = input.substr(5);
                        Savefile(argv[1],word);
                        Display(argv[1]); 
                        savecount++;
                        saveflag = 1;
                    }   
                    else
                    {                 
                        moveCursorToDown();//, argv[1]);
                        if (input.size()!= 1)
                        {
                        word = input.substr(2);
                        //cout<<word<<endl;
                        for (int i = 0; i < stoi(word)-1; i++)
                        {
                            moveCursorToDown();//,argv[1])
                        }

                        }
                        Display(argv[1]); 
                    }   
                }
                else if (word == "i")
                {
                    // bufstack.push(buffer);
                    word = input.substr(2);
                    Insertion(word);
                    Display(argv[1]);
                    bufstack.push(buffer);
                    //buffer = bufstack.top();
                    // cout<<endl;
                    // for (size_t i = 0; i < bufstack.top().size(); i++)
                    // {
                    //     for (size_t j = 0; j < bufstack.top()[i].size(); j++)
                    //     {
                    //         cout<<bufstack.top()[i][j];
                    //     }
                    //     cout<<endl;
                        
                    // }
                    undocount++;  
                    insertcount++;  
                    while(!redobufstack.empty())
                    {
                    redobufstack.pop();       
                    }    
                    redocount = 0;
                    saveflag = 2;
                }    
                else if (word == "u")
                {
                    //cout<<undocount<<endl;
                    if (undocount < 1)
                    {
                        cout<<"Cannot undo.\n"<<endl;
                        Display(argv[1]);
                    }
                    else
                    {
                    redobufstack.push(buffer);
                    bufstack.pop(); 
                    buffer = bufstack.top();                       
                    Display(argv[1]);
                    insertcount--;
                    undocount--;
                    redocount++;
                    }
                    
                }    
                else if (word == "r")
                {
                    if (redocount < 1)
                    {
                        cout<<"Cannot redo.\n"<<endl;
                        Display(argv[1]);   
                    }
                    else
                    {
                    buffer = redobufstack.top();
                    bufstack.push(redobufstack.top());
                    redobufstack.pop();
                    Display(argv[1]);
                    insertcount++;
                    redocount--;
                    undocount++;
                    }
                }
        
        cout<<"Enter command: ";
        getline(cin, input);
        cout<<endl;
        if (input.empty())
        {
            input = stack.top();
        }
        else
        {
            stack.push(input);
        }
    }
    
    if (saveflag != 0 && saveflag != 1 && insertcount != savecount)
    //(insertcount != savecount)
    {
        cout<<"You have unsaved changes.\n";
        cout<<"Are you sure you want to quit (y or n)?\n";
        getline(cin, input);
        if (input == "n")
        {
            Display(argv[1]);
            goto label;
        }
        
    }
    cout<<"Goodbye!"<<endl;
    return 0;
}
