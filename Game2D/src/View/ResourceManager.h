#pragma once

#include "Shader.h"
#include "Texture.h"

#include <GL/glew.h>
#include <map>
#include <string>

/// <summary>
/// A static singleton ResourceManager class that hosts several
/// functions to load Textures and Shaders. Each loaded texture
/// and/or shader is also stored for future reference by string
/// handles. All functions and resources are static and no
/// public constructor is defined.
/// </summary>
class ResourceManager {
  public:
    // resource storage
    static std::map<std::string, Shader> shaders;
    static std::map<std::string, Texture2D> textures;
    
    /// <summary>
    /// Loads (and generates) a shader program from file loading vertex, fragment shader's source code
    /// </summary>
    /// <param name="vShaderFile">filepath to vertex shader</param>
    /// <param name="fShaderFile">filepath to fragment shader</param>
    /// <param name="name">shader name</param>
    /// <returns>shader</returns>
    static Shader loadShader(const char *vShaderFile, const char *fShaderFile, std::string name);

    /// <summary>
    /// Retrieves a stored shader by its name
    /// </summary>
    /// <param name="name">shaders name</param>
    /// <returns>shader</returns>
    static Shader getShader(std::string name);

    /// <summary>
    /// Loads (and generates) a texture from file
    /// </summary>
    /// <param name="file">filepath to bitmap file</param>
    /// <param name="name">textures name</param>
    /// <returns>texture</returns>
    static Texture2D loadTexture(const char *file, std::string name);

    static Texture2D loadCompressedTexture(const char *file, std::string name);

    /// <summary>
    /// Retrieves a stored texture
    /// </summary>
    /// <param name="name">textures name</param>
    /// <returns>texture</returns>
    static Texture2D getTexture(std::string name);

    /// <summary>
    /// Properly de-allocates all loaded resources
    /// </summary>
    static void clear();

  private:
    /// <summary>
    /// Private constructor, that is we do not want any actual resource manager objects. Its members and functions should
    /// be publicly available (static)
    /// </summary>
    ResourceManager() {}

    /// <summary>
    /// Loads and generates a shader from file
    /// </summary>
    /// <param name="vShaderFile">filepath to vertex shader</param>
    /// <param name="fShaderFile">filepath to fragment shader</param>
    /// <returns>shader</returns>
    static Shader loadShaderFromFile(const char *vShaderFile, const char *fShaderFile);

    /// <summary>
    /// Loads a single texture from file
    /// </summary>
    /// <param name="file">filepath to a bitmap file</param>
    /// <returns>texture</returns>
    static Texture2D loadTextureFromFile(const char *file);

    static Texture2D loadTextureFromCompressedFile(const char *file);
};
