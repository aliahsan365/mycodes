// GLarena, a plugin based platform to teach OpenGL programming
// © Copyright 2012-2018, ViRVIG Research Group, UPC, https://www.virvig.eu
// 
// This file is part of GLarena
//
// GLarena is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#include "splatting.h"
#include <QFileDialog>
 
void Splatting::onPluginLoad()
{
    GLWidget &g = *glwidget();
    g.makeCurrent();
    QGLShader fs(QGLShader::Fragment,this);
    QGLShader vs(QGLShader::Vertex,this);
	vs.compileSourceFile("./shaders/splatting.vert");
	fs.compileSourceFile("./shaders/splatting.frag");
    //program
    program = new QGLShaderProgram(this);
  	program->addShader(&fs);
  	program->addShader(&vs);
  	program->link();



	// Load Texture 1
	QString filename = QFileDialog::getOpenFileName(0, "Open Image noise", "/assig/grau-g/Textures", "Image file (*.png *.jpg)");	
	QImage img0(filename);	
	QImage im0 = img0.convertToFormat(QImage::Format_ARGB32).rgbSwapped().mirrored();
        
        g.makeCurrent();
	g.glActiveTexture(GL_TEXTURE0);//actica la textura 0 (opengl permite varias 0123...)
	g.glGenTextures( 1, &textureId0); //generar textura con un id
	g.glBindTexture(GL_TEXTURE_2D, textureId0); // activar la textura
	
	//objetivo 
	// nivel 0
	// formato : rgba
	// ancho imagen
	//altura imagen
	// borde 0
	// tipo de dato byte
	// tipo de dato type : bits
	g.glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, im0.width(), im0.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, im0.bits()); 
	g.glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	g.glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	g.glBindTexture(GL_TEXTURE_2D, 0);

	// Load Texture 2
	QString filename2 = QFileDialog::getOpenFileName(0, "Open Image rock", "/assig/grau-g/Textures", "Image file (*.png *.jpg)");	
	QImage img1(filename2);	
	QImage im1 = img1.convertToFormat(QImage::Format_ARGB32).rgbSwapped().mirrored();
        g.makeCurrent();
	g.glActiveTexture(GL_TEXTURE1);
	g.glGenTextures( 1, &textureId1);
	g.glBindTexture(GL_TEXTURE_2D, textureId1);
	g.glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, im1.width(), im1.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, im1.bits());
	g.glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	g.glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	g.glBindTexture(GL_TEXTURE_2D, 0);


	// Load Texture 3
	QString filename3 = QFileDialog::getOpenFileName(0, "Open Image grass", "/assig/grau-g/Textures", "Image file (*.png *.jpg)");	
	QImage img2(filename3);	
	QImage im2 = img2.convertToFormat(QImage::Format_ARGB32).rgbSwapped().mirrored();
        g.makeCurrent();
	g.glActiveTexture(GL_TEXTURE2);
	g.glGenTextures( 1, &textureId2);
	g.glBindTexture(GL_TEXTURE_2D, textureId2);
	g.glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, im2.width(), im2.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, im2.bits());
	g.glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	g.glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	g.glBindTexture(GL_TEXTURE_2D, 0);



}

void Splatting::preFrame() 
{
    GLWidget &g = *glwidget();
    //importante siempre el makecurrent antes de cada acion
    g.makeCurrent();
  
    // bind shader and define uniforms
    // pasando datos
    program->bind();
    program->setUniformValue("noise0", 0);  // texture unit del primer sampler 
    program->setUniformValue("rock1", 1);  // texture unit del segon  sampler 
    program->setUniformValue("grass2", 2);  // texture unit del segon  sampler 

    program->setUniformValue("modelViewProjectionMatrix", g.camera()->projectionMatrix() * g.camera()->viewMatrix());
    //activando textura por cada frame
    // bind textures
    g.glActiveTexture(GL_TEXTURE0);
    g.glBindTexture(GL_TEXTURE_2D, textureId0);
    g.glActiveTexture(GL_TEXTURE1);
    g.glBindTexture(GL_TEXTURE_2D, textureId1);
    g.glActiveTexture(GL_TEXTURE2);
    g.glBindTexture(GL_TEXTURE_2D, textureId2);
}

void Splatting::postFrame() 
{
    GLWidget &g = *glwidget();
    g.makeCurrent();

    // bind default shaders
    g.defaultProgram()->bind();
    // unbind textures
    
    // desactivando textura por cada frame
    g.glActiveTexture(GL_TEXTURE0);
    g.glBindTexture(GL_TEXTURE_2D, 0);
    g.glActiveTexture(GL_TEXTURE1);
    g.glBindTexture(GL_TEXTURE_2D, 0);
    g.glActiveTexture(GL_TEXTURE2);
    g.glBindTexture(GL_TEXTURE_2D, 0);


}





