#version 330

uniform sampler2D tex1;

in vec2 TexCoord;
in float diffTerm;
out vec4 outputColor;

void main() 
{
	vec4 texColor1 = texture(tex1, TexCoord);  //Get colour from texture  

	outputColor = diffTerm * texColor1;  //Apply lighting term.
}
