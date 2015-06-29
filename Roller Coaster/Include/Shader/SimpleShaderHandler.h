//--------------------------------------------------------- 
// 作者: DR 
// 2013/11/4 
// 
// GLSL&GLUT 從環境設定開始的基礎教學(01) 
//--------------------------------------------------------- 
// 
#pragma once
#include <glew.h>
#include <iostream> 
#include <GL/freeglut.h>
#include <vector> 
#include <string> 
#include <fstream> 


void loadFile( const char* filename, std::string &string ) 
{ 
   std::ifstream fp(filename); 
   if( !fp.is_open() ){ 
      std::cout << "Open <" << filename << "> error." << std::endl;
	  system("pause");
      return; 
   } 

   char temp[300]; 
   while( !fp.eof() ){ 
      fp.getline( temp, 300 ); 
      string += temp; 
      string += '\n'; 
   } 
   fp.close(); 
} 

GLuint loadShader(std::string &source, GLenum type) 
{ 
   GLuint ShaderID; 
   ShaderID = glCreateShader(type);      // 告訴OpenGL我們要創的是哪種shader 

   const char* csource = source.c_str();   // 把std::string結構轉換成const char* 
    
   glShaderSource( ShaderID, 1, &csource, NULL );      // 把程式碼放進去剛剛創建的shader object中 
   glCompileShader( ShaderID );                  // 編譯shader 
   char error[1000] = ""; 
   glGetShaderInfoLog( ShaderID, 1000, NULL, error );   // 這是編譯過程的訊息, 錯誤什麼的把他丟到error裡面 
   std::cout << "Complie status: \n" << error << std::endl;   // 然後輸出出來 
    
   return ShaderID; 
} 

GLuint vs, fs, program;      // 用來儲存shader還有program的id 

void initShader(const char* vname, const char* fname)
{
	std::string source;

	loadFile(vname, source);      // 把程式碼讀進source 
	vs = loadShader(source, GL_VERTEX_SHADER);   // 編譯shader並且把id傳回vs 
	source = "";
	loadFile(fname, source);
	fs = loadShader(source, GL_FRAGMENT_SHADER);

	program = glCreateProgram();   // 創建一個program 
	glAttachShader(program, vs);   // 把vertex shader跟program連結上 
	glAttachShader(program, fs);   // 把fragment shader跟program連結上 

	glLinkProgram(program);      // 根據被連結上的shader, link出各種processor 
	glUseProgram(program);      // 然後使用它 
}

void clean() 
{ 
   glDetachShader( program, vs ); 
   glDetachShader( program, fs ); 
   glDeleteShader( vs ); 
   glDeleteShader( fs ); 
   glDeleteProgram( program ); 
} 