#ifndef TEXTURE_HH
#define TEXTURE_HH

#include <SDL2/SDL.h>
#include <GL/glew.h>

#include <unordered_map>
#include <string>

struct Texture
{
    std::string source = "";

    GLuint id = 0;

    int width = 0;
    int height = 0;
    int nrchannel = 0;

    Texture() = default;
};

// Do we really need texture loading with mutex because opengl would 
// be running through a single thread thus all texture would be loaded
// via the same thread

struct TextureResourceHandler
{
    static std::unordered_map<std::string, std::pair<int, Texture>> resource_map;
    static SDL_mutex * mutex; // check

    static bool initialise(void);

    static Texture load_texture(std::string sourcepath);
    static void unload_texture(Texture & texture);
};


#endif