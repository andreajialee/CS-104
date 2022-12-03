#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <cmath>
#include <stdlib.h>
#include <sstream>
using namespace std;

double log100(int n){
    return (int)floor(log(n)/log(100));
}
int findM(string word){
    map<char,string> vals;  string m;
    vals[' '] = "00";   vals['a'] = "01";   vals['b'] = "02";   vals['c'] = "03";
    vals['d'] = "04";   vals['e'] = "05";   vals['f'] = "06";   vals['g'] = "07";
    vals['h'] = "08";   vals['i'] = "09";   vals['j'] = "10";   vals['k'] = "11";
    vals['l'] = "12";   vals['m'] = "13";   vals['n'] = "14";   vals['o'] = "15";
    vals['p'] = "16";   vals['q'] = "17";   vals['r'] = "18";   vals['s'] = "19";
    vals['t'] = "20";   vals['u'] = "21";   vals['v'] = "22";   vals['w'] = "23";
    vals['x'] = "24";   vals['y'] = "25";   vals['z'] = "26";
    // Create the value m 
    for(unsigned int i = 0; i<word.length(); i++){
        m += vals[word[i]];
    }
    return stoll(m);
}
//  M = C^d mod n
//  C = M^e mod n
long mod(long a, int b, int n)
{
    int x = 1;
    while(b>0){
        if(b%2==1)
            x = (x*a)%n;
        b = b >> 1;
        a = (a*a)%n;
    }
    return x;
}

void encrypt(string file, int n, string s){
    // If n is less than 27
    int e = 65537;
    if(n < 27){                 
        cout << "Error, n value is less than 27" << std::endl;
        return;
    }
    // Create ofstream to output stuff into file
    ofstream f(file);
    // Cacluate x: x = 1+log_100 (n/27)
    int x = 1 + log100(n/27);
    long m, c;
    while(s!=""){                       // Encrypt
        if((int)s.length()<x){
            int spaces = x - s.length();
            for(int i=0; i<spaces; i++){
                s += " ";
            }
            m = findM(s);
            c = mod(m,e,n);
            f << c;
            return;
        }
        string temp = s.substr(0,x);    // Find first x chars
        s = s.substr(x,s.length()-1);   // Make string shorter
        m = findM(temp);                // Find value of M
        c = mod(m, e, n);               // Calculate C = M^e mod n
        f << c << " ";                  // Print info
    }
    return;
}

int gcd(int a, int b){
    if(b==0){
        return a;
    }
    return gcd(b, a%b);
}

// Find GCD(e,L) GCD(a,b)
int gcdEx(int a, int b, int *x, int *y) 
{ 
    if (a == 0) 
    { 
        *x = 0; 
        *y = 1; 
        return b; 
    } 
    int x1, y1;
    int gcd = gcdEx(b%a, a, &x1, &y1); 
    *x = y1 - (b/a) * x1; 
    *y = x1; 
    return gcd; 
}

string findS(string s){
    string message = "";
    map<int,char> chars;
    chars[0] = ' '; chars[1] = 'a'; chars[2] = 'b'; chars[3] = 'c'; chars[4] = 'd';
    chars[5] = 'e'; chars[6] = 'f'; chars[7] = 'g'; chars[8] = 'h'; chars[9] = 'i';
    chars[10] = 'j'; chars[11] = 'k'; chars[12] = 'l'; chars[13] = 'm'; chars[14] = 'n';
    chars[15] = 'o'; chars[16] = 'p'; chars[17] = 'q'; chars[18] = 'r'; chars[19] = 's';
    chars[20] = 't'; chars[21] = 'u'; chars[22] = 'v'; chars[23] = 'w'; chars[24] = 'x';
    chars[25] = 'y'; chars[26] = 'z';
    while(s!=""){
        if(s.length()<=2){
            int m = stoi(s);
            message += chars[m];
            return message;
        }
        int m = stoi(s.substr(0,2));
        s = s.substr(2, s.length()-1);
        message += chars[m];
    }
    return message;
}

int findKey(int p, int q){
    int l = ((p-1) * (q-1)) / gcd(p-1, q-1);
    int e = 65537;
    if(l <= e){
        cout << "Error, l value is less than or equal to e" << endl;
        return 0;
    }
    int d; int y;
    int GCD = gcdEx(e, l, &d, &y);
    if(d<0){
        d+= (p-1)*(q-1);
    }
    if(GCD!=1){
        cout << "Error, p and q are not prime numbers" << endl;
        return 0;
    }
    return d;
}

void decrypt(string i, string o, int p, int q){
    int n = p * q;
    int d = findKey(p,q);
    ifstream in(i);
    ofstream out(o);
    if(in.is_open()){
        int c;
        while(in >> c){
            string m = to_string(mod(c,d,n));
            if(m.length()%2!=0){
                m = "0" + m;
            }
            string message = findS(m);
            out << message;
        }
    }
}

int main(int argc, char* argv[]){
    // Check if enough inputs
    if(argc < 3){
        std::cout << "Error, not enough inputs" << std::endl;
        return 1;
    }
    // Get p, q, & n
    long p = atoi(argv[1]);
    long q = atoi(argv[2]);
    // Set up variables
    string line, command, in, out, file, message;
    int num;
    // Continue to take in commands from user
    while(getline(cin,line)){
        stringstream ss(line);
        ss >> command;
        if(command == "EXIT"){
            return 0;
        }
        else if(command == "ENCRYPT"){
            ss >> file; 
            ss >> num; 
            string word;
            while(ss >> word){
                message += word + " ";
            }
            message = message.substr(0, message.length()-1);
            encrypt(file, num, message);
        }
        else if(command == "DECRYPT"){
            ss >> in;
            ss >> out;
            decrypt(in, out, p, q);
        }
        else{
            return 0;
        }
    }
}
