#include "easyLineRender.hpp"


void drawEasyLine(glm::vec3 start, glm::vec3 end) 
{
    float line_vertex[]=
    {
    start.x, start.y, start.z,
    end.x, end.y, end.z
    };
    GLuint vbo;
 	glGenBuffers(1, &vbo);
 
 	glBindBuffer(GL_ARRAY_BUFFER, vbo);
 	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*6, line_vertex, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
    glEnableVertexAttribArray(0);
    glDrawArrays(GL_LINES, 0, 2);
    glDeleteBuffers(1, &vbo);
}
