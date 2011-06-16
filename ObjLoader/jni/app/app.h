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

#ifndef APP_H
#define APP_H

#include <jni.h>




void renderFrame();
void onSurfaceCreated();
void onResize(int width, int height);


extern "C" {
    JNIEXPORT void JNICALL Java_com_objLoader_AppLib_renderFrame(JNIEnv * env, jobject obj);
    JNIEXPORT void JNICALL Java_com_objLoader_AppLib_onSurfaceCreated(JNIEnv * env, jclass cls, jstring appPath);
    JNIEXPORT void JNICALL Java_com_objLoader_AppLib_resize(JNIEnv * env, jobject obj, jint width, jint height);
};



#endif // APP_H
