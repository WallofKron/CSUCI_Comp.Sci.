// spherical camera + persp + lighting + texture
// Display a color cube
// Colors are assigned to each vertex and then the rasterizer interpolates
//   those colors across the triangles.  We us an orthographic projection
//   as the default projetion.

#include <unistd.h>

#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <iostream>
using namespace std;

#include <GLUT/glut.h>

#include "Angel.h"
#include "simplemodels.h"

GLuint loadBMP_custom(unsigned char** data, int* w, int* h, const char * imagepath);


// Array of rotation angles (in degrees) for each coordinate axis
enum { Xaxis = 0, Yaxis = 1, Zaxis = 2, NumAxes = 3 };

int      Axis = Zaxis;

GLfloat boardX,boardY,boardZ,frontTrAxX,frontTrAxY,frontTrAxZ,frontWheelsX,frontWheelsY,frontWheelsZ,rearTrAxX,rearTrAxY,rearTrAxZ,rearWheelsX,rearWheelsY,rearWheelsZ = 0.0;

GLfloat  Theta1[NumAxes] = { 80.0, 0.0, 0.0 };
GLfloat  Theta2[NumAxes] = { 0.0, 30.0, 0.0 };
GLfloat  Theta3[NumAxes] = { 0.0, 0.0, 0.0 };
GLfloat  Theta4[NumAxes] = { 0.0, 0.0, 0.0 };

GLfloat dist = 0.0;

float environmentShifty = 0.0;
float environmentShifty2 = 0.0;


float grass1 = 10.0;
float grass2 = 40.0;


bool lightSource = false;

size_t CUBE_OFFSET;
size_t COLOR_OFFSET;
size_t CUBE_NORMALS_OFFSET;
size_t CUBE_TEXCOORDS_OFFSET;
size_t CYLINDER_OFFSET;
size_t CYLINDER_NORMALS_OFFSET;
size_t SPHERE_OFFSET;
size_t SPHERE_NORMALS_OFFSET;
size_t SPHERE_TEXCOORDS_OFFSET;
size_t TORUS_OFFSET;
size_t TORUS_NORMALS_OFFSET;
size_t TORUS_TEXCOORDS_OFFSET;
size_t TRIANGLE_OFFSET;
size_t TRIANGLE_NORMALS_OFFSET;
size_t TRIANGLE_TEXCOORDS_OFFSET;


//----------------------------------------------------------------------------

GLuint program;

GLuint vPosition;
GLuint vNormal;
GLuint vColor;
GLuint vTexCoord;

GLuint textures[16];

void init(){
    // Load shaders and use the resulting shader program
    program = InitShader( "vshader21.glsl", "fshader21.glsl" );
    glUseProgram( program );
    
    
    
    //---------------------------------------------------------------------
    colorcube();
    colortube();
    colorbube();
    colortorus();
    colorTri();
    
    
    
    //---- Initialize texture objects
    glGenTextures( 16, textures );
    glActiveTexture( GL_TEXTURE0 );
    
    
    unsigned char* pic0 = NULL;
    int w0,h0;
    loadBMP_custom(&pic0, &w0, &h0, "Cilo.bmp");
    
    glBindTexture( GL_TEXTURE_2D, textures[0] );
    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, w0, h0, 0, GL_BGR, GL_UNSIGNED_BYTE, pic0 );
    glGenerateMipmap(GL_TEXTURE_2D);
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
    
    
    
    unsigned char* pic1 = NULL;
    int w,h;
    loadBMP_custom(&pic1, &w, &h, "Grass.bmp");
    
    glBindTexture( GL_TEXTURE_2D, textures[1] );
    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_BGR, GL_UNSIGNED_BYTE, pic1 );
    glGenerateMipmap(GL_TEXTURE_2D);
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
    
    
    unsigned char* pic2 = NULL;
    int w2,h2;
    loadBMP_custom(&pic2, &w2, &h2, "griptape.bmp");
    
    glBindTexture( GL_TEXTURE_2D, textures[2] );
    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, w2, h2, 0, GL_BGR, GL_UNSIGNED_BYTE, pic2 );
    glGenerateMipmap(GL_TEXTURE_2D);
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
    
    
    unsigned char* pic3 = NULL;
    int w3,h3;
    loadBMP_custom(&pic3, &w3, &h3, "Concrete.bmp");
    
    glBindTexture( GL_TEXTURE_2D, textures[3] );
    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, w3, h3, 0, GL_BGR, GL_UNSIGNED_BYTE, pic3 );
    glGenerateMipmap(GL_TEXTURE_2D);
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
    
    
    unsigned char* pic4 = NULL;
    int w4,h4;
    loadBMP_custom(&pic4, &w4, &h4, "sideskirtgraffiti.bmp");
    
    glBindTexture( GL_TEXTURE_2D, textures[4] );
    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, w4, h4, 0, GL_BGR, GL_UNSIGNED_BYTE, pic4 );
    glGenerateMipmap(GL_TEXTURE_2D);
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
    
    
    unsigned char* pic5 = NULL;
    int w5,h5;
    loadBMP_custom(&pic5, &w5, &h5, "Metal.bmp");
    
    glBindTexture( GL_TEXTURE_2D, textures[5] );
    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, w5, h5, 0, GL_BGR, GL_UNSIGNED_BYTE, pic5 );
    glGenerateMipmap(GL_TEXTURE_2D);
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
    
    
    
    unsigned char* pic6 = NULL;
    int w6,h6;
    loadBMP_custom(&pic6, &w6, &h6, "Sky.bmp");
    
    glBindTexture( GL_TEXTURE_2D, textures[6] );
    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, w6, h6, 0, GL_BGR, GL_UNSIGNED_BYTE, pic6 );
    glGenerateMipmap(GL_TEXTURE_2D);
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
    
    
    
    
    unsigned char* pic7 = NULL;
    int w7,h7;
    loadBMP_custom(&pic7, &w7, &h7, "Fabric.bmp");
    
    glBindTexture( GL_TEXTURE_2D, textures[7] );
    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, w7, h7, 0, GL_BGR, GL_UNSIGNED_BYTE, pic7 );
    glGenerateMipmap(GL_TEXTURE_2D);
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
    
    
    
    unsigned char* pic8 = NULL;
    int w8,h8;
    loadBMP_custom(&pic8, &w8, &h8, "CeeLo0.bmp");
    
    glBindTexture( GL_TEXTURE_2D, textures[8] );
    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, w8, h8, 0, GL_BGR, GL_UNSIGNED_BYTE, pic8 );
    glGenerateMipmap(GL_TEXTURE_2D);
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );

    
    
    
    
    unsigned char* pic9 = NULL;
    int w9,h9;
    loadBMP_custom(&pic9, &w9, &h9, "CeeLo1.bmp");
    
    glBindTexture( GL_TEXTURE_2D, textures[9] );
    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, w9, h9, 0, GL_BGR, GL_UNSIGNED_BYTE, pic9 );
    glGenerateMipmap(GL_TEXTURE_2D);
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );

    
    
    
    
    
    
    unsigned char* pic10 = NULL;
    int w10,h10;
    loadBMP_custom(&pic10, &w10, &h10, "CeeLo2.bmp");
    
    glBindTexture( GL_TEXTURE_2D, textures[10] );
    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, w10, h10, 0, GL_BGR, GL_UNSIGNED_BYTE, pic10 );
    glGenerateMipmap(GL_TEXTURE_2D);
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );

    
    
    
    
    
    
    
    unsigned char* pic11 = NULL;
    int w11,h11;
    loadBMP_custom(&pic11, &w11, &h11, "CeeLo3.bmp");
    
    glBindTexture( GL_TEXTURE_2D, textures[11] );
    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, w11, h11, 0, GL_BGR, GL_UNSIGNED_BYTE, pic11 );
    glGenerateMipmap(GL_TEXTURE_2D);
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
    

    
    
    
    unsigned char* pic12 = NULL;
    int w12,h12;
    loadBMP_custom(&pic12, &w12, &h12, "sw0.bmp");
    
    glBindTexture( GL_TEXTURE_2D, textures[12] );
    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, w12, h12, 0, GL_BGR, GL_UNSIGNED_BYTE, pic12 );
    glGenerateMipmap(GL_TEXTURE_2D);
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );

    
    
    
    
    
    unsigned char* pic13 = NULL;
    int w13,h13;
    loadBMP_custom(&pic13, &w13, &h13, "sw1.bmp");
    
    glBindTexture( GL_TEXTURE_2D, textures[13] );
    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, w13, h13, 0, GL_BGR, GL_UNSIGNED_BYTE, pic13 );
    glGenerateMipmap(GL_TEXTURE_2D);
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );

    
    
    
    
    
    
    unsigned char* pic14 = NULL;
    int w14,h14;
    loadBMP_custom(&pic14, &w14, &h14, "sw2.bmp");
    
    glBindTexture( GL_TEXTURE_2D, textures[14] );
    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, w14, h14, 0, GL_BGR, GL_UNSIGNED_BYTE, pic14);
    glGenerateMipmap(GL_TEXTURE_2D);
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );

    
    
    
    
    
    
    unsigned char* pic15 = NULL;
    int w15,h15;
    loadBMP_custom(&pic15, &w15, &h15, "sw3.bmp");
    
    glBindTexture( GL_TEXTURE_2D, textures[15] );
    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, w15, h15, 0, GL_BGR, GL_UNSIGNED_BYTE, pic15 );
    glGenerateMipmap(GL_TEXTURE_2D);
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );

    
    
    
    
    
    
    
    
    
    
    //----set offset variables
    
    CUBE_OFFSET = 0;
    COLOR_OFFSET = sizeof(points_cube);
    CUBE_NORMALS_OFFSET = COLOR_OFFSET + sizeof(colors);
    CUBE_TEXCOORDS_OFFSET = CUBE_NORMALS_OFFSET + sizeof(normals_cube);
    CYLINDER_OFFSET = CUBE_TEXCOORDS_OFFSET + sizeof(tex_coords_cube);
    CYLINDER_NORMALS_OFFSET = CYLINDER_OFFSET + sizeof(points_cylinder);
    SPHERE_OFFSET = CYLINDER_NORMALS_OFFSET + sizeof(normals_cylinder);
    SPHERE_NORMALS_OFFSET = SPHERE_OFFSET + sizeof(points_sphere);
    SPHERE_TEXCOORDS_OFFSET = SPHERE_NORMALS_OFFSET + sizeof(normals_sphere);
    TORUS_OFFSET = SPHERE_TEXCOORDS_OFFSET + sizeof(tex_coords_sphere);
    TORUS_NORMALS_OFFSET = TORUS_OFFSET + sizeof(points_torus);
    TORUS_TEXCOORDS_OFFSET = TORUS_NORMALS_OFFSET + sizeof(normals_torus);
    TRIANGLE_OFFSET = TORUS_TEXCOORDS_OFFSET + sizeof(tex_coords_torus);
    TRIANGLE_NORMALS_OFFSET = TRIANGLE_OFFSET + sizeof(points_triangle);
    TRIANGLE_TEXCOORDS_OFFSET = TRIANGLE_NORMALS_OFFSET + sizeof(normals_triangle);
    
    
    
    // Create a vertex array object
    GLuint vao;
    glGenVertexArrays( 1, &vao );  // removed 'APPLE' suffix for 3.2
    glBindVertexArray( vao );
    
    
    
    
    // Create and initialize a buffer object
    GLuint buffer;
    glGenBuffers( 1, &buffer );
    glBindBuffer( GL_ARRAY_BUFFER, buffer );
    glBufferData( GL_ARRAY_BUFFER, sizeof(points_cube) + sizeof(normals_cube) + sizeof(tex_coords_cube) + sizeof(colors) + sizeof(points_cylinder) + sizeof(normals_cylinder) + sizeof(points_sphere) + sizeof(normals_sphere) + sizeof(tex_coords_sphere) + sizeof(points_torus) + sizeof(normals_torus) + sizeof(tex_coords_torus) + sizeof(points_triangle) + sizeof(normals_triangle) + sizeof(tex_coords_triangle), NULL, GL_STATIC_DRAW );
    glBufferSubData( GL_ARRAY_BUFFER, CUBE_OFFSET, sizeof(points_cube), points_cube );
    glBufferSubData( GL_ARRAY_BUFFER, COLOR_OFFSET, sizeof(colors), colors );
    glBufferSubData( GL_ARRAY_BUFFER, CUBE_NORMALS_OFFSET, sizeof(normals_cube), normals_cube );
    glBufferSubData( GL_ARRAY_BUFFER, CUBE_TEXCOORDS_OFFSET, sizeof(tex_coords_cube), tex_coords_cube );
    glBufferSubData( GL_ARRAY_BUFFER, CYLINDER_OFFSET, sizeof(points_cylinder), points_cylinder );
    glBufferSubData( GL_ARRAY_BUFFER, CYLINDER_NORMALS_OFFSET, sizeof(normals_cylinder), normals_cylinder );
    glBufferSubData( GL_ARRAY_BUFFER, SPHERE_OFFSET, sizeof(points_sphere), points_sphere );
    glBufferSubData( GL_ARRAY_BUFFER, SPHERE_NORMALS_OFFSET, sizeof(normals_sphere), normals_sphere );
    glBufferSubData( GL_ARRAY_BUFFER, SPHERE_TEXCOORDS_OFFSET, sizeof(tex_coords_sphere), tex_coords_sphere );
    glBufferSubData( GL_ARRAY_BUFFER, TORUS_OFFSET, sizeof(points_torus), points_torus );
    glBufferSubData( GL_ARRAY_BUFFER, TORUS_NORMALS_OFFSET, sizeof(normals_torus), normals_torus );
    glBufferSubData( GL_ARRAY_BUFFER, TORUS_TEXCOORDS_OFFSET, sizeof(tex_coords_torus), tex_coords_torus);
    glBufferSubData( GL_ARRAY_BUFFER, TRIANGLE_OFFSET, sizeof(points_triangle), points_triangle );
    glBufferSubData( GL_ARRAY_BUFFER, TRIANGLE_NORMALS_OFFSET, sizeof(normals_triangle), normals_triangle );
    glBufferSubData( GL_ARRAY_BUFFER, TRIANGLE_TEXCOORDS_OFFSET, sizeof(tex_coords_triangle), tex_coords_triangle);
    
    
    
    
    //---------------------------------------------------------------------
    
    
    
    
    // set up vertex arrays
    vPosition = glGetAttribLocation( program, "vPosition" );
    glEnableVertexAttribArray( vPosition );
    glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(CUBE_OFFSET) );
    
    vNormal = glGetAttribLocation( program, "vNormal" );
    glEnableVertexAttribArray( vNormal );
    glVertexAttribPointer( vNormal, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(CUBE_NORMALS_OFFSET) );
    
    vColor = glGetAttribLocation( program, "vColor" );
    glEnableVertexAttribArray( vColor );
    glVertexAttribPointer( vColor, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(COLOR_OFFSET) );
    
    vTexCoord = glGetAttribLocation( program, "vTexCoord" );
    glEnableVertexAttribArray( vTexCoord );
    glVertexAttribPointer( vTexCoord, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(SPHERE_TEXCOORDS_OFFSET) );
    
    // Set the value of the fragment shader texture sampler variable (myTextureSampler) to GL_TEXTURE0
    glUniform1i( glGetUniformLocation(program, "myTextureSampler"), 0 );
    
    
    
    //---------------------------------------------------------------------
    
    
    glEnable( GL_DEPTH_TEST );
    glClearColor( 0.8632, 0.9804, 1.0, 1.0 );               //blue sky
}




//----------------------------------------------------------------------------



void
SetMaterial( vec4 ka, vec4 kd, vec4 ks, float s )
{
    glUniform4fv( glGetUniformLocation(program, "ka"), 1, ka );
    glUniform4fv( glGetUniformLocation(program, "kd"), 1, kd );
    glUniform4fv( glGetUniformLocation(program, "ks"), 1, ks );
    glUniform1f( glGetUniformLocation(program, "Shininess"), s );
}


//----------------------------------------------------------------------------



void
SetLight( vec4 lpos, vec4 la, vec4 ld, vec4 ls )
{
    glUniform4fv( glGetUniformLocation(program, "LightPosition"), 1, lpos);
    glUniform4fv( glGetUniformLocation(program, "AmbientLight"), 1, la);
    glUniform4fv( glGetUniformLocation(program, "DiffuseLight"), 1, ld);
    glUniform4fv( glGetUniformLocation(program, "SpecularLight"), 1, ls);
}




//----------------------------------------------------------------------------



mat4 proj_matrix;
mat4 view_matrix;
mat4 wheelOneTransform, wheelTwoTransform, wheelThreeTransform, wheelFourTransform, frontAxleTransform, rearAxleTransform, frontTruckTransform, rearTruckTransform, boardCenterTransform, rearBoardEdgeTransform, frontBoardEdgeTransform;
float r = 5.0;
float railY = 0.2325;
float nearPostX = -1, nearPostY = .122, nearPostZ = -9.5, farPostX = -1, farPostY = .120, farPostZ = -18.0, roadY = .005;
float initialThetaX, initialThetaY, initialThetaZ, thetaX, thetaY, thetaZ = 0.0;
float xOffset = 0.0, yOffset = 0.16, zOffset = 0.225;



void display( void ){
    
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    
    
    //---- lights
    
    SetLight( vec4( 0.0, 4.0, 0.0, 1.0), vec4(0.4, 0.4, 0.4, 1.0), vec4(0.95, 0.95, 0.95, 1.0), vec4(0.2, 0.2, 0.2, 1.0));
    
    
    //---- camera intrinsic parameters
    
    float left = -1.0;
    float right = 1.0;
    float bottom = -1.0;
    float top = 1.0;
    float zNear = 1.0;
    float zFar = 50.0;
    
    
    proj_matrix = Frustum( left, right, bottom, top, zNear, zFar );
    
    glUniformMatrix4fv( glGetUniformLocation( program, "projection" ), 1, GL_TRUE, proj_matrix );
    
    
    
    //---- camera extrinsic parameters
    
    float tr_y = Theta3[Yaxis]* M_PI/180.0;
    float tr_z = Theta3[Zaxis]* M_PI/180.0;
    float eye_z = r * (cos(tr_z)) * cos(tr_y);
    float eye_x = r * (cos(tr_z)) * sin(tr_y);
    float eye_y = r * sin(tr_z);
    
    vec4 up = vec4(0.0, cos(tr_z), 0.0, 0.0);
    cout << up << ' ' << normalize(up) << endl;
    
    view_matrix = LookAt( vec4(eye_x, eye_y, eye_z, 1.0), vec4(0.0, 0.0, 0.0, 1.0), vec4(0.0, cos(tr_z), 0.0, 0.0));
    
    glUniformMatrix4fv( glGetUniformLocation( program, "view" ), 1, GL_TRUE, view_matrix );
    glUniform4fv( glGetUniformLocation( program, "cam_location" ), 1, vec4(eye_x, eye_y, eye_z, 1.0) );
    
    
    
    
    
    
    
    
    
    
    
    // -------------- OBJECTS --------------
    
    
    
    
    
    // ----------- SKATEBOARD ------------
    //---- wh33l 0n3 rear left wheel
    
    glBindTexture( GL_TEXTURE_2D, textures[0] );
    glUniform1i( glGetUniformLocation(program, "texture_on"), false );
    
    SetMaterial( vec4(0.9, 0.9, 0.5, 1.0), vec4(0.9, 0.9, 0.5, 1.0), vec4(0.9, 0.9, 0.0, 1.0), 0.5);
    glUniform1i( glGetUniformLocation(program, "light_out"), false );
    
    wheelOneTransform = Translate(rearWheelsX,rearWheelsY,rearWheelsZ) * RotateX(thetaX) * RotateY(thetaY) * RotateZ(thetaZ) * Translate(-0.118 + xOffset, 0.08, -zOffset+zOffset ) * RotateY(90) * RotateZ(initialThetaZ) * Scale(0.08, 0.08, 0.08);
    glUniformMatrix4fv( glGetUniformLocation( program, "model" ), 1, GL_TRUE, wheelOneTransform );
    
    glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(TORUS_OFFSET) );
    glVertexAttribPointer( vNormal, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(TORUS_NORMALS_OFFSET) );
    glVertexAttribPointer( vTexCoord, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(TORUS_TEXCOORDS_OFFSET) );
    glDrawArrays( GL_TRIANGLES, 0, NumVerticesTorus );
    
    
    
    //---- wh33l 7w0 rear right wheel
    
    glBindTexture( GL_TEXTURE_2D, textures[0] );
    glUniform1i( glGetUniformLocation(program, "texture_on"), false );
    
    SetMaterial( vec4(0.9, 0.9, 0.5, 1.0), vec4(0.9, 0.9, 0.5, 1.0), vec4(0.9, 0.9, 0.0, 1.0), 0.5);
    glUniform1i( glGetUniformLocation(program, "light_out"), false );
    wheelTwoTransform = Translate(rearWheelsX,rearWheelsY,rearWheelsZ) * RotateX(thetaX) * RotateY(thetaY) * RotateZ(thetaZ) *Translate( 0.118 + xOffset, 0.08, -zOffset+zOffset ) * RotateY(90) * RotateZ(initialThetaZ) * Scale(0.08, 0.08, 0.08);
    glUniformMatrix4fv( glGetUniformLocation( program, "model" ), 1, GL_TRUE, wheelTwoTransform );
    
    glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(TORUS_OFFSET) );
    glVertexAttribPointer( vNormal, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(TORUS_NORMALS_OFFSET) );
    glVertexAttribPointer( vTexCoord, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(TORUS_TEXCOORDS_OFFSET) );
    glDrawArrays( GL_TRIANGLES, 0, NumVerticesTorus );
    
    
    
    //---- wh33l 7HR33 front wheel
    
    glBindTexture( GL_TEXTURE_2D, textures[0] );
    glUniform1i( glGetUniformLocation(program, "texture_on"), false );
    
    SetMaterial( vec4(0.9, 0.9, 0.5, 1.0), vec4(0.9, 0.9, 0.5, 1.0), vec4(0.9, 0.9, 0.0, 1.0), 0.5);
    glUniform1i( glGetUniformLocation(program, "light_out"), false );
    
    wheelThreeTransform = Translate(frontWheelsX,frontWheelsY,frontWheelsZ) * RotateX(thetaX) * RotateY(thetaY) * RotateZ(thetaZ) *Translate( -0.118 + xOffset, 0.08, zOffset+zOffset ) * RotateY(90) * RotateZ(initialThetaZ) * Scale(0.08, 0.08, 0.08);
    glUniformMatrix4fv( glGetUniformLocation( program, "model" ), 1, GL_TRUE, wheelThreeTransform );
    
    glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(TORUS_OFFSET) );
    glVertexAttribPointer( vNormal, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(TORUS_NORMALS_OFFSET) );
    glVertexAttribPointer( vTexCoord, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(TORUS_TEXCOORDS_OFFSET) );
    glDrawArrays( GL_TRIANGLES, 0, NumVerticesTorus );
    
    
    
    //---- wh33l F0|_|R front wheel
    
    glBindTexture( GL_TEXTURE_2D, textures[0] );
    glUniform1i( glGetUniformLocation(program, "texture_on"), false );
    
    SetMaterial( vec4(0.9, 0.9, 0.5, 1.0), vec4(0.9, 0.9, 0.5, 1.0), vec4(0.9, 0.9, 0.0, 1.0), 0.5);
    glUniform1i( glGetUniformLocation(program, "light_out"), false );
    
    wheelFourTransform = Translate(frontWheelsX,frontWheelsY,frontWheelsZ)* RotateX(thetaX) * RotateY(thetaY) * RotateZ(thetaZ) *Translate( 0.118 + xOffset, 0.08, zOffset+zOffset ) * RotateY(90) * RotateZ(initialThetaZ) * Scale(0.08, 0.08, 0.08);
    glUniformMatrix4fv( glGetUniformLocation( program, "model" ), 1, GL_TRUE, wheelFourTransform );
    
    glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(TORUS_OFFSET) );
    glVertexAttribPointer( vNormal, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(TORUS_NORMALS_OFFSET) );
    glVertexAttribPointer( vTexCoord, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(TORUS_TEXCOORDS_OFFSET) );
    glDrawArrays( GL_TRIANGLES, 0, NumVerticesTorus );
    
    
    
    //----- Axle 1, front axle
    
    glBindTexture( GL_TEXTURE_2D, textures[5] );
    glUniform1i( glGetUniformLocation(program, "texture_on"), true );
    
    SetMaterial(vec4(0.0, 0.4, 0.4, 1.0), vec4(0.925, 0.925, 0.925, 1.0), vec4(0.2, 0.2, 0.2, 1.0), 1.0);
    glUniform1i( glGetUniformLocation(program, "light_out"), false );
    
    frontAxleTransform =  Translate(frontTrAxX,frontTrAxY,frontTrAxZ)* RotateX(thetaX) * RotateY(thetaY) * RotateZ(thetaZ) *Translate( xOffset, 0.08, zOffset+zOffset ) * Scale(0.3, 0.04, 0.04) * RotateZ(90 + initialThetaZ);
    glUniformMatrix4fv( glGetUniformLocation( program, "model" ), 1, GL_TRUE, frontAxleTransform );
    
    glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(CYLINDER_OFFSET) );
    glVertexAttribPointer( vNormal, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(CYLINDER_NORMALS_OFFSET) );
    glDrawArrays( GL_TRIANGLES, 0, NumVerticesCylinder );
    
    
    
    //----- Axle 2, rear axle
    
    glBindTexture( GL_TEXTURE_2D, textures[5] );
    glUniform1i( glGetUniformLocation(program, "texture_on"), true );
    
    SetMaterial(vec4(0.0, 0.4, 0.4, 1.0), vec4(0.925, 0.925, 0.925, 1.0), vec4(0.2, 0.2, 0.2, 1.0), 1.0);
    glUniform1i( glGetUniformLocation(program, "light_out"), false );
    
    rearAxleTransform = Translate(rearTrAxX,rearTrAxY,rearTrAxZ)* RotateX(thetaX) * RotateY(thetaY) * RotateZ(thetaZ) *Translate( xOffset, 0.08, -zOffset+zOffset ) * Scale(0.3, 0.04, 0.04) * RotateZ(90 + initialThetaZ);
    glUniformMatrix4fv( glGetUniformLocation( program, "model" ), 1, GL_TRUE, rearAxleTransform );
    
    glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(CYLINDER_OFFSET) );
    glVertexAttribPointer( vNormal, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(CYLINDER_NORMALS_OFFSET) );
    glDrawArrays( GL_TRIANGLES, 0, NumVerticesCylinder );
    
    
    
    //----- Truck1, front truck
    
    glBindTexture( GL_TEXTURE_2D, textures[5] );
    glUniform1i( glGetUniformLocation(program, "texture_on"), true );
    
    SetMaterial(vec4(0.0, 0.4, 0.4, 1.0), vec4(0.925, 0.925, 0.925, 1.0), vec4(0.2, 0.2, 0.2, 1.0), 1.0);
    glUniform1i( glGetUniformLocation(program, "light_out"), false );
    
    frontTruckTransform = Translate(frontTrAxX,frontTrAxY,frontTrAxZ) * RotateX(thetaX) * RotateY(thetaY) * RotateZ(thetaZ) * Translate( xOffset, 0.11, zOffset+zOffset ) * * RotateZ(initialThetaZ) * Scale(0.03, 0.08, 0.04);
    glUniformMatrix4fv( glGetUniformLocation( program, "model" ), 1, GL_TRUE, frontTruckTransform );
    
    glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(CYLINDER_OFFSET) );
    glVertexAttribPointer( vNormal, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(CYLINDER_NORMALS_OFFSET) );
    glDrawArrays( GL_TRIANGLES, 0, NumVerticesCylinder );
    
    
    //----- Truck2, rear truck
    
    glBindTexture( GL_TEXTURE_2D, textures[5] );
    glUniform1i( glGetUniformLocation(program, "texture_on"), true );
    
    SetMaterial(vec4(0.0, 0.4, 0.4, 1.0), vec4(0.925, 0.925, 0.925, 1.0), vec4(0.2, 0.2, 0.2, 1.0), 1.0);
    glUniform1i( glGetUniformLocation(program, "light_out"), false );
    
    rearTruckTransform = Translate(rearTrAxX,rearTrAxY,rearTrAxZ)* RotateX(thetaX) * RotateY(thetaY) * RotateZ(thetaZ) *Translate( xOffset, 0.11, -zOffset+zOffset ) * RotateZ(initialThetaZ) *Scale(0.03, 0.08, 0.04);
    glUniformMatrix4fv( glGetUniformLocation( program, "model" ), 1, GL_TRUE, rearTruckTransform );
    
    glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(CYLINDER_OFFSET) );
    glVertexAttribPointer( vNormal, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(CYLINDER_NORMALS_OFFSET) );
    glDrawArrays( GL_TRIANGLES, 0, NumVerticesCylinder );
    
    
    //---- board
    
    glBindTexture( GL_TEXTURE_2D, textures[2] );
    glUniform1i( glGetUniformLocation(program, "texture_on"), true );
    
    SetMaterial(vec4(0.4, 0.4, 0.4, 1.0), vec4(0.94, 0.95, 0.95, 1.0), vec4(0.2, 0.2, 0.2, 1.0), 1.0);
    glUniform1i( glGetUniformLocation(program, "light_out"), false );
    
    boardCenterTransform = Translate(boardX,boardY, boardZ) * RotateX(thetaX) * RotateY(thetaY) * RotateZ(thetaZ) * Translate( xOffset, yOffset, zOffset ) * RotateY(initialThetaY) * RotateZ(initialThetaZ) * Scale(0.25, 0.025, 0.75);
    glUniformMatrix4fv( glGetUniformLocation( program, "model" ), 1, GL_TRUE, boardCenterTransform );
    
    glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(CUBE_OFFSET) );
    glVertexAttribPointer( vNormal, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(CUBE_NORMALS_OFFSET) );
    glVertexAttribPointer( vTexCoord, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(CUBE_TEXCOORDS_OFFSET) );
    glDrawArrays( GL_TRIANGLES, 0, NumVerticesCube );
    
    
    
    
    
    
    
    
    
    
    
    
    
    //-------- Environment! -----
    
    //---- Concrete road
    
    glBindTexture( GL_TEXTURE_2D, textures[3] );
    glUniform1i( glGetUniformLocation(program, "texture_on"), true);
    
    SetMaterial(vec4(0.2, 0.2, 0.2, 1.0), vec4(0.7343, 0.5546, 0.4336, 1.0), vec4(0.2, 0.2, 0.2, 1.0), 1.0);
    glUniform1i( glGetUniformLocation(program, "light_out"), false );
    
    mat4 transform = Translate( 0.0, roadY, grass1 ) * Scale(2.25, 0.05, 30.0);
    glUniformMatrix4fv( glGetUniformLocation( program, "model" ), 1, GL_TRUE, transform );
    
    glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(CUBE_OFFSET) );
    glVertexAttribPointer( vNormal, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(CUBE_NORMALS_OFFSET) );
    glVertexAttribPointer( vTexCoord, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(CUBE_TEXCOORDS_OFFSET) );
    
    glDrawArrays( GL_TRIANGLES, 0, NumVerticesCube );
    
    
    
    //---- Concrete road2
    
    glBindTexture( GL_TEXTURE_2D, textures[3] );
    glUniform1i( glGetUniformLocation(program, "texture_on"), true);
    
    SetMaterial(vec4(0.2, 0.2, 0.2, 1.0), vec4(0.7343, 0.5546, 0.4336, 1.0), vec4(0.2, 0.2, 0.2, 1.0), 1.0);
    glUniform1i( glGetUniformLocation(program, "light_out"), false );
    
    transform = Translate( 0.0, roadY, grass2 ) * Scale(2.25, 0.05, 30.0);
    glUniformMatrix4fv( glGetUniformLocation( program, "model" ), 1, GL_TRUE, transform );
    
    glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(CUBE_OFFSET) );
    glVertexAttribPointer( vNormal, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(CUBE_NORMALS_OFFSET) );
    glVertexAttribPointer( vTexCoord, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(CUBE_TEXCOORDS_OFFSET) );
    
    glDrawArrays( GL_TRIANGLES, 0, NumVerticesCube );
    
    
    
    
    
    
    //---- Grass
    
    glBindTexture( GL_TEXTURE_2D, textures[1] );
    glUniform1i( glGetUniformLocation(program, "texture_on"), true );
    
    SetMaterial(vec4(0.2, 0.2, 0.2, 1.0), vec4(0.23, 0.726, 0.421, 1.0), vec4(0.2, 0.2, 0.2, 1.0), 1.0);
    glUniform1i( glGetUniformLocation(program, "light_out"), false );
    
    transform = Translate( 0.0, 0.0, grass1) * Scale(12.0, 0.05, 30.0);
    glUniformMatrix4fv( glGetUniformLocation( program, "model" ), 1, GL_TRUE, transform );
    
    glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(CUBE_OFFSET) );
    glVertexAttribPointer( vNormal, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(CUBE_NORMALS_OFFSET) );
    glVertexAttribPointer( vTexCoord, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(CUBE_TEXCOORDS_OFFSET) );
    glDrawArrays( GL_TRIANGLES, 0, NumVerticesCube );
    
    
    
    
    
    //---- Grass2
    
    glBindTexture( GL_TEXTURE_2D, textures[1] );
    glUniform1i( glGetUniformLocation(program, "texture_on"), true );
    
    SetMaterial(vec4(0.2, 0.2, 0.2, 1.0), vec4(0.23, 0.726, 0.421, 1.0), vec4(0.2, 0.2, 0.2, 1.0), 1.0);
    glUniform1i( glGetUniformLocation(program, "light_out"), false );
    
    transform = Translate( 0.0, 0.0, grass2) * Scale(12.0, 0.05, 30.0);
    glUniformMatrix4fv( glGetUniformLocation( program, "model" ), 1, GL_TRUE, transform );
    
    glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(CUBE_OFFSET) );
    glVertexAttribPointer( vNormal, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(CUBE_NORMALS_OFFSET) );
    glVertexAttribPointer( vTexCoord, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(CUBE_TEXCOORDS_OFFSET) );
    glDrawArrays( GL_TRIANGLES, 0, NumVerticesCube );
    
    
    
    
    
    
    
    
    
    
    
    
    //----- Grinding Rail
    // Rail
    
    glBindTexture( GL_TEXTURE_2D, textures[5] );
    glUniform1i( glGetUniformLocation(program, "texture_on"), true );
    
    SetMaterial(vec4(0.0, 0.0, 1.0, 1.0), vec4(0.925, 0.925, 0.925, 1.0), vec4(0.2, 0.2, 0.2, 1.0), 1.0);
    glUniform1i( glGetUniformLocation(program, "light_out"), false );
    
    mat4 rail = Translate( 0, railY, -13.75 + grass1 ) * RotateY(90) * Scale(9.0, 0.04, 0.04) * RotateZ(90);
    glUniformMatrix4fv( glGetUniformLocation( program, "model" ), 1, GL_TRUE, rail );
    
    glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(CUBE_OFFSET) );
    glVertexAttribPointer( vNormal, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(CUBE_NORMALS_OFFSET) );
    glVertexAttribPointer( vTexCoord, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(CUBE_TEXCOORDS_OFFSET) );
    glDrawArrays( GL_TRIANGLES, 0, NumVerticesCube );
    
    
    //------ Post 1
    
    glBindTexture( GL_TEXTURE_2D, textures[5] );
    glUniform1i( glGetUniformLocation(program, "texture_on"), true );
    
    SetMaterial(vec4(0.0, 0.0, 1.0, 1.0), vec4(0.925, 0.925, 0.925, 1.0), vec4(0.2, 0.2, 0.2, 1.0), 1.0);
    glUniform1i( glGetUniformLocation(program, "light_out"), false );
    
    mat4 post = Translate( 0.0, nearPostY, nearPostZ + grass1 ) * Scale(0.04, .265, 0.05);
    glUniformMatrix4fv( glGetUniformLocation( program, "model" ), 1, GL_TRUE, post);
    
    glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(CUBE_OFFSET) );
    glVertexAttribPointer( vNormal, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(CUBE_NORMALS_OFFSET) );
    glVertexAttribPointer( vTexCoord, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(CUBE_TEXCOORDS_OFFSET) );
    glDrawArrays( GL_TRIANGLES, 0, NumVerticesCube );
    
    
    //------ Post 2
    
    glBindTexture( GL_TEXTURE_2D, textures[5] );
    glUniform1i( glGetUniformLocation(program, "texture_on"), true );
    
    SetMaterial(vec4(0.0, 0.0, 1.0, 1.0), vec4(0.925, 0.925, 0.925, 1.0), vec4(0.2, 0.2, 0.2, 1.0), 1.0);
    glUniform1i( glGetUniformLocation(program, "light_out"), false );
    
    post = Translate( 0.0, farPostY, farPostZ + grass1 ) * Scale(0.04, .265, 0.05);
    glUniformMatrix4fv( glGetUniformLocation( program, "model" ), 1, GL_TRUE, post);
    
    glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(CUBE_OFFSET) );
    glVertexAttribPointer( vNormal, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(CUBE_NORMALS_OFFSET) );
    glVertexAttribPointer( vTexCoord, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(CUBE_TEXCOORDS_OFFSET) );
    glDrawArrays( GL_TRIANGLES, 0, NumVerticesCube );
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    //----------- Bench 1!!! ------
    //---- BenchBase
    
    glBindTexture( GL_TEXTURE_2D, textures[3] );
    glUniform1i( glGetUniformLocation(program, "texture_on"), true );
    
    SetMaterial(vec4(0.4, 0.4, 0.4, 1.0), vec4(0.94, 0.95, 0.95, 1.0), vec4(0.2, 0.2, 0.2, 1.0), 1.0);
    glUniform1i( glGetUniformLocation(program, "light_out"), false );
    
    transform = Translate( -2.5, 0.2, -22.5 + grass2 ) * Scale(0.5, 0.07, 1.0);
    glUniformMatrix4fv( glGetUniformLocation( program, "model" ), 1, GL_TRUE, transform );
    
    glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(CUBE_OFFSET) );
    glVertexAttribPointer( vNormal, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(CUBE_NORMALS_OFFSET) );
    glVertexAttribPointer( vTexCoord, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(CUBE_TEXCOORDS_OFFSET) );
    glDrawArrays( GL_TRIANGLES, 0, NumVerticesCube );
    
    
    
    //---- BenchLeftLeg
    
    glBindTexture( GL_TEXTURE_2D, textures[3] );
    glUniform1i( glGetUniformLocation(program, "texture_on"), true );
    
    SetMaterial(vec4(0.4, 0.4, 0.4, 1.0), vec4(0.94, 0.95, 0.95, 1.0), vec4(0.2, 0.2, 0.2, 1.0), 1.0);
    glUniform1i( glGetUniformLocation(program, "light_out"), false );
    
    transform = Translate( -2.5, 0.2, -23.0 + grass2 ) * Scale(0.5, 0.4, 0.05);
    glUniformMatrix4fv( glGetUniformLocation( program, "model" ), 1, GL_TRUE, transform );
    
    glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(CUBE_OFFSET) );
    glVertexAttribPointer( vNormal, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(CUBE_NORMALS_OFFSET) );
    glVertexAttribPointer( vTexCoord, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(CUBE_TEXCOORDS_OFFSET) );
    glDrawArrays( GL_TRIANGLES, 0, NumVerticesCube );
    
    
    
    //---- BenchRightLeg
    
    glBindTexture( GL_TEXTURE_2D, textures[3] );
    glUniform1i( glGetUniformLocation(program, "texture_on"), true );
    
    SetMaterial(vec4(0.4, 0.4, 0.4, 1.0), vec4(0.94, 0.95, 0.95, 1.0), vec4(0.2, 0.2, 0.2, 1.0), 1.0);
    glUniform1i( glGetUniformLocation(program, "light_out"), false );
    
    transform = Translate( -2.5, 0.2, -22.0 + grass2 ) * Scale(0.5, 0.4, 0.05);
    glUniformMatrix4fv( glGetUniformLocation( program, "model" ), 1, GL_TRUE, transform );
    
    glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(CUBE_OFFSET) );
    glVertexAttribPointer( vNormal, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(CUBE_NORMALS_OFFSET) );
    glVertexAttribPointer( vTexCoord, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(CUBE_TEXCOORDS_OFFSET) );
    glDrawArrays( GL_TRIANGLES, 0, NumVerticesCube );
    
    
    
    //---- BenchBack
    
    glBindTexture( GL_TEXTURE_2D, textures[4] );
    glUniform1i( glGetUniformLocation(program, "texture_on"), true );
    
    SetMaterial(vec4(0.4, 0.4, 0.4, 1.0), vec4(0.94, 0.95, 0.95, 1.0), vec4(0.2, 0.2, 0.2, 1.0), 1.0);
    glUniform1i( glGetUniformLocation(program, "light_out"), false );
    
    transform = Translate( -2.75, 0.3, -22.5 + grass2 ) * Scale(0.05, 0.5, 1.05);
    glUniformMatrix4fv( glGetUniformLocation( program, "model" ), 1, GL_TRUE, transform );
    
    glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(CUBE_OFFSET) );
    glVertexAttribPointer( vNormal, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(CUBE_NORMALS_OFFSET) );
    glVertexAttribPointer( vTexCoord, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(CUBE_TEXCOORDS_OFFSET) );
    glDrawArrays( GL_TRIANGLES, 0, NumVerticesCube );
    
    
    
    
    
    
    
    
    
    
    
    
    //----------- Bench 2 !!! ------
    //---- BenchBase
    
    glBindTexture( GL_TEXTURE_2D, textures[3] );
    glUniform1i( glGetUniformLocation(program, "texture_on"), true );
    
    SetMaterial(vec4(0.4, 0.4, 0.4, 1.0), vec4(0.94, 0.95, 0.95, 1.0), vec4(0.2, 0.2, 0.2, 1.0), 1.0);
    glUniform1i( glGetUniformLocation(program, "light_out"), false );
    
    transform = Translate( -2.5, 0.2, -22.5 + grass1 ) * Scale(0.5, 0.07, 1.0);
    glUniformMatrix4fv( glGetUniformLocation( program, "model" ), 1, GL_TRUE, transform );
    
    glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(CUBE_OFFSET) );
    glVertexAttribPointer( vNormal, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(CUBE_NORMALS_OFFSET) );
    glVertexAttribPointer( vTexCoord, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(CUBE_TEXCOORDS_OFFSET) );
    glDrawArrays( GL_TRIANGLES, 0, NumVerticesCube );
    
    
    
    //---- BenchLeftLeg
    
    glBindTexture( GL_TEXTURE_2D, textures[3] );
    glUniform1i( glGetUniformLocation(program, "texture_on"), true );
    
    SetMaterial(vec4(0.4, 0.4, 0.4, 1.0), vec4(0.94, 0.95, 0.95, 1.0), vec4(0.2, 0.2, 0.2, 1.0), 1.0);
    glUniform1i( glGetUniformLocation(program, "light_out"), false );
    
    transform = Translate( -2.5, 0.2, -23.0 + grass1 ) * Scale(0.5, 0.4, 0.05);
    glUniformMatrix4fv( glGetUniformLocation( program, "model" ), 1, GL_TRUE, transform );
    
    glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(CUBE_OFFSET) );
    glVertexAttribPointer( vNormal, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(CUBE_NORMALS_OFFSET) );
    glVertexAttribPointer( vTexCoord, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(CUBE_TEXCOORDS_OFFSET) );
    glDrawArrays( GL_TRIANGLES, 0, NumVerticesCube );
    
    
    
    //---- BenchRightLeg
    
    glBindTexture( GL_TEXTURE_2D, textures[3] );
    glUniform1i( glGetUniformLocation(program, "texture_on"), true );
    
    SetMaterial(vec4(0.4, 0.4, 0.4, 1.0), vec4(0.94, 0.95, 0.95, 1.0), vec4(0.2, 0.2, 0.2, 1.0), 1.0);
    glUniform1i( glGetUniformLocation(program, "light_out"), false );
    
    transform = Translate( -2.5, 0.2, -22.0 + grass1 ) * Scale(0.5, 0.4, 0.05);
    glUniformMatrix4fv( glGetUniformLocation( program, "model" ), 1, GL_TRUE, transform );
    
    glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(CUBE_OFFSET) );
    glVertexAttribPointer( vNormal, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(CUBE_NORMALS_OFFSET) );
    glVertexAttribPointer( vTexCoord, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(CUBE_TEXCOORDS_OFFSET) );
    glDrawArrays( GL_TRIANGLES, 0, NumVerticesCube );
    
    
    
    //---- BenchBack
    
    glBindTexture( GL_TEXTURE_2D, textures[3] );
    glUniform1i( glGetUniformLocation(program, "texture_on"), true );
    
    SetMaterial(vec4(0.4, 0.4, 0.4, 1.0), vec4(0.94, 0.95, 0.95, 1.0), vec4(0.2, 0.2, 0.2, 1.0), 1.0);
    glUniform1i( glGetUniformLocation(program, "light_out"), false );
    
    transform = Translate( -2.75, 0.3, -22.5 + grass1 ) * Scale(0.05, 0.5, 1.05);
    glUniformMatrix4fv( glGetUniformLocation( program, "model" ), 1, GL_TRUE, transform );
    
    glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(CUBE_OFFSET) );
    glVertexAttribPointer( vNormal, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(CUBE_NORMALS_OFFSET) );
    glVertexAttribPointer( vTexCoord, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(CUBE_TEXCOORDS_OFFSET) );
    glDrawArrays( GL_TRIANGLES, 0, NumVerticesCube );
    
    
    
    
    
    
    
    
    
    
    
    
    
    //----------- Bench 3!!! ---------
    //---- BenchBase
    
    glBindTexture( GL_TEXTURE_2D, textures[3] );
    glUniform1i( glGetUniformLocation(program, "texture_on"), true );
    
    SetMaterial(vec4(0.4, 0.4, 0.4, 1.0), vec4(0.94, 0.95, 0.95, 1.0), vec4(0.2, 0.2, 0.2, 1.0), 1.0);
    glUniform1i( glGetUniformLocation(program, "light_out"), false );
    
    transform = Translate( 2.5, 0.2, -7.5 + grass2 ) * Scale(0.5, 0.07, 1.0);
    glUniformMatrix4fv( glGetUniformLocation( program, "model" ), 1, GL_TRUE, transform );
    
    glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(CUBE_OFFSET) );
    glVertexAttribPointer( vNormal, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(CUBE_NORMALS_OFFSET) );
    glVertexAttribPointer( vTexCoord, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(CUBE_TEXCOORDS_OFFSET) );
    glDrawArrays( GL_TRIANGLES, 0, NumVerticesCube );
    
    
    
    //---- BenchLeftLeg
    
    glBindTexture( GL_TEXTURE_2D, textures[3] );
    glUniform1i( glGetUniformLocation(program, "texture_on"), true );
    
    SetMaterial(vec4(0.4, 0.4, 0.4, 1.0), vec4(0.94, 0.95, 0.95, 1.0), vec4(0.2, 0.2, 0.2, 1.0), 1.0);
    glUniform1i( glGetUniformLocation(program, "light_out"), false );
    
    transform = Translate( 2.5, 0.2, -7.0 + grass2 ) * Scale(0.5, 0.4, 0.05);
    glUniformMatrix4fv( glGetUniformLocation( program, "model" ), 1, GL_TRUE, transform );
    
    glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(CUBE_OFFSET) );
    glVertexAttribPointer( vNormal, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(CUBE_NORMALS_OFFSET) );
    glVertexAttribPointer( vTexCoord, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(CUBE_TEXCOORDS_OFFSET) );
    glDrawArrays( GL_TRIANGLES, 0, NumVerticesCube );
    
    
    
    //---- BenchRightLeg
    
    glBindTexture( GL_TEXTURE_2D, textures[3] );
    glUniform1i( glGetUniformLocation(program, "texture_on"), true );
    
    SetMaterial(vec4(0.4, 0.4, 0.4, 1.0), vec4(0.94, 0.95, 0.95, 1.0), vec4(0.2, 0.2, 0.2, 1.0), 1.0);
    glUniform1i( glGetUniformLocation(program, "light_out"), false );
    
    transform = Translate( 2.5, 0.2, -8.0 + grass2 ) * Scale(0.5, 0.4, 0.05);
    glUniformMatrix4fv( glGetUniformLocation( program, "model" ), 1, GL_TRUE, transform );
    
    glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(CUBE_OFFSET) );
    glVertexAttribPointer( vNormal, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(CUBE_NORMALS_OFFSET) );
    glVertexAttribPointer( vTexCoord, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(CUBE_TEXCOORDS_OFFSET) );
    glDrawArrays( GL_TRIANGLES, 0, NumVerticesCube );
    
    
    
    //---- BenchBack
    
    glBindTexture( GL_TEXTURE_2D, textures[4] );
    glUniform1i( glGetUniformLocation(program, "texture_on"), true );
    
    SetMaterial(vec4(0.4, 0.4, 0.4, 1.0), vec4(0.94, 0.95, 0.95, 1.0), vec4(0.2, 0.2, 0.2, 1.0), 1.0);
    glUniform1i( glGetUniformLocation(program, "light_out"), false );
    
    transform = Translate( 2.75, 0.3, -7.5 + grass2 ) * Scale(0.05, 0.5, 1.05);
    glUniformMatrix4fv( glGetUniformLocation( program, "model" ), 1, GL_TRUE, transform );
    
    glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(CUBE_OFFSET) );
    glVertexAttribPointer( vNormal, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(CUBE_NORMALS_OFFSET) );
    glVertexAttribPointer( vTexCoord, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(CUBE_TEXCOORDS_OFFSET) );
    glDrawArrays( GL_TRIANGLES, 0, NumVerticesCube );
    
    
    
    
    
    
    
    
    
    
    
    //----------- Bench 4!!! ----------
    //---- BenchBase
    
    glBindTexture( GL_TEXTURE_2D, textures[3] );
    glUniform1i( glGetUniformLocation(program, "texture_on"), true );
    
    SetMaterial(vec4(0.4, 0.4, 0.4, 1.0), vec4(0.94, 0.95, 0.95, 1.0), vec4(0.2, 0.2, 0.2, 1.0), 1.0);
    glUniform1i( glGetUniformLocation(program, "light_out"), false );
    
    transform = Translate( 2.5, 0.2, -7.5 + grass1 ) * Scale(0.5, 0.07, 1.0);
    glUniformMatrix4fv( glGetUniformLocation( program, "model" ), 1, GL_TRUE, transform );
    
    glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(CUBE_OFFSET) );
    glVertexAttribPointer( vNormal, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(CUBE_NORMALS_OFFSET) );
    glVertexAttribPointer( vTexCoord, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(CUBE_TEXCOORDS_OFFSET) );
    glDrawArrays( GL_TRIANGLES, 0, NumVerticesCube );
    
    
    
    //---- BenchLeftLeg
    
    glBindTexture( GL_TEXTURE_2D, textures[3] );
    glUniform1i( glGetUniformLocation(program, "texture_on"), true );
    
    SetMaterial(vec4(0.4, 0.4, 0.4, 1.0), vec4(0.94, 0.95, 0.95, 1.0), vec4(0.2, 0.2, 0.2, 1.0), 1.0);
    glUniform1i( glGetUniformLocation(program, "light_out"), false );
    
    transform = Translate( 2.5, 0.2, -7.0 + grass1 ) * Scale(0.5, 0.4, 0.05);
    glUniformMatrix4fv( glGetUniformLocation( program, "model" ), 1, GL_TRUE, transform );
    
    glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(CUBE_OFFSET) );
    glVertexAttribPointer( vNormal, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(CUBE_NORMALS_OFFSET) );
    glVertexAttribPointer( vTexCoord, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(CUBE_TEXCOORDS_OFFSET) );
    glDrawArrays( GL_TRIANGLES, 0, NumVerticesCube );
    
    
    
    //---- BenchRightLeg
    
    glBindTexture( GL_TEXTURE_2D, textures[3] );
    glUniform1i( glGetUniformLocation(program, "texture_on"), true );
    
    SetMaterial(vec4(0.4, 0.4, 0.4, 1.0), vec4(0.94, 0.95, 0.95, 1.0), vec4(0.2, 0.2, 0.2, 1.0), 1.0);
    glUniform1i( glGetUniformLocation(program, "light_out"), false );
    
    transform = Translate( 2.5, 0.2, -8.0 + grass1 ) * Scale(0.5, 0.4, 0.05);
    glUniformMatrix4fv( glGetUniformLocation( program, "model" ), 1, GL_TRUE, transform );
    
    glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(CUBE_OFFSET) );
    glVertexAttribPointer( vNormal, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(CUBE_NORMALS_OFFSET) );
    glVertexAttribPointer( vTexCoord, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(CUBE_TEXCOORDS_OFFSET) );
    glDrawArrays( GL_TRIANGLES, 0, NumVerticesCube );
    
    
    
    //---- BenchBack
    
    glBindTexture( GL_TEXTURE_2D, textures[4] );
    glUniform1i( glGetUniformLocation(program, "texture_on"), true );
    
    SetMaterial(vec4(0.4, 0.4, 0.4, 1.0), vec4(0.94, 0.95, 0.95, 1.0), vec4(0.2, 0.2, 0.2, 1.0), 1.0);
    glUniform1i( glGetUniformLocation(program, "light_out"), false );
    
    transform = Translate( 2.75, 0.3, -7.5 + grass1 ) * Scale(0.05, 0.5, 1.05);
    glUniformMatrix4fv( glGetUniformLocation( program, "model" ), 1, GL_TRUE, transform );
    
    glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(CUBE_OFFSET) );
    glVertexAttribPointer( vNormal, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(CUBE_NORMALS_OFFSET) );
    glVertexAttribPointer( vTexCoord, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(CUBE_TEXCOORDS_OFFSET) );
    glDrawArrays( GL_TRIANGLES, 0, NumVerticesCube );
    
    
    
    
    
    
    
    
    
    
    //  ----------    GUY 1(SKATER)   -------
    //---- Body
    
    glBindTexture( GL_TEXTURE_2D, textures[7] );
    glUniform1i( glGetUniformLocation(program, "texture_on"), true );
    
    SetMaterial(vec4(0.4, 0.4, 0.4, 1.0), vec4(0.98, 0.98, 0.98, 1.0), vec4(0.2, 0.2, 0.2, 1.0), 1.0);
    glUniform1i( glGetUniformLocation(program, "light_out"), false );
    
    transform = RotateX(thetaX) * RotateY(thetaY) * Translate( 0.0 + boardX, 0.6 + boardY, 0.2 + boardZ ) * Scale(0.1, 0.35, 0.2);
    glUniformMatrix4fv( glGetUniformLocation( program, "model" ), 1, GL_TRUE, transform );
    
    glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(CUBE_OFFSET) );
    glVertexAttribPointer( vNormal, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(CUBE_NORMALS_OFFSET) );
    glVertexAttribPointer( vTexCoord, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(CUBE_TEXCOORDS_OFFSET) );
    glDrawArrays( GL_TRIANGLES, 0, NumVerticesCube );
    
    
    // ---- Leg1
    
    glBindTexture( GL_TEXTURE_2D, textures[0] );
    glUniform1i( glGetUniformLocation(program, "texture_on"), false );
    
    SetMaterial(vec4(0.4, 0.4, 0.4, 1.0), vec4(0.0, 0.0, 0.0, 1.0), vec4(0.2, 0.2, 0.2, 1.0), 1.0);
    glUniform1i( glGetUniformLocation(program, "light_out"), false );
    
    transform = RotateX(thetaX) * RotateY(thetaY) * Translate( 0.0 + boardX, 0.3 + boardY, 0.25 + boardZ ) * Scale(0.05, 0.25, 0.05);
    glUniformMatrix4fv( glGetUniformLocation( program, "model" ), 1, GL_TRUE, transform );
    
    glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(CYLINDER_OFFSET) );
    glVertexAttribPointer( vNormal, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(CYLINDER_NORMALS_OFFSET) );
    glDrawArrays( GL_TRIANGLES, 0, NumVerticesCylinder );
    
    
    // ---- Leg2
    
    glUniform1i( glGetUniformLocation(program, "texture_on"), false );
    
    SetMaterial(vec4(0.4, 0.4, 0.4, 1.0), vec4(0.0, 0.0, 0.0, 1.0), vec4(0.2, 0.2, 0.2, 1.0), 1.0);
    glUniform1i( glGetUniformLocation(program, "light_out"), false );
    
    transform = RotateX(thetaX) * RotateY(thetaY) * Translate( 0.0 + boardX, 0.3 + boardY, 0.15 + boardZ ) * Scale(0.05, 0.25, 0.05);
    glUniformMatrix4fv( glGetUniformLocation( program, "model" ), 1, GL_TRUE, transform );
    
    glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(CYLINDER_OFFSET) );
    glVertexAttribPointer( vNormal, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(CYLINDER_NORMALS_OFFSET) );
    glDrawArrays( GL_TRIANGLES, 0, NumVerticesCylinder );
    
    
    
    // ---- Arm1
    
    glBindTexture( GL_TEXTURE_2D, textures[7] );
    glUniform1i( glGetUniformLocation(program, "texture_on"), true );
    
    SetMaterial(vec4(0.4, 0.4, 0.4, 1.0), vec4(0.0, 0.0, 0.0, 1.0), vec4(0.2, 0.2, 0.2, 1.0), 1.0);
    glUniform1i( glGetUniformLocation(program, "light_out"), false );
    
    transform = RotateX(thetaX) * RotateY(thetaY) * Translate( 0.0 + boardX, 0.6 + boardY, 0.35 + boardZ ) *  RotateX(-45) * Scale(0.05, 0.25, 0.05);
    glUniformMatrix4fv( glGetUniformLocation( program, "model" ), 1, GL_TRUE, transform );
    
    glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(CYLINDER_OFFSET) );
    glVertexAttribPointer( vNormal, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(CYLINDER_NORMALS_OFFSET) );
    glDrawArrays( GL_TRIANGLES, 0, NumVerticesCylinder );
    
    
    
    // ---- Arm2
    
    glBindTexture( GL_TEXTURE_2D, textures[7] );
    glUniform1i( glGetUniformLocation(program, "texture_on"), true );
    
    SetMaterial(vec4(0.4, 0.4, 0.4, 1.0), vec4(0.0, 0.0, 0.0, 1.0), vec4(0.2, 0.2, 0.2, 1.0), 1.0);
    glUniform1i( glGetUniformLocation(program, "light_out"), false );
    
    transform = RotateX(thetaX) * RotateY(thetaY) * Translate( 0.0 + boardX, 0.6 + boardY, 0.05 + boardZ ) * RotateX(45) * Scale(0.05, 0.25, 0.05);
    glUniformMatrix4fv( glGetUniformLocation( program, "model" ), 1, GL_TRUE, transform );
    
    glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(CYLINDER_OFFSET) );
    glVertexAttribPointer( vNormal, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(CYLINDER_NORMALS_OFFSET) );
    glDrawArrays( GL_TRIANGLES, 0, NumVerticesCylinder );
    
    
    
    //---- Head
    
    glBindTexture( GL_TEXTURE_2D, textures[0] );
    glUniform1i( glGetUniformLocation(program, "texture_on"), true );
    
    SetMaterial( vec4(0.4, 0.4, 0.4, 1.0), vec4(0.985, 0.985, 0.985, 1.0), vec4(0.2, 0.2, 0.2, 1.0), 1.0);
    glUniform1i( glGetUniformLocation(program, "light_out"), false );
    
    mat4 transform_bube3 = RotateX(thetaX) * RotateY(thetaY) * Translate( 0.0 + boardX, 0.9 + boardY, 0.2 + boardZ ) *  Scale(0.25, 0.25, 0.25) * RotateY(180);
    glUniformMatrix4fv( glGetUniformLocation( program, "model" ), 1, GL_TRUE, transform_bube3 );
    
    glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(SPHERE_OFFSET) );
    glVertexAttribPointer( vNormal, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(SPHERE_NORMALS_OFFSET) );
    glVertexAttribPointer( vTexCoord, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(SPHERE_TEXCOORDS_OFFSET) );
    glDrawArrays( GL_TRIANGLES, 0, NumVerticesSphere );
    
    
    
    
    
    
    
    
    
    
    
    //  ----------    GUY 2   -------
    //---- Body
    
    glBindTexture( GL_TEXTURE_2D, textures[12] );
    glUniform1i( glGetUniformLocation(program, "texture_on"), true );
    
    SetMaterial(vec4(0.4, 0.4, 0.4, 1.0), vec4(0.98, 0.98, 0.98, 1.0), vec4(0.2, 0.2, 0.2, 1.0), 1.0);
    glUniform1i( glGetUniformLocation(program, "light_out"), false );
    
    transform = Translate( -2.75, 0.425, -13.5 + grass1 ) * Scale(0.1, 0.35, 0.2);
    glUniformMatrix4fv( glGetUniformLocation( program, "model" ), 1, GL_TRUE, transform );
    
    glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(CUBE_OFFSET) );
    glVertexAttribPointer( vNormal, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(CUBE_NORMALS_OFFSET) );
    glVertexAttribPointer( vTexCoord, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(CUBE_TEXCOORDS_OFFSET) );
    glDrawArrays( GL_TRIANGLES, 0, NumVerticesCube );
    
    
    // ---- Leg1
    
    glBindTexture( GL_TEXTURE_2D, textures[0] );
    glUniform1i( glGetUniformLocation(program, "texture_on"), false );
    
    SetMaterial(vec4(0.4, 0.4, 0.4, 1.0), vec4(0.0, 0.0, 0.0, 1.0), vec4(0.2, 0.2, 0.2, 1.0), 1.0);
    glUniform1i( glGetUniformLocation(program, "light_out"), false );
    
    transform = Translate( -2.75, 0.125, -13.6 + grass1 ) * Scale(0.05, 0.25, 0.05);
    glUniformMatrix4fv( glGetUniformLocation( program, "model" ), 1, GL_TRUE, transform );
    
    glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(CYLINDER_OFFSET) );
    glVertexAttribPointer( vNormal, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(CYLINDER_NORMALS_OFFSET) );
    glDrawArrays( GL_TRIANGLES, 0, NumVerticesCylinder );
    
    
    // ---- Leg2
    
    glUniform1i( glGetUniformLocation(program, "texture_on"), false );
    
    SetMaterial(vec4(0.4, 0.4, 0.4, 1.0), vec4(0.0, 0.0, 0.0, 1.0), vec4(0.2, 0.2, 0.2, 1.0), 1.0);
    glUniform1i( glGetUniformLocation(program, "light_out"), false );
    
    transform = Translate( -2.75, 0.125, -13.4 + grass1 ) * Scale(0.05, 0.25, 0.05);
    glUniformMatrix4fv( glGetUniformLocation( program, "model" ), 1, GL_TRUE, transform );
    
    glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(CYLINDER_OFFSET) );
    glVertexAttribPointer( vNormal, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(CYLINDER_NORMALS_OFFSET) );
    glDrawArrays( GL_TRIANGLES, 0, NumVerticesCylinder );
    
    
    
    // ---- Arm1
    
    glBindTexture( GL_TEXTURE_2D, textures[7] );
    glUniform1i( glGetUniformLocation(program, "texture_on"), true );
    
    SetMaterial(vec4(0.4, 0.4, 0.4, 1.0), vec4(0.0, 0.0, 0.0, 1.0), vec4(0.2, 0.2, 0.2, 1.0), 1.0);
    glUniform1i( glGetUniformLocation(program, "light_out"), false );
    
    transform = Translate( -2.75, 0.6, -13.625 + grass1 ) *  RotateX(-55) * Scale(0.05, 0.30, 0.05);
    glUniformMatrix4fv( glGetUniformLocation( program, "model" ), 1, GL_TRUE, transform );
    
    glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(CYLINDER_OFFSET) );
    glVertexAttribPointer( vNormal, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(CYLINDER_NORMALS_OFFSET) );
    glDrawArrays( GL_TRIANGLES, 0, NumVerticesCylinder );
    
    
    
    // ---- Arm2
    
    glBindTexture( GL_TEXTURE_2D, textures[7] );
    glUniform1i( glGetUniformLocation(program, "texture_on"), true );
    
    SetMaterial(vec4(0.4, 0.4, 0.4, 1.0), vec4(0.0, 0.0, 0.0, 1.0), vec4(0.2, 0.2, 0.2, 1.0), 1.0);
    glUniform1i( glGetUniformLocation(program, "light_out"), false );
    
    transform = Translate( -2.75, 0.6, -13.375 + grass1 ) * RotateX(55) * Scale(0.05, 0.30, 0.05);
    glUniformMatrix4fv( glGetUniformLocation( program, "model" ), 1, GL_TRUE, transform );
    
    glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(CYLINDER_OFFSET) );
    glVertexAttribPointer( vNormal, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(CYLINDER_NORMALS_OFFSET) );
    glDrawArrays( GL_TRIANGLES, 0, NumVerticesCylinder );
    
    
    
    //---- Head
    
    glBindTexture( GL_TEXTURE_2D, textures[8] );
    glUniform1i( glGetUniformLocation(program, "texture_on"), true );
    
    SetMaterial( vec4(0.4, 0.4, 0.4, 1.0), vec4(0.985, 0.985, 0.985, 1.0), vec4(0.2, 0.2, 0.2, 1.0), 1.0);
    glUniform1i( glGetUniformLocation(program, "light_out"), false );
    
    transform_bube3 = Translate( -2.75, 0.725, -13.5 + grass1 ) *  Scale(0.25, 0.25, 0.25) * RotateY(180);
    glUniformMatrix4fv( glGetUniformLocation( program, "model" ), 1, GL_TRUE, transform_bube3 );
    
    glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(SPHERE_OFFSET) );
    glVertexAttribPointer( vNormal, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(SPHERE_NORMALS_OFFSET) );
    glVertexAttribPointer( vTexCoord, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(SPHERE_TEXCOORDS_OFFSET) );
    glDrawArrays( GL_TRIANGLES, 0, NumVerticesSphere );
    
    
    
    
    
    
    
    
    
    
    
    //  ----------    GUY 3   -------
    //---- Body
    
    glBindTexture( GL_TEXTURE_2D, textures[13] );
    glUniform1i( glGetUniformLocation(program, "texture_on"), true );
    
    SetMaterial(vec4(0.4, 0.4, 0.4, 1.0), vec4(0.98, 0.98, 0.98, 1.0), vec4(0.2, 0.2, 0.2, 1.0), 1.0);
    glUniform1i( glGetUniformLocation(program, "light_out"), false );
    
    transform = Translate( -2.75, 0.425, -12.5 + grass1 ) * Scale(0.1, 0.35, 0.2);
    glUniformMatrix4fv( glGetUniformLocation( program, "model" ), 1, GL_TRUE, transform );
    
    glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(CUBE_OFFSET) );
    glVertexAttribPointer( vNormal, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(CUBE_NORMALS_OFFSET) );
    glVertexAttribPointer( vTexCoord, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(CUBE_TEXCOORDS_OFFSET) );
    glDrawArrays( GL_TRIANGLES, 0, NumVerticesCube );
    
    
    // ---- Leg1
    
    glBindTexture( GL_TEXTURE_2D, textures[0] );
    glUniform1i( glGetUniformLocation(program, "texture_on"), false );
    
    SetMaterial(vec4(0.4, 0.4, 0.4, 1.0), vec4(0.0, 0.0, 0.0, 1.0), vec4(0.2, 0.2, 0.2, 1.0), 1.0);
    glUniform1i( glGetUniformLocation(program, "light_out"), false );
    
    transform = Translate( -2.75, 0.125, -12.6 + grass1 ) * Scale(0.05, 0.25, 0.05);
    glUniformMatrix4fv( glGetUniformLocation( program, "model" ), 1, GL_TRUE, transform );
    
    glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(CYLINDER_OFFSET) );
    glVertexAttribPointer( vNormal, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(CYLINDER_NORMALS_OFFSET) );
    glDrawArrays( GL_TRIANGLES, 0, NumVerticesCylinder );
    
    
    // ---- Leg2
    
    glUniform1i( glGetUniformLocation(program, "texture_on"), false );
    
    SetMaterial(vec4(0.4, 0.4, 0.4, 1.0), vec4(0.0, 0.0, 0.0, 1.0), vec4(0.2, 0.2, 0.2, 1.0), 1.0);
    glUniform1i( glGetUniformLocation(program, "light_out"), false );
    
    transform = Translate( -2.75, 0.125, -12.4 + grass1 ) * Scale(0.05, 0.25, 0.05);
    glUniformMatrix4fv( glGetUniformLocation( program, "model" ), 1, GL_TRUE, transform );
    
    glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(CYLINDER_OFFSET) );
    glVertexAttribPointer( vNormal, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(CYLINDER_NORMALS_OFFSET) );
    glDrawArrays( GL_TRIANGLES, 0, NumVerticesCylinder );
    
    
    
    // ---- Arm1
    
    glBindTexture( GL_TEXTURE_2D, textures[7] );
    glUniform1i( glGetUniformLocation(program, "texture_on"), true );
    
    SetMaterial(vec4(0.4, 0.4, 0.4, 1.0), vec4(0.0, 0.0, 0.0, 1.0), vec4(0.2, 0.2, 0.2, 1.0), 1.0);
    glUniform1i( glGetUniformLocation(program, "light_out"), false );
    
    transform = Translate( -2.75, 0.6, -12.625 + grass1 ) *  RotateX(-55) * Scale(0.05, 0.30, 0.05);
    glUniformMatrix4fv( glGetUniformLocation( program, "model" ), 1, GL_TRUE, transform );
    
    glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(CYLINDER_OFFSET) );
    glVertexAttribPointer( vNormal, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(CYLINDER_NORMALS_OFFSET) );
    glDrawArrays( GL_TRIANGLES, 0, NumVerticesCylinder );
    
    
    
    // ---- Arm2
    
    glBindTexture( GL_TEXTURE_2D, textures[7] );
    glUniform1i( glGetUniformLocation(program, "texture_on"), true );
    
    SetMaterial(vec4(0.4, 0.4, 0.4, 1.0), vec4(0.0, 0.0, 0.0, 1.0), vec4(0.2, 0.2, 0.2, 1.0), 1.0);
    glUniform1i( glGetUniformLocation(program, "light_out"), false );
    
    transform = Translate( -2.75, 0.6, -12.375 + grass1 ) * RotateX(55) * Scale(0.05, 0.30, 0.05);
    glUniformMatrix4fv( glGetUniformLocation( program, "model" ), 1, GL_TRUE, transform );
    
    glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(CYLINDER_OFFSET) );
    glVertexAttribPointer( vNormal, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(CYLINDER_NORMALS_OFFSET) );
    glDrawArrays( GL_TRIANGLES, 0, NumVerticesCylinder );
    
    
    
    //---- Head
    
    glBindTexture( GL_TEXTURE_2D, textures[9] );
    glUniform1i( glGetUniformLocation(program, "texture_on"), true );
    
    SetMaterial( vec4(0.4, 0.4, 0.4, 1.0), vec4(0.985, 0.985, 0.985, 1.0), vec4(0.2, 0.2, 0.2, 1.0), 1.0);
    glUniform1i( glGetUniformLocation(program, "light_out"), false );
    
    transform_bube3 = Translate( -2.75, 0.725, -12.5 + grass1 ) *  Scale(0.25, 0.25, 0.25) * RotateY(180);
    glUniformMatrix4fv( glGetUniformLocation( program, "model" ), 1, GL_TRUE, transform_bube3 );
    
    glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(SPHERE_OFFSET) );
    glVertexAttribPointer( vNormal, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(SPHERE_NORMALS_OFFSET) );
    glVertexAttribPointer( vTexCoord, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(SPHERE_TEXCOORDS_OFFSET) );
    glDrawArrays( GL_TRIANGLES, 0, NumVerticesSphere );
    
    
    
    
    
    
    
    
    
    
    
    
    
    //  ----------    GUY 4   -------
    //---- Body
    
    glBindTexture( GL_TEXTURE_2D, textures[14] );
    glUniform1i( glGetUniformLocation(program, "texture_on"), true );
    
    SetMaterial(vec4(0.4, 0.4, 0.4, 1.0), vec4(0.98, 0.98, 0.98, 1.0), vec4(0.2, 0.2, 0.2, 1.0), 1.0);
    glUniform1i( glGetUniformLocation(program, "light_out"), false );
    
    transform = Translate( -2.75, 0.425, -11.5 + grass1 ) * Scale(0.1, 0.35, 0.2);
    glUniformMatrix4fv( glGetUniformLocation( program, "model" ), 1, GL_TRUE, transform );
    
    glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(CUBE_OFFSET) );
    glVertexAttribPointer( vNormal, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(CUBE_NORMALS_OFFSET) );
    glVertexAttribPointer( vTexCoord, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(CUBE_TEXCOORDS_OFFSET) );
    glDrawArrays( GL_TRIANGLES, 0, NumVerticesCube );
    
    
    // ---- Leg1
    
    glBindTexture( GL_TEXTURE_2D, textures[0] );
    glUniform1i( glGetUniformLocation(program, "texture_on"), false );
    
    SetMaterial(vec4(0.4, 0.4, 0.4, 1.0), vec4(0.0, 0.0, 0.0, 1.0), vec4(0.2, 0.2, 0.2, 1.0), 1.0);
    glUniform1i( glGetUniformLocation(program, "light_out"), false );
    
    transform = Translate( -2.75, 0.125, -11.6 + grass1 ) * Scale(0.05, 0.25, 0.05);
    glUniformMatrix4fv( glGetUniformLocation( program, "model" ), 1, GL_TRUE, transform );
    
    glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(CYLINDER_OFFSET) );
    glVertexAttribPointer( vNormal, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(CYLINDER_NORMALS_OFFSET) );
    glDrawArrays( GL_TRIANGLES, 0, NumVerticesCylinder );
    
    
    // ---- Leg2
    
    glUniform1i( glGetUniformLocation(program, "texture_on"), false );
    
    SetMaterial(vec4(0.4, 0.4, 0.4, 1.0), vec4(0.0, 0.0, 0.0, 1.0), vec4(0.2, 0.2, 0.2, 1.0), 1.0);
    glUniform1i( glGetUniformLocation(program, "light_out"), false );
    
    transform = Translate( -2.75, 0.125, -11.4 + grass1 ) * Scale(0.05, 0.25, 0.05);
    glUniformMatrix4fv( glGetUniformLocation( program, "model" ), 1, GL_TRUE, transform );
    
    glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(CYLINDER_OFFSET) );
    glVertexAttribPointer( vNormal, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(CYLINDER_NORMALS_OFFSET) );
    glDrawArrays( GL_TRIANGLES, 0, NumVerticesCylinder );
    
    
    
    // ---- Arm1
    
    glBindTexture( GL_TEXTURE_2D, textures[7] );
    glUniform1i( glGetUniformLocation(program, "texture_on"), true );
    
    SetMaterial(vec4(0.4, 0.4, 0.4, 1.0), vec4(0.0, 0.0, 0.0, 1.0), vec4(0.2, 0.2, 0.2, 1.0), 1.0);
    glUniform1i( glGetUniformLocation(program, "light_out"), false );
    
    transform = Translate( -2.75, 0.6, -11.625 + grass1 ) *  RotateX(-55) * Scale(0.05, 0.30, 0.05);
    glUniformMatrix4fv( glGetUniformLocation( program, "model" ), 1, GL_TRUE, transform );
    
    glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(CYLINDER_OFFSET) );
    glVertexAttribPointer( vNormal, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(CYLINDER_NORMALS_OFFSET) );
    glDrawArrays( GL_TRIANGLES, 0, NumVerticesCylinder );
    
    
    
    // ---- Arm2
    
    glBindTexture( GL_TEXTURE_2D, textures[7] );
    glUniform1i( glGetUniformLocation(program, "texture_on"), true );
    
    SetMaterial(vec4(0.4, 0.4, 0.4, 1.0), vec4(0.0, 0.0, 0.0, 1.0), vec4(0.2, 0.2, 0.2, 1.0), 1.0);
    glUniform1i( glGetUniformLocation(program, "light_out"), false );
    
    transform = Translate( -2.75, 0.6, -11.375 + grass1 ) * RotateX(55) * Scale(0.05, 0.30, 0.05);
    glUniformMatrix4fv( glGetUniformLocation( program, "model" ), 1, GL_TRUE, transform );
    
    glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(CYLINDER_OFFSET) );
    glVertexAttribPointer( vNormal, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(CYLINDER_NORMALS_OFFSET) );
    glDrawArrays( GL_TRIANGLES, 0, NumVerticesCylinder );
    
    
    
    //---- Head
    
    glBindTexture( GL_TEXTURE_2D, textures[10] );
    glUniform1i( glGetUniformLocation(program, "texture_on"), true );
    
    SetMaterial( vec4(0.4, 0.4, 0.4, 1.0), vec4(0.985, 0.985, 0.985, 1.0), vec4(0.2, 0.2, 0.2, 1.0), 1.0);
    glUniform1i( glGetUniformLocation(program, "light_out"), false );
    
    transform_bube3 = Translate( -2.75, 0.725, -11.5 + grass1 ) *  Scale(0.25, 0.25, 0.25) * RotateY(180);
    glUniformMatrix4fv( glGetUniformLocation( program, "model" ), 1, GL_TRUE, transform_bube3 );
    
    glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(SPHERE_OFFSET) );
    glVertexAttribPointer( vNormal, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(SPHERE_NORMALS_OFFSET) );
    glVertexAttribPointer( vTexCoord, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(SPHERE_TEXCOORDS_OFFSET) );
    glDrawArrays( GL_TRIANGLES, 0, NumVerticesSphere );
    
    
    
    
    
    
    
    
    
    
    //  ----------    GUY 5   -------
    //---- Body
    
    glBindTexture( GL_TEXTURE_2D, textures[15] );
    glUniform1i( glGetUniformLocation(program, "texture_on"), true );
    
    SetMaterial(vec4(0.4, 0.4, 0.4, 1.0), vec4(0.98, 0.98, 0.98, 1.0), vec4(0.2, 0.2, 0.2, 1.0), 1.0);
    glUniform1i( glGetUniformLocation(program, "light_out"), false );
    
    transform = Translate( -2.75, 0.425, -10.5 + grass1 ) * Scale(0.1, 0.35, 0.2);
    glUniformMatrix4fv( glGetUniformLocation( program, "model" ), 1, GL_TRUE, transform );
    
    glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(CUBE_OFFSET) );
    glVertexAttribPointer( vNormal, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(CUBE_NORMALS_OFFSET) );
    glVertexAttribPointer( vTexCoord, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(CUBE_TEXCOORDS_OFFSET) );
    glDrawArrays( GL_TRIANGLES, 0, NumVerticesCube );
    
    
    // ---- Leg1
    
    glBindTexture( GL_TEXTURE_2D, textures[0] );
    glUniform1i( glGetUniformLocation(program, "texture_on"), false );
    
    SetMaterial(vec4(0.4, 0.4, 0.4, 1.0), vec4(0.0, 0.0, 0.0, 1.0), vec4(0.2, 0.2, 0.2, 1.0), 1.0);
    glUniform1i( glGetUniformLocation(program, "light_out"), false );
    
    transform = Translate( -2.75, 0.125, -10.6 + grass1 ) * Scale(0.05, 0.25, 0.05);
    glUniformMatrix4fv( glGetUniformLocation( program, "model" ), 1, GL_TRUE, transform );
    
    glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(CYLINDER_OFFSET) );
    glVertexAttribPointer( vNormal, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(CYLINDER_NORMALS_OFFSET) );
    glDrawArrays( GL_TRIANGLES, 0, NumVerticesCylinder );
    
    
    // ---- Leg2
    
    glUniform1i( glGetUniformLocation(program, "texture_on"), false );
    
    SetMaterial(vec4(0.4, 0.4, 0.4, 1.0), vec4(0.0, 0.0, 0.0, 1.0), vec4(0.2, 0.2, 0.2, 1.0), 1.0);
    glUniform1i( glGetUniformLocation(program, "light_out"), false );
    
    transform = Translate( -2.75, 0.125, -10.4 + grass1 ) * Scale(0.05, 0.25, 0.05);
    glUniformMatrix4fv( glGetUniformLocation( program, "model" ), 1, GL_TRUE, transform );
    
    glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(CYLINDER_OFFSET) );
    glVertexAttribPointer( vNormal, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(CYLINDER_NORMALS_OFFSET) );
    glDrawArrays( GL_TRIANGLES, 0, NumVerticesCylinder );
    
    
    
    // ---- Arm1
    
    glBindTexture( GL_TEXTURE_2D, textures[7] );
    glUniform1i( glGetUniformLocation(program, "texture_on"), true );
    
    SetMaterial(vec4(0.4, 0.4, 0.4, 1.0), vec4(0.0, 0.0, 0.0, 1.0), vec4(0.2, 0.2, 0.2, 1.0), 1.0);
    glUniform1i( glGetUniformLocation(program, "light_out"), false );
    
    transform = Translate( -2.75, 0.6, -10.625 + grass1 ) *  RotateX(-55) * Scale(0.05, 0.30, 0.05);
    glUniformMatrix4fv( glGetUniformLocation( program, "model" ), 1, GL_TRUE, transform );
    
    glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(CYLINDER_OFFSET) );
    glVertexAttribPointer( vNormal, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(CYLINDER_NORMALS_OFFSET) );
    glDrawArrays( GL_TRIANGLES, 0, NumVerticesCylinder );
    
    
    
    // ---- Arm2
    
    glBindTexture( GL_TEXTURE_2D, textures[7] );
    glUniform1i( glGetUniformLocation(program, "texture_on"), true );
    
    SetMaterial(vec4(0.4, 0.4, 0.4, 1.0), vec4(0.0, 0.0, 0.0, 1.0), vec4(0.2, 0.2, 0.2, 1.0), 1.0);
    glUniform1i( glGetUniformLocation(program, "light_out"), false );
    
    transform = Translate( -2.75, 0.6, -10.375 + grass1 ) * RotateX(55) * Scale(0.05, 0.30, 0.05);
    glUniformMatrix4fv( glGetUniformLocation( program, "model" ), 1, GL_TRUE, transform );
    
    glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(CYLINDER_OFFSET) );
    glVertexAttribPointer( vNormal, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(CYLINDER_NORMALS_OFFSET) );
    glDrawArrays( GL_TRIANGLES, 0, NumVerticesCylinder );
    
    
    
    //---- Head
    
    glBindTexture( GL_TEXTURE_2D, textures[11] );
    glUniform1i( glGetUniformLocation(program, "texture_on"), true );
    
    SetMaterial( vec4(0.4, 0.4, 0.4, 1.0), vec4(0.985, 0.985, 0.985, 1.0), vec4(0.2, 0.2, 0.2, 1.0), 1.0);
    glUniform1i( glGetUniformLocation(program, "light_out"), false );
    
    transform_bube3 = Translate( -2.75, 0.725, -10.5 + grass1 ) *  Scale(0.25, 0.25, 0.25) * RotateY(180);
    glUniformMatrix4fv( glGetUniformLocation( program, "model" ), 1, GL_TRUE, transform_bube3 );
    
    glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(SPHERE_OFFSET) );
    glVertexAttribPointer( vNormal, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(SPHERE_NORMALS_OFFSET) );
    glVertexAttribPointer( vTexCoord, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(SPHERE_TEXCOORDS_OFFSET) );
    glDrawArrays( GL_TRIANGLES, 0, NumVerticesSphere );

    
    
    
    
    
    
    
    
    
    //---- Sky Sphere
    
    glBindTexture( GL_TEXTURE_2D, textures[6] );
    glUniform1i( glGetUniformLocation(program, "texture_on"), true );
    
    SetMaterial( vec4(0.4, 0.4, 0.4, 1.0), vec4(0.925, 0.925, 0.925, 1.0), vec4(0.2, 0.2, 0.2, 1.0), 1.0);
    glUniform1i( glGetUniformLocation(program, "light_out"), true );
    
    mat4 transform_bube4 = Translate( 0.0, 6.0, 0.0 ) * Scale(25.0, 25.0, 25.0);
    glUniformMatrix4fv( glGetUniformLocation( program, "model" ), 1, GL_TRUE, transform_bube4 );
    
    glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(SPHERE_OFFSET) );
    glVertexAttribPointer( vNormal, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(SPHERE_NORMALS_OFFSET) );
    glVertexAttribPointer( vTexCoord, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(SPHERE_TEXCOORDS_OFFSET) );
    glDrawArrays( GL_TRIANGLES, 0, NumVerticesSphere );
    
    
    
    
    glutSwapBuffers();
}




//----------------------------------------------------------------------------

enum Trick {ollie=0,kickflip=1,shoveIt=2};
enum Grind {boardSlide = 0, fiveOh = 1};
Grind railGrind = fiveOh;
Trick entryTrick = kickflip;
Trick exitTrick = shoveIt;
float popAngle = 30;
float counter = 0;
bool postReached = false, grind = false, enterGrind = false, grindStart = false, exitGrind = false, endReached = false;
bool skateForward = false, skateBackwards = false, skateRight = false, skateLeft = false;
bool doShoveIt = false, shoveItReached = false, doNinety = false;
bool doKickflip = false;
bool doOllie = false, doPop = false, ollieReached = false, ollieDone = false;
bool doManual = false, manualReached = false, manualDone = false;
void keyboard( unsigned char key, int x, int y ){
    switch( key ) {
        case 033:    // Escape key
        case 'q': case 'Q':
            exit( EXIT_SUCCESS );
            break;
            
        case 'y':    //---- theta
            Axis = Yaxis;
            Theta3[Axis] += 4.0;
            Theta3[Axis] = fmod(Theta3[Axis], 360.0);
            glutPostRedisplay();
            break;
            
        case 'Y':    //---- theta
            Axis = Yaxis;
            Theta3[Axis] -= 4.0;
            Theta3[Axis] = fmod(Theta3[Axis], 360.0);
            glutPostRedisplay();
            break;
            
        case 'z':    //---- phi
            Axis = Zaxis;
            Theta3[Axis] += 4.0;
            Theta3[Axis] = fmod(Theta3[Axis], 360.0);
            glutPostRedisplay();
            break;
            
        case 'Z':    //---- phi
            Axis = Zaxis;
            Theta3[Axis] -= 4.0;
            Theta3[Axis] = fmod(Theta3[Axis], 360.0);
            glutPostRedisplay();
            break;
            
        case 'r':    //---- increase radius
            r += 0.5;
            glutPostRedisplay();
            break;
            
        case 'R':    //---- decrease radius
            r -= 0.5;
            glutPostRedisplay();
            break;
            
        case 'u':
            //view_matrix = default_view_matrix;
            Theta3[Xaxis] = 0.0;
            Theta3[Yaxis] = 0.0;
            Theta3[Zaxis] = 0.0;
            glutPostRedisplay();
            break;
            
        case 'k':  // kickflip
            doOllie = true;
            doPop = true;
            ollieReached = false;
            ollieDone = false;
            doKickflip = true;
            glutPostRedisplay();
            break;
            
        case 'm':   // manual
            doManual = true;
            manualReached = false;
            manualDone = false;
            glutPostRedisplay();
            break;
            
        case 'o':  // ollie
            doOllie = true;
            doPop = true;
            ollieReached = false;
            ollieDone = false;
            glutPostRedisplay();
            break;
            
        case 'P': // pedal forward
            skateForward = true;
            skateBackwards = false;
            glutPostRedisplay();
            break;
            
        case '1':  // ollie in, kickflip out
            entryTrick = ollie;
            exitTrick = kickflip;
            enterGrind = true;
            glutPostRedisplay();
            break;
            
        case '2': // ollie in, shoveIt out
            //skateForward = true;
            entryTrick = ollie;
            exitTrick = shoveIt;
            enterGrind = true;
            glutPostRedisplay();
            break;
            
        case '3': // shoveIt in, kickflip out
            entryTrick = shoveIt;
            exitTrick = kickflip;
            enterGrind = true;
            glutPostRedisplay();
            break;
            
            
    }
}




//----------------------------------------------------------------------------

void mouse( int button, int state, int x, int y ){
    if ( state == GLUT_DOWN ) {
        switch( button ) {
            case GLUT_LEFT_BUTTON:    Axis = Xaxis;  break;
            case GLUT_MIDDLE_BUTTON:  Axis = Yaxis;  break;
            case GLUT_RIGHT_BUTTON:   Axis = Zaxis;  break;
        }
    }
}

//----------------------------------------------------------------------------

void idle( void ){
    Theta4[Xaxis] = fmod(Theta4[Xaxis]+0.5, 360.0);
    
    
    if (grass1 < -25.0){
        grass1 = 34.85;
    } else {
        grass1 -= 0.075;
    }
    
    
    
    if (grass2 < -25.0){
        grass2 = 34.85;
    } else {
        grass2 -= 0.075;
    }
    
    
    
    
    float frontBoundary = 4.0;
    float rearBoundary = -3.0;
    float step = 0.1/10;
    float oneRadian = M_PI/180;
    
    
    float boardToRailDifference = (farPostZ+grass1) - (boardZ+zOffset);
    if (boardToRailDifference > 0 && boardToRailDifference <= 4.0  && enterGrind)
    {
        grind = true;
        enterGrind = false;
        postReached = true;
        switch(entryTrick)
        {
            case shoveIt:
            {
                doShoveIt = true;
                doOllie = true;
                doPop = true;
                ollieReached = false;
                ollieDone = false;
                break;
            }
            case kickflip:
            {
                doKickflip = true;
            }
            case ollie:
            {
                doOllie = true;
                doPop = true;
                ollieReached = false;
                ollieDone = false;
                break;
            }
        }
        if (railGrind == boardSlide)
        {
            doShoveIt = true;
            doNinety = true;
            shoveItReached = false;
        }
        grindStart = false;
        endReached = false;
        exitGrind = false;
    }
    if (postReached && !doPop)
    {
        if (railGrind == boardSlide && boardY-railY <= 0)
        {
            switch(entryTrick)
            {
                case shoveIt:
                {
                    doShoveIt = false;
                    doOllie = false;
                    doPop = false;
                    ollieReached = true;
                    ollieDone = true;
                    break;
                }
                case kickflip:
                {
                    doKickflip = false;
                }
                case ollie:
                {
                    doOllie = false;
                    doPop = false;
                    ollieReached = true;
                    ollieDone = true;
                    break;
                }
            }
            grindStart = true;
        }
        else if (railGrind != boardSlide && frontTrAxY-railY <= 0)
        {
            switch(entryTrick)
            {
                case shoveIt:
                {
                    doShoveIt = false;
                    doOllie = false;
                    doPop = false;
                    ollieReached = true;
                    ollieDone = true;
                    break;
                }
                case kickflip:
                {
                    doKickflip = false;
                }
                case ollie:
                {
                    doOllie = false;
                    doPop = false;
                    ollieReached = true;
                    ollieDone = true;
                    break;
                }
            }
            grindStart = true;
            doManual = true;
            manualReached = false;
            manualDone = false;
            postReached = false;
        }
    }
    if (grindStart && !endReached)
    {
        float truckToRailEndDifference = nearPostZ + (grass1+frontTrAxZ);
        if (truckToRailEndDifference > 0 && truckToRailEndDifference <= 1.5)
        {
            grindStart = false;
            endReached = true;
            doManual=false;
            manualDone = true;
            manualReached = true;
        }
    }
    if (endReached)
    {
        endReached = false;
        exitGrind = true;
        postReached = false;
        grindStart = false;
        switch(exitTrick)
        {
            case shoveIt:
            {
                doShoveIt = true;
                doOllie = true;
                doPop = true;
                ollieReached = false;
                ollieDone = false;
                break;
            }
            case kickflip:
            {
                doKickflip = true;
            }
            case ollie:
            {
                doOllie = true;
                doPop = true;
                ollieReached = false;
                ollieDone = false;
                break;
            }
        }
    }
    if (skateForward)
    {
        boardZ += step;
        frontTrAxZ += step;
        frontWheelsZ += step;
        rearTrAxZ += step;
        rearWheelsZ += step;
        boardZ = fmod(boardZ,frontBoundary);
        rearWheelsZ = fmod(rearWheelsZ,frontBoundary);
        frontWheelsZ = fmod(frontWheelsZ,frontBoundary);
        rearTrAxZ = fmod(rearTrAxZ,frontBoundary);
        frontTrAxZ = fmod(frontTrAxZ,frontBoundary);
        if(frontBoundary-frontTrAxZ <= 0.1)
        {
            skateForward = false;
        }
    }
    if (doShoveIt)
    {
        if(ollieReached)
        {
            if (!doNinety)
            {
                thetaY += 9;
                thetaY = fmod(thetaY,360);
                if(thetaY == 0)
                {
                    doShoveIt = false;
                    shoveItReached = true;
                }
                
            }
            else
            {
                
                thetaY += 9;
                if(fmod(thetaY,90) == 0)
                {
                    doShoveIt = false;
                    shoveItReached = true;
                }
            }
        }
    }
    if (doManual)
    {
        if(!manualDone)
        {
            if(manualReached)
            {
                if(grind)
                {
                    float boardNose = boardZ+zOffset;
                    if(nearPostZ-boardNose <= 0.3)
                    {
                        grind = false;
                    }
                }
                else
                {
                    thetaX += 1;
                    if(thetaX == 0)
                    {
                        thetaX = 0;
                        manualDone = true;
                        doManual = false;
                    }
                }
            }
            else
            {
                thetaX -= 1;
                thetaX = fmod(thetaX, 25);
                if(thetaX == 0)  // angle reached
                {// theta reached
                    thetaX = -25;
                    manualReached = true;
                }
            }
        }
    }
    if (doOllie)
    {
        if (!ollieDone)
        {
            if(doPop)
            {
                if(!ollieReached)
                {
                    thetaX -= 1;
                    thetaX = fmod(thetaX, popAngle);
                    if(thetaX == 0)
                    {
                        dist = 0;
                        ollieReached = true;
                        thetaX = -popAngle;
                    }
                }
                else
                {
                    float oneRadian = M_PI/180;
                    boardY += oneRadian;
                    frontTrAxY += oneRadian;
                    frontWheelsY += oneRadian;
                    rearTrAxY += oneRadian;
                    rearWheelsY += oneRadian;
                    thetaX += 1;
                    if(thetaX == 0)
                        doPop = false;
                }
            }
            else
            {
                cout << exitGrind << endl;
                counter++;
                float oneRadian = M_PI/180;
                boardY -= oneRadian;
                frontTrAxY -= oneRadian;
                frontWheelsY -= oneRadian;
                rearTrAxY -= oneRadian;
                rearWheelsY -= oneRadian;
                if(frontWheelsY <= roadY && !exitGrind)
                {
                    ollieDone = true;
                    doOllie = false;
                    counter = 0;
                }
                else if(exitGrind)
                {
                    if (frontWheelsY-railY <= -railY+.01)
                    {
                        ollieDone = true;
                        doOllie = false;
                    }
                }
            }
            
        }
    }
    if (doKickflip)
    {
        if (!doPop)
        {
            thetaZ += 36;
            thetaZ = fmod(thetaZ,360);
            if(thetaZ == 0)
                doKickflip = false;
        }
    }
    glutPostRedisplay();
}


//----------------------------------------------------------------------------


void reshape( int w, int h ){
    glViewport(0,0,w,h);
}


//----------------------------------------------------------------------------


int main( int argc, char **argv ){
    glutInit( &argc, argv );
    glutInitDisplayMode(GLUT_3_2_CORE_PROFILE | GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH );
    glutInitWindowSize( 1000, 1000 );
    glutCreateWindow( "SKATE!" );
    
    init();
    
    glutDisplayFunc( display );
    glutReshapeFunc( reshape );
    glutKeyboardFunc( keyboard );
    //glutKeyboardUpFunc(<#void (*func)(unsigned char, int, int)#>)
    glutMouseFunc( mouse );
    glutIdleFunc( idle );
    
    glutMainLoop();
    return 0;
}




