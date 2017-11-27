#include <iostream>
#include <cstdint>
using namespace std;

class Box {
	private:
		int l, b, h;
	public:
		Box();
		Box(const int length, const int breadth, const int height);
		Box(const Box& box);
		
		int getLength()const {return this->l; }
		int getBreadth()const {return this->b; }
		int getHeight()const {return this->h; }
		long long CalculateVolume()const {return (long long) l * b * h; }
		
		bool operator<(const Box& box);
		friend ostream& operator<<(ostream& out, const Box& box) {
			out << box.l << " " << box.b << " " << box.h;
			return out;
		}
};

Box::Box() {
	l = 0;
	b = 0;
	h = 0;
}

Box::Box(const int length, const int breadth, const int height) {
	l = length;
	b = breadth;
	h = height;
}

Box::Box(const Box& box) {
	this->l = box.l;
	this->b = box.b;
	this->h = box.h;
}

bool Box::operator<(const Box& box) {
	if(l < box.l)
		return true;
		
	if(l == box.l && b < box.b)
		return true;
		
	if(l == box.l && b == box.b && h < box.h)
		return true;
		
	return false;
}



void check2()
{
	int n;
	cin>>n;
	Box temp;
	for(int i=0;i<n;i++)
	{
		int type;
		cin>>type;
		if(type ==1)
		{
			cout<<temp<<endl;
		}
		if(type == 2)
		{
			int l,b,h;
			cin>>l>>b>>h;
			Box NewBox(l,b,h);
			temp=NewBox;
			cout<<temp<<endl;
		}
		if(type==3)
		{
			int l,b,h;
			cin>>l>>b>>h;
			Box NewBox(l,b,h);
			if(NewBox<temp)
			{
				cout<<"Lesser\n";
			}
			else
			{
				cout<<"Greater\n";
			}
		}
		if(type==4)
		{
			cout<<temp.CalculateVolume()<<endl;
		}
		if(type==5)
		{
			Box NewBox(temp);
			cout<<NewBox<<endl;
		}

	}
}

int main()
{
	check2();
}




