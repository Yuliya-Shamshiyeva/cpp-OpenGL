#include <string>
#include <iostream>
#include <string>
#include <fstream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <string>
#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#pragma comment (lib, "glew32.lib")
#pragma comment (lib, "freeglut.lib")
using namespace std;
typedef struct
{
    float XYZW[4];
    float RGBA[4];
} Vertex;
#define WINDOW_TITLE_PREFIX "2nd OpenGL program"
int
CurrentWidth = 800,
CurrentHeight = 800,
WindowHandle = 0;
void Initialize(int, char* []);
void InitWindow(int, char* []);
void ResizeFunction(int, int);
void RenderFunction(void);
int fps = 0;

GLuint
VertexShaderId,
FragmentShaderId,
ProgramId,
VaoId,
BufferId,
IndexBufferId[2],
IndexBufferIDE[2],
VboId,
ActiveIndexBuffer = 0,
ActiveIndexBuffer2 = 0;
const GLchar* VertexShader = {
  "#version 400\n"\

  "layout(location=0) in vec4 in_Position;\n"\
  "layout(location=1) in vec4 in_Color;\n"\
  "out vec4 ex_Color;\n"\
   " uniform mat4 transform;\n"
  "void main(void)\n"\
  "{\n"\
  "  gl_Position = transform * in_Position;\n"\
  "  ex_Color = in_Color;\n"\
  "}\n"
};
const GLchar* FragmentShader = {
  "#version 400\n"\

  "in vec4 ex_Color;\n"\
  "out vec4 out_Color;\n"\

  "void main(void)\n"\
  "{\n"\
  "  out_Color = ex_Color;\n"\
  "}\n"
};


float z = 0.0f, w = 1.0f,
x = 0.3f, y = -0.5f, zoom = 0.5;


void CreateVBO(void)
{
    Vertex Vertices[] =
    {
         {{-.5f, -.5f,  .5f, 1.0f}, {0, 1, 0, 1}}, //0
         { { -.5f,  .5f,  .5f, 1.0f }, { 0, 1, 0, 1 } }, //1
         { {  .5f,  .5f,  .5f, 1.0f }, { 0, 1, 0, 1 } }, //2
         { {  .5f, -.5f,  .5f, 1.0f }, { 0, 1, 0, 1 } }, //3

         {{-.5f, -.5f, -.5f, 1}, {1, 0, 0, 1}}, //4
         { { -.5f,  .5f, -.5f, 1 }, { 0, 1, 0, 1 } }, //5
         { {  .5f,  .5f, -.5f, 1 }, { 0, 1, 0, 1 } }, //6
         { {  .5f, -.5f, -.5f, 1 }, { 0, 1, 0, 1 } }, //7

         { {  .0f,  .5f,  .0f, 1 }, { 1, 0, 0, 1 } }, //8
         { {  .5f, -.5f,  .5f, 1 }, { 1, 0, 0, 1 } }, //9
         { { -.5f, -.5f,  .5f, 1 }, { 1, 0, 0, 1 } }, //10
         { {  .0f, -.5f, -.5f, 1 }, { 1, 0, 0, 1 } }, //11

         { {  .5f, -.5f,  .5f, 1 }, { 1, 0, 0, 1 } }, //12 - 3
         { { -.5f, -.5f,  .5f, 1 }, { 1, 0, 0, 1 } }, //13 - 0
         { {  .5f, -.5f, -.5f, 1 }, { 1, 0, 0, 1 } }, //14 - 7

         { { -.5f, -.5f, -.5f, 1 }, { 0, 0, 1, 1 } }, //15 - 4
         { { -.5f,  .5f,  .5f, 1 }, { 0, 0, 1, 1 } }, //16 - 1
         { { -.5f,  .5f, -.5f, 1 }, { 0, 0, 1, 1 } }, //17 - 5
         { { -.5f, -.5f,  .5f, 1 }, { 0, 0, 1, 1 } }, //18 - 0

         { {  .5f, -.5f,  .5f, 1 }, { 1, 1, 0, 1 } }, //19 - 3
         { {  .5f,  .5f, -.5f, 1 }, { 1, 1, 0, 1 } }, //20 - 6
         { {  .5f,  .5f,  .5f, 1 }, { 1, 1, 0, 1 } }, //21 - 2
         { {  .5f, -.5f, -.5f, 1 }, { 1, 1, 0, 1 } }, //22 - 7

         { { -.5f,  .5f,  .5f, 1 }, { 0, 1, 1, 1 } }, //23 - 1
         { {  .5f,  .5f, -.5f, 1 }, { 0, 1, 1, 1 } }, //24 - 6
         { { -.5f,  .5f, -.5f, 1 }, { 0, 1, 1, 1 } }, //25 - 5
         { {  .5f,  .5f,  .5f, 1 }, { 0, 1, 1, 1 } }, //26 - 2

         { {  .5f, -.5f, -.5f, 1 }, { 1, 0, 1, 1 } }, //27 - 7
         { { -.5f,  .5f, -.5f, 1 }, { 1, 0, 1, 1 } }, //28 - 5
         { {  .5f,  .5f, -.5f, 1 }, { 1, 0, 1, 1 } }, //29 - 6
         { { -.5f, -.5f, -.5f, 1 }, { 1, 0, 1, 1 } }, ///30 - 4*/

                  { {  .0f,  .5f,  .0f, 1 }, { 1, 0, 1, 1 } }, //31
         { {  .5f, -.5f,  .5f, 1 }, { 1, 0, 1, 1 } }, //32
         { { -.5f, -.5f,  .5f, 1 }, { 1, 0, 1, 1 } }, //33
         { {  .0f, -.5f, -.5f, 1 }, { 1, 0, 1, 1 } }, //34

        { {  .0f,  .5f,  .0f, 1 }, { 1, 0, 1, 1 } }, //35
         { {  .5f, -.5f,  .5f, 1 }, { 1, 0, 1, 1 } }, //36
         { { -.5f, -.5f,  .5f, 1 }, { 1, 0, 1, 1 } }, //37
         { {  .0f, -.5f, -.5f, 1 }, { 1, 1, 1, 1 } }, //38

    };

    const GLuint Indices[] =
    {
        0,2,1,  0,3,2,
        4,12,13,  4,14,12,
        15,16,17,  15,18,16,
        19,20,21,  19,22,20,
        23,24,25,  23,26,24,
        27,28,29,  27,30,28,

        8, 9, 10,
        8, 11, 32,
        31, 37, 38,
        36, 33, 34



    };





    GLenum ErrorCheckValue = glGetError();
    const size_t BufferSize = sizeof(Vertices);
    const size_t VertexSize = sizeof(Vertices[0]);
    const size_t RgbOffset = sizeof(Vertices[0].XYZW);

    glGenBuffers(1, &VboId);
    glGenBuffers(2, IndexBufferId);
    glGenBuffers(3, IndexBufferIDE);
    glGenVertexArrays(1, &VaoId);
    glBindVertexArray(VaoId);

    glBindBuffer(GL_ARRAY_BUFFER, VboId);
    glBufferData(GL_ARRAY_BUFFER, BufferSize, Vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, VertexSize, 0);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, VertexSize, (GLvoid*)RgbOffset);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glGenBuffers(1, IndexBufferId);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexBufferId[0]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_STATIC_DRAW);





    ErrorCheckValue = glGetError();
    if (ErrorCheckValue != GL_NO_ERROR)
    {
        fprintf(
            stderr,
            "ERROR: Could not create a VBO: %s\n",
            gluErrorString(ErrorCheckValue)
        );

        exit(-1);
    }
};
void DestroyVBO(void) {
    GLenum ErrorCheckValue = glGetError();

    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDeleteBuffers(1, &VboId);

    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glDeleteBuffers(2, IndexBufferId);
    glDeleteVertexArrays(1, &VaoId);
    glDeleteBuffers(2, IndexBufferIDE);

    ErrorCheckValue = glGetError();
    if (ErrorCheckValue != GL_NO_ERROR)
    {
        fprintf(
            stderr,
            "ERROR: Could not destroy the VBO: %s \n",
            gluErrorString(ErrorCheckValue)
        );

        exit(-1);
    }
}
void CreateShaders(void) {
    GLenum ErrorCheckValue = glGetError();

    VertexShaderId = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(VertexShaderId, 1, &VertexShader, NULL);
    glCompileShader(VertexShaderId);

    FragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(FragmentShaderId, 1, &FragmentShader, NULL);
    glCompileShader(FragmentShaderId);

    ProgramId = glCreateProgram();
    glAttachShader(ProgramId, VertexShaderId);
    glAttachShader(ProgramId, FragmentShaderId);
    glLinkProgram(ProgramId);
    glUseProgram(ProgramId);

    ErrorCheckValue = glGetError();
    if (ErrorCheckValue != GL_NO_ERROR)
    {
        fprintf(
            stderr,
            "ERROR: Could not create the shaders: %s \n",
            gluErrorString(ErrorCheckValue)
        );

        exit(-1);
    }
}
void DestroyShaders(void)
{
    GLenum ErrorCheckValue = glGetError();

    glUseProgram(0);

    glDetachShader(ProgramId, VertexShaderId);
    glDetachShader(ProgramId, FragmentShaderId);

    glDeleteShader(FragmentShaderId);
    glDeleteShader(VertexShaderId);

    glDeleteProgram(ProgramId);

    ErrorCheckValue = glGetError();
    if (ErrorCheckValue != GL_NO_ERROR)
    {
        fprintf(
            stderr,
            "ERROR: Could not destroy the shaders: %s \n",
            gluErrorString(ErrorCheckValue)
        );

        exit(-1);
    }
}
void Cleanup(void) {
    DestroyShaders();
    DestroyVBO();
}
void IdleFunction()
{
    glutPostRedisplay();
}
void KeyboardFunction(unsigned char, int, int);
void TimerFunction(int Value)
{
    if (Value != 0)
    {
        char* TempString = new char[512 + strlen(WINDOW_TITLE_PREFIX)];
        sprintf(TempString, "%s: %d Frames Per Second @ %d x %d",
            WINDOW_TITLE_PREFIX, fps * 4, CurrentWidth, CurrentHeight);
        glutSetWindowTitle(TempString);
        delete[] TempString;
    }
    fps = 0;
    glutTimerFunc(250, TimerFunction, 1);
}

int main(int argc, char* argv[])
{
    Initialize(argc, argv);
    glutMainLoop();
    exit(EXIT_SUCCESS);
}
void Initialize(int argc, char* argv[])
{
    GLenum GlewInitResult;
    InitWindow(argc, argv);
    GlewInitResult = glewInit();
    if (GLEW_OK != GlewInitResult)
    {
        cerr << "ERROR " << glewGetErrorString(GlewInitResult) << endl;
        exit(EXIT_FAILURE);
    }
    cout << "INFO: OpenGL Version: " << glGetString(GL_VERSION) << endl;
    CreateShaders();
    CreateVBO();
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
}
void InitWindow(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitContextVersion(4, 0);
    glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);
    glutInitContextProfile(GLUT_CORE_PROFILE);
    glutSetOption(
        GLUT_ACTION_ON_WINDOW_CLOSE,
        GLUT_ACTION_GLUTMAINLOOP_RETURNS
    );
    glutInitWindowSize(CurrentWidth, CurrentHeight);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    WindowHandle = glutCreateWindow(WINDOW_TITLE_PREFIX);
    if (WindowHandle < 1)
    {
        cerr << "ERROR: Could not create a new rendering window.\n";
        exit(EXIT_FAILURE);
    }
    glutReshapeFunc(ResizeFunction);
    glutDisplayFunc(RenderFunction);
    glutIdleFunc(IdleFunction);
    glutTimerFunc(0, TimerFunction, 0);
    glutCloseFunc(Cleanup);
    glutKeyboardFunc(KeyboardFunction);
}
void KeyboardFunction(unsigned char Key, int X, int Y)
{
    switch (Key)
    {
    case 'T':
    case 't':
    {
        ActiveIndexBuffer = (ActiveIndexBuffer == 1 ? 0 : 1);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexBufferId[ActiveIndexBuffer]);
        break;
    }
    case 'J':
    case 'j':
    {
        ActiveIndexBuffer2 = (ActiveIndexBuffer2 == 1 ? 0 : 1);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexBufferIDE[ActiveIndexBuffer2]);
        break;
    }
    default:
        break;
    }
}
void ResizeFunction(int Width, int Height)
{
    CurrentWidth = Width;
    CurrentHeight = Height;
    glViewport(0, 0, CurrentWidth, CurrentHeight);
}

void ResizeFunction1(int Width, int Height)
{
    CurrentWidth = Width;
    CurrentHeight = Height;
    glViewport(0, 0, CurrentWidth, CurrentHeight);
}
float r = 1. / 2000, a = 0;
void RenderFunction(void) {
    fps++;
    glEnable(GL_DEPTH_TEST);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glm::mat4 trans = glm::mat4(1.0);
    GLuint transformLoc;
    a += r;
    trans = glm::translate(trans, glm::vec3(0.2f, 0.0f, 0.0f));
    trans = glm::rotate(trans, a, glm::vec3(1.0, 1.0, 1.0));
    trans = glm::scale(trans, glm::vec3(0.5f, 0.5f, 0.5f));
    transformLoc = glGetUniformLocation(ProgramId, "transform");
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (GLvoid*)(sizeof(GLuint) * 0));
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (GLvoid*)(sizeof(GLuint) * 6));
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (GLvoid*)(sizeof(GLuint) * 12));
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (GLvoid*)(sizeof(GLuint) * 18));
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (GLvoid*)(sizeof(GLuint) * 24));
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (GLvoid*)(sizeof(GLuint) * 30));

    trans = glm::translate(trans, glm::vec3(-1.5f, 0.0f, 0.0f));
    transformLoc = glGetUniformLocation(ProgramId, "transform");
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
    glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, (GLvoid*)(sizeof(GLuint) * 36));
    glutSwapBuffers();
    glutPostRedisplay();
}
