#include <QLCDNumber>
#include <iostream>
using namespace std;
class MyLCD:public QLCDNumber
{
	Q_OBJECT
	public:
	MyLCD(QWidget *parent);
	
	int op1;
	int op2;
	int acc;
	int res;
	int LCDn;
	
	public slots:
		//reset es lo deberia ejecuar si se clicka el btn de reset.
		void reset_all();
		void suma();
		void resta();
		void multiplicacion();
		void division();
		void abs();
		
		
	
	signals:
	
	
	
	
};
