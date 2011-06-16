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


#define _USE_MATH_DEFINES

#include <math.h>
#include <jni.h>
#include <GLES/gl.h>
#include <app.h>
#include <libpng/png.h>
#include <libzip/zip.h>
#include <libobj/MeshUtil.h>


Mesh* mesh;

float rot = 0.0;

float lightSpec[]= {1.0f, 1.0f, 1.0f, 1.0f };
float lightAmb[]= { 0.6f, 0.6f, 0.6f, 1.0f };
float lightDif[]= {10.0f, 10.0f, 10.0f, 1.0f };
float lightPos[]= { 0.0f, 10.0f, 0.0f, 0.0f };


void gluPerspective(GLfloat fovy, GLfloat aspect, GLfloat zNear, GLfloat zFar)
{
    GLfloat xmin, xmax, ymin, ymax;

    ymax = zNear * (GLfloat)tan(fovy * M_PI / 360.0f);
    ymin = -ymax;
    xmin = ymin * aspect;
    xmax = ymax * aspect;

    glFrustumx((GLfixed)(xmin * 65536), (GLfixed)(xmax * 65536),
               (GLfixed)(ymin * 65536), (GLfixed)(ymax * 65536),
               (GLfixed)(zNear * 65536), (GLfixed)(zFar * 65536));

}


void onResize(int w, int h)
{

    glViewport(0, 0, w, h);
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glShadeModel(GL_SMOOTH);

    glLoadIdentity();
    //glFrustumf(-1.0f,1.0f,-1.0f,1.0f,1.5f,20.0f);
    gluPerspective(45.0f, (float)w / h, 1.0f, 100.0f);

    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();



}

void onSurfaceCreated(const char* pathStr)
{

    zip* APKArchive = zip_open(pathStr, 0, NULL);

    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();

    glFrustumf(-1.0f,1.0f,-1.0f,1.0f,1.5f,20.0f);

    mesh = MeshUtil::loadMesh(APKArchive,"assets/table.obj", "assets/table.png");

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    zip_close(APKArchive);

    glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpec);
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmb);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDif);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);


}

void renderFrame()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_TEXTURE_2D);

    glLoadIdentity();

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glPushMatrix();

        glTranslatef(0.0f,0.0f,-30.0f);
        glRotatef(20.0f,1.0f,0.0f,0.0f);
        glRotatef(rot,0.0f,1.0f,0.0f);

        glScalef(2.0f,2.0f,2.0f);

        rot += 0.5f;

       //glBindTexture(GL_TEXTURE_2D, texture);
       mesh->render();

    glPopMatrix();
}



JNIEXPORT void JNICALL Java_com_objLoader_AppLib_resize(JNIEnv * env, jobject obj, jint width, jint height)
{
    onResize(width,height);
}

JNIEXPORT void JNICALL Java_com_objLoader_AppLib_renderFrame(JNIEnv * env, jobject obj)
{
    renderFrame();
}

JNIEXPORT void JNICALL Java_com_objLoader_AppLib_onSurfaceCreated(JNIEnv * env, jclass cls, jstring appPath)
{
    const char* pathStr;
    jboolean copyFlag;

    pathStr = env->GetStringUTFChars(appPath,&copyFlag);

    onSurfaceCreated(pathStr);
}
