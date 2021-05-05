#include <util/resource.hh>

#include <string>
#include <cstdio>

std::pair<int, char *> load_file_content(std::string filename)
{
    char * buffer = nullptr;
    long length = 0;
    size_t size = 0;
    FILE * f = fopen(filename.c_str(), "r");

    std::pair<int, char *> retval;

    if(f)
    {
        fseek(f, 0, SEEK_END);
        length = ftell(f);
        fseek(f, 0, SEEK_SET);
        buffer = (char *)malloc(length + 1);

        retval.first = 0;

        if(buffer)
        {
            size = fread(buffer, 1, length, f);
            if(size != length)
            {
                printf("%s: read operation was not able to read the entire file\n", filename.c_str());
                retval.first = -1;
            }
        }

        fclose(f);

        retval.second = buffer;
        buffer[length] = '\0';
    }
    else
    {
        printf("Error opening file : %s\n", filename.c_str());
        perror("Unable to open specified file source");

        retval.first = -1;
    }

    retval.second = buffer;

    return retval;
}