#include <iostream>
#include <wiringPi.h>
#include <fstream>
#include <string>

using namespace std;

int main(void) {
//    ifstream file("led_test_data.txt");

    ifstream file("led_test_data.txt");
    if(true == file.is_open()) {
        int i=0;
        string s[100];
        while(file) {
            getline(file, s[i]);
            cout << i << s[i] << endl;
            i++;
        }
        file.close();
    } else {
        cout << "file open fail" << endl;
    }

    return 0;

}
