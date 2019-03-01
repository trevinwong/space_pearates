#ifndef PROGRAM_H
#define PROGRAM_H

#include "utility.hpp"

/*	Utility class to compile and link shaders into a program object.
 *	Contains functions to set uniforms, and to generate compilation/linking error messages.
 *
 *	To use this class:
 *	- Pass in the correct path to both shaders upon construction (use shader_path("myShader.vert")), look at utility.hpp for reference
 *	- Set any uniforms you need in your shaders by using the set functions.
 *	- Use the program by explicitly calling use() before any render calls.
 *
 *	Code modified from LearnOpenGL: https://learnopengl.com/Getting-started/Shaders
 */
class Program
{
public:
	GLuint ID;
	Program(const char* vertexPath, const char* fragmentPath); // Automatically compiles and links shaders into a program.
	~Program();
	void  	use(); // Use the current program for render calls.	
	void    setBool(const std::string &name, GLboolean value) const;
	void    setInt(const std::string &name, GLint value) const;
	void    setFloat(const std::string &name, GLfloat value) const;
	void    setVec2(const std::string &name, const glm::vec2 &value) const;
	void    setVec3(const std::string &name, const glm::vec3 &value) const;
  void    setVec3Array(const std::string &name, const vector<glm::vec3> &value) const;
	void    setVec4(const std::string &name, const glm::vec4 &value) const;
	void    setMat2(const std::string &name, const glm::mat2 &matrix) const;
	void    setMat3(const std::string &name, const glm::mat3 &matrix) const;
	void    setMat4(const std::string &name, const glm::mat4 &matrix) const;
private:
	void    checkCompileOrLinkErrors(unsigned int shader, std::string type);
};

#endif
