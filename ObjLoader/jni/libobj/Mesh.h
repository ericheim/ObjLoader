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

#ifndef MESH_H
#define MESH_H

#include <GLES/gl.h>

class Mesh
{

private:

    int numberOfvertices;
    float* vBuffer;
    float* tBuffer;
    float* nBuffer;

    GLuint texture;

public:

    Mesh(GLuint _texture, int n, float* vertexBuffer, float* textureCoordBuffer, float* normalBuffer);
    virtual ~Mesh();

    void render(void) const;
};

#endif // MESH_H
