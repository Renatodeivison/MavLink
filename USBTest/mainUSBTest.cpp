/* 
 * File:   main.cpp
 * Author: serl
 *
 * Created on June 3, 2015, 10:39 AM
 */


#include <iostream>
#include <string>
#include <fstream>




using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
        
        ofstream myfile ("/media/serl/637C-20AF/test.txt");
        if (myfile.is_open()){
            myfile << "This is a line.\n";
            myfile << "Testing line 2.\n";
            myfile.close();
        }else cout << "Unable to open file";
        
        string text;
        ifstream myfile1 ("/media/serl/637C-20AF/test.txt");
        if (myfile1.is_open()){
                while ( getline (myfile1,text) ){
                cout << text << endl;
                }
        myfile1.close();
        }else cout << "Unable to open file"; 
        


        return 0;
}
