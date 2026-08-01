#include <iostream>
using namespace std;
class A{
    char a;
  public:
    A(){
      cout << "construct A() function\n";
    }   
    A(const A  ){
      cout << "copy construct A() function\n";
    }
    ~A(){
      cout << "destruct ~A() function\n";
    }
};
int main(void)
{
    A a;
    A b = a;
    return 0;
}
