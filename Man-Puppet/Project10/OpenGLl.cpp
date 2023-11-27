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
#define WINDOW_TITLE_PREFIX "Человек- марионетка"
int CurrentWidth = 600, CurrentHeight = 600, WindowHandle = 0;
int FrameCount = 0;
const int st = 9;

const int N = 11 * ((180 / st) * (360 / st));

GLuint
VertexShaderId,
FragmentShaderId,
ProgramId,
VaoId,
BufferId,
IndexBufferId[2],
IndexBufferID[2],
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
void Initialize(int, char* []);
void InitWindow(int, char* []);
void ResizeFunction(int, int);
void RenderFunction(void);
void RenderFunction(void);
void IdleFunction();
void KeyboardFunction(unsigned char, int, int);
void Cleanup(void);
void CreateVBO(void);
void DestroyVBO(void);
void CreateShaders(void);
void DestroyShaders(void);
void TimerFunction(int);

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
            WINDOW_TITLE_PREFIX, FrameCount * 4, CurrentWidth, CurrentHeight);
        glutSetWindowTitle(TempString);
        delete[] TempString;
    }
    FrameCount = 0;
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

void ResizeFunction(int Width, int Height)
{
    CurrentWidth = Width;
    CurrentHeight = Height;
    glViewport(0, 0, CurrentWidth, CurrentHeight);
}

float k1, k, fps;
float  a = 0.;
float   b = 0.;
float   s = 1.;
float   e = 0.;
float   e1 = 0.;
void KeyboardFunction(unsigned char Key, int hX, int hY)
{
    switch (Key)
    {
    case 'e':
    case 'E':
    {
        s -= 0.01;
        if (s <= 0) {
            s = 0.01;
        }
        break;
    }
    case 'a':
    case 'A':
    {
        a -= 0.01;
        break;
    }
    case 'd':
    case 'D':
    {
        a += 0.01;
        break;
    }
    case 's':
    case 'S':
    {
        b += 0.01;
        break;
    }
    case 'w':
    case 'W':
    {
        b -= 0.01;
        break;
    }
    case 'u':
    case 'U':
    {
        e += 0.01;
        break;
    }
    case 'I':
    case 'i':
    {
        e -= 0.01;
        break;
    }
    case 'O':
    case 'o':
    {
        e1 -= 0.01;
        break;
    }
    case 'P':
    case 'p':
    {
        e1 += 0.01;
        break;
    }
    default:
        break;
    }

}
float m = 0;
void RenderFunction(void) {
    fps++;
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glm::mat4 trans = glm::mat4(1.0);
    glm::mat4 trans1 = glm::mat4(1.0);
    glm::mat4 trans2 = glm::mat4(1.0);
    glm::mat4 trans3 = glm::mat4(1.0);
    glm::mat4 trans4 = glm::mat4(1.0);
    glm::mat4 trans5 = glm::mat4(1.0);
    glm::mat4 trans6 = glm::mat4(1.0);
    glm::mat4 trans7 = glm::mat4(1.0);
    glm::mat4 trans8 = glm::mat4(1.0);
    glm::mat4 trans9 = glm::mat4(1.0);

    GLuint transformLoc;
    GLuint transformLoc1;
    GLuint transformLoc2;
    GLuint transformLoc3;
    GLuint transformLoc4;
    GLuint transformLoc5, transformLoc6, transformLoc7, transformLoc8, transformLoc9;


    trans = glm::rotate(trans, a, glm::vec3(0.f, 1.f, 0.f));
    trans = glm::rotate(trans, b, glm::vec3(1.f, 0.f, 0.f));
    trans = glm::scale(trans, glm::vec3(s, s, s));
    transformLoc = glGetUniformLocation(ProgramId, "transform");
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
    

    glDrawArrays(GL_LINE_STRIP, 0, N / 11);//туловище
    glDrawArrays(GL_LINE_STRIP, N / 11, N / 11);//голова
    glDrawArrays(GL_LINE_STRIP, 2 * N / 11, N / 11);//шея
    glDrawArrays(GL_LINE_STRIP, 3 * N / 11, N / 11);//плечи
    trans = glm::rotate(trans, e, glm::vec3(0.f, 0.f, 1.f));
    transformLoc = glGetUniformLocation(ProgramId, "transform");
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
    trans = glm::rotate(trans, e1, glm::vec3(1.f, 0.f, 0.f));
    transformLoc = glGetUniformLocation(ProgramId, "transform");
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
    glDrawArrays(GL_LINE_STRIP, 4 * N / 11, N / 11);
    glDrawArrays(GL_LINE_STRIP, 4 * N / 11, N / 11);
    glDrawArrays(GL_LINE_STRIP, 5 * N / 11, N / 11);
    glDrawArrays(GL_LINE_STRIP, 6 * N / 11, N / 11);
    glDrawArrays(GL_LINE_STRIP, 7 * N / 11, N / 11);

    glDrawArrays(GL_LINE_STRIP, 8 * N / 11, N / 11);
    glDrawArrays(GL_LINE_STRIP, 9 * N / 11, N / 11);




    k += 0.0005f;
    k1 += 0.001f;

    glutSwapBuffers();
    glutPostRedisplay();
}

void Cleanup(void) {
    DestroyShaders();
    DestroyVBO();
}

void CreateVBO(void)
{

    float rx = 0.1;
    float r1 = 0.2;
    float rz = 0.3;
    Vertex Vertices[N];
    int k = 0;
    //Туловище
    for (float i = -90; i < 90; i += st) {
        for (float j = -180; j < 180; j += st) {
            float rd = i * 3.14 / 180;
            float rs = j * 3.14 / 180;
            Vertices[k] =
            {
            {float(0.1) * cos(rd) * cos(rs), r1 * cos(rd) * sin(rs) - float(0.03),float(0.1) * sin(rd) , 1.0f},
            { 0.0f, 1.0f, 1.0f, 1.0f } };
            k++;

        }
    }

    //голова
    for (float i = -90; i < 90; i += st) {
        for (float j = -180; j < 180; j += st) {
            float rd = i * 3.14 / 180;
            float rs = j * 3.14 / 180;
            Vertices[k] =
            {
            {rx * cos(rd) * cos(rs), rx * cos(rd) * sin(rs) + float(0.3) ,rx * sin(rd) , 1.0f},
            { 0.0f, 1.0f, 1.0f, 1.0f } };
            k++;

        }
    }
    //шея
    for (float i = -90; i < 90; i += st) {
        for (float j = -180; j < 180; j += st) {
            float rd = i * 3.14 / 180;
            float rs = j * 3.14 / 180;
            Vertices[k] =
            {
            {float(0.03) * cos(rd) * cos(rs),float(0.05) * cos(rd) * sin(rs) + float(0.2),float(0.03) * sin(rd) , 1.0f},
            { 0.0f, 1.0f, 1.0f, 1.0f } };
            k++;

        }
    }
    //плечи
    for (float i = -90; i < 90; i += st) {
        for (float j = -180; j < 180; j += st) {
            float rd = i * 3.14 / 180;
            float rs = j * 3.14 / 180;
            Vertices[k] =
            {
            {float(0.05) * cos(rd) * cos(rs), float(0.06) * cos(rd) * sin(rs) + float(0.09) ,float(0.2) * sin(rd)  , 1.0f},
            { 0.0f, 1.0f, 1.0f, 1.0f } };
            k++;

        }
    }
    //рукi
     //правая
    for (float i = -90; i < 90; i += st) {
        for (float j = -180; j < 180; j += st) {
            float rd = i * 3.14 / 180;
            float rs = j * 3.14 / 180;
            Vertices[k] =
            {
            {float(0.05) * cos(rd) * cos(rs) , float(0.15) * cos(rd) * sin(rs) + float(0.002) ,float(0.04) * sin(rd) - float(0.16) , 1.0f},
            { 0.0f, 1.0f, 1.0f, 1.0f } };
            k++;

        }
    }
    //левая
    for (float i = -90; i < 90; i += st) {
        for (float j = -180; j < 180; j += st) {
            float rd = i * 3.14 / 180;
            float rs = j * 3.14 / 180;
            Vertices[k] =
            {
            {float(0.05) * cos(rd) * cos(rs) , float(0.15) * cos(rd) * sin(rs) - float(0.002) ,float(0.04) * sin(rd) + float(0.16) , 1.0f},
            { 0.0f, 1.0f, 1.0f, 1.0f } };
            k++;

        }
    }


    //бедро правое
    for (float i = -90; i < 90; i += st) {
        for (float j = -180; j < 180; j += st) {
            float rd = i * 3.14 / 180;
            float rs = j * 3.14 / 180;
            Vertices[k] =
            {
            {float(0.05) * cos(rd) * cos(rs) , float(0.15) * cos(rd) * sin(rs) - float(0.3) ,float(0.04) * sin(rd) - float(0.06) , 1.0f},
            { 0.0f, 1.0f, 1.0f, 1.0f } };
            k++;

        }
    }
    //верхняя часть левой ногт
    for (float i = -90; i < 90; i += st) {
        for (float j = -180; j < 180; j += st) {
            float rd = i * 3.14 / 180;
            float rs = j * 3.14 / 180;
            Vertices[k] =
            {
            {float(0.05) * cos(rd) * cos(rs) , float(0.15) * cos(rd) * sin(rs) - float(0.3) ,float(0.04) * sin(rd) + float(0.06) , 1.0f},
            { 0.0f, 1.0f, 1.0f, 1.0f } };
            k++;

        }
    }
    //нижняя часть левой ноги
    for (float i = -90; i < 90; i += st) {
        for (float j = -180; j < 180; j += st) {
            float rd = i * 3.14 / 180;
            float rs = j * 3.14 / 180;
            Vertices[k] =
            {
            {float(0.05) * cos(rd) * cos(rs) , float(0.15) * cos(rd) * sin(rs) - float(0.5) ,float(0.04) * sin(rd) + float(0.06) , 1.0f},
            { 0.0f, 1.0f, 1.0f, 1.0f } };
            k++;

        }
    }
    //нижняя часть правой ноги
    for (float i = -90; i < 90; i += st) {
        for (float j = -180; j < 180; j += st) {
            float rd = i * 3.14 / 180;
            float rs = j * 3.14 / 180;
            Vertices[k] =
            {
            {float(0.05) * cos(rd) * cos(rs) , float(0.15) * cos(rd) * sin(rs) - float(0.5) ,float(0.04) * sin(rd) - float(0.06) , 1.0f},
            { 0.0f, 1.0f, 1.0f, 1.0f } };
            k++;

        }
    }


    GLenum ErrorCheckValue = glGetError();
    const size_t BufferSize = sizeof(Vertices);
    const size_t VertexSize = sizeof(Vertices[0]);
    const size_t RgbOffset = sizeof(Vertices[0].XYZW);

    glGenBuffers(1, &VboId);
    glGenBuffers(2, IndexBufferId);
    glGenBuffers(3, IndexBufferID);
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
    glDeleteBuffers(2, IndexBufferID);

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