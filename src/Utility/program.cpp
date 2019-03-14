#include "Utility/program.hpp"

Program::Program(const char* vertexPath, const char* fragmentPath)
{
	// 1. Retrieve vertex and fragment code from corresponding files.
	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;
	// Ensure ifstream objects can throw exceptions.
	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		// Open files
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);
		std::stringstream vShaderStream, fShaderStream;
		// Read file's contents into streams.
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();
		// Close file handlers.
		vShaderFile.close();
		fShaderFile.close();
		// Convert streams into strings.
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR (program.cpp): Unable to read shader code into file stream." << std::endl;
	}
	// glShaderSource doesn't accept strings, only GLchar**
	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();

	// 2. Compile shaders and link into a program.
	GLuint vertex, fragment;

	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);
	checkCompileOrLinkErrors(vertex, "VERTEX");

	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);
	checkCompileOrLinkErrors(fragment, "FRAGMENT");

	ID = glCreateProgram();
	glAttachShader(ID, vertex);
	glAttachShader(ID, fragment);
	glLinkProgram(ID);
	checkCompileOrLinkErrors(ID, "PROGRAM");

	// 3. Delete shaders as they are linked into our program now and no longer necessary.
	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

Program::~Program()
{
	glDeleteProgram(ID);
}

// Start using this program for render calls.
void Program::use()
{
	glUseProgram(ID);
}

// Functions to set uniform variables for the current program (either vertex or fragment shader.)
void Program::setBool(const std::string &name, GLboolean value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}
void Program::setInt(const std::string &name, GLint value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}
void Program::setFloat(const std::string &name, GLfloat value) const
{
	glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}
void Program::setVec2(const std::string &name, const glm::vec2 &value) const
{
	glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}
void Program::setVec3(const std::string &name, const glm::vec3 &value) const
{
	GLint uloc = glGetUniformLocation(ID, name.c_str());
	glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}
void Program::setVec3Array(const std::string &name, const vector<glm::vec3> &value) const
{
  GLint uloc = glGetUniformLocation(ID, name.c_str());
  if(!value.empty())
    glUniform3fv(uloc, value.size(), reinterpret_cast<const GLfloat *>(&value[0]));
}
void Program::setVec4(const std::string &name, const glm::vec4 &value) const
{
	glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}
void Program::setMat2(const std::string &name, const glm::mat2 &mat) const
{
	glUniformMatrix2fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
void Program::setMat3(const std::string &name, const glm::mat3 &mat) const
{
	glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
void Program::setMat4(const std::string &name, const glm::mat4 &mat) const
{
	GLint uloc = glGetUniformLocation(ID, name.c_str());
	glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
// Used for checking shader compilation/linking errors.
void Program::checkCompileOrLinkErrors(unsigned int shader, std::string type)
{
	int success;
	char infoLog[1024];
	if (type != "PROGRAM")
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "ERROR (program.cpp): Could not compile a " << type << " shader:\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
		}
	}
	else
	{
		glGetProgramiv(shader, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "ERROR (program.cpp): Could not link shaders into " << type << ":\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
		}
	}
}
