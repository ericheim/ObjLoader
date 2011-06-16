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

#ifndef MESHUTIL_H
#define MESHUTIL_H

#include <GLES/gl.h>
#include <libpng/png.h>
#include <libzip/zip.h>
#include  "Mesh.h"


#define VERTEX_TYPE     "v"
#define TEXTURE_TYPE    "vt"
#define NORMAL_TYPE     "vn"
#define FACE_TYPE       "f"


class MeshUtil
{

private:

    static zip_file* file;

    MeshUtil();

public:


    static GLuint loadTexture(zip* apk, const char* filename);
    static void png_zip_read(png_structp png_ptr, png_bytep data, png_size_t length);
    static Mesh* loadMesh(zip* apk, const char* meshName, const char* textureName);

};

#endif // MESHUTIL_H
