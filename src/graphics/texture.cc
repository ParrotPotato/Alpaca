#include <graphics/texture.hh>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <iostream>


std::unordered_map<std::string, std::pair<int, Texture>> TextureResourceHandler::resource_map;
SDL_mutex * TextureResourceHandler::mutex;

bool TextureResourceHandler::initialise()
{
    stbi_set_flip_vertically_on_load(1);
    mutex = SDL_CreateMutex();
    if(mutex == NULL) return false;
    else return true;
}

Texture TextureResourceHandler::load_texture(std::string sourcepath)
{
    if(resource_map.find(sourcepath) != resource_map.end())
    {
        // increasing the reference count
        resource_map[sourcepath].first += 1;
        return resource_map[sourcepath].second;
    }

    int width, height, nrchannel;
    unsigned char * texture_data = stbi_load(sourcepath.c_str(), &width, &height, &nrchannel, 0);

    if(!texture_data)
    {
        return Texture();
    }

    GLuint texture_id;
    glGenTextures(1, &texture_id);
    glBindTexture(GL_TEXTURE_2D, texture_id);

    // TODO(nitesh) : Figure out how to know the exact bytes alignment of the textures
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    // setting up the texture information wrt buffer like wrapping etc

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    if (nrchannel == STBI_rgb_alpha)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, texture_data);
    }
    else if (nrchannel == STBI_rgb)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, texture_data);
    }

    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(texture_data);

    Texture texture;
    texture.source = sourcepath;
    texture.id = texture_id;
    texture.height = height;
    texture.width = width;
    texture.nrchannel = nrchannel;

    resource_map[sourcepath] = std::make_pair(1, texture);

    return texture;
}

void TextureResourceHandler::unload_texture(Texture & texture)
{
    std::string deletepath = "";
    for(auto & entry : resource_map)
    {
        std::string sourcepath = entry.first;
        int refcount = entry.second.first;
        Texture texture = entry.second.second;

        if(sourcepath.compare(texture.source) == 0)
        {
            if(refcount == 1)
            {
                glDeleteTextures(1, &texture.id);
                deletepath = sourcepath;
            }
            else 
            {
                // updating the reference counter
                entry.second.first -= 1;
            }
            break;
        }
    }

    // if deletepath is not equal to ""
    if(deletepath.compare(""))
    {
        resource_map.erase(deletepath);
    }

    // making the unloaded Texture unusable for loading textures

    texture = Texture();

    return;
}