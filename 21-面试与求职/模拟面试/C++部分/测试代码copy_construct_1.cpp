#include <iostream>
using namespace std;
class point{
     //默认为私有还是公有?
     int x,y;
     static int class_count;//为什么要申请static变量？
                   //应该在哪里初始化？
     public:
     point(int x,int y)
     {//可否不使用this？
     	 this->x = x;
     	 this->y = y;
     	 class_count++;
     	 cout <<"construct point "<<class_count<<endl;
     }
     point(const point & p)
     {
     	x = p.x;
     	y = p.y;
     	class_count++;
     	cout <<"copy construct point "<<class_count<<endl;
     }
     ~point()
     {
     	x = 0;
     	y = 0;
     	cout <<"~point "<<class_count<<endl;
     	class_count--;
     }

};
int point::class_count = 0;
void copy_point(point p)
{
     cout << "---enter copy_point---"<<endl;
     
     cout << "---end copy_point---"<<endl;
}
int main(void)
{
   point p1(3,4);
   point p2(p1);
   point p3 = p2;
   copy_point(p3);
   return 0;
}
