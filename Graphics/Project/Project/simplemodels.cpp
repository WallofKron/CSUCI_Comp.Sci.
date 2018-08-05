#include "Angel.h"
#include "simplemodels.h"


//----------------------------------------------------------------------------
vec4 points_cube[NumVerticesCube];
vec4 colors[NumVerticesCube];
vec3 normals_cube[NumVerticesCube];
vec2 tex_coords_cube[NumVerticesCube];

// Vertices of a unit cube centered at origin, sides aligned with axes
vec4 vertices[8] = {
    vec4( -0.5, -0.5,  0.5, 1.0 ),
    vec4( -0.5,  0.5,  0.5, 1.0 ),
    vec4(  0.5,  0.5,  0.5, 1.0 ),
    vec4(  0.5, -0.5,  0.5, 1.0 ),
    vec4( -0.5, -0.5, -0.5, 1.0 ),
    vec4( -0.5,  0.5, -0.5, 1.0 ),
    vec4(  0.5,  0.5, -0.5, 1.0 ),
    vec4(  0.5, -0.5, -0.5, 1.0 )
};

// RGBA colors
vec4 vertex_colors[8] = {
    vec4( 0.1, 0.1, 0.1, 1.0 ),  // black
    vec4( 1.0, 0.0, 0.0, 1.0 ),  // red
    vec4( 1.0, 1.0, 0.0, 1.0 ),  // yellow
    vec4( 0.0, 1.0, 0.0, 1.0 ),  // green
    vec4( 0.0, 0.0, 1.0, 1.0 ),  // blue
    vec4( 1.0, 0.0, 1.0, 1.0 ),  // magenta
    vec4( 0.9, 0.9, 0.9, 1.0 ),  // white
    vec4( 0.0, 1.0, 1.0, 1.0 )   // cyan
};



//----------------------------------------------------------------------------

// quad generates two triangles for each face and assigns colors
//    to the vertices
int Index = 0;
void
quad( int a, int b, int c, int d )
{
    // Initialize temporary vectors along the quad's edge to compute its face normal
    vec4 u = vertices[b] - vertices[a];
    vec4 v = vertices[c] - vertices[b];
    
    vec3 normal = normalize( cross(u, v) );
    
    normals_cube[Index] = normal; colors[Index] = vertex_colors[a]; points_cube[Index] = vertices[a];
    tex_coords_cube[Index] = vec2( 1.0, 1.0 ); Index++;
    normals_cube[Index] = normal; colors[Index] = vertex_colors[a]; points_cube[Index] = vertices[b];
    tex_coords_cube[Index] = vec2( 1.0, 0.0 ); Index++;
    normals_cube[Index] = normal; colors[Index] = vertex_colors[a]; points_cube[Index] = vertices[c];
    tex_coords_cube[Index] = vec2( 0.0, 0.0 ); Index++;
    normals_cube[Index] = normal; colors[Index] = vertex_colors[a]; points_cube[Index] = vertices[a];
    tex_coords_cube[Index] = vec2( 1.0, 1.0 ); Index++;
    normals_cube[Index] = normal; colors[Index] = vertex_colors[a]; points_cube[Index] = vertices[c];
    tex_coords_cube[Index] = vec2( 0.0, 0.0 ); Index++;
    normals_cube[Index] = normal; colors[Index] = vertex_colors[a]; points_cube[Index] = vertices[d];
    tex_coords_cube[Index] = vec2( 0.0, 1.0 ); Index++;

}

vec4 points_triangle[NumVerticesTri];
vec3 normals_triangle[NumVerticesTri];
vec2 tex_coords_triangle[NumVerticesTri];

int triangleIndex = 0;
void
tri( int a, int b, int c)
{
    // Initialize temporary vectors along the quad's edge to compute its face normal
    vec4 u = vertices[b] - vertices[a];
    vec4 v = vertices[c] - vertices[b];
    
    vec3 normal = normalize( cross(u, v) );
    
    normals_triangle[triangleIndex] = normal; colors[triangleIndex] = vertex_colors[a]; points_triangle[triangleIndex] = vertices[a];
    tex_coords_triangle[triangleIndex] = vec2( 1.0, 1.0 ); triangleIndex++;
    normals_triangle[triangleIndex] = normal; colors[triangleIndex] = vertex_colors[a]; points_triangle[triangleIndex] = vertices[b];
    tex_coords_triangle[triangleIndex] = vec2( 1.0, 0.0 ); triangleIndex++;
    normals_triangle[triangleIndex] = normal; colors[triangleIndex] = vertex_colors[a]; points_triangle[triangleIndex] = vertices[c];
    tex_coords_triangle[triangleIndex] = vec2( 0.0, 0.0 ); triangleIndex++;
}

void
colorTri()
{
    tri( 1, 0, 3);
    tri( 2, 3, 7);
    tri( 3, 0, 4);
//    quad( 6, 5, 1, 2 );
//    quad( 4, 5, 6, 7 );
//    quad( 5, 4, 0, 1 );
}
//----------------------------------------------------------------------------

// generate 12 triangles: 36 vertices and 36 colors
void
colorcube()
{
    quad( 1, 0, 3, 2 );
    quad( 2, 3, 7, 6 );
    quad( 3, 0, 4, 7 );
    quad( 6, 5, 1, 2 );
    quad( 4, 5, 6, 7 );
    quad( 5, 4, 0, 1 );
}









//---- cylinder model
//----------------------------------------------------------------------------
vec4 points_cylinder[NumVerticesCylinder];
vec4 vertices_cylinder[4];
vec3 normals_cylinder[NumVerticesCylinder];


// quad generates two triangles for each face and assigns colors to the vertices
void
quad_cylinder( int a, int b, int c, int d )
{
    points_cylinder[Index] = vertices_cylinder[a];
    normals_cylinder[Index] = vec3(vertices_cylinder[a].x, 0.0, vertices_cylinder[a].z);
    Index++;
    points_cylinder[Index] = vertices_cylinder[b];
    normals_cylinder[Index] = vec3(vertices_cylinder[b].x, 0.0, vertices_cylinder[b].z);
    Index++;
    points_cylinder[Index] = vertices_cylinder[c];
    normals_cylinder[Index] = vec3(vertices_cylinder[c].x, 0.0, vertices_cylinder[c].z);
    Index++;
    points_cylinder[Index] = vertices_cylinder[a];
    normals_cylinder[Index] = vec3(vertices_cylinder[a].x, 0.0, vertices_cylinder[a].z);
    Index++;
    points_cylinder[Index] = vertices_cylinder[c];
    normals_cylinder[Index] = vec3(vertices_cylinder[c].x, 0.0, vertices_cylinder[c].z);
    Index++;
    points_cylinder[Index] = vertices_cylinder[d];
    normals_cylinder[Index] = vec3(vertices_cylinder[d].x, 0.0, vertices_cylinder[d].z);
    Index++;
}


float const bottom = -0.5;
float const top    = 0.5;

void colortube(void){
    float r = 0.5;
    Index = 0;
    
    for ( int n = 0; n < segments; n++ )
    {
        GLfloat const t0 = 2 * M_PI * (float)n / (float)segments;
        GLfloat const t1 = 2 * M_PI * (float)(n+1) / (float)segments;
        
        points_cylinder[Index].x = 0.0;
        points_cylinder[Index].y = top;
        points_cylinder[Index].z = 0.0;
        points_cylinder[Index].w = 1.0;
        normals_cylinder[Index] = vec3(0.0, 1.0, 0.0);
        Index++;
        points_cylinder[Index].x = cos(t0) * r;
        points_cylinder[Index].y = top;
        points_cylinder[Index].z = sin(t0) * r;
        points_cylinder[Index].w = 1.0;
        normals_cylinder[Index] = vec3(0.0, 1.0, 0.0);
        Index++;
        points_cylinder[Index].x = cos(t1) * r;
        points_cylinder[Index].y = top;
        points_cylinder[Index].z = sin(t1) * r;
        points_cylinder[Index].w = 1.0;
        normals_cylinder[Index] = vec3(0.0, 1.0, 0.0);
        Index++;
    }
    
    
    int num;
    for ( int n = 0; n < segments; n++ )
    {
        num = 0;
        float r = 0.5;
        
        GLfloat const t0 = 2 * M_PI * (float)n / (float)segments;
        GLfloat const t1 = 2 * M_PI * (float)(n+1) / (float)segments;
        
        //quad vertex 0
        vertices_cylinder[num].x = cos(t0) * r;
        vertices_cylinder[num].y = bottom;
        vertices_cylinder[num].z = sin(t0) * r;
        vertices_cylinder[num++].w = 1.0;
        //quad vertex 1
        vertices_cylinder[num].x = cos(t1) * r;
        vertices_cylinder[num].y = bottom;
        vertices_cylinder[num].z = sin(t1) * r;
        vertices_cylinder[num++].w = 1.0;
        //quad vertex 2
        vertices_cylinder[num].x = cos(t1) * r;
        vertices_cylinder[num].y = top;
        vertices_cylinder[num].z = sin(t1) * r;
        vertices_cylinder[num++].w = 1.0;
        //quad vertex 3
        vertices_cylinder[num].x = cos(t0) * r;
        vertices_cylinder[num].y = top;
        vertices_cylinder[num].z = sin(t0) * r;
        vertices_cylinder[num++].w = 1.0;
        
        quad_cylinder( 0, 1, 2, 3 );
    }
 
    
    for ( int n = 0; n < segments; n++ )
    {
        GLfloat const t0 = 2 * M_PI * (float)n / (float)segments;
        GLfloat const t1 = 2 * M_PI * (float)(n+1) / (float)segments;
        
        points_cylinder[Index].x = 0.0;
        points_cylinder[Index].y = bottom;
        points_cylinder[Index].z = 0.0;
        points_cylinder[Index].w = 1.0;
        normals_cylinder[Index] = vec3(0.0, -1.0, 0.0);
        Index++;
        points_cylinder[Index].x = cos(t1) * r;
        points_cylinder[Index].y = bottom;
        points_cylinder[Index].z = sin(t1) * r;
        points_cylinder[Index].w = 1.0;
        normals_cylinder[Index] = vec3(0.0, -1.0, 0.0);
        Index++;
        points_cylinder[Index].x = cos(t0) * r;
        points_cylinder[Index].y = bottom;
        points_cylinder[Index].z = sin(t0) * r;
        points_cylinder[Index].w = 1.0;
        normals_cylinder[Index] = vec3(0.0, -1.0, 0.0);
        Index++;
    }
    
}








//---- sphere model
//----------------------------------------------------------------------------
vec4 points_sphere[NumVerticesSphere];
vec4 vertices_sphere[4];
vec3 normals_sphere[NumVerticesSphere];
vec2 tex_coords_sphere[NumVerticesSphere];

// quad generates two triangles for each face and assigns colors to the vertices
void quad_sphere( int a, int b, int c, int d, float t0, float t1, float p0, float p1 ){
    points_sphere[Index] = vertices_sphere[a];
    normals_sphere[Index] = vec3(vertices_sphere[a].x, vertices_sphere[a].y, vertices_sphere[a].z);
    tex_coords_sphere[Index] = vec2( t0/(2*M_PI), -(p1-M_PI/2.0)/M_PI );
    Index++;
    
    points_sphere[Index] = vertices_sphere[b];
    normals_sphere[Index] = vec3(vertices_sphere[b].x, vertices_sphere[b].y, vertices_sphere[b].z);
    tex_coords_sphere[Index] = vec2( t1/(2*M_PI), -(p1-M_PI/2.0)/M_PI );
    Index++;
    
    points_sphere[Index] = vertices_sphere[c];
    normals_sphere[Index] = vec3(vertices_sphere[c].x, vertices_sphere[c].y, vertices_sphere[c].z);
    tex_coords_sphere[Index] = vec2( t1/(2*M_PI), -(p0-M_PI/2.0)/M_PI );
    Index++;
    
    points_sphere[Index] = vertices_sphere[a];
    normals_sphere[Index] = vec3(vertices_sphere[a].x, vertices_sphere[a].y, vertices_sphere[a].z);
    tex_coords_sphere[Index] = vec2( t0/(2*M_PI), -(p1-M_PI/2.0)/M_PI );
    Index++;
    
    points_sphere[Index] = vertices_sphere[c];
    normals_sphere[Index] = vec3(vertices_sphere[c].x, vertices_sphere[c].y, vertices_sphere[c].z);
    tex_coords_sphere[Index] = vec2( t1/(2*M_PI), -(p0-M_PI/2.0)/M_PI );
    Index++;
    
    points_sphere[Index] = vertices_sphere[d];
    normals_sphere[Index] = vec3(vertices_sphere[d].x, vertices_sphere[d].y, vertices_sphere[d].z);
    tex_coords_sphere[Index] = vec2( t0/(2*M_PI), -(p0-M_PI/2.0)/M_PI );
    Index++;
}


void colorbube(void){
    Index = 0;
    
    for( int m = 0; m < ssegments; m++ )
    {
        float p0 = M_PI/2.0 - m * M_PI/(float)ssegments;
        float p1 = M_PI/2.0 - (m+1) * M_PI/(float)ssegments;
        
        int num;
        for ( int n = 0; n < ssegments; n++ )
        {
            num = 0;
            float r = 0.5;
            
            GLfloat const t0 = 2 * M_PI * (float)n / (float)ssegments;
            GLfloat const t1 = 2 * M_PI * (float)(n+1) / (float)ssegments;
            
            //quad vertex 0
            vertices_sphere[num].x = cos(p1)*cos(t0) * r;
            vertices_sphere[num].y = sin(p1) * r;
            vertices_sphere[num].z = cos(p1)*sin(t0) * r;
            vertices_sphere[num++].w = 1.0;
            //quad vertex 1
            vertices_sphere[num].x = cos(p1)*cos(t1) * r;
            vertices_sphere[num].y = sin(p1) * r;
            vertices_sphere[num].z = cos(p1)*sin(t1) * r;
            vertices_sphere[num++].w = 1.0;
            //quad vertex 2
            vertices_sphere[num].x = cos(p0)*cos(t1) * r;
            vertices_sphere[num].y = sin(p0) * r;
            vertices_sphere[num].z = cos(p0)*sin(t1) * r;
            vertices_sphere[num++].w = 1.0;
            //quad vertex 3
            vertices_sphere[num].x = cos(p0)*cos(t0) * r;
            vertices_sphere[num].y = sin(p0) * r;
            vertices_sphere[num].z = cos(p0)*sin(t0) * r;
            vertices_sphere[num++].w = 1.0;
            
            quad_sphere( 0, 1, 2, 3, t0, t1, p0, p1 );
        }
    }
}









//---- torus model

vec4 points_torus[NumVerticesTorus];
vec4 vertices_torus[4];
vec3 normals_torus[NumVerticesTorus];
vec2 tex_coords_torus[NumVerticesTorus];

// quad generates two triangles for each face and assigns colors to the vertices

void quad_torus( int a, int b, int c, int d, float t0, float t1, float p0, float p1 ){
    points_torus[Index] = vertices_torus[a];
    normals_torus[Index] = vec3(vertices_torus[a].x, vertices_torus[a].y, vertices_torus[a].z);
    tex_coords_torus[Index] = vec2( t0/(2*M_PI), -(p1-M_PI/2.0)/M_PI );
    Index++;
    
    points_torus[Index] = vertices_torus[b];
    normals_torus[Index] = vec3(vertices_torus[b].x, vertices_torus[b].y, vertices_torus[b].z);
    tex_coords_torus[Index] = vec2( t1/(2*M_PI), -(p1-M_PI/2.0)/M_PI );
    Index++;
    
    points_torus[Index] = vertices_torus[c];
    normals_torus[Index] = vec3(vertices_torus[c].x, vertices_torus[c].y, vertices_torus[c].z);
    tex_coords_torus[Index] = vec2( t1/(2*M_PI), -(p0-M_PI/2.0)/M_PI );
    Index++;
    
    points_torus[Index] = vertices_torus[a];
    normals_torus[Index] = vec3(vertices_torus[a].x, vertices_torus[a].y, vertices_torus[a].z);
    tex_coords_torus[Index] = vec2( t0/(2*M_PI), -(p1-M_PI/2.0)/M_PI );
    Index++;
    
    points_torus[Index] = vertices_torus[c];
    normals_torus[Index] = vec3(vertices_torus[c].x, vertices_torus[c].y, vertices_torus[c].z);
    tex_coords_torus[Index] = vec2( t1/(2*M_PI), -(p0-M_PI/2.0)/M_PI );
    Index++;
    
    points_torus[Index] = vertices_torus[d];
    normals_torus[Index] = vec3(vertices_torus[d].x, vertices_torus[d].y, vertices_torus[d].z);
    tex_coords_torus[Index] = vec2( t0/(2*M_PI), -(p0-M_PI/2.0)/M_PI );
    Index++;
}



void colortorus(void){
    float r = 0.3;
    float rd = 0.5;
    Index = 0;
    
    for( int m = 0; m < tsegments; m++ )
    {
        GLfloat const p0 = 2 * M_PI * (float)m / (float)tsegments;
        GLfloat const p1 = 2 * M_PI * (float)(m+1) / (float)tsegments;
        
        int num;
        for ( int n = 0; n < tsegments; n++ )
        {
            num = 0;
            float x = 0.0, y = 0.0;
            
            GLfloat const t0 = 2 * M_PI * (float)n / (float)tsegments;
            GLfloat const t1 = 2 * M_PI * (float)(n+1) / (float)tsegments;
            
            //quad vertex 0
            x = cos(t0) * r + rd;
            y = 0.0;
            vertices_torus[num].z = sin(t0) * r;
            // rotated by p1
            vertices_torus[num].x = x*cos(p1) - y*sin(p1);
            vertices_torus[num].y = x*sin(p1) + y*cos(p1);
            vertices_torus[num++].w = 1.0;
            
            //quad vertex 1
            x = cos(t1) * r + rd;
            y = 0.0;
            vertices_torus[num].z = sin(t1) * r;
            // rotated by p1
            vertices_torus[num].x = x*cos(p1) - y*sin(p1);
            vertices_torus[num].y = x*sin(p1) + y*cos(p1);
            vertices_torus[num++].w = 1.0;
            
            //quad vertex 2
            x = cos(t1) * r + rd;
            y = 0.0;
            vertices_torus[num].z = sin(t1) * r;
            // rotated by p0
            vertices_torus[num].x = x*cos(p0) - y*sin(p0);
            vertices_torus[num].y = x*sin(p0) + y*cos(p0);
            
            vertices_torus[num++].w = 1.0;
            
            //quad vertex 3
            x = cos(t0) * r + rd;
            y = 0.0;
            vertices_torus[num].z = sin(t0) * r;
            // rotated by p0
            vertices_torus[num].x = x*cos(p0) - y*sin(p0);
            vertices_torus[num].y = x*sin(p0) + y*cos(p0);
            
            vertices_torus[num++].w = 1.0;
            
            quad_torus( 0, 1, 2, 3, t0, t1, p0, p1);
        }
    }
}
