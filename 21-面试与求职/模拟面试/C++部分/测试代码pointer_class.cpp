#include <iostream>
#include <string.h>
using namespace std;
class ch_class{
     char *ch;
     public:
       ch_class(const char *str=NULL ){//构造函数
            ch = new char[20];//因为ch指针分配空间
            if(str==NULL)//防止定义的对象为空的情况
              strncpy(ch,"nameless",8);//如果为空则内部定义为无名人士
            if(strlen(str)>20)//因为ch指针分配空间是20个字符，防止越界
              strncpy(ch,str,20);
            else
              strncpy(ch,str,strlen(str));
            cout << "construct ch....." << endl;
       }
       ch_class(const ch_class & o){//拷贝构造函数
           ch = new char[20];
           if(strlen(o.ch)>20)
              strncpy(ch,o.ch,20);
           else
              strncpy(ch,o.ch,strlen(o.ch));
           cout << "copy construct ch......" << endl;
       }
       void show()
       {
           cout << "ch = " << ch <<endl;
       }
       ~ch_class()
       {
            delete []ch;
            ch = NULL;
            cout << "destruct ch....." << endl;
       }
};
int main(void)
{
  ch_class a("xiajiashan");
  cout << "a is ";
  a.show();
  ch_class b = a;
  cout << "b is ";
  b.show();
  return 0;
}
