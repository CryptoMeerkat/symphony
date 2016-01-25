#version 330 core
 
layout(location = 0) in vec3 position;	//object space vertex position
layout(location = 1) in vec3 color;	//per-vertex colour

//output from the vertex shader
smooth out vec4 vSmoothColor;		//smooth colour to fragment shader

//uniform
//uniform mat4 MVP;	//combined modelview projection matrix

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projMatrix;

void main()
{
	//assign the per-vertex colour to vSmoothColor varying
   vSmoothColor = vec4(color,1);

	mat4 MVP = projMatrix * viewMatrix * modelMatrix;
	
   //get the clip space position by multiplying the combined MVP matrix with the object space 
   //vertex position
   gl_Position = MVP*vec4(position,1);
}