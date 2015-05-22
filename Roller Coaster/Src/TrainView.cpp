#include "TrainView.h"  

#include "Load3DModel/Model.h"
#include "Load3DModel/point3d.h"

#include "Load3DModel/3DSLoader.h"
#include "Load3DModel/CbmpLoader.h"
#include "Load3DModel/vector.h"

//#include "glm/glm.hpp"
//#include "glm/gtc/matrix_transform.hpp"
//#include "glm/gtc/type_ptr.hpp"
#include "armadillo"

#include <cmath>
#include <algorithm>

using namespace std;
using namespace arma;

TrainView::TrainView(QWidget *parent) :  
QGLWidget(parent)  
{
	//MatCard << -1 << 2 << -1 << 0 << endr
	//	<< 3 << -5 << 0 << 2 << endr
	//	<< -3 << 4 << 1 << 0 << endr
	//	<< 1 << -1 << 0 << 0 << endr;

	resetArcball();
}  
TrainView::~TrainView()  
{}  

void TrainView:: resetArcball()
	//========================================================================
{
	// Set up the camera to look at the world
	// these parameters might seem magical, and they kindof are
	// a little trial and error goes a long way
	arcball.setup(this, 40, 250, .2f, .4f, 0);
}

bool once = true;
void TrainView::paintGL()
{
	//Init once
	if (once){
		once = false;
		Mobj = new Model("D:/Downloads/ToyTrain/Toy Train.obj", 15.0,
			Point3d(m_pTrack->points[0].pos.x, m_pTrack->points[0].pos.y, m_pTrack->points[0].pos.z));
		
		//M3ds.Init("D:/Users/Chien-Hsuan/Documents/Visual Studio 2013/Projects/RollerCoaster/Win32/Debug/ToyTrain/Toy Train.3ds");
	}

	//*********************************************************************
	//
	// * Set up basic opengl informaiton
	//
	//**********************************************************************
	// Set up the view port
	glViewport(0,0,width(),height());

	// clear the window, be sure to clear the Z-Buffer too
	glClearColor(0,0,.3f,0);		// background should be blue

	// we need to clear out the stencil buffer since we'll use
	// it for shadows
	glClearStencil(0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	glEnable(GL_DEPTH);

	// Blayne prefers GL_DIFFUSE
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

	// prepare for projection
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	setProjection();		// put the code to set up matrices here

	//######################################################################
	// TODO: 
	// you might want to set the lighting up differently. if you do, 
	// we need to set up the lights AFTER setting up the projection
	//######################################################################
	// enable the lighting
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	// top view only needs one light
	if (this->camera == 1) {
		glDisable(GL_LIGHT1);
		glDisable(GL_LIGHT2);
	} else {
		glEnable(GL_LIGHT1);
		glEnable(GL_LIGHT2);
	}

	//*********************************************************************
	//
	// * set the light parameters
	//
	//**********************************************************************
	GLfloat lightPosition1[]	= {0,1,1,0}; // {50, 200.0, 50, 1.0};
	GLfloat lightPosition2[]	= {1, 0, 0, 0};
	GLfloat lightPosition3[]	= {0, -1, 0, 0};
	GLfloat yellowLight[]		= {0.5f, 0.5f, .1f, 1.0};
	GLfloat whiteLight[]		= {1.0f, 1.0f, 1.0f, 1.0};
	GLfloat blueLight[]			= {.1f,.1f,.3f,1.0};
	GLfloat grayLight[]			= {.3f, .3f, .3f, 1.0};

	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition1);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, whiteLight);
	glLightfv(GL_LIGHT0, GL_AMBIENT, grayLight);

	glLightfv(GL_LIGHT1, GL_POSITION, lightPosition2);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, yellowLight);

	glLightfv(GL_LIGHT2, GL_POSITION, lightPosition3);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, blueLight);



	//*********************************************************************
	// now draw the ground plane
	//*********************************************************************
	setupFloor();
	glDisable(GL_LIGHTING);
	drawFloor(200,10);


	//*********************************************************************
	// now draw the object and we need to do it twice
	// once for real, and then once for shadows
	//*********************************************************************
	glEnable(GL_LIGHTING);
	setupObjects();

	drawStuff();

	// this time drawing is for shadows (except for top view)
	if (this->camera != 1) {
		setupShadows();
		drawStuff(true);
		unsetupShadows();
	}
}

//************************************************************************
//
// * This sets up both the Projection and the ModelView matrices
//   HOWEVER: it doesn't clear the projection first (the caller handles
//   that) - its important for picking
//========================================================================
void TrainView::
setProjection()
//========================================================================
{
	// Compute the aspect ratio (we'll need it)
	float aspect = static_cast<float>(width()) / static_cast<float>(height());

	// Check whether we use the world camp
	if (this->camera == 0){
		arcball.setProjection(false);
		update();
	// Or we use the top cam
	}else if (this->camera == 1) {
		float wi, he;
		if (aspect >= 1) {
			wi = 110;
			he = wi / aspect;
		} 
		else {
			he = 110;
			wi = he * aspect;
		}

		// Set up the top camera drop mode to be orthogonal and set
		// up proper projection matrix
		glMatrixMode(GL_PROJECTION);
		glOrtho(-wi, wi, -he, he, 200, -200);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glRotatef(-90,1,0,0);
		update();
	}
	else if (this->camera == 2){
		glMatrixMode(GL_PROJECTION);
		gluPerspective(120, 1, 1, 200); 
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		//qt0.normalize();
		//qt.normalize();
		gluLookAt(tt0.x, tt0.y + 20, tt0.z,
			tt1.x, tt1.y + 20, tt1.z,
			orient_t.x, orient_t.y + 20, orient_t.z);
		update();
	}
	// Or do the train view or other view here
	//####################################################################
	// TODO: 
	// put code for train view projection here!	
	//####################################################################
	else {
#ifdef EXAMPLE_SOLUTION
		trainCamView(this,aspect);
#endif
		update();
	}
}

//************************************************************************
//
// * this draws all of the stuff in the world
//
//	NOTE: if you're drawing shadows, DO NOT set colors (otherwise, you get 
//       colored shadows). this gets called twice per draw 
//       -- once for the objects, once for the shadows
//########################################################################
// TODO: 
// if you have other objects in the world, make sure to draw them
//########################################################################
//========================================================================


void TrainView::drawStuff(bool doingShadows)
{
	// Draw the control points
	// don't draw the control points if you're driving 
	// (otherwise you get sea-sick as you drive through them)
	if (this->camera != 2) {
		for(size_t i = 0; i < this->m_pTrack->points.size(); ++i) {
			if (!doingShadows) {
				if ( ((int) i) != selectedCube)
					glColor3ub(240, 60, 60);
				else
					glColor3ub(240, 240, 30);
			}
			this->m_pTrack->points[i].draw();
		}
		update();
	}
	// draw the track
	//####################################################################
	// TODO: 
	// call your own track drawing code
	//####################################################################
	Mobj->render(false, false);
	drawTrack(doingShadows);

#ifdef EXAMPLE_SOLUTION
	drawTrack(this, doingShadows);
#endif
	// draw the train
	//####################################################################
	// TODO: 
	//	call your own train drawing code
	//####################################################################
	
	/*M3ds.Draw();*/
	drawTrain(t_time, doingShadows);

#ifdef EXAMPLE_SOLUTION
	// don't draw the train if you're looking out the front window
	if (!tw->trainCam->value())
		drawTrain(this, doingShadows);
#endif
}

float MatCardinal[4][4] =
{
	{ -1 / 2.0, 2 / 2.0, -1 / 2.0, 0 },
	{ 3 / 2.0, -5 / 2.0, 0, 2 / 2.0 },
	{ -3 / 2.0, 4 / 2.0, 1 / 2.0, 0 },
	{ 1 / 2.0, -1 / 2.0, 0, 0 }
	};
float MatBspline[4][4] =
{
	{ -1 / 6.0, 3 / 6.0, -3 / 6.0, 1 / 6.0 },
	{ 3 / 6.0, -6 / 6.0, 0, 4 / 6.0 },
	{ -3 / 6.0, 3 / 6.0, 3 / 6.0, 1 / 6.0 },
	{ 1 / 6.0 ,0,0,0}
};
void TrainView::drawTrack(bool doingShadows)
{
	track_t type_track = (track_t)track;
	spline_t type_spline = (spline_t)curve;
	samplePoints.clear();
	for (size_t i = 0; i < m_pTrack->points.size(); ++i)
	{
		// pos
		Pnt3f cp_pos_p1 = m_pTrack->points[i].pos;
		Pnt3f cp_pos_p2 = m_pTrack->points[(i + 1) % m_pTrack->points.size()].pos;
		Pnt3f cp_pos_p3 = m_pTrack->points[(i + 2) % m_pTrack->points.size()].pos;
		Pnt3f cp_pos_p4 = m_pTrack->points[(i + 3) % m_pTrack->points.size()].pos;

		Pnt3f cp_pos[4] = { cp_pos_p1,	cp_pos_p2,	cp_pos_p3,	cp_pos_p4	};

		// orient
		Pnt3f cp_orient_p1 = m_pTrack->points[i].orient;
		Pnt3f cp_orient_p2 = m_pTrack->points[(i + 1) % m_pTrack->points.size()].orient;

		qt = qt1;
		float percent = 1.0f / DIVIDE_LINE;
		float t = 0;
		for (size_t j = 0; j < DIVIDE_LINE; j++){
			qt0 = qt;
			switch (type_spline){
			case spline_Linear:
				orient_t = (1 - t) * cp_orient_p1 + t * cp_orient_p2;
				break;
			case spline_CardinalCubic:
				orient_t = (1 - t) * cp_orient_p1 + t * cp_orient_p2;
				break;
			case spline_CubicB_Spline:
				orient_t = (1 - t) * cp_orient_p1 + t * cp_orient_p2;
				break;
			}

			t += percent;
			switch (type_spline){
			case spline_Linear:
				qt = (1 - t) * cp_pos_p1 + t * cp_pos_p2;
				break;
			case spline_CardinalCubic:
			case spline_CubicB_Spline:
				float T[4] = {t*t*t, t*t, t, 1};
				float MT[4] = { 0 };
				Pnt3f GMT(0,0,0);
				for (int i = 0; i < 4; i++){
					for (int j = 0; j < 4; j++){
						if (type_spline == spline_CardinalCubic)
							MT[i] += MatCardinal[i][j] * T[j];
						else if (type_spline == spline_CubicB_Spline)
							MT[i] += MatBspline[i][j] * T[j];
					}
					GMT = GMT + cp_pos[i] * MT[i];
				}
				if (t < DIVIDE_LINE / 4)
					samplePoints.push_back(GMT);
				qt = GMT;
				break;
				//colvec4 T;
				//T << t*t*t << t*t << t << 1;
				//rowvec4 Cx, Cy, Cz;
				//Cx << cp_pos_p1.x << cp_pos_p2.x << cp_pos_p3.x << cp_pos_p4.x;
				//Cy << cp_pos_p1.y << cp_pos_p2.y << cp_pos_p3.y << cp_pos_p4.y;
				//Cz << cp_pos_p1.z << cp_pos_p2.z << cp_pos_p3.z << cp_pos_p4.z;
				//colvec3 ResX = Cx * 1.0 / 2.0 * MatCard * T;
				//colvec3 ResY = Cy * 1.0 / 2.0 * MatCard * T;
				//colvec3 ResZ = Cz * 1.0 / 2.0 * MatCard * T;
				//qt.x = ResX(0,0);
				//qt.y = ResY(0,0);
				//qt.z = ResZ(0,0);
				//mat U = Cx * MatCard * T;
				//Res << vec4(cp_pos_p1.x, cp_pos_p2.x, cp_pos_p3.x, cp_pos_p4.x) * MatCard * T
				//	<< 1 
				//	<< 1;
				//glm::vec4 T = glm::vec4(t*t*t, t*t, t, 1);
				//glm::vec4 Gx = glm::vec4(cp_pos_p1.x, cp_pos_p2.x, cp_pos_p3.x, cp_pos_p4.x);
				//glm::vec4 kk = glm::vec4(Gx * MatCardinal * T,0.1,0.5,0.5);
				//glm::vec3 tmp = glm::vec3(
				//	glm::vec4(cp_pos_p1.x, cp_pos_p2.x, cp_pos_p3.x, cp_pos_p4.x) * MatCardinal * T,
				//	glm::vec4(cp_pos_p1.y, cp_pos_p2.y, cp_pos_p3.y, cp_pos_p4.y) * MatCardinal * T,
				//	glm::vec4(cp_pos_p1.z, cp_pos_p2.z, cp_pos_p3.z, cp_pos_p4.z) * MatCardinal * T);
				//qt.x = tmp.x; qt.y = tmp.y; qt.z = tmp.z;
			}
			qt1 = qt;

			switch (type_track)
			{
			case TrainView::Line:
				glLineWidth(10);
				glBegin(GL_LINES);
				if (!doingShadows){
					glColor3ub(32, 32, 64);
				}
				glVertex3f(qt0.x, qt0.y, qt0.z);
				glVertex3f(qt1.x, qt1.y, qt1.z);
				glEnd();
				glLineWidth(1);
				break;
			case TrainView::Track:
				//Calculate cross
				orient_t.normalize();
				cross_t = (qt1 - qt0) * orient_t;
				cross_t.normalize();
				cross_t = cross_t * 2.5f;

				//draw two parallel track
				glLineWidth(3);
				glBegin(GL_LINES);
				if (!doingShadows){
					glColor3ub(0, 0, 0);
				}
				glVertex3f(qt0.x + cross_t.x, qt0.y + cross_t.y, qt0.z + cross_t.z);
				glVertex3f(qt1.x + cross_t.x, qt1.y + cross_t.y, qt1.z + cross_t.z);

				glVertex3f(qt0.x - cross_t.x, qt0.y - cross_t.y, qt0.z - cross_t.z);
				glVertex3f(qt1.x - cross_t.x, qt1.y - cross_t.y, qt1.z - cross_t.z);

				glEnd();
				glLineWidth(1);

				//Draw crosstie
				if ((int)(t * DIVIDE_LINE) % 100 == 1){
					glLineWidth(50);
					glBegin(GL_LINES);
					if (!doingShadows){
						glColor3ub(255, 204, 0);
					}
					glVertex3f(qt0.x + cross_t.x, qt0.y + cross_t.y, qt0.z + cross_t.z);
					glVertex3f(qt0.x - cross_t.x, qt0.y - cross_t.y, qt0.z - cross_t.z);

					glEnd();
					glLineWidth(1);
				}
				break;
			case TrainView::Road:
				break;
			default:
				break;
			}
		}
	}
}

void TrainView::drawTrain(float t, bool doingShadows)
{
	spline_t type_spline = (spline_t)curve;
	float Lt = t * m_pTrack->points.size();
	size_t i;
	for (i = 0; Lt > 1; Lt -= 1)
		i++;

	// pos
	Pnt3f cp_pos_p1 = m_pTrack->points[i].pos;
	Pnt3f cp_pos_p2 = m_pTrack->points[(i + 1) % m_pTrack->points.size()].pos;
	// orient
	Pnt3f cp_orient_p1 = m_pTrack->points[i].orient;
	Pnt3f cp_orient_p2 = m_pTrack->points[(i + 1) % m_pTrack->points.size()].orient;
		
	switch (type_spline){
	case spline_Linear:
		// Linear
		tt0 = (1 - (Lt - 0.01)) * cp_pos_p1 + (Lt - 0.01) * cp_pos_p2;
		tt1 = (1 - Lt) * cp_pos_p1 + Lt * cp_pos_p2;
		orient_t = (1 - Lt) * cp_orient_p1 + Lt * cp_orient_p2;
		break; 
	case spline_CardinalCubic:
	case spline_CubicB_Spline:
		tt0 = samplePoints[floor(t * samplePoints.size()) - 1];
		tt1 = samplePoints[floor(t * samplePoints.size())];
		break; 
	}

	glColor3ub(255, 255, 255);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(tt1.x - 5, tt1.y - 5, tt1.z - 5);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(tt1.x + 5, tt1.y - 5, tt1.z - 5);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(tt1.x + 5, tt1.y + 5, tt1.z - 5);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(tt1.x - 5, tt1.y + 5, tt1.z - 5);
	glEnd();

}

void TrainView::
	doPick(int mx, int my)
	//========================================================================
{
	// since we'll need to do some GL stuff so we make this window as 
	// active window
	makeCurrent();

	// get the viewport - most reliable way to turn mouse coords into GL coords
	int viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity ();

	gluPickMatrix((double)mx, (double)(viewport[3]-my), 
		5, 5, viewport);

	// now set up the projection
	setProjection();

	// now draw the objects - but really only see what we hit
	GLuint buf[100];
	glSelectBuffer(100,buf);
	glRenderMode(GL_SELECT);
	glInitNames();
	glPushName(0);


	// draw the cubes, loading the names as we go
	for(size_t i=0; i<m_pTrack->points.size(); ++i) {
		glLoadName((GLuint) (i+1));
		m_pTrack->points[i].draw();
	}

	// go back to drawing mode, and see how picking did
	int hits = glRenderMode(GL_RENDER);
	if (hits) {
		// warning; this just grabs the first object hit - if there
		// are multiple objects, you really want to pick the closest
		// one - see the OpenGL manual 
		// remember: we load names that are one more than the index
		selectedCube = buf[3]-1;
	} else // nothing hit, nothing selected
		selectedCube = -1;
}
