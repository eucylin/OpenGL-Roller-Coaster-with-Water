#ifndef TRAINVIEW_H  
#define TRAINVIEW_H  
#include <QtOpenGL/QGLWidget>  
#include <QtGui/QtGui>  
#include <QtOpenGL/QtOpenGL>  
//#include <GL/freeglut.h>
#include <iostream>
#include <vector>
#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"glu32.lib") 
#include "Utilities/ArcBallCam.H"
#include "Utilities/3DUtils.H"
#include "Track.H"

#include "Load3DModel/Model.h"
#include "Load3DModel/point3d.h"

#include "Load3DModel/3DSLoader.h"
#include "Load3DModel/CbmpLoader.h"
#include "Load3DModel/vector.h"
#include "Load3DModel/TGATexture.h"


//#include "glm/glm.hpp"
//#include "glm/gtc/matrix_transform.hpp"
//#include "glm/gtc/type_ptr.hpp"

using namespace std;

class AppMain;
class CTrack;

//#######################################################################
// TODO
// You might change the TrainView in order to add different objects to
// be drawn, or adjust the lighting, or ...
//#######################################################################


class TrainView : public QGLWidget, protected QOpenGLFunctions
{  
	Q_OBJECT  
public:  
	explicit TrainView(QWidget *parent = 0);  
	~TrainView();  
	enum eSkyBox{
		blood = 0,
		cloudLightRay,
		DarkStormy,
		FullMoon,
		SunSet,
		ThickCloudsWater,
		TropicalSunnyDay
	};
	enum eShader{
		NONE = -1,
		wood = 0,
		dimple,
		kill,
		sWater,
		Phong
	};

public:
	virtual void initializeGL();
	// overrides of important window things
	//virtual int handle(int);
	virtual void paintGL();

	// all of the actual drawing happens in this routine
	// it has to be encapsulated, since we draw differently if
	// we're drawing shadows (no colors, for example)
	void drawStuff(bool doingShadows=false);

	//[Cloud_Lin]
	void myDrawFloor();
	void drawTrack(bool doingShadows = false);
	void drawTrain(float, bool doingShadows = false);
	void drawCubeSets(eShader shadeName = eShader::NONE);
	// setup the projection - assuming that the projection stack has been
	// cleared for you
	void setProjection();

	// Reset the Arc ball control
	void resetArcball();

	// pick a point (for when the mouse goes down)
	void doPick(int mx, int my);

	//[Cloud_Lin]
	void LoadObj(QString m_fileName){
		Mobj = new Model(m_fileName, 1.0,
			Point3d(m_pTrack->points[0].pos.x, m_pTrack->points[0].pos.y, m_pTrack->points[0].pos.z));
	}
	void RenderObj(){
		Mobj->render(true, true);
	}

	void readSkyBox(eSkyBox skyBoxName = eSkyBox::blood);
	void drawSkyBox(eSkyBox skyBoxName = eSkyBox::blood);
	void drawWater();

	void ApplyShader(eShader shaderName = eShader::NONE);

public:
	ArcBallCam		arcball;			// keep an ArcBall for the UI
	int				selectedCube;  // simple - just remember which cube is selected

	CTrack*			m_pTrack;		// The track of the entire scene

	int camera;
	int curve;
	int track;
	bool isrun;

	//[Cloud_Lin]
	float t_time = 0;
	unsigned int DIVIDE_LINE = 1000;
	Pnt3f qt, qt0, qt1, tt0, tt1, orient_t, cross_t;
	vector<Pnt3f> samplePoints;

	typedef enum{
		spline_Linear = 0,
		spline_CardinalCubic = 1,
		spline_CubicB_Spline = 2
	} spline_t;

	enum track_t{
		Line = 0,
		Track = 1,
		Road = 2
	};

	Model *Mobj;
	C3DSLoader M3ds;
	Pnt3f modelPos0, modelPos1;
	//TextureImage arrSkyboxTexture[6];
	GLuint arrSkyboxTexture[6];
	GLuint floorTexID = 0;
	TextureImage moonTex;
	GLuint program1, woodProgram, dimpleProgram, killProgram, sWaterProgram, PhongProgram;
	vector<Pnt3f> cubePntSets;
	float cubeTime = 0,cubeFreq = 0.0001;
	eShader nowCubeShader = eShader::NONE;

	GLfloat waveTime = 0.5,
		waveWidth = 0.6,
		waveHeight = 0.9,
		waveFreq = 0.0004;
	GLuint sWaterTex[3];

	/*float MatCardinal[4][4];*/
	/*mat MatCard = mat(4, 4);*/

	//glm::mat4 MatCardinal = glm::mat4
	//	(-1, 3, -3, 1,
	//	2, -5, 4, -1,
	//	-1, 0, 1, 0,
	//	0, 2, 0, 0);

};  
#endif // TRAINVIEW_H  