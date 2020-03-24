#include "MyGLWidget.h"
#include <iostream>
using namespace std;

MyGLWidget::MyGLWidget (QWidget* parent) : QOpenGLWidget(parent), program(NULL)
{
  setFocusPolicy(Qt::StrongFocus);  // per rebre events de teclat
}

MyGLWidget::~MyGLWidget ()
{
  if (program != NULL)
    delete program;
}

void MyGLWidget::initializeGL ()
{
  // Cal inicialitzar l'ús de les funcions d'OpenGL
  initializeOpenGLFunctions();
  glClearColor (0.5, 0.7, 1.0, 1.0); // defineix color de fons (d'esborrat)
  carregaShaders();
  createBuffersQuadrat();
  doubleViewport = false;

 }

void MyGLWidget::pintaQuadrat ()  // AQUEST MÈTODE NO ES POT MODIFICAR !!!
{
  // Activem l'Array a pintar 
  glBindVertexArray(VAO1);
  // Pintem el quadrat
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

void MyGLWidget::pintaEscena ()  
{
  modelTransformR1();
  pintaQuadrat ();
  modelTransformR2();
  pintaQuadrat ();
}

void MyGLWidget::pintaEscenaGiradaZ180 ()  
{
  modelTransformR1giradoZ();;
  pintaQuadrat ();
  modelTransformR2giradoZ ();
  pintaQuadrat ();
}


void MyGLWidget::paintGL ()
{
	if (!doubleViewport) {
		glClear (GL_COLOR_BUFFER_BIT);  // Esborrem el frame-buffer
		glViewport (0, 0, width(), height()); // Aquesta crida no caldria perquè Qt la fa de forma automàtica amb aquests paràmetres
	  	pintaEscena ();
		// Desactivem el VAO
		glBindVertexArray(0);
	  }
	else  {
		glClear (GL_COLOR_BUFFER_BIT);  // Esborrem el frame-buffer		
		//left top
		glViewport(0, height()/2, width()/2, height()/2);
		pintaEscena();
		//right bottom
		glViewport(width()/2, 0, width()/2, height()/2);
		pintaEscenaGiradaZ180();
		glBindVertexArray(0);
	}
}

void MyGLWidget::modelTransformR1 () 
{
	glm::mat4 TG(1.0);
    TG = glm::translate (TG, glm::vec3 (-0.5,0.1,0.0));
    // hacemos las escalar juntas .
    // 0.4*escalaX = 0.2 -> escalaX = 0.2/0.4=0.5
    // 0.4*escalaY = 1.0 -> escalaY = 1.0/0.4 = 2.5
    TG = glm::scale (TG, glm::vec3 (0.5,2.5,0.0));
    TG = glm::translate (TG, glm::vec3 (0.0,0.0,0.0));
    glUniformMatrix4fv(transLoc,1,GL_FALSE,&TG[0][0]);
}

void MyGLWidget::modelTransformR2 () 
{	
	glm::mat4 TG(1.0);
    TG = glm::translate (TG, glm::vec3 (-0.3,-0.5,0.0));
    // hacemos las escalas juntas .
    // 0.4*escalaX = 0.6 -> escalaX = 0.6/0.4=1.5
    // 0.4*escalaY = 0.2 -> escalaY = 0.2/0.4 = 0.5
    TG = glm::scale (TG, glm::vec3 (1.5,0.5,0.0));
    TG = glm::translate (TG, glm::vec3 (0.0,0.0,0.0));
    glUniformMatrix4fv(transLoc,1,GL_FALSE,&TG[0][0]);
}


void MyGLWidget::modelTransformR1giradoZ () 
{
	glm::mat4 TG(1.0);
	//se multiplican por (-1) los puntos de tranlascion originales
	TG = glm::translate (TG, glm::vec3 (0.5,-0.1,0.0));
	//las ecalas siguen siendo las mismas
    TG = glm::scale (TG, glm::vec3 (0.5,2.5,0.0));
    //girar 180 grados
    TG = glm::rotate (TG, float(M_PI), glm::vec3 (0.0,0.0,1.0));
    TG = glm::translate (TG, glm::vec3 (0.0,0.0,0.0));
    glUniformMatrix4fv(transLoc,1,GL_FALSE,&TG[0][0]);
}


void MyGLWidget::modelTransformR2giradoZ () 
{	
	glm::mat4 TG(1.0);
    //se multiplican por (-1) los puntos de tranlascion originales
    TG = glm::translate (TG, glm::vec3 (0.3,0.5,0.0));
	//las ecalas siguen siendo las mismas
    TG = glm::scale (TG, glm::vec3 (1.5,0.5,0.0));
    //girar 180 grados
    TG = glm::rotate (TG, float(M_PI), glm::vec3 (0.0,0.0,1.0));
    TG = glm::translate (TG, glm::vec3 (0.0,0.0,0.0));
    glUniformMatrix4fv(transLoc,1,GL_FALSE,&TG[0][0]);
}




void MyGLWidget::resizeGL (int w, int h)
{
  // Aquí anirà el codi que cal fer quan es redimensiona la finestra
  // no es demana en aquest exercici!
  glViewport (0, 0, w, h);
  
}


void MyGLWidget::keyPressEvent(QKeyEvent* event) 
{
  makeCurrent();
  switch (event->key()) {
    case Qt::Key_V: { // canvi entre un i dos viewports
      doubleViewport = !doubleViewport;
	  break;
    }
    default: event->ignore(); break;
  }
  update();
}

void MyGLWidget::createBuffersQuadrat ()  // AQUEST MÈTODE NO ES POT MODIFICAR !!!
{
  glm::vec3 Vertices[4];  // Quatre vèrtexs amb X, Y i Z
  Vertices[0] = glm::vec3(-0.2, -0.2, 0.0);
  Vertices[1] = glm::vec3(0.2, -0.2, 0.0);
  Vertices[2] = glm::vec3(-0.2, 0.2, 0.0);
  Vertices[3] = glm::vec3(0.2, 0.2, 0.0);
  
  glm::vec3 Colors[4];
  Colors[0] = glm::vec3(1.0, 1.0, 0.0);
  Colors[1] = glm::vec3(1.0, 0.0, 0.0);
  Colors[2] = glm::vec3(1.0, 1.0, 0.0);
  Colors[3] = glm::vec3(1.0, 0.0, 0.0);
  
  // Creació del Vertex Array Object (VAO) que usarem per pintar
  glGenVertexArrays(1, &VAO1);
  glBindVertexArray(VAO1);

  // Creació del buffer amb les dades dels vèrtexs
  GLuint VBOs[2];
  glGenBuffers(2, VBOs);
  glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
  // Activem l'atribut que farem servir per vèrtex (només el 0 en aquest cas)   
  glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(vertexLoc);

  glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Colors), Colors, GL_STATIC_DRAW);
  // Activem l'atribut que farem servir per vèrtex (només el 0 en aquest cas)   
  glVertexAttribPointer(colorLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(colorLoc);

  // Desactivem el VAO
  glBindVertexArray(0);
}

void MyGLWidget::carregaShaders()
{
  // Creem els shaders per al fragment shader i el vertex shader
  QOpenGLShader fs (QOpenGLShader::Fragment, this);
  QOpenGLShader vs (QOpenGLShader::Vertex, this);
  // Carreguem el codi dels fitxers i els compilem
  fs.compileSourceFile("shaders/fragshad.frag");
  vs.compileSourceFile("shaders/vertshad.vert");
  // Creem el program
  program = new QOpenGLShaderProgram(this);
  // Li afegim els shaders corresponents
  program->addShader(&fs);
  program->addShader(&vs);
  // Linkem el program
  program->link();
  // Indiquem que aquest és el program que volem usar
  program->bind();

  // Obtenim identificador per a l'atribut “vertex” del vertex shader
  vertexLoc = glGetAttribLocation (program->programId(), "vertex");
  // Obtenim identificador per a l'atribut “color” del vertex shader
  colorLoc = glGetAttribLocation (program->programId(), "color");
  //conectaamos con el vertex shader para pasarle la mat4 TG con lo valores.
  // Obtenemi identificador per a l'atribut "TG" del vertex shader
   transLoc = glGetUniformLocation (program-> programId() , "TG");
}
