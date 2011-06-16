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

#include "MeshUtil.h"
#include <libpng/png.h>
#include <stdio.h>
#include <GLES/gl.h>
#include <android/log.h>
#include <stdlib.h>
#include "zip_fgets.h"
#include "array_list.h"


#define  LOG_TAG    "MeshUtils.cpp"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define TEXTURE_LOAD_ERROR 0

zip_file* MeshUtil::file = NULL;


//! Funktion that loads a Wavefrontfile in a Meshobject
Mesh* MeshUtil::loadMesh(zip *archive, const char *meshName, const char *textureName)
{

        zip_file* zipFile = zip_fopen(archive, meshName,0);

        char* type;
        char* num;

        char buf[128];
        GLuint texture = 0;

        int vertices = 0;
        int normals = 0;
        int uv = 0;
        int faces = 0;

        array_list<float> facesVertList;
        array_list<float> facesNormList;
        array_list<float> facesUVList;

        array_list<float> vertexList;
        array_list<float> uvList;
        array_list<float> normalsList;


        while (zip_fgets( buf, 128 * sizeof (char), zipFile) != 0)
        {

            type = strtok(buf," ");

            if(strcmp(VERTEX_TYPE, type) == 0)
            {
                    num = strtok(NULL," ");
                    vertexList.push_back(atof(num));

                    num = strtok(NULL," ");
                    vertexList.push_back(atof(num));

                    num = strtok(NULL," ");
                    vertexList.push_back(atof(num));

                    vertices++;

            }else if(strcmp(NORMAL_TYPE, type) == 0){

                    num = strtok(NULL," ");
                    normalsList.push_back(atof(num));

                    num = strtok(NULL," ");
                    normalsList.push_back(atof(num));

                    num = strtok(NULL," ");
                    normalsList.push_back(atof(num));

                    normals++;

            }else if(strcmp(TEXTURE_TYPE, type) == 0){

                    num = strtok(NULL," ");
                    uvList.push_back(atof(num));

                    num = strtok(NULL," ");
                    uvList.push_back(atof(num));

                    uv++;

            }else if(strcmp(FACE_TYPE, type) == 0){


                char* chunk1 = strtok(NULL, " ");
                char* chunk2 = strtok(NULL, " ");
                char* chunk3 = strtok(NULL, " ");


                num = strtok(chunk1, "/");
                facesVertList.push_back((atoi(num) - 1));
                num = strtok(NULL, "/");
                facesUVList.push_back((atoi(num) -1));
                num = strtok(NULL, "/");
                facesNormList.push_back((atoi(num) -1));

                num = strtok(chunk2, "/");
                facesVertList.push_back((atoi(num) - 1));
                num = strtok(NULL, "/");
                facesUVList.push_back((atoi(num) -1));
                num = strtok(NULL, "/");
                facesNormList.push_back((atoi(num) -1));

                num = strtok(chunk3, "/");
                facesVertList.push_back((atoi(num) - 1));
                num = strtok(NULL, "/");
                facesUVList.push_back((atoi(num) -1));
                num = strtok(NULL, "/");
                facesNormList.push_back((atoi(num) -1));

                faces++;

            }

        }


        float* vertexBuffer  = new float[faces * 3 * 3];
        float* textureBuffer = new float[faces * 3 * 2];
        float* normalBuffer  = new float[faces * 3 * 3];

        for(int i = 0, offset = 0, idx = 0; i < faces * 3 ; i++)
        {
               offset = i * 3;
               idx = facesNormList.at(i) * 3;
               normalBuffer[offset]     = normalsList.at(idx);
               normalBuffer[offset + 1] = normalsList.at(idx + 1);
               normalBuffer[offset + 2] = normalsList.at(idx + 2);

               idx = facesVertList.at(i) * 3;
               vertexBuffer[offset]     = vertexList.at(idx);
               vertexBuffer[offset + 1] = vertexList.at(idx + 1);
               vertexBuffer[offset + 2] = vertexList.at(idx + 2);

               offset =  i * 2;
               idx = facesUVList.at(i) * 2;
               textureBuffer[offset]     = uvList.at(idx);
               textureBuffer[offset + 1] = uvList.at(idx + 1);

        }


        zip_fclose(zipFile);

        //load the corresponding texture
        texture = loadTexture(archive,textureName);



        return new Mesh(texture, faces * 3 , vertexBuffer, textureBuffer, normalBuffer);
}


void MeshUtil::png_zip_read(png_structp png_ptr, png_bytep data, png_size_t length)
{
  zip_fread(MeshUtil::file, data, length);
}

//  Taken from http://en.wikibooks.org/wiki/OpenGL_Programming/Intermediate/Textures
//  modified the ported version from http://www.anddev.org/resources/source/1912
//  to load rgb & rgba images and added mimpamps
/** loadTexture
 *   loads a png file into an opengl texture object, using cstdio , libpng, and opengl.
 *
 *   \param filename : the png file to be loaded
 *
 */
GLuint MeshUtil::loadTexture(zip* apk,const char* filename)
{


  file = zip_fopen(apk, filename, 0);

  if (!file) {
    LOGI("Error opening %s from APK", filename);
    return TEXTURE_LOAD_ERROR;
  }

  //header for testing if it is a png
  png_byte header[8];

  //read the header
  zip_fread(file, header, 8);

  //test if png
  int is_png = !png_sig_cmp(header, 0, 8);
  if (!is_png) {
    zip_fclose(file);
    LOGI("Not a png file : %s", filename);
    return TEXTURE_LOAD_ERROR;
  }

  //create png struct
  png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL,
      NULL, NULL);
  if (!png_ptr) {
    zip_fclose(file);
    LOGI("Unable to create png struct : %s", filename);
    return (TEXTURE_LOAD_ERROR);
  }

  //create png info struct
  png_infop info_ptr = png_create_info_struct(png_ptr);
  if (!info_ptr) {
    png_destroy_read_struct(&png_ptr, (png_infopp) NULL, (png_infopp) NULL);
    LOGI("Unable to create png info : %s", filename);
    zip_fclose(file);
    return (TEXTURE_LOAD_ERROR);
  }

  //create png info struct
  png_infop end_info = png_create_info_struct(png_ptr);
  if (!end_info) {
    png_destroy_read_struct(&png_ptr, &info_ptr, (png_infopp) NULL);
    LOGI("Unable to create png end info : %s", filename);
    zip_fclose(file);
    return (TEXTURE_LOAD_ERROR);
  }

  //png error stuff, not sure libpng man suggests this.
  if (setjmp(png_jmpbuf(png_ptr))) {
    zip_fclose(file);
    LOGI("Error during setjmp : %s", filename);
    png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
    return (TEXTURE_LOAD_ERROR);
  }

  //init png reading
  //png_init_io(png_ptr, fp);
  png_set_read_fn(png_ptr, NULL, png_zip_read);

  //let libpng know you already read the first 8 bytes
  png_set_sig_bytes(png_ptr, 8);

  // read all the info up to the image data
  png_read_info(png_ptr, info_ptr);

  //variables to pass to get info
  int bit_depth, color_type;
  png_uint_32 twidth, theight;

  // get info about png
  png_get_IHDR(png_ptr, info_ptr, &twidth, &theight, &bit_depth, &color_type,
      NULL, NULL, NULL);

  GLint texFormat = 0;

  //set the right texture format
  if(color_type == PNG_COLOR_TYPE_RGBA){
      texFormat = GL_RGBA;
  }else if(color_type == PNG_COLOR_TYPE_RGB){
      texFormat = GL_RGB;
  }else{
      zip_fclose(file);
      LOGI("Texture color format is not supported");
      png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
      return TEXTURE_LOAD_ERROR;
  }

  // Update the png info struct.
  png_read_update_info(png_ptr, info_ptr);

  // Row size in bytes.
  int rowbytes = png_get_rowbytes(png_ptr, info_ptr);

  // Allocate the image_data as a big block, to be given to opengl
  png_byte *image_data = new png_byte[rowbytes * theight];
  if (!image_data) {
    //clean up memory and close stuff
    png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
    LOGI("Unable to allocate image_data while loading %s ", filename);
    zip_fclose(file);
    return TEXTURE_LOAD_ERROR;
  }

  //row_pointers is for pointing to image_data for reading the png with libpng
  png_bytep *row_pointers = new png_bytep[theight];
  if (!row_pointers) {
    //clean up memory and close stuff
    png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
    delete[] image_data;
    LOGI("Unable to allocate row_pointer while loading %s ", filename);
    zip_fclose(file);
    return TEXTURE_LOAD_ERROR;
  }
  // set the individual row_pointers to point at the correct offsets of image_data
  for (unsigned int i = 0; i < theight; ++i)
    row_pointers[theight - 1 - i] = image_data + i * rowbytes;

  //read the png into image_data through row_pointers
  png_read_image(png_ptr, row_pointers);


  //Now generate the OpenGL texture object
   GLuint texture;
   glGenTextures(1, &texture);
   glBindTexture(GL_TEXTURE_2D, texture);
   glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
   glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
   glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
   glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
   glTexParameterf(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
   glTexImage2D(GL_TEXTURE_2D, 0, texFormat, twidth, theight, 0, texFormat, GL_UNSIGNED_BYTE, image_data);

   //glMatrixMode(GL_TEXTURE );
   glLoadIdentity();

  //clean up memory and close stuff
  png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
  delete[] image_data;
  delete[] row_pointers;
  zip_fclose(file);

  return texture;
}
