#version 130
// The Vertex shader operates on each vertex

// input data from the VBO. Each vertex is 2 floats
in vec2 vertexPosition;
in vec4 vertexColor;
in vec2 vertexUV;

out vec2 fragmentPosition;
out vec4 fragmentColor;
out vec2 fragmentUV;

void main() {
	// Set the x,y position on the screen
	gl_Position.xy = vertexPosition;

	// The Z position is zero since we are in 2D
	gl_Position.z = 0.0;

	// Indicates that the cordinates are normalized
	gl_Position.w = 1.0;
 
	fragmentPosition = vertexPosition;
	
	fragmentColor = vertexColor;
	
	// create a 2D vertexUV and flip the y cordinate by subtracting from 1.0
	fragmentUV = vec2(vertexUV.x, 1.0 - vertexUV.y);
}