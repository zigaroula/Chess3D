#include "vao.h"
#include <vector>
#include <fstream>
#include <sstream>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/matrix_transform.hpp>

Vao Vao::loadObj(std::string filename)
{
    Vao vao;
    
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
                        std::cout << "attention:fichier obj avec text" << std::endl;
                }
        
            }
        }
    }
    
    std::vector<glm::vec3> vertices_new, normals_new;
    for (unsigned int i = 0; i < vertex_indices.size(); ++i)
    {
        vertices_new.push_back(vertices[vertex_indices[i]]);
        normals_new.push_back(normals[normal_indices[i]]);
        
        std::cout << glm::to_string(vertices_new[i]) << ";" << glm::to_string(normals_new[i]) << std::endl;
    }
    
    vao.vertex_count = vertices_new.size();
    vao.model_matrix = glm::mat4(1.f);
    vao.model_matrix = glm::translate(vao.model_matrix, glm::vec3(1.f, 1.f, 0.f));

    
    return vao;
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
