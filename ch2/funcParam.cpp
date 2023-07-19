//函数指针
#include <iostream>

double besty(int);
double pam(int);

void estimate(int lines, double (*pf) (int));
int main(){
    using namespace std;
    int code;
    cout << "How many lines of code do you need?\n";
    cin >> code;
    cout << "Here's besty's estimate\n";
    estimate(code, besty);
    cout << "Here's Pam's estimate\n";
    estimate(code, pam);
    return 0;
}

double besty(int lns){
    return 0.05 * lns;
}
double pam(int lns){
    return 0.03 * lns + 0.004 * lns * lns;
}
void estimate(int lines, double (*pf) (int)){
    using namespace std;
    cout << lines << "lines will take";
    cout << (*pf)(lines) << "hours\n";
}