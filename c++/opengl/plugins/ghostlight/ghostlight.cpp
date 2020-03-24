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

#include "ghostlight.h"
#include "glwidget.h"


void Ghostlight::onPluginLoad()
{
    
    vs = new QOpenGLShader(QOpenGLShader::Vertex, this);
    vs->compileSourceFile("ghostlight.vert");
    cout << "VS log:" << vs->log().toStdString() << endl;
 	
 	fs = new QOpenGLShader(QOpenGLShader::Fragment, this);
    fs->compileSourceFile("ghostlight.frag");
    cout << "FS log:" << fs->log().toStdString() << endl;

    program = new QOpenGLShaderProgram(this);
    program->addShader(vs);
    program->addShader(fs);
    program->link();
    cout << "Link log:" << program->log().toStdString() << endl;
    //sendVFinfo();



}

void Ghostlight::mouseMoveEvent(QMouseEvent *e)
{ 
    
    //this->makeCurrent();
    posx = e->x();
    posy = e->y();
    cout << posx << endl;
    cout << posy << endl;
    sendVFinfo();
    //preFrame();

    //GLWidget->updateGL();
}


void Ghostlight::sendVFinfo() {
    // bind shader and define uniforms
    program->bind();
    program->setUniformValue("n", 6);
    QMatrix4x4 MVP = camera()->projectionMatrix() * camera()->viewMatrix();
    program->setUniformValue("modelViewProjectionMatrix", MVP); 
    program->setUniformValue("mouseX",posx);
    program->setUniformValue("mouseY",posy);

}

void Ghostlight::preFrame() 
{
    glDisable(GL_DEPTH_TEST);
    glBlendEquation(GL_FUNC_ADD);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);


    
}

void Ghostlight::postFrame() 
{
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_BLEND);
}








