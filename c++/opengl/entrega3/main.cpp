
#include <QApplication>
#include "Calculadora.h"

int main(int argc, char**argv) {
	QApplication app(argc,argv);
	Calculadora calculadora;
	calculadora.show();
	return app.exec();
	
	}
