#include "Model.h"

Model::Model(std::string const& path)
{
    loadModel(path);
}

void Model::Draw(GLuint shaderProgram)
{
    for (auto& mesh : meshes)
        mesh.Draw(shaderProgram);
}

void Model::loadModel(std::string const& path)
{
    std::ifstream file(path);
    if (!file.is_open()) {
        std::cerr << "Failed to open the model file: " << path << std::endl;
        return;
    }

    std::vector<glm::vec3> positions;
    std::vector<glm::vec2> texCoords;
    std::vector<glm::vec3> normals;
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream ss(line);
        std::string prefix;
        ss >> prefix;

        if (prefix == "v") {
            glm::vec3 position;
            ss >> position.x >> position.y >> position.z;
            positions.push_back(position);
        }
        else if (prefix == "vt") {
            glm::vec2 texCoord;
            ss >> texCoord.x >> texCoord.y;
            texCoords.push_back(texCoord);
        }
        else if (prefix == "vn") {
            glm::vec3 normal;
            ss >> normal.x >> normal.y >> normal.z;
            normals.push_back(normal);
        }
        else if (prefix == "f") {
            GLuint idx1, idx2, idx3;
            GLuint uv1, uv2, uv3;
            GLuint norm1, norm2, norm3;

            // OBJ format is 1-based indexing, so we subtract 1 for 0-based arrays.
            ss >> idx1 >> uv1 >> norm1 >> idx2 >> uv2 >> norm2 >> idx3 >> uv3 >> norm3;

            Vertex v1 = { positions[idx1 - 1], normals[norm1 - 1], texCoords[uv1 - 1] };
            Vertex v2 = { positions[idx2 - 1], normals[norm2 - 1], texCoords[uv2 - 1] };
            Vertex v3 = { positions[idx3 - 1], normals[norm3 - 1], texCoords[uv3 - 1] };

            vertices.push_back(v1);
            vertices.push_back(v2);
            vertices.push_back(v3);

            indices.push_back(indices.size());
            indices.push_back(indices.size());
            indices.push_back(indices.size());
        }
    }

    file.close();

    processMesh(vertices, indices);
}

void Model::processMesh(const std::vector<Vertex>& vertices, const std::vector<GLuint>& indices)
{
    meshes.push_back(Mesh(vertices, indices));
}

Model::Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<GLuint>& indices)
{
    this->vertices = vertices;
    this->indices = indices;

    // Generate buffers
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    // Normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));
    glEnableVertexAttribArray(1);

    // Texture coordinate attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, texCoords));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);  // Unbind VAO
}

void Model::Mesh::Draw(GLuint shaderProgram)
{
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}
