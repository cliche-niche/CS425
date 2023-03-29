#include <bits/stdc++.h>

using namespace std;

string bit_string(int k){
    string s = "";
    while(k--){
        s += ( (rand() & 1) ? '1' : '0');
    }
    return s;
}

void string_xor(string (&a), const string (&b), const int index = 0){
    if(index + b.size() > a.size()){
        return;
    }

    for(int i = 0; i < b.size(); i++){
        a[index + i] = ( (a[index + i] != b[i]) ? '1' : '0' );
    }
}

string find_remainder(string dividend, const string (&divisor)){
    string remainder = "";

    for(int i = 0; i < dividend.size(); i++){
        if(i + divisor.size() <= dividend.size()){
            if(dividend[i] == '1'){
                string_xor(dividend, divisor, i);
            }
        }else{
            remainder += dividend[i];
        }
    }

    return remainder;
}

string find_crc(string message, const string (&polynomial)){
    for(int i = 0; i < polynomial.size() - 1; i++){
        message += '0';
    }

    return find_remainder(message, polynomial);
}

inline string find_fcs(const string (&message), const string(&polynomial)){
    return message + find_crc(message, polynomial);
}

void add_errors(string (&t)){
    int error_prob = 10; // * Each bit is flipped with an error probability of $1/error_prob$
    
    for(auto &i : t){
        if(rand() % error_prob == 0){
            i = '1' - i + '0';
        }
    }
}

bool check_valid(string t, const string (&p)){
    cout<<"\nChecking validity of "<<t<<" with respect to "<<p<<"...\n";
    t = find_remainder(t, p);
    for(const auto &i : t){
        if(i == '1'){
            cout<<"Non-zero remainder: "<<t<<"\nInvalid! It should be discarded.\n";
            return false;
        }
    }

    cout<<"Valid! It should be accepted.\n";
    return true;
}

void q1_original(void);     // * For checking CRC generation with 2 inputs
void q1_modified(void);     // * For parts a, b, c, d

int main(){

    srand(time(NULL));

    string s;


    while(1){
        cout<<"\n\nThis program can be used in two ways:\n";
        cout<<"(1) Generate CRC from two random strings\n";
        cout<<"(2) Generate a 15-bit frame, introduce some errors, and check validity of resulting string\n\n";
        cin>>s;
        cout<<endl;

        if(s.size() != 1){
            cout<<"Please write only 1 or 2.\n";
        }else if(s[0] == '1'){
            q1_original();
            break;
        }else if(s[0] == '2'){
            q1_modified();
            break;
        }else{
            cout<<"Please write only 1 or 2.\n";
        }
    }

    cout<<'\n';

    return 0;
}

void q1_original(){
    int n = 10, k = 6;
    string t;

    while(1){
        cout<<"\nDo you want to give custom input ($n$ and $k$)? [y/n]\n";
        cin>>t;

        if(t.size() != 1){
            cout<<"Please only enter 'y' or 'n' (without the quotes)\n";
        }else if(t[0] == 'y'){
            cout<<"Enter the value of integer $n$, the frame size: ";
            cin>>n;
            cout<<"Enter the value of integer $k$, the message size: ";
            cin>>k;
            
            if(n-k+1 <= 0){
                cout<<"$n$ should be greater than or equal to $k$\n";
                n = 10; k = 6;
                continue;
            }else{
                break;
            }
        }else if(t[0] == 'n'){
            cout<<"\n\nProceeding with default values $n=10$ and $k=6$...\n\n";
            break;
        }else{
            cout<<"\nPlease only enter 'y' or 'n' (without the quotes)\n";
        }
    }

    cout<<"First input:\n";
    string m = bit_string(k), p = "0";
    while(p[0] != '1'){
        p = bit_string(n-k+1);
    }
    string crc = find_crc(m, p);
    
    cout << "M = " << m << ", P = " << p << '\n' << "CRC = " << crc << "\nFCS = " << m + crc << '\n';
    check_valid(m + crc, p);

    cout<<"\nSecond input:\n";
    m = bit_string(k), p = "0";
    while(p[0] != '1'){
        p = bit_string(n-k+1);
    }
    crc = find_crc(m, p);
    
    cout << "M = " << m << ", P = " << p << '\n' << "CRC = " << crc << "\nFCS = " << m + crc << '\n';
    check_valid(m + crc, p);

    cout<<'\n';
}

void q1_modified(){
    int n = 15, k = 10;

    string m = bit_string(k), p = "110101";
    string t = find_fcs(m, p);

    cout<<"\nMessage: "<<m<<", Polynomial: "<<p;
    cout<<"\nTransmission frame (T):\n"<<t<<'\n';

    add_errors(t);

    cout<<"\nTransmission frame after introducing errors:\n"<<t<<'\n';

    check_valid(t, p);
}