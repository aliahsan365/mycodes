#include "MyGLWidget.h" 
#include <iostream> 
using namespace std; 
MyGLWidget::MyGLWidget (QWidget* parent) : QOpenGLWidget(parent), 
program(NULL) {
  setFocusPolicy(Qt::StrongFocus);  // per rebre events de teclat
  xClick = yClick = 0;
  DoingInteractive = NONE;
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

  glClearColor(0.5, 0.7, 1.0, 1.0); // defineix color de fons (d'esborrat)
  glEnable(GL_DEPTH_TEST);
  carregaShaders();
  createBuffersModel();
  createBuffersTerraIParet();

  iniEscena();
  iniCamera();
}

void MyGLWidget::iniEscena ()
{

  xf = 0.0;
  zf = 0.0;
  fescena = false;
  glUniform1i(fescenaLoc, fescena);
  posFocus = glm::vec3(xf,1,zf);
  glUniform3fv(posFocusLoc,  1,  &posFocus[0]);

  nf = 0;
  selected.first = false;
  selected.second = 0;
  xp1 = -1.5; zp1 = 1.5;
  xp2 = 1.5; zp2 = 1.5;

  boundingBoxMin = glm::vec3(-2.0,-2.0,-2.0);
  boundingBoxMax = glm::vec3(2.0,2.0,2.0);
  float dist = distance(boundingBoxMin,boundingBoxMax);
  radiEsc = dist/2;
  //radiEsc = sqrt(3.0);

  //radiEsc = sqrt(12);  // sqrt(4+4+4)
}

void MyGLWidget::iniCamera ()
{
  angleY = 0.0;
  ra = 1.0;
  perspectiva = true;

  projectTransform ();
  viewTransform ();
}

void MyGLWidget::paintGL ()
{
  glViewport (0, 0, width(), height()); // Aquesta crida no caldria perquè Qt la fa de forma automàtica amb aquests paràmetres

  // Esborrem el frame-buffer i el depth-buffer
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Activem el VAO per a pintar el terra
  glBindVertexArray (VAO_Terra);

  modelTransformTerra ();

  // pintem
  glDrawArrays(GL_TRIANGLES, 0, 12);

  // Activem el VAO per a pintar el Patricio
  glBindVertexArray (VAO_Patr);

  modelTransformModel1 ();

  // Pintem l'escena
  glDrawArrays(GL_TRIANGLES, 0, patr.faces().size()*3);

	// Activem el VAO per a pintar el Patricio
  glBindVertexArray (VAO_Patr);

  modelTransformModel2 ();

  // Pintem l'escena
  glDrawArrays(GL_TRIANGLES, 0, patr.faces().size()*3);



  glBindVertexArray(0);
}

void MyGLWidget::resizeGL (int w, int h)
{
  
  // para que no se deform
  ra = w/h;
  projectTransform();
  update();
  glViewport(0,0,w,h);
  
  
  //no pide que no se recorte.
  // si se piede que no se recorte habria que hacer trigonometria y calcular
  // (en perspectiva)
  
  
  // Aquí anirà el codi que cal fer quan es redimensiona la finestra
  // En aquest exercici no es demana...
  
  
  
}

void MyGLWidget::createBuffersModel ()
{
  // Carreguem el model de l'OBJ - Atenció! Abans de crear els buffers!
  patr.load("./models/Patricio.obj");

  // Calculem la capsa contenidora del model
  calculaCapsaModel ();

  // Creació del Vertex Array Object del Patricio
  glGenVertexArrays(1, &VAO_Patr);
  glBindVertexArray(VAO_Patr);

  // Creació dels buffers del model patr
  GLuint VBO_Patr[6];
  // Buffer de posicions
  glGenBuffers(6, VBO_Patr);
  glBindBuffer(GL_ARRAY_BUFFER, VBO_Patr[0]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*patr.faces().size()*3*3, patr.VBO_vertices(), GL_STATIC_DRAW);

  // Activem l'atribut vertexLoc
  glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(vertexLoc);

  // Buffer de normals
  glBindBuffer(GL_ARRAY_BUFFER, VBO_Patr[1]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*patr.faces().size()*3*3, patr.VBO_normals(), GL_STATIC_DRAW);

  glVertexAttribPointer(normalLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(normalLoc);

  // En lloc del color, ara passem tots els paràmetres dels materials
  // Buffer de component ambient
  glBindBuffer(GL_ARRAY_BUFFER, VBO_Patr[2]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*patr.faces().size()*3*3, patr.VBO_matamb(), GL_STATIC_DRAW);

  glVertexAttribPointer(matambLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(matambLoc);

  // Buffer de component difusa
  glBindBuffer(GL_ARRAY_BUFFER, VBO_Patr[3]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*patr.faces().size()*3*3, patr.VBO_matdiff(), GL_STATIC_DRAW);

  glVertexAttribPointer(matdiffLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(matdiffLoc);

  // Buffer de component especular
  glBindBuffer(GL_ARRAY_BUFFER, VBO_Patr[4]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*patr.faces().size()*3*3, patr.VBO_matspec(), GL_STATIC_DRAW);

  glVertexAttribPointer(matspecLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(matspecLoc);

  // Buffer de component shininness
  glBindBuffer(GL_ARRAY_BUFFER, VBO_Patr[5]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*patr.faces().size()*3, patr.VBO_matshin(), GL_STATIC_DRAW);

  glVertexAttribPointer(matshinLoc, 1, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(matshinLoc);

  glBindVertexArray(0);
}


void MyGLWidget::createBuffersTerraIParet ()
{
  // VBO amb la posició dels vèrtexs
  glm::vec3 posterra[12] = {
	glm::vec3(-2.0, -2.0, 2.0),
	glm::vec3(2.0, -2.0, 2.0),
	glm::vec3(-2.0, -2.0, -2.0),
	glm::vec3(-2.0, -2.0, -2.0),
	glm::vec3(2.0, -2.0, 2.0),
	glm::vec3(2.0, -2.0, -2.0),
	glm::vec3(-2.0, -2.0, -2.0),
	glm::vec3(2.0, -2.0, -2.0),
	glm::vec3(-2.0, 2.0, -2.0),
	glm::vec3(-2.0, 2.0, -2.0),
	glm::vec3(2.0, -2.0, -2.0),
	glm::vec3(2.0, 2.0, -2.0)
  };

  // VBO amb la normal de cada vèrtex
  glm::vec3 norm1 (0,1,0);
  glm::vec3 norm2 (0,0,1);
  glm::vec3 normterra[12] = {
	norm1, norm1, norm1, norm1, norm1, norm1, // la normal (0,1,0) per als primers dos triangles
	norm2, norm2, norm2, norm2, norm2, norm2  // la normal (0,0,1) per als dos últims triangles
  };

  // Definim el material del terra
  glm::vec3 amb(0.2,0.2,0.2);
  glm::vec3 diff(0.2,0.2,0.6);
  //modificar del spec del terra para que haya taca especular.
  glm::vec3 spec(1,1,1);
  float shin = 100;

  // Fem que aquest material afecti a tots els vèrtexs per igual
  glm::vec3 matambterra[12] = {
	amb, amb, amb, amb, amb, amb, amb, amb, amb, amb, amb, amb
  };
  glm::vec3 matdiffterra[12] = {
	diff, diff, diff, diff, diff, diff, diff, diff, diff, diff, diff, diff
  };
  glm::vec3 matspecterra[12] = {
	spec, spec, spec, spec, spec, spec, spec, spec, spec, spec, spec, spec
  };
  float matshinterra[12] = {
	shin, shin, shin, shin, shin, shin, shin, shin, shin, shin, shin, shin
  };

// Creació del Vertex Array Object del terra
  glGenVertexArrays(1, &VAO_Terra);
  glBindVertexArray(VAO_Terra);

  GLuint VBO_Terra[6];
  glGenBuffers(6, VBO_Terra);
  glBindBuffer(GL_ARRAY_BUFFER, VBO_Terra[0]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(posterra), posterra, GL_STATIC_DRAW);

  // Activem l'atribut vertexLoc
  glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(vertexLoc);

  glBindBuffer(GL_ARRAY_BUFFER, VBO_Terra[1]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(normterra), normterra, GL_STATIC_DRAW);

  // Activem l'atribut normalLoc
  glVertexAttribPointer(normalLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(normalLoc);

  // En lloc del color, ara passem tots els paràmetres dels materials
  // Buffer de component ambient
  glBindBuffer(GL_ARRAY_BUFFER, VBO_Terra[2]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(matambterra), matambterra, GL_STATIC_DRAW);

  glVertexAttribPointer(matambLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(matambLoc);

  // Buffer de component difusa
  glBindBuffer(GL_ARRAY_BUFFER, VBO_Terra[3]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(matdiffterra), matdiffterra, GL_STATIC_DRAW);

  glVertexAttribPointer(matdiffLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(matdiffLoc);

  // Buffer de component especular
  glBindBuffer(GL_ARRAY_BUFFER, VBO_Terra[4]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(matspecterra), matspecterra, GL_STATIC_DRAW);

  glVertexAttribPointer(matspecLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(matspecLoc);

  // Buffer de component shininness
  glBindBuffer(GL_ARRAY_BUFFER, VBO_Terra[5]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(matshinterra), matshinterra, GL_STATIC_DRAW);

  glVertexAttribPointer(matshinLoc, 1, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(matshinLoc);

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
  // Obtenim identificador per a l'atribut “normal” del vertex shader
  normalLoc = glGetAttribLocation (program->programId(), "normal");
  // Obtenim identificador per a l'atribut “matamb” del vertex shader
  matambLoc = glGetAttribLocation (program->programId(), "matamb");
  // Obtenim identificador per a l'atribut “matdiff” del vertex shader
  matdiffLoc = glGetAttribLocation (program->programId(), "matdiff");
  // Obtenim identificador per a l'atribut “matspec” del vertex shader
  matspecLoc = glGetAttribLocation (program->programId(), "matspec");
  // Obtenim identificador per a l'atribut “matshin” del vertex shader
  matshinLoc = glGetAttribLocation (program->programId(), "matshin");

  // Demanem identificadors per als uniforms del vertex shader
  transLoc = glGetUniformLocation (program->programId(), "TG");
  projLoc = glGetUniformLocation (program->programId(), "proj");
  viewLoc = glGetUniformLocation (program->programId(), "view");
  
  //enviar los punteros a fs fauzia
  fescenaLoc = glGetUniformLocation (program->programId(), "fescena");
  posFocusLoc = glGetUniformLocation (program->programId(), "posFocus");
  
  
  
}



void MyGLWidget::modelTransformModel1 ()
{
  glm::mat4 TG(1.f);  // Matriu de transformació
  TG = glm::translate(TG, glm::vec3(xp1, -2.0, zp1));
  TG = glm::rotate(TG,float(-M_PI/4), glm::vec3(0.0,1.0,0.0));
  TG = glm::rotate(TG,float(M_PI), glm::vec3(0.0,1.0,0.0));
  TG = glm::scale(TG, glm::vec3(escalaP1, escalaP1, escalaP1));
  TG = glm::translate(TG, -centreBasePatr);

  glUniformMatrix4fv (transLoc, 1, GL_FALSE, &TG[0][0]);
}



void MyGLWidget::modelTransformModel2 ()
{
  glm::mat4 TG(1.f);  // Matriu de transformació
  TG = glm::translate(TG, glm::vec3(xp2, -2.0, zp2));
  TG = glm::rotate(TG,float(M_PI/4), glm::vec3(0.0,1.0,0.0));
  TG = glm::rotate(TG,float(M_PI), glm::vec3(0.0,1.0,0.0));
  TG = glm::scale(TG, glm::vec3(escalaP2, escalaP2, escalaP2));
  TG = glm::translate(TG, -centreBasePatr);

  glUniformMatrix4fv (transLoc, 1, GL_FALSE, &TG[0][0]);
}


void MyGLWidget::modelTransformTerra ()
{
  glm::mat4 TG(1.f);  // Matriu de transformació
  glUniformMatrix4fv (transLoc, 1, GL_FALSE, &TG[0][0]);
}

void MyGLWidget::projectTransform ()
{
  glm::mat4 Proj;  // Matriu de projecció
  if (perspectiva)
	Proj = glm::perspective(float(M_PI/3.0), ra, radiEsc, 3.0f*radiEsc);
  else
	Proj = glm::ortho(-radiEsc, radiEsc, -radiEsc, radiEsc, radiEsc, 3.0f*radiEsc);

  glUniformMatrix4fv (projLoc, 1, GL_FALSE, &Proj[0][0]);
}

void MyGLWidget::viewTransform ()
{
  glm::mat4 View;  // Matriu de posició i orientació
  View = glm::translate(glm::mat4(1.f), glm::vec3(0, 0, -2*radiEsc));
  View = glm::rotate(View, -angleY, glm::vec3(0, 1, 0));

  glUniformMatrix4fv (viewLoc, 1, GL_FALSE, &View[0][0]);
}

void MyGLWidget::calculaCapsaModel ()
{
  // Càlcul capsa contenidora i valors transformacions inicials
  float minx, miny, minz, maxx, maxy, maxz;
  minx = maxx = patr.vertices()[0];
  miny = maxy = patr.vertices()[1];
  minz = maxz = patr.vertices()[2];
  for (unsigned int i = 3; i < patr.vertices().size(); i+=3)
  {
	if (patr.vertices()[i+0] < minx)
	  minx = patr.vertices()[i+0];
	if (patr.vertices()[i+0] > maxx)
	  maxx = patr.vertices()[i+0];
	if (patr.vertices()[i+1] < miny)
	  miny = patr.vertices()[i+1];
	if (patr.vertices()[i+1] > maxy)
	  maxy = patr.vertices()[i+1];
	if (patr.vertices()[i+2] < minz)
	  minz = patr.vertices()[i+2];
	if (patr.vertices()[i+2] > maxz)
	  maxz = patr.vertices()[i+2];
  }
  escalaP1 = 2.0/(maxy-miny);
  escalaP2 = 1.0/(maxy-miny);
  centreBasePatr[0] = (minx+maxx)/2.0; centreBasePatr[1] = miny; centreBasePatr[2] = (minz+maxz)/2.0;



}

void MyGLWidget::keyPressEvent(QKeyEvent* event)
{
  makeCurrent();
  switch (event->key()) {
	case Qt::Key_O: { // canvia òptica entre perspectiva i axonomètrica
	  perspectiva = !perspectiva;
	  projectTransform ();
	  break;
	}

	case Qt::Key_F: { // canvia òptica entre perspectiva i axonomètrica
	 ++nf;
	 cout << "nf " << nf << endl;
	 if (nf % 3 == 0) {
		 //inicial
		cout << "modo 0  no se selecionado ninguna patrico" << endl;
	
        selected.first = false;
		selected.second = 0;
		cout << "xf " << xf << endl;
		cout << "zf " << zf << endl;
        //focus de camara
		posFocus = glm::vec3(0,0,0);
		glUniform3fv(posFocusLoc,  1,  &posFocus[0]);
		fescena =  selected.first;
		glUniform1i(fescenaLoc, fescena);
		if (!fescena) {cout << "estamos en el foco de camara" << endl;}
  
        }
	 else if (nf % 3 == 1) {
		 //foco sobre el patricio 1
	     selected.first = true;
		 selected.second = 1;
		 cout << "el pat selecionado es " << selected.second << endl;
		 xf = xp1;
		 zf = zp1;
         cout << "xf " << xf << endl;
		 cout << "zf " << zf << endl;
         //1 viene de -2+3 , el terra esta en y -2 y el lo quienre a +3
         // respecte el terra, luego "y" del foco es 1
         posFocus = glm::vec3(xf,1,zf);
		 glUniform3fv(posFocusLoc,  1,  &posFocus[0]);
		 cout << posFocus[0] << " " << posFocus[1] << " " << posFocus[2] <<  endl;
		 fescena =  selected.first;
		 glUniform1i(fescenaLoc, fescena);
		 if (fescena) {cout << "estamos en el foco de escena" << endl;} 

		 }
	 else if (nf % 3 == 2) {
		 selected.first = true;
		 selected.second = 2;
		 cout << "el pat selecionado es " << selected.second << endl;
         //foco sobre el patricio 2
         xf = xp2;
		 zf = zp2;
	     cout << "xf " << xf << endl;
		 cout << "zf " << zf << endl;
		 // el focus esta a altura 3 respecto al suelo, el suelo esta en -2
		 // luego focus esta en x,-2+3,z.
		 posFocus = glm::vec3(xf,-2+3,zf);
		 glUniform3fv(posFocusLoc,  1,  &posFocus[0]);
		 fescena =  selected.first;
		 glUniform1i(fescenaLoc, fescena);
		 if (fescena) {cout << "estamos en el foco de escena" << endl;}
		 }
	 break;
	}

	case Qt::Key_Up: { // canvia òptica entre perspectiva i axonomètrica

	  if (selected.first) {
		cout << "vamos hacia adelante" << endl;
	    fescena =  selected.first;
		glUniform1i(fescenaLoc, fescena);
		if (selected.second == 1) {
			  //pat 1 esta selecionado
			  //segund el calculo es de xp1 <= 1.5 && zp1 >= -1.5
			  if (xp1  < 1.5 and zp1 > -1.5) {
				  xp1 += 0.25;
				  zp1 -= 0.25;
				  xf = xp1;
				  zf = zp1;
				  posFocus = glm::vec3(xf,1,zf);
		          glUniform3fv(posFocusLoc,  1,  &posFocus[0]);
		          cout << posFocus[0] << " " << posFocus[1] << " " << posFocus[2] <<  endl;
                  modelTransformModel1();
			
		       }
			  cout << "xp1 " << xp1 << endl;
			  cout << "zp1 " << zp1 << endl;
			  cout << "xf " << xf << endl;
			  cout << "zf " << zf << endl;
			 }
		  else if (selected.second == 2) {
			  // pat 2 esta selecionado
			  if (xp2 > -1.5 and zp2 > -1.5) {
				  xp2 -= 0.25;
				  zp2 -= 0.25;
				  xf = xp2;
				  zf = zp2;
				  posFocus = glm::vec3(xf,1,zf);
				  glUniform3fv(posFocusLoc,  1,  &posFocus[0]);
				  cout << posFocus[0] << " " << posFocus[1] << " " << posFocus[2] <<  endl;
				  modelTransformModel2();
			
				 }
			  cout << "xp2 " << xp2 << endl;
			  cout << "zp2 " << zp2 << endl;
			  cout << "xf " << xf << endl;
			  cout << "zf " << zf << endl;
			 }
		}
	  break;
	}
     case Qt::Key_Down: { // canvia òptica entre perspectiva i axonomètrica
		if (selected.first) {
		  cout << "vamos hacia atras" << endl;
		  fescena =  selected.first;
		  glUniform1i(fescenaLoc, fescena);
		  if (selected.second == 1) {
			  //pat 1 esta selecionado
			  //segund el calculo es de xp1 <= 1.5 && zp1 >= -1.5
			if (xp1 > -1.5 and zp1 < 1.5) {
				  xp1 -= 0.25;
				  zp1 += 0.25;
				  xf = xp1;
				  zf = zp1;
				  posFocus = glm::vec3(xf,1,zf);
		          glUniform3fv(posFocusLoc,  1,  &posFocus[0]);
		          cout << posFocus[0] << " " << posFocus[1] << " " << posFocus[2] <<  endl;
				  modelTransformModel1();
	
			}
			  cout << "xp1 " << xp1 << endl;
			  cout << "zp1 " << zp1 << endl;
		      cout << "xf " << xf << endl;
			  cout << "zf " << zf << endl;
			 }
		  else if (selected.second == 2) {
			  // pat 2 esta selecionado
			  if (xp2 < 1.5 and zp2 < 1.5) {
				  xp2 += 0.25;
				  zp2 += 0.25;
				  xf = xp2;
				  zf = zp2;
				  posFocus = glm::vec3(xf,1,zf);
				  cout << posFocus[0] << " " << posFocus[1] << " " << posFocus[2] <<  endl;
				  glUniform3fv(posFocusLoc,  1,  &posFocus[0]);
				  modelTransformModel2();
			
			   }
			  cout << "xp2 " << xp2 << endl;
			  cout << "zp2 " << zp2 << endl;
			  cout << "xf " << xf << endl;
			  cout << "zf " << zf << endl;
			 }
		}
	  break;
	}
	default: event->ignore(); break;
  }
  update();
}

void MyGLWidget::mousePressEvent (QMouseEvent *e)
{
  xClick = e->x();
  yClick = e->y();

  if (e->button() & Qt::LeftButton &&
	  ! (e->modifiers() & (Qt::ShiftModifier|Qt::AltModifier|Qt::ControlModifier)))
  {
	DoingInteractive = ROTATE;
  }
}

void MyGLWidget::mouseReleaseEvent( QMouseEvent *)
{
  DoingInteractive = NONE;
}

void MyGLWidget::mouseMoveEvent(QMouseEvent *e)
{
  makeCurrent();
  // Aqui cal que es calculi i s'apliqui la rotacio o el zoom com s'escaigui...
  if (DoingInteractive == ROTATE)
  {
	// Fem la rotació
	angleY += (e->x() - xClick) * M_PI / 180.0;
	viewTransform ();
  }

  xClick = e->x();
  yClick = e->y();

  update ();
}


