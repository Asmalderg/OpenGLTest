#version 330												
layout (location = 0) in vec3 pos;							
															
void main()													
{															
	gl_Position = vec4(0.5*pos.x, 0.5*pos.y, 0.5*pos.z, 1.0);
}