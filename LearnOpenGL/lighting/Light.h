#ifndef LIGHT_H
#define LIGHT_H
#include "glm/glm.hpp"

class Light
{
public:
    glm::vec3 position = glm::vec3(0.);
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    bool enabled;

    Light(glm::vec3 position, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular)
    {
        this->position = position;
        this->ambient = ambient;
        this->diffuse = diffuse;
        this->specular = specular;
        enabled = true;
    }
};

class DirectionalLight : public Light
{
public:
    glm::vec3 direction;

    DirectionalLight(glm::vec3 direction, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular) : Light(glm::vec3(0.), ambient, diffuse, specular)
    {
        this->direction = direction;
    }
};

class PointLight : public Light
{
public:
    float constant = 1;
    float linear;
    float quadratic;

    // Constructor name should match the class name
    PointLight(glm::vec3 position, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float linear, float quadratic) : Light(position, ambient, diffuse, specular)
    {
        this->linear = linear;
        this->quadratic = quadratic;
    }
};

class SpotLight : public Light
{
public:
    glm::vec3 direction;
    float constant = 1;
    float linear;
    float quadratic;
    float cutOff;
    float outerCutOff;

    SpotLight(glm::vec3 position, glm::vec3 direction, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular,
        float linear, float quadratic, float cutOff, float outerCutOff) : Light(position, ambient, diffuse, specular)
    {
        this->direction = direction;
        this->linear = linear;
        this->quadratic = quadratic;
        this->cutOff = cutOff;
        this->outerCutOff = outerCutOff;
    }
};

#endif