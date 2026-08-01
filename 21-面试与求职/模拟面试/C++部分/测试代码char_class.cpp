#include <iostream>
using namespace std;
class ch_class{
     char ch;
     public:
       ch_class(char c){
            ch = c;
            cout << "construct ch....." << endl;
       }
       ch_class(const ch_class & o){
           ch = o.ch;
           cout << "copy construct ch......" << endl;
       }
       void show(){
           cout << "ch = " << ch <<endl;
       }
       ~ch_class(){
            ch = 0;
            cout << "destruct ch....." << endl;
       }
};
int main(void)
{
  ch_class a('A');
  cout << "a is ";
  a.show();
  ch_class b = a;
  cout << "b is ";
  b.show();
  return 0;
}
