#include "mesh_component.hpp"

MeshComponent::MeshComponent(string meshPath)
{
	program = new Program(shader_path("mesh.vert"), shader_path("mesh.frag"));

	vector<vec3> vertices;
	vector<vec3> positions;
	vector<uint16_t> indices;

	// Reads the mesh from a file, which contains a list of vertices and indices
	FILE* mesh_file = fopen(meshPath.c_str(), "r");

	if (mesh_file == nullptr) {
		cout << "Error reading mesh: " << meshPath << " from file!" << endl;
		return;
	}

	// Reading vertices and colors
	size_t num_vertices;
	fscanf(mesh_file, "%zu\n", &num_vertices);
	for (size_t i = 0; i < num_vertices; ++i)
	{
		float x, y, z;
		float _u[3]; // unused
		int r, g, b;
		fscanf(mesh_file, "%f %f %f %f %f %f %d %d %d\n", &x, &y, &z, _u, _u+1, _u+2, &r, &g, &b);
		vec3 position = glm::normalize(vec3(x, y, -z));
		vec3 color = { (float) r / 255, (float) g / 255, (float) b / 255 };
		vertices.push_back(position);
		positions.push_back(position);
		vertices.push_back(color);
	}

	// Reading associated indices
	size_t num_indices;
	fscanf(mesh_file, "%zu\n", &num_indices);
	for (size_t i = 0; i < num_indices; ++i)
	{
		int idx[3];
		fscanf(mesh_file, "%d %d %d\n", idx, idx + 1, idx + 2);
		indices.push_back((uint16_t)idx[0]);
		indices.push_back((uint16_t)idx[1]);
		indices.push_back((uint16_t)idx[2]);
	}

	// Construct triangle information
	for (int i = 0; i < indices.size(); i += 3) {
		vec3 pt1 = positions[indices[i]];
		vec3 pt2 = positions[indices[i + 1]];
		vec3 pt3 = positions[indices[i + 2]];
		triangles.push_back(Triangle(vec2(pt1), vec2(pt2), vec2(pt3)));
	}

	// Done reading
	fclose(mesh_file);

	// Vertex Buffer creation
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vec3) * 2 * vertices.size(), vertices.data(), GL_STATIC_DRAW);

	// Index Buffer creation
	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint16_t) * indices.size(), indices.data(), GL_STATIC_DRAW);

	// Vertex Array (Container for Vertex + Index buffer)
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	GLint in_position_loc = glGetAttribLocation(program->ID, "in_vertex");
	GLint in_color_loc = glGetAttribLocation(program->ID, "in_color");
	glEnableVertexAttribArray(in_position_loc);
	glEnableVertexAttribArray(in_color_loc);
	glVertexAttribPointer(in_position_loc, 3, GL_FLOAT, GL_FALSE, sizeof(vec3) * 2, (void*)0);
	glVertexAttribPointer(in_color_loc, 3, GL_FLOAT, GL_FALSE, sizeof(vec3) * 2, (void*)sizeof(vec3));
	
	numIndices = indices.size();

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

MeshComponent::~MeshComponent()
{
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &IBO);
	glDeleteBuffers(1, &VAO);
}
