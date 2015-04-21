#include "vao.h"
#include "tga.h"
#include <vector>
#include <fstream>
#include <sstream>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>


void Vao::endMovement()
{
    movement_requested = false;
}

void Vao::updateMovement()
{
    double elasped_time = glfwGetTime() - movement_start_time;
    double total = 1.0;
    float movement_length = (float)elasped_time/total * getMovementLength();
    
    glm::vec3 translation = movement_length * getMovementDirection();
    
    model_matrix = glm::translate(model_matrix_before_movement, translation);
    
    if (elasped_time >= total)
    {
        movement_requested = false;
        
    }

}

void Vao::requestMovement(glm::vec3 pos_end)
{
    position_start = glm::vec3(model_matrix * glm::vec4(0, 0, 0, 1));
    movement_requested = true;
    position_end = pos_end;
    movement_length = glm::length(position_end-position_start);
    movement_direction =position_end-position_start;
    movement_direction = glm::normalize(movement_direction);
    movement_start_time = glfwGetTime();
    model_matrix_before_movement = model_matrix;

}
Vao Vao::loadObj(std::string filename, glm::vec3 color)
{

    return Vao::loadObj(filename, color, "");
}

Vao Vao::loadObj(std::string filename, glm::vec3 color, std::string texture_filename)
{
    
    Vao vao;
    
    vao.ambient_color = color;

    std::vector<glm::vec3> vertices, normals;
    std::vector<glm::vec2> textures;

    std::vector<unsigned int> vertex_indices, normal_indices, texture_indices;

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
            else if (str[0] == 'v' && str[1] == 't')
            {
                getline(iss, token, ' ');
                
                for (int i = 0; i < 2; ++i) {
                    getline(iss, token, ' ');
                    vec[i] = std::stof(token);
                }
                
                textures.push_back(glm::vec2(vec[0], vec[1]));
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
                        texture_indices.push_back(std::stoi(b) - 1);
                        normal_indices.push_back(std::stoi(c) - 1);

                    }
                }

            }
        }
    }

    std::vector<glm::vec3> vertices_new, normals_new;
    std::vector<glm::vec2> textures_new;
    
    vao.texture_enabled = textures.size() > 0 && texture_indices.size() > 0 && texture_filename.size() > 0;


    for (unsigned int i = 0; i < vertex_indices.size(); ++i)
    {
        vertices_new.push_back(vertices[vertex_indices[i]]);
        normals_new.push_back(normals[normal_indices[i]]);
        
        if (vao.texture_enabled)
            textures_new.push_back(textures[texture_indices[i]]);

        //std::cout << glm::to_string(vertices_new[i]) << ";" << glm::to_string(normals_new[i]) << std::endl;
    }

    vao.vertex_count = (GLuint)vertices_new.size();
    vao.model_matrix = glm::mat4(1.f);

    /*std::cout << filename << std::endl;
    std::cout << texture_indices.size() << ";" << textures.size() << std::endl;
    std::cout << normal_indices.size() << ";" << normals.size() << std::endl;
    std::cout << "texture enabled" << (vao.texture_enabled?"yes:":"no") << std::endl;*/

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
    
    if (vao.texture_enabled)
    {
        glGenTextures(1, &vao.texture_id);
        glBindTexture(GL_TEXTURE_2D, vao.texture_id);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        
    
        Tga tga = Tga::LoadTGAFile(texture_filename.c_str());
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, tga.imageWidth, tga.imageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, tga.imageData);

        
        GLuint vbo_textures;
        glGenBuffers(1, &vbo_textures);
        glBindBuffer(GL_ARRAY_BUFFER, vbo_textures);
        glBufferData(GL_ARRAY_BUFFER, vao.vertex_count * sizeof(glm::vec2), &textures_new[0], GL_STATIC_DRAW);
        glVertexAttribPointer((GLuint)2, 2, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(2);
        
    }

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

Vao Vao::getSkyBoxCube(){
    float points[] = {
        -1000.0f,  1000.0f, -1000.0f,
        -1000.0f, -1000.0f, -1000.0f,
        1000.0f, -1000.0f, -1000.0f,
        1000.0f, -1000.0f, -1000.0f,
        1000.0f,  1000.0f, -1000.0f,
        -1000.0f,  1000.0f, -1000.0f,

        -1000.0f, -1000.0f,  1000.0f,
        -1000.0f, -1000.0f, -1000.0f,
        -1000.0f,  1000.0f, -1000.0f,
        -1000.0f,  1000.0f, -1000.0f,
        -1000.0f,  1000.0f,  1000.0f,
        -1000.0f, -1000.0f,  1000.0f,

        1000.0f, -1000.0f, -1000.0f,
        1000.0f, -1000.0f,  1000.0f,
        1000.0f,  1000.0f,  1000.0f,
        1000.0f,  1000.0f,  1000.0f,
        1000.0f,  1000.0f, -1000.0f,
        1000.0f, -1000.0f, -1000.0f,

        -1000.0f, -1000.0f,  1000.0f,
        -1000.0f,  1000.0f,  1000.0f,
        1000.0f,  1000.0f,  1000.0f,
        1000.0f,  1000.0f,  1000.0f,
        1000.0f, -1000.0f,  1000.0f,
        -1000.0f, -1000.0f,  1000.0f,

        -1000.0f,  1000.0f, -1000.0f,
        1000.0f,  1000.0f, -1000.0f,
        1000.0f,  1000.0f,  1000.0f,
        1000.0f,  1000.0f,  1000.0f,
        -1000.0f,  1000.0f,  1000.0f,
        -1000.0f,  1000.0f, -1000.0f,

        -1000.0f, -1000.0f, -1000.0f,
        -1000.0f, -1000.0f,  1000.0f,
        1000.0f, -1000.0f, -1000.0f,
        1000.0f, -1000.0f, -1000.0f,
        -1000.0f, -1000.0f,  1000.0f,
        1000.0f, -1000.0f,  1000.0f
    };
    GLuint vbo;
    glGenBuffers (1, &vbo);
    glBindBuffer (GL_ARRAY_BUFFER, vbo);
    glBufferData (GL_ARRAY_BUFFER, 3 * 36 * sizeof (float), &points, GL_STATIC_DRAW);

    GLuint vaoID = 0;
    Vao vao;
    vao.id = vaoID;
    vao.vertex_count = 6*2*3;
    vao.model_matrix = glm::mat4(1.0f);
    vao.ambient_color = glm::vec3(0.0f,0.0f,1.0f);

    glGenVertexArrays (1, &vaoID);
    glBindVertexArray (vaoID);
    glEnableVertexAttribArray (0);
    glBindBuffer (GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 0, NULL);


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
