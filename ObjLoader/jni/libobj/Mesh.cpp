/*
 *
 *      Copyright Jun 18:04:36 CEST 2011 Eric Heim
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#include "Mesh.h"

#include <GLES/gl.h>

Mesh::Mesh(GLuint _texture ,int n,float* vertexBuffer, float* textureCoordBuffer, float* normalBuffer)
{

    this->vBuffer = vertexBuffer;
    this->tBuffer = textureCoordBuffer;
    this->nBuffer = normalBuffer;
    this->numberOfvertices = n;

    this->texture = _texture;
}

Mesh::~Mesh()
{
    delete[] vBuffer;
    delete[] tBuffer;
    delete[] nBuffer;

    glDeleteTextures(1,&texture);
}

void Mesh::render(void) const
{
    glBindTexture(GL_TEXTURE_2D, this->texture);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

        glVertexPointer(3, GL_FLOAT, 0, this->vBuffer);
        glTexCoordPointer(2, GL_FLOAT, 0, this->tBuffer);
        glNormalPointer(GL_FLOAT, 0, this->nBuffer);

        glDrawArrays(GL_TRIANGLES, 0, this->numberOfvertices);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}
