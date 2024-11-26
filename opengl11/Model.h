#ifndef MODEL_H
#define MODEL_H

#include <string>
#include <vector>
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <fstream>
#include <sstream>
#include <iostream>

class Model {
public:
    struct Vertex {
        glm::vec3 position;
        glm::vec3 normal;
        glm::vec2 texCoords;
    };

    struct Mesh {
        std::vector<Vertex> vertices;
        std::vector<GLuint> indices;
        GLuint VAO, VBO, EBO;

        Mesh(const std::vector<Vertex>& vertices, const std::vector<GLuint>& indices);
        void Draw(GLuint shaderProgram);
    };

    Model(std::string const& path);
    void Draw(GLuint shaderProgram);

private:
    void loadModel(std::string const& path);
    void processMesh(const std::vector<Vertex>& vertices, const std::vector<GLuint>& indices);

    std::vector<Mesh> meshes;
    std::string directory;
};

#endif
