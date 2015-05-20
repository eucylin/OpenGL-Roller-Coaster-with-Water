#ifndef TRAINVIEW_H  
#define TRAINVIEW_H  
#include <QtOpenGL/QGLWidget>  
#include <QtGui/QtGui>  
#include <QtOpenGL/QtOpenGL>  
#include <GL/freeglut.h>
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
class AppMain;
class CTrack;

//#######################################################################
// TODO
// You might change the TrainView in order to add different objects to
// be drawn, or adjust the lighting, or ...
//#######################################################################


class TrainView : public QGLWidget  
{  
	Q_OBJECT  
public:  
	explicit TrainView(QWidget *parent = 0);  
	~TrainView();  

public:
	// overrides of important window things
	//virtual int handle(int);
	virtual void paintGL();

	// all of the actual drawing happens in this routine
	// it has to be encapsulated, since we draw differently if
	// we're drawing shadows (no colors, for example)
	void drawStuff(bool doingShadows=false);

	//[Cloud_Lin]
	void drawTrack(bool doingShadows = false);
	void drawTrain(float, bool doingShadows = false);

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

	typedef enum{
		spline_Linear = 0,
		spline_CardinalCubic = 1,
		spline_CubicB_Spline = 2
	} spline_t;

	Model *Mobj;
	C3DSLoader M3ds;

};  
#endif // TRAINVIEW_H  