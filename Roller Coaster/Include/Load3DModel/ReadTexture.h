#include <QtOpenGL/QGLWidget>
#include <QtOpenGL/QtOpenGL>
#include <QtOpenGL/QGL>
#include <QtOpenGL/qgl.h>
#include <QtGui/QtGui>
#include <iostream>
GLuint ReadTexture(const char *texturePath) {
	GLuint texID;
	QImage textureImg;// = QImage(texturePath);
	textureImg.load(texturePath);
	QSize sss = textureImg.size();
	if (textureImg.isNull())
		qDebug() << "Error when loading texture img";
	textureImg = QGLWidget::convertToGLFormat(textureImg);

	glGenTextures( 1, &texID );
	glBindTexture( GL_TEXTURE_2D, texID );

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureImg.width(), textureImg.height(), 0, GL_RGBA,
	             GL_UNSIGNED_BYTE, textureImg.bits());
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glBindTexture( GL_TEXTURE_2D, 0 );

	return texID;
}