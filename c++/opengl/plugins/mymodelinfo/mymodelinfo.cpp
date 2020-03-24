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

#include "Mymodelinfo.h"

void Mymodelinfo::showinfo()
{

  
  /*
  
  unsigned int nobj = scene()->objects().size();
  cout << "Numero de objetos: " << nobj << endl;
    int nobj, npol, nver, ntri;
  for (unsigned int i = 0; i < nobj; ++i) {
        cout << "info del objeto numero: " << i << endl;
        const Object& obj = scene()->objects()[i];
        unsigned int nvert =  obj.faces().size()*3;
        cout <<  "numero de vertices del objeto " << i << " es " << nvert << endl;
  
  }
  */
  
  Scene* scn=scene();
  int nobj, npol, nver, ntri;
  nobj=scn->objects().size();
  npol=nver=ntri=0;
  for (int i=0; i<(int)scn->objects().size(); ++i) {
    const Object &obj=scn->objects()[i];
    for (int j=0; j<(int)obj.faces().size(); ++j) {
      const Face &face=obj.faces()[j];
      int fver=face.numVertices();
      ++npol;
      nver+=fver;
      ntri+=fver==3;
    }
  }
  double percent = (ntri / npol)*100;
  cout << "Numero objectes: " << nobj << endl;
  cout << "Numero poligons: " << npol << endl;
  cout << "Numero vertex: " << nver << endl;
  cout << "Percentatge triangles: " << percent << endl; 
  
    
    
}


void Mymodelinfo::onPluginLoad()
{

    
    
    
    
}

void Mymodelinfo::preFrame() 
{


}

void Mymodelinfo::postFrame() 
{
    showinfo();
}




