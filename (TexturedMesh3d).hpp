#include <fstream>
#include <string>
#include <vector>

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL_image.h>

using namespace std;

namespace TIE {
  class TexturedMesh3d {
    private:
      double* vertice;
      double* normals;
      double* textureCoords;

      size_t vertexCount;
      unsigned int textureId;

    public:
      TexturedMesh3d() {
        vertexCount = textureId = 0;
      }

      ~TexturedMesh3d() {
        delete[] vertice;
        delete[] normals;
        delete[] textureCoords;
      }

      void loadMesh(const char* fileName) {
        ifstream file(fileName);
        if (file.is_open()) {
          int index;
          string text;
          double component;

          vector<double> tmpVertice;
          vector<double> tmpNormals;
          vector<double> tmpTextureCoords;

          vector<int> vertexIndices;
          vector<int> normalIndices;
          vector<int> textureCoordIndices;

          // Parse file
          while (!file.eof()) {
            text = "";
            file >> text;
            switch (text[0]) {
              case 'v':
                if (text.size() == 2) {
                  // Normal
                  if (text[1] == 'n') {
                    file >> component; tmpNormals.push_back(component);
                    file >> component; tmpNormals.push_back(component);
                    file >> component; tmpNormals.push_back(component);
                  }
                  // Texture Coordinate
                  else {
                    file >> component; tmpTextureCoords.push_back(component);
                    file >> component; tmpTextureCoords.push_back(component);
                  }
                }
                // Vertex
                else {
                  file >> component; tmpVertice.push_back(component);
                  file >> component; tmpVertice.push_back(component);
                  file >> component; tmpVertice.push_back(component);
                }
                break;
              // Face
              case 'f':
                for (unsigned char i = 0; i < 3; i++) {
                  file >> index; vertexIndices.push_back(index - 1); file.ignore(1);
                  file >> index; textureCoordIndices.push_back(index - 1); file.ignore(1);
                  file >> index; normalIndices.push_back(index - 1);
                }
                break;
              // Other
              default:
                file.ignore(30, 10);
            }
          }

          file.close();

          // Create arrays
          vertexCount = vertexIndices.size();
          vertice = new double[vertexCount * 3];
          normals = new double[vertexCount * 3];
          textureCoords = new double[vertexCount * 2];

          // Fill arrays
          size_t index2, index3, vIndex, nIndex, tIndex;
          for (size_t i = 0; i < vertexCount; i++) {
            vIndex = vertexIndices[i] * 3; nIndex = normalIndices[i] * 3; tIndex = textureCoordIndices[i] * 2;
            index3 = i * 3; index2 = i *2;

            vertice[index3] = tmpVertice[vIndex++];
            normals[index3++] = tmpNormals[nIndex++];
            textureCoords[index2++] = tmpTextureCoords[tIndex++];

            vertice[index3] = tmpVertice[vIndex++];
            normals[index3++] = tmpNormals[nIndex++];
            textureCoords[index2] = tmpTextureCoords[tIndex];

            vertice[index3] = tmpVertice[vIndex];
            normals[index3] = tmpNormals[nIndex];
          }
        }
      }

      void loadTexture(const char* fileName) {
        glGenTextures(1, &textureId);
        glBindTexture(GL_TEXTURE_2D, textureId);

        SDL_Surface* sdlSurface = IMG_Load(fileName);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, sdlSurface->w, sdlSurface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, sdlSurface->pixels);
        SDL_FreeSurface(sdlSurface);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);        
      }

      void draw() {
        glBindTexture(GL_TEXTURE_2D, textureId);

        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_NORMAL_ARRAY);
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);

        glVertexPointer(3, GL_DOUBLE, 0, vertice);
        glNormalPointer(GL_DOUBLE, 0, normals);
        glTexCoordPointer(2, GL_DOUBLE, 0, textureCoords);

        glDrawArrays(GL_TRIANGLES, 0, vertexCount);

        glDisableClientState(GL_VERTEX_ARRAY);
        glDisableClientState(GL_NORMAL_ARRAY);
        glDisableClientState(GL_TEXTURE_COORD_ARRAY);        
      }
  };
}