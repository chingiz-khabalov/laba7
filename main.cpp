#include <windows.h>
#include <gl/gl.h>
#include <math.h>
#include "camera.h"

float vert[] = {1,1,0,1,-1,0,-1,-1,0,-1,1,0};
LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);
void EnableOpenGL(HWND hwnd, HDC*, HGLRC*);
void DisableOpenGL(HWND, HDC, HGLRC);
void showAxis(int size){
        size++;
    glColor3f(1.0, 0.0, 0.0);
    glLineWidth(2);
    glBegin(GL_LINES);
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(size*4, 0.0, 0.0);
    glEnd();
    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_LINES);
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(0.0, size*4, 0.0);
    glEnd();
    glColor3f(1.0, 1.0, 0.0);
    glBegin(GL_LINES);
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(0.0, 0.0, size*4);
    glEnd();

}
void Init_Light(GLfloat theta)
{
glEnable(GL_LIGHTING);
glShadeModel(GL_SMOOTH);
GLfloat light_position[] = { 0.0f, 0.0f, 15.0f, 1.0f };
GLfloat light_spot_direction[] = {0.0, 0.0, -1.0, 1.0};
GLfloat light_ambient[] = { 0.1f, 0.1f, 0.1f, 1.0f };
GLfloat light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat light_specular[] = { 0.2f, 0.2f, 0.2f, 32.0f };
glPushMatrix();
        glRotatef(theta,0,1,0);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glTranslatef(0,0,15);
    glColor3f(1,1,1);
    glEnable(GL_VERTEX_ARRAY);
        glVertexPointer(3,GL_FLOAT,0,&vert);
        glDrawArrays(GL_TRIANGLE_FAN,0,4);
    glDisable(GL_VERTEX_ARRAY);
glPopMatrix();

glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 55);
glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, light_spot_direction);
glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 8.0);
glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
glEnable(GL_LIGHT0);
}
void Init_Material()
{
    glEnable(GL_BLEND);
glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
glEnable(GL_COLOR_MATERIAL);
glShadeModel(GL_SMOOTH);
GLfloat material_ambient[] = { 0.2f, 0.2f, 0.2f, 0.0f };
GLfloat material_diffuse[] = { 1.0f, 1.0f, 1.0f, 0.0f };
GLfloat material_specular[] = { 1.0f, 1.0f, 1.0f, 32.0f };
GLfloat material_shininess[] = { 50.0f };
glMaterialfv(GL_FRONT, GL_AMBIENT, material_ambient);
glMaterialfv(GL_FRONT, GL_DIFFUSE, material_diffuse);
glMaterialfv(GL_FRONT, GL_SPECULAR, material_specular);
glMaterialfv(GL_FRONT, GL_SHININESS, material_shininess);

}

void drawDoubleTruncatedCone(float topRadius, float bottomRadius, float height, int numSides) {

glBegin(GL_QUAD_STRIP);
glEnableClientState(GL_NORMAL_ARRAY);
for (int i = 0; i <= numSides; i++) {
float angle = 2.0f * M_PI * i / numSides;
float xTopInner = topRadius * cos(angle);
float zTopInner = topRadius * sin(angle);
float xBottomInner = bottomRadius * cos(angle);
float zBottomInner = bottomRadius * sin(angle);
glNormal3f(xTopInner, height, zTopInner);
glVertex3f(xTopInner, height, zTopInner);
glNormal3f(xBottomInner, 0.0f, zBottomInner);
glVertex3f(xBottomInner, 0.0f, zBottomInner);
}
glEnd();
}

void drawHyperboloid() {
float topRadius1 = 0.5f;
    float bottomRadius1 = 0.25f;
    float height1 = 1.0f;

    float topRadius2 = 0.5f;
    float bottomRadius2 = 0.25f;
    float height2 = 1.0f;

    int numSides = 30;
    glRotatef(90,1,0,0);
    glPushMatrix();
    glTranslatef(-2.0f, 0.0f, 0.0f);
    drawDoubleTruncatedCone(topRadius1, bottomRadius1, height1, 8);
    glRotatef(180,1,0,0);
    glTranslatef(0.0f, 0.0f, 0.0f);
    drawDoubleTruncatedCone(topRadius2, bottomRadius2, height2, 8);
    glPopMatrix();
}
 void drawHyperboloids(){
      for (int i = 0; i < 10; i++) {
            glPushMatrix();
            glColor4f(0.0f, 0.0f, 1.0f, 1.0f);
            glRotatef(90+i*10,0,0,1);
            glTranslatef(4,i,1);
            drawHyperboloid();
            glPopMatrix();
        }
 }

void Draw_Cube(){
glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
GLfloat vertices[] = {
-0.5f, -0.5f, -0.5f,
0.5f, -0.5f, -0.5f,
0.5f, 0.5f, -0.5f,
-0.5f, 0.5f, -0.5f,
-0.5f, -0.5f, 0.5f,
0.5f, -0.5f, 0.5f,
0.5f, 0.5f, 0.5f,
-0.5f, 0.5f, 0.5f
};
GLuint indices[] = {
0, 1, 2,
2, 3, 0,
1, 5, 6,
6, 2, 1,
7, 6, 5,
5, 4, 7,
4, 0, 3,
3, 7, 4,
4, 5, 1,
1, 0, 4,
3, 2, 6,
6, 7, 3
};
GLfloat normals[] = {
0.0f, 0.0f, -1.0f,
0.0f, 0.0f, -1.0f,
0.0f, 0.0f, -1.0f,
0.0f, 0.0f, -1.0f,
0.0f, 0.0f, 1.0f,
0.0f, 0.0f, 1.0f,
0.0f, 0.0f, 1.0f,
0.0f, 0.0f, 1.0f,
-1.0f, 0.0f, 0.0f,
-1.0f, 0.0f, 0.0f,
-1.0f, 0.0f, 0.0f,
-1.0f, 0.0f, 0.0f,
1.0f, 0.0f, 0.0f,
1.0f, 0.0f, 0.0f,
1.0f, 0.0f, 0.0f,
1.0f, 0.0f, 0.0f,
0.0f, -1.0f, 0.0f,
0.0f, -1.0f, 0.0f,
0.0f, -1.0f, 0.0f,
0.0f, -1.0f, 0.0f,
0.0f, 1.0f, 0.0f,
0.0f, 1.0f, 0.0f,
0.0f, 1.0f, 0.0f,
0.0f, 1.0f, 0.0f
};
glEnableClientState(GL_VERTEX_ARRAY);
glVertexPointer(3, GL_FLOAT, 0, vertices);
glEnableClientState(GL_NORMAL_ARRAY);
glNormalPointer(GL_FLOAT, 0, normals);
glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, indices);
glDisableClientState(GL_VERTEX_ARRAY);
glDisableClientState(GL_NORMAL_ARRAY);
}
float normal_vert[]={0,0,1, 0,0,1, 0,0,1, 0,0,1};

void showWorld(int squares){
    glEnable(GL_DEPTH_TEST);
    showAxis(squares);

        glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(3,GL_FLOAT,0,&vert);
        glEnableClientState(GL_NORMAL_ARRAY);
   glNormalPointer(GL_FLOAT,0,&normal_vert);
        for(int i = -squares; i < squares; i++)
            for(int j = -squares; j < squares; j++){
                glPushMatrix();
                    if((i+j) % 2 == 0 )
                        glColor3f(0,0,0);
                    else
                        glColor3f(1,1,1);
                    glTranslatef(i*2,j*2,0);
                    glDrawArrays(GL_TRIANGLE_FAN,0,4);
                glPopMatrix();
        }
   glDisable(GL_NORMAL_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
    glPushMatrix();
    drawHyperboloids();
    glTranslatef(2,2,1);
    Draw_Cube();
    glTranslatef(5,-2,4);
    Draw_Cube();
      glPopMatrix();
}

int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine,
                   int nCmdShow)
{
    WNDCLASSEX wcex;
    HWND hwnd;
    HDC hDC;
    HGLRC hRC;
    MSG msg;
    BOOL bQuit = FALSE;
    float theta = 0.0f;

    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_OWNDC;
    wcex.lpfnWndProc = WindowProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = "GLSample";
    wcex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);;


    if (!RegisterClassEx(&wcex))
        return 0;
    hwnd = CreateWindowEx(0,
                          "GLSample",
                          "OpenGL Sample",
                          WS_OVERLAPPEDWINDOW,
                          CW_USEDEFAULT,
                          CW_USEDEFAULT,
                          GetSystemMetrics(SM_CXSCREEN),
                          GetSystemMetrics(SM_CYSCREEN),
                          NULL,
                          NULL,
                          hInstance,
                          NULL);

    ShowWindow(hwnd, nCmdShow);

    EnableOpenGL(hwnd, &hDC, &hRC);
    glFrustum(-1,1,-1,1,2,100);
    GLfloat xAngleSpeed = 20;
    GLfloat zAngleSpeed = 20;
    POINTFLOAT playerPos = {0,0};
    POINT curPos;
    POINT centerPos={250,250};
    ShowCursor(false);

    GLfloat dir=0.5f;
    while (!bQuit)
    {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
            {
                bQuit = TRUE;
            }
            else
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
        else
        {
            glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glPushMatrix();
             GetCursorPos(&curPos);
             moveCamera(xAngleSpeed, zAngleSpeed, playerPos, curPos);
            Init_Light(theta);
            Init_Material();
             showWorld(5);


            glPopMatrix();
            SwapBuffers(hDC);
            if(theta>90)
                dir=-0.25f;
            if(theta<=-90)
                dir=0.25f;
            theta+=dir;


            Sleep (1);
        }
    }

    DisableOpenGL(hwnd, hDC, hRC);

    DestroyWindow(hwnd);

    return msg.wParam;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
        case WM_CLOSE:
            PostQuitMessage(0);
        break;

        case WM_DESTROY:
            return 0;

        case WM_KEYDOWN:
        {
            switch (wParam)
            {
                case VK_ESCAPE:
                    PostQuitMessage(0);
                break;
            }
        }
        break;

        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }

    return 0;
}

void EnableOpenGL(HWND hwnd, HDC* hDC, HGLRC* hRC)
{
    PIXELFORMATDESCRIPTOR pfd;

    int iFormat;

    *hDC = GetDC(hwnd);

    ZeroMemory(&pfd, sizeof(pfd));

    pfd.nSize = sizeof(pfd);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW |
                  PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 24;
    pfd.cDepthBits = 16;
    pfd.iLayerType = PFD_MAIN_PLANE;

    iFormat = ChoosePixelFormat(*hDC, &pfd);

    SetPixelFormat(*hDC, iFormat, &pfd);

    *hRC = wglCreateContext(*hDC);

    wglMakeCurrent(*hDC, *hRC);
}

void DisableOpenGL (HWND hwnd, HDC hDC, HGLRC hRC)
{
    wglMakeCurrent(NULL, NULL);
    wglDeleteContext(hRC);
    ReleaseDC(hwnd, hDC);
}

