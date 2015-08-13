#ifndef TGATEXTURE_H  
#define TGATEXTURE_H  

#include <GL/glut.h>  
#include <iostream>  
  
using  namespace  std;  
  
//紋理結構體定義  
typedef  struct  
{  
    GLubyte *imageData; //圖像數據  
    GLuint bpp; //像素深度  
    GLuint width; //圖像寬度  
    GLuint height; //圖像高度  
    GLuint texID; //對應的紋理ID  
}TextureImage;  
  
//加載TGA圖像，生成紋理  
bool  LoadTGA(TextureImage *texture,const char  *fileName);  
  
#endif  