#include "vao.h"
#include <vector>
#include <fstream>
#include <sstream>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/matrix_transform.hpp>



Vao Vao::loadObj(std::string filename, glm::vec3 color)
{
    Vao vao;
    
    vao.ambient_color = color;

    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> normals;

    std::vector<unsigned int> vertex_indices;
    std::vector<unsigned int> normal_indices;
    std::ifstream inputfile(filename);
    std::string str;

    while (std::getline(inputfile, str))
    {
        if (str.size() > 2)
        {
            std::istringstream iss(str);
            std::string token;
            float vec[3];

            if (str[0] == 'v' && str[1] == ' ')
            {
                getline(iss, token, ' ');

                for (int i = 0; i < 3; ++i) {
                    getline(iss, token, ' ');
                    vec[i] = std::stof(token);
                }

                vertices.push_back(glm::vec3(vec[0], vec[1], vec[2]));
            }
            else if (str[0] == 'v' && str[1] == 'n')
            {
                getline(iss, token, ' ');

                for (int i = 0; i < 3; ++i) {
                    getline(iss, token, ' ');
                    vec[i] = std::stof(token);
                }

                normals.push_back(glm::vec3(vec[0], vec[1], vec[2]));
            }
            else if (str[0] == 'f' && str[1] == ' ')
            {
                getline(iss, token, ' ');

                for (int i = 0; i < 3; ++i) {
                    getline(iss, token, ' ');
                    size_t index;

                    if ((index = token.find("//")) != std::string::npos)
                    {
                        std::string a = token.substr(0, index);
                        std::string b = token.substr(index + 2, token.size() - index);

                        vertex_indices.push_back(std::stoi(a) - 1);
                        normal_indices.push_back(std::stoi(b) - 1);
                    }
                    else
                    {
                        /* corriger */
                        index = token.find("/");
                        size_t index2 = token.find("/", index + 1);
                        std::string a = token.substr(0, index);
                        std::string b = token.substr(index + 1, index2 - index - 1);
                        std::string c = token.substr(index2 + 1, token.size() - index2 + 1);
                        

                        vertex_indices.push_back(std::stoi(a) - 1);
                        normal_indices.push_back(std::stoi(c) - 1);

                    }
                }

            }
        }
    }
    
    std::vector<glm::vec3> vertices_new, normals_new;

    for (unsigned int i = 0; i < vertex_indices.size(); ++i)
    {
        vertices_new.push_back(vertices[vertex_indices[i]]);
        normals_new.push_back(normals[normal_indices[i]]);

        //std::cout << glm::to_string(vertices_new[i]) << ";" << glm::to_string(normals_new[i]) << std::endl;
    }

    vao.vertex_count = (GLuint)vertices_new.size();
    vao.model_matrix = glm::mat4(1.f);
    //vao.model_matrix = glm::translate(vao.model_matrix, glm::vec3(1.f, 1.f, 0.f));

    glGenVertexArrays(1, &vao.id);
    glBindVertexArray(vao.id);

    GLuint vbo_positions;
    glGenBuffers(1, &vbo_positions);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_positions);
    glBufferData(GL_ARRAY_BUFFER, vao.vertex_count * sizeof(glm::vec3), &vertices_new[0], GL_STATIC_DRAW);
    glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    GLuint vbo_normals;
    glGenBuffers(1, &vbo_normals);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_normals);
    glBufferData(GL_ARRAY_BUFFER, vao.vertex_count * sizeof(glm::vec3), &normals_new[0], GL_STATIC_DRAW);
    glVertexAttribPointer((GLuint)1, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);

    return vao;
}

void Vao::translate(const glm::vec3 &vector)
{
    model_matrix = glm::translate(model_matrix, vector);
}

void Vao::rotate(float angle, const glm::vec3 &vector)
{
    model_matrix = glm::rotate(model_matrix, angle, vector);
}

void Vao::scale(const glm::vec3 &vector)
{
    model_matrix = glm::scale(model_matrix, vector);
}

Vao Vao::getCube()
{
    Vao vao;

    vao.vertex_count = 6*2*3;
    vao.model_matrix = glm::mat4(1.0f);

    float vertexPositions[] = {
        -0.5f,  0.5f,  -0.5f,
        0.5f, -0.5f,  -0.5f,
        -0.5f, -0.5f,  -0.5f,
        -0.5f, 0.5f, -0.5f,
        0.5f, 0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,

        0.5f, 0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, 0.5f,
        0.5f, 0.5f, -0.5f,
        0.5f, -0.5f, 0.5f,
        0.5f, 0.5f, 0.5f,

        -0.5f, 0.5f, -0.5f,
        0.5f, 0.5f, -0.5f,
        -0.5f, 0.5f, 0.5f,
        0.5f, 0.5f, -0.5f,
        -0.5f, 0.5f, 0.5f,
        0.5f, 0.5f, 0.5f,

        -0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, 0.5f,
        0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, 0.5f,
        0.5f, -0.5f, 0.5f,

        -0.5f,  0.5f,  0.5f,
        0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f, 0.5f, 0.5f,
        0.5f, 0.5f, 0.5f,
        0.5f, -0.5f, 0.5f,

        -0.5f, 0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, 0.5f,
        -0.5f, 0.5f, -0.5f,
        -0.5f, -0.5f, 0.5f,
        -0.5f, 0.5f, 0.5f
    };

    float vertexColors[] = {
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,

        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,

        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,

        1.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 0.0f,

        1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f,

        0.0f, 1.0f, 1.0f,
        0.0f, 1.0f, 1.0f,
        0.0f, 1.0f, 1.0f,
        0.0f, 1.0f, 1.0f,
        0.0f, 1.0f, 1.0f,
        0.0f, 1.0f, 1.0f
    };

    glGenVertexArrays(1, &vao.id);
    glBindVertexArray(vao.id);

    GLuint vbo_positions;
    glGenBuffers(1, &vbo_positions);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_positions);
    glBufferData(GL_ARRAY_BUFFER, 12*9*sizeof(float), vertexPositions, GL_STATIC_DRAW);

    glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    GLuint vbo_colors;
    glGenBuffers(1, &vbo_colors);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_colors);
    glBufferData(GL_ARRAY_BUFFER, 12*9*sizeof(float), vertexColors, GL_STATIC_DRAW);

    glVertexAttribPointer((GLuint)2, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);

    return vao;
}
