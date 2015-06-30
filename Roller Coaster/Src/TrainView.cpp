#include "opencv/cv.h"
#include "opencv/highgui.h"

//#include "Shader/SimpleShaderHandler.h"
#include "Shader/Shader_Loader.h"

#include "TrainView.h"  
#include "Load3DModel/TGATexture.h"  
#include "Load3DModel/ReadTexture.h"

#include "Load3DModel/Model.h"
#include "Load3DModel/point3d.h"

#include "Load3DModel/3DSLoader.h"
#include "Load3DModel/vector.h"
#include "Utilities/ArcBallCam.H"
#include <string>
#include <cstdio>
//#include "glm/glm.hpp"
//#include "glm/gtc/matrix_transform.hpp"
//#include "glm/gtc/type_ptr.hpp"
#include <vector>
#include <cmath>
#include <algorithm>


using namespace std;

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

void TrainView::initializeGL()
{
	initializeOpenGLFunctions();
	GLenum err = glewInit();
	printf("OpenGL version supported by this platform (%s): \n", glGetString(GL_VERSION));

	Core::Shader_Loader shaderLoader;
	program1 = shaderLoader.CreateProgram("Vertex_Shader.glsl", "Fragment_Shader.glsl");
	woodProgram = shaderLoader.CreateProgram("Shaders/wood.vert", "Shaders/wood.frag");
	dimpleProgram = shaderLoader.CreateProgram("Shaders/dimple.vert", "Shaders/dimple.frag");
	killProgram = shaderLoader.CreateProgram("Shaders/kill.vert", "Shaders/kill.frag");
	sWaterProgram = shaderLoader.CreateProgram("Shaders/swater.vert", "Shaders/swater.frag");
	PhongProgram = shaderLoader.CreateProgram("Shaders/Phong.vert", "Shaders/Phong.frag");
	//initShader("vertex.vs", "fragment.frag");
	readSkyBox(eSkyBox::blood);

	/*Mobj = new Model("D:/Users/Chien-Hsuan/Documents/Visual Studio 2013/Projects/RollerCoaster/Win32/Debug/Models/colony sector/colony sector.obj", 15.0,
	Point3d(m_pTrack->points[0].pos.x, m_pTrack->points[0].pos.y, m_pTrack->points[0].pos.z));*/
	/*M3ds.Init("D:/Users/Chien-Hsuan/Documents/Visual Studio 2013/Projects/RollerCoaster/Win32/Debug/ToyTrain/Toy Train.3ds");*/
	modelPos0 = Pnt3f(m_pTrack->points[0].pos.x, m_pTrack->points[0].pos.y, m_pTrack->points[0].pos.z);
	//M3ds.Init("D:/Downloads/Little train/Small train.3ds");
	//M3ds.Init("D:/Users/Chien-Hsuan/Documents/Visual Studio 2013/Projects/RollerCoaster/Win32/Debug/GothamTrain/train.3DS");
	//M3ds.Init("D:/Users/Chien-Hsuan/Documents/Visual Studio 2013/Projects/RollerCoaster/Win32/Debug/Models/CODMapShipment/Files/CODMapShipment.3ds");
	//M3ds.Init("D:/Users/Chien-Hsuan/Documents/Visual Studio 2013/Projects/RollerCoaster/Win32/Debug/Models/old fashion town/old town block.3DS");

	//M3ds.Init("D:/Users/Chien-Hsuan/Documents/Visual Studio 2013/Projects/RollerCoaster/Win32/Debug/Models/Train3/Train3S.3DS");
	
	//M3ds.Init("C:/Users/Chien-Hsuan/Desktop/Little_train/Small_train.3ds");
	//CBMPLoader cmbp;
	//cmbp.LoadBitmap("NA1.JPG");
	//LoadTGA(&moonTex, "Various0430_SO.tga");
	floorTexID = ReadTexture("D:/Users/Chien-Hsuan/Documents/Visual Studio 2013/Projects/RollerCoaster/Win32/Debug/rockFloor");
	//sWaterTex[0] = ReadTexture("wattex.png");
	sWaterTex[0] = ReadTexture("sea");

	for (int i = 0; i < 80; i++){
		cubePntSets.push_back(Pnt3f(rand() % 2000 - 1000, 10 + rand() % 800 - 400, rand() % 2000 - 1000));
	}
}

void TrainView::resetArcball()
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
	GLfloat lightPosition1[]	= {1000,1000,0, 0}; // {50, 200.0, 50, 1.0};
	GLfloat lightPosition2[] = { 1000, -1000, 0, 0 };
	GLfloat lightPosition3[] = { -1000, 1000, 0, 0 };
	GLfloat yellowLight[]		= {1000, 1000, .1f, 1.0};
	GLfloat whiteLight[]		= {1.0f, 1.0f, 1.0f, 1.0};
	GLfloat blueLight[]			= {.1f,.1f,.3f,1.0};
	GLfloat grayLight[]			= {.3f, .3f, .3f, 1.0};

	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition1);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, whiteLight);
	glLightfv(GL_LIGHT0, GL_AMBIENT, whiteLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, whiteLight);

	glLightfv(GL_LIGHT1, GL_POSITION, lightPosition2);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, yellowLight);

	glLightfv(GL_LIGHT2, GL_POSITION, lightPosition3);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, blueLight);


	
	//*********************************************************************
	// now draw the ground plane
	//*********************************************************************
	drawSkyBox();
	glDisable(GL_LIGHTING);
	setupFloor();
	//myDrawFloor();
	//drawFloor();

	//*********************************************************************
	// now draw the object and we need to do it twice
	// once for real, and then once for shadows
	//*********************************************************************
	glEnable(GL_LIGHTING);
	setupObjects();
	
	drawStuff(false);
	glDisable(GL_TEXTURE_2D);
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
		glOrtho(-wi, wi, -he, he, 5000, -5000);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glRotatef(-90,1,0,0);
		update();
	}
	else if (this->camera == 2){
		glMatrixMode(GL_PROJECTION);
		gluPerspective(120, 1, .1, 5000); 
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
	/*Mobj->render(false, false);*/
	drawTrack(doingShadows);

#ifdef EXAMPLE_SOLUTION
	drawTrack(this, doingShadows);
#endif
	// draw the train
	//####################################################################
	// TODO: 
	//	call your own train drawing code
	//####################################################################
	
	//M3ds.Draw(modelPos);
	drawTrain(t_time, doingShadows);
	drawCubeSets(eShader::Phong);
	drawWater();
#ifdef EXAMPLE_SOLUTION
	// don't draw the train if you're looking out the front window
	if (!tw->trainCam->value())
		drawTrain(this, doingShadows);
#endif
}

void TrainView::myDrawFloor()
{
	float maxX = 200 / 2, maxY = 200 / 2;
	float minX = -200 / 2, minY = -200 / 2;

	int x, y, v[3], i;
	float xp, yp, xd, yd;
	v[2] = 0;
	xd = (maxX - minX) / ((float)10);
	yd = (maxY - minY) / ((float)10);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, floorTexID);
	glBegin(GL_QUADS);

	glNormal3f(0, 1, 0);
	glTexCoord2f(0, 0); glVertex3d(-55, 0, -55);
	glTexCoord2f(0, 1); glVertex3d(-55, 0, 55);
	glTexCoord2f(1, 1); glVertex3d(55, 0, 55);
	glTexCoord2f(1, 0); glVertex3d(55, 0, -55);

	glEnd();
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);
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

		switch (type_spline){
		case spline_Linear:
			DIVIDE_LINE = floor(sqrt(pow(cp_pos_p2.x - cp_pos_p1.x, 2.0) + pow(cp_pos_p2.y - cp_pos_p1.y, 2.0) + pow(cp_pos_p2.z - cp_pos_p1.z, 2.0)) * 1);
			break;
		case spline_CardinalCubic:
		case spline_CubicB_Spline:
			DIVIDE_LINE = floor(sqrt(pow(cp_pos_p2.x - cp_pos_p3.x, 2.0) + pow(cp_pos_p2.y - cp_pos_p3.y, 2.0) + pow(cp_pos_p2.z - cp_pos_p3.z, 2.0)) * 1);
			break;
		}

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

			//glUseProgram(program1);
			switch (type_track)
			{
			case TrainView::Line:
				glLineWidth(10);
				glBegin(GL_LINES);
				if (!doingShadows){
					glColor3ub(2, 132, 130);
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
				cross_t = cross_t * 4.5f;

				//draw two parallel track
				glLineWidth(10);
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
				if ((int)(t * DIVIDE_LINE) % 50 == 5){
					float cWidthScale = 0.8;
					glLineWidth(50);
					glBegin(GL_QUADS);
					if (!doingShadows){
						glColor3ub(150, 75, 0);
						//glColor3ub(255, 255, 255);
					}
					glVertex3f(qt1.x - cross_t.x, qt1.y - cross_t.y, qt1.z - cross_t.z);
					glVertex3f(qt0.x - cross_t.x, qt0.y - cross_t.y, qt0.z - cross_t.z);
					glVertex3f(qt0.x + cross_t.x, qt0.y + cross_t.y, qt0.z + cross_t.z);
					glVertex3f(qt1.x + cross_t.x, qt1.y + cross_t.y, qt1.z + cross_t.z);

					//Pnt3f oldPoints = samplePoints[floor(samplePoints.size() * 0.95)];
					//glTexCoord2f(0, 1);
					//glVertex3f(qt1.x - cross_t.x, qt1.y - cross_t.y, qt1.z - cross_t.z);
					//glTexCoord2f(0, 0);
					//glVertex3f(oldPoints.x - cross_t.x, oldPoints.y - cross_t.y, oldPoints.z - cross_t.z);
					//glTexCoord2f(1, 0);
					//glVertex3f(oldPoints.x + cross_t.x, oldPoints.y + cross_t.y, oldPoints.z + cross_t.z);
					//glTexCoord2f(1, 1);
					//glVertex3f(qt1.x + cross_t.x, qt1.y + cross_t.y, qt1.z + cross_t.z);
					/*glVertex3f(qt0.x + (cross_t.x)*1.8, qt0.y + (cross_t.y)*1.8, qt0.z + (cross_t.z)*1.8);
					glVertex3f(qt0.x - (cross_t.x)*1.8, qt0.y - (cross_t.y)*1.8, qt0.z - (cross_t.z)*1.8);*/

					glEnd();
					glLineWidth(1);
				}
				break;
			case TrainView::Road:
				break;
			default:
				break;
			}
			//glUseProgram(0);
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
		tt0 = samplePoints[floor(t * (samplePoints.size()-1))];
		tt1 = samplePoints[floor(t * (samplePoints.size()-1)) + 1];
		break; 
	} 
	glColor3ub(0, 0, 0);
	glBegin(GL_QUADS);
	//glTexCoord2f(0.0f, 0.0f);
	glVertex3f(tt1.x - 5, tt1.y - 5, tt1.z - 5);
	//glTexCoord2f(1.0f, 0.0f);
	glVertex3f(tt1.x + 5, tt1.y - 5, tt1.z - 5);
	//glTexCoord2f(1.0f, 1.0f);
	glVertex3f(tt1.x + 5, tt1.y + 5, tt1.z - 5);
	//glTexCoord2f(0.0f, 1.0f);
	glVertex3f(tt1.x - 5, tt1.y + 5, tt1.z - 5);
	glEnd();

	modelPos0 = tt0;
	modelPos1 = tt1;
	/*Mobj->render();*/
	/*if (this->camera != 2)
		M3ds.Draw(modelPos0, modelPos1, orient_t);*/
}

void TrainView::drawCubeSets(eShader shadeName)
{
	glEnable(GL_LIGHTING);
	ApplyShader(shadeName);
	drawCube(0, -55, 0, 112);
	glPushMatrix();
	float cubeSpeed = 1050;
	if (cubeTime >= 1)
		cubeTime = 0;
	if (cubeTime < 0.5)
		glTranslatef(cubeTime*cubeSpeed, 0, 0);
	else
		glTranslatef((1 - cubeTime)*cubeSpeed, 0, 0);
	for (int i = 0; i < cubePntSets.size(); i++)
		drawCube(cubePntSets[i].x, cubePntSets[i].y, cubePntSets[i].z, 30);
	glPopMatrix();
	cubeTime += cubeFreq;
	glUseProgram(0);
}

void TrainView::readSkyBox(eSkyBox skyBoxName)
{
	GLuint _skybox[6];
	vector<string> s_filename;
	s_filename.clear();
	//"D:/Users/Chien-Hsuan/Documents/Visual Studio 2013/Projects/RollerCoaster/Win32/Debug/SkyboxSet1/abc/abcFront2048.png"
	switch (skyBoxName)
	{
	case TrainView::blood:
		s_filename.push_back("blood_ft");
		s_filename.push_back("blood_lf");
		s_filename.push_back("blood_bk");
		s_filename.push_back("blood_rt");
		s_filename.push_back("blood_up");
		s_filename.push_back("blood_dn");
		break;
	case TrainView::cloudLightRay:
		s_filename.push_back("D:/Users/Chien-Hsuan/Documents/Visual Studio 2013/Projects/RollerCoaster/Win32/Debug/SkyboxSet1/CloudyLightRays/CloudyLightRaysFront2048.png");
		s_filename.push_back("D:/Users/Chien-Hsuan/Documents/Visual Studio 2013/Projects/RollerCoaster/Win32/Debug/SkyboxSet1/CloudyLightRays/CloudyLightRaysLeft2048.png");
		s_filename.push_back("D:/Users/Chien-Hsuan/Documents/Visual Studio 2013/Projects/RollerCoaster/Win32/Debug/SkyboxSet1/CloudyLightRays/CloudyLightRaysBack2048.png");
		s_filename.push_back("D:/Users/Chien-Hsuan/Documents/Visual Studio 2013/Projects/RollerCoaster/Win32/Debug/SkyboxSet1/CloudyLightRays/CloudyLightRaysRight2048.png");
		s_filename.push_back("D:/Users/Chien-Hsuan/Documents/Visual Studio 2013/Projects/RollerCoaster/Win32/Debug/SkyboxSet1/CloudyLightRays/CloudyLightRaysUp2048.png");
		s_filename.push_back("D:/Users/Chien-Hsuan/Documents/Visual Studio 2013/Projects/RollerCoaster/Win32/Debug/SkyboxSet1/CloudyLightRays/CloudyLightRaysDown2048.png");
		break;
	case TrainView::DarkStormy:
		s_filename.push_back("D:/Users/Chien-Hsuan/Documents/Visual Studio 2013/Projects/RollerCoaster/Win32/Debug/SkyboxSet1/DarkStormy/DarkStormyFront2048.png");
		s_filename.push_back("D:/Users/Chien-Hsuan/Documents/Visual Studio 2013/Projects/RollerCoaster/Win32/Debug/SkyboxSet1/DarkStormy/DarkStormyLeft2048.png");
		s_filename.push_back("D:/Users/Chien-Hsuan/Documents/Visual Studio 2013/Projects/RollerCoaster/Win32/Debug/SkyboxSet1/DarkStormy/DarkStormyBack2048.png");
		s_filename.push_back("D:/Users/Chien-Hsuan/Documents/Visual Studio 2013/Projects/RollerCoaster/Win32/Debug/SkyboxSet1/DarkStormy/DarkStormyRight2048.png");
		s_filename.push_back("D:/Users/Chien-Hsuan/Documents/Visual Studio 2013/Projects/RollerCoaster/Win32/Debug/SkyboxSet1/DarkStormy/DarkStormyUp2048.png");
		s_filename.push_back("D:/Users/Chien-Hsuan/Documents/Visual Studio 2013/Projects/RollerCoaster/Win32/Debug/SkyboxSet1/DarkStormy/DarkStormyDown2048.png");
		break;
	case TrainView::FullMoon:
		s_filename.push_back("D:/Users/Chien-Hsuan/Documents/Visual Studio 2013/Projects/RollerCoaster/Win32/Debug/SkyboxSet1/FullMoon/FullMoonFront2048.png");
		s_filename.push_back("D:/Users/Chien-Hsuan/Documents/Visual Studio 2013/Projects/RollerCoaster/Win32/Debug/SkyboxSet1/FullMoon/FullMoonLeft2048.png");
		s_filename.push_back("D:/Users/Chien-Hsuan/Documents/Visual Studio 2013/Projects/RollerCoaster/Win32/Debug/SkyboxSet1/FullMoon/FullMoonBack2048.png");
		s_filename.push_back("D:/Users/Chien-Hsuan/Documents/Visual Studio 2013/Projects/RollerCoaster/Win32/Debug/SkyboxSet1/FullMoon/FullMoonRight2048.png");
		s_filename.push_back("D:/Users/Chien-Hsuan/Documents/Visual Studio 2013/Projects/RollerCoaster/Win32/Debug/SkyboxSet1/FullMoon/FullMoonUp2048.png");
		s_filename.push_back("D:/Users/Chien-Hsuan/Documents/Visual Studio 2013/Projects/RollerCoaster/Win32/Debug/SkyboxSet1/FullMoon/FullMoonDown2048.png");
		break;
	case TrainView::SunSet:
		s_filename.push_back("D:/Users/Chien-Hsuan/Documents/Visual Studio 2013/Projects/RollerCoaster/Win32/Debug/SkyboxSet1/SunSet/SunSetFront2048.png");
		s_filename.push_back("D:/Users/Chien-Hsuan/Documents/Visual Studio 2013/Projects/RollerCoaster/Win32/Debug/SkyboxSet1/SunSet/SunSetLeft2048.png");
		s_filename.push_back("D:/Users/Chien-Hsuan/Documents/Visual Studio 2013/Projects/RollerCoaster/Win32/Debug/SkyboxSet1/SunSet/SunSetBack2048.png");
		s_filename.push_back("D:/Users/Chien-Hsuan/Documents/Visual Studio 2013/Projects/RollerCoaster/Win32/Debug/SkyboxSet1/SunSet/SunSetRight2048.png");
		s_filename.push_back("D:/Users/Chien-Hsuan/Documents/Visual Studio 2013/Projects/RollerCoaster/Win32/Debug/SkyboxSet1/SunSet/SunSetUp2048.png");
		s_filename.push_back("D:/Users/Chien-Hsuan/Documents/Visual Studio 2013/Projects/RollerCoaster/Win32/Debug/SkyboxSet1/SunSet/SunSetDown2048.png");
		break;
	case TrainView::ThickCloudsWater:
		s_filename.push_back("D:/Users/Chien-Hsuan/Documents/Visual Studio 2013/Projects/RollerCoaster/Win32/Debug/SkyboxSet1/ThickCloudsWater/ThickCloudsWaterFront2048.png");
		s_filename.push_back("D:/Users/Chien-Hsuan/Documents/Visual Studio 2013/Projects/RollerCoaster/Win32/Debug/SkyboxSet1/ThickCloudsWater/ThickCloudsWaterLeft2048.png");
		s_filename.push_back("D:/Users/Chien-Hsuan/Documents/Visual Studio 2013/Projects/RollerCoaster/Win32/Debug/SkyboxSet1/ThickCloudsWater/ThickCloudsWaterBack2048.png");
		s_filename.push_back("D:/Users/Chien-Hsuan/Documents/Visual Studio 2013/Projects/RollerCoaster/Win32/Debug/SkyboxSet1/ThickCloudsWater/ThickCloudsWaterRight2048.png");
		s_filename.push_back("D:/Users/Chien-Hsuan/Documents/Visual Studio 2013/Projects/RollerCoaster/Win32/Debug/SkyboxSet1/ThickCloudsWater/ThickCloudsWaterUp2048.png");
		s_filename.push_back("D:/Users/Chien-Hsuan/Documents/Visual Studio 2013/Projects/RollerCoaster/Win32/Debug/SkyboxSet1/ThickCloudsWater/ThickCloudsWaterDown2048.png");
		break;
	case TrainView::TropicalSunnyDay:
		s_filename.push_back("D:/Users/Chien-Hsuan/Documents/Visual Studio 2013/Projects/RollerCoaster/Win32/Debug/SkyboxSet1/TropicalSunnyDay/TropicalSunnyDayFront2048.png");
		s_filename.push_back("D:/Users/Chien-Hsuan/Documents/Visual Studio 2013/Projects/RollerCoaster/Win32/Debug/SkyboxSet1/TropicalSunnyDay/TropicalSunnyDayLeft2048.png");
		s_filename.push_back("D:/Users/Chien-Hsuan/Documents/Visual Studio 2013/Projects/RollerCoaster/Win32/Debug/SkyboxSet1/TropicalSunnyDay/TropicalSunnyDayBack2048.png");
		s_filename.push_back("D:/Users/Chien-Hsuan/Documents/Visual Studio 2013/Projects/RollerCoaster/Win32/Debug/SkyboxSet1/TropicalSunnyDay/TropicalSunnyDayRight2048.png");
		s_filename.push_back("D:/Users/Chien-Hsuan/Documents/Visual Studio 2013/Projects/RollerCoaster/Win32/Debug/SkyboxSet1/TropicalSunnyDay/TropicalSunnyDayUp2048.png");
		s_filename.push_back("D:/Users/Chien-Hsuan/Documents/Visual Studio 2013/Projects/RollerCoaster/Win32/Debug/SkyboxSet1/TropicalSunnyDay/TropicalSunnyDayDown2048.png");
		break;
	default:
		break;
	}

	//for (int i = 0; i < 6; i++){
	//	//char tmp[] = s_filename[i];
	//	if (!LoadTGA(&arrSkyboxTexture[i], s_filename[i].c_str()))
	//		qDebug() << "SHIT! Load Skybox Texture Failed";
	//}

	for (int i = 0; i < 6; i++){
		arrSkyboxTexture[i] = ReadTexture(s_filename[i].c_str());
	}
}

void TrainView::drawSkyBox(eSkyBox skyBoxName)
{
	//SKYBOX

	//for (int i = 0; i < 6; i++){
	//	glGenTextures(1, &_skybox[i]);
	//	glBindTexture(GL_TEXTURE_2D, _skybox[i]);
	//	/*CBMPLoader m_image;
	//	m_image.LoadBitmap(s_filename[i].c_str());*/
	//	IplImage *m_image;
	//	m_image = cvLoadImage(s_filename[i].c_str(), 1);
	//	/*FILE *m_image = fopen("s_filename[i]", "rb");*/
	//	glTexImage2D(GL_TEXTURE_2D,// 目标  
	//		0,// 级别  
	//		4,// 纹理内部格式  
	//		512,// 纹理的宽（最好2的次方）  
	//		512,// 纹理的高（最好2的次方）  
	//		0,// 纹理的深度（最好2的次方）  
	//		0x80E1,// 纹理单元格式（GL_BGRA=0x80E1）  
	//		GL_UNSIGNED_BYTE,// 像素的数据类型  
	//		m_image);// 数据指针  );
	//	glEnable(GL_TEXTURE_2D);
	//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	//}

	// Store the current matrix
	/*glPushMatrix();
	glLoadIdentity();*/
	/*glTranslatef(arcball.eyeX, arcball.eyeY, arcball.eyeZ);*/
	/*gluLookAt(
	0, 0, 0,
	arcball.eyeX, arcball.eyeY, arcball.eyeZ,
	0, 1, 0);*/

	// Enable/Disable features
	//glPushAttrib(GL_ENABLE_BIT);

	glEnable(GL_TEXTURE_2D);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glDisable(GL_BLEND);

	// Just in case we set all vertices to white.
	glColor4f(1, 1, 1, 1);

	// Render the front quad
	glBindTexture(GL_TEXTURE_2D, arrSkyboxTexture[0]);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(1500, -1500, -1500);
	glTexCoord2f(1, 0); glVertex3f(-1500, -1500, -1500);
	glTexCoord2f(1, 1); glVertex3f(-1500, 1500, -1500);
	glTexCoord2f(0, 1); glVertex3f(1500, 1500, -1500);
	glEnd();

	// Render the left quad
	glBindTexture(GL_TEXTURE_2D, arrSkyboxTexture[1]);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(1500, -1500, 1500);
	glTexCoord2f(1, 0); glVertex3f(1500, -1500, -1500);
	glTexCoord2f(1, 1); glVertex3f(1500, 1500, -1500);
	glTexCoord2f(0, 1); glVertex3f(1500, 1500, 1500);
	glEnd();

	// Render the back quad
	glBindTexture(GL_TEXTURE_2D, arrSkyboxTexture[2]);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(-1500, -1500, 1500);
	glTexCoord2f(1, 0); glVertex3f(1500, -1500, 1500);
	glTexCoord2f(1, 1); glVertex3f(1500, 1500, 1500);
	glTexCoord2f(0, 1); glVertex3f(-1500, 1500, 1500);

	glEnd();

	// Render the right quad
	glBindTexture(GL_TEXTURE_2D, arrSkyboxTexture[3]);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(-1500, -1500, -1500);
	glTexCoord2f(1, 0); glVertex3f(-1500, -1500, 1500);
	glTexCoord2f(1, 1); glVertex3f(-1500, 1500, 1500);
	glTexCoord2f(0, 1); glVertex3f(-1500, 1500, -1500);
	glEnd();

	// Render the top quad
	glBindTexture(GL_TEXTURE_2D, arrSkyboxTexture[4]);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 1); glVertex3f(-1500, 1500, -1500);
	glTexCoord2f(0, 0); glVertex3f(-1500, 1500, 1500);
	glTexCoord2f(1, 0); glVertex3f(1500, 1500, 1500);
	glTexCoord2f(1, 1); glVertex3f(1500, 1500, -1500);
	glEnd();

	// Render the bottom quad
	glBindTexture(GL_TEXTURE_2D, arrSkyboxTexture[5]);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(-1500, -1500, -1500);
	glTexCoord2f(0, 1); glVertex3f(-1500, -1500, 1500);
	glTexCoord2f(1, 1); glVertex3f(1500, -1500, 1500);
	glTexCoord2f(1, 0); glVertex3f(1500, -1500, -1500);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
	// Restore enable bits and matrix
	//glPopAttrib();
	/*glPopMatrix();*/
	//Cloud
}

void TrainView::drawWater()
{
	//draw water
	ApplyShader(eShader::sWater);
	glPushMatrix();
	glScalef(100, 100, 100);
	float TS = 1.0 / 40; //0.025;
	glEnable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);
	for (int i = -20; i < 20; i++)
		for (int j = -20; j < 20; j++)
		{

			float startX = TS*(i + 20);
			float startY = TS*(j + 20);
			glTexCoord2f(startX + 0.0f, startY + 0);  glVertex3f(i, -2, j);
			glTexCoord2f(startX + TS, startY + 0);  glVertex3f(i + 1, -2, j);
			glTexCoord2f(startX + TS, startY + TS);  glVertex3f(i + 1, -2, j + 1);
			glTexCoord2f(startX + 0.0f, startY + TS);  glVertex3f(i, -2, j + 1);
		}
	glEnd();
	// Update wave variables
	waveTime += waveFreq;
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	glUseProgram(0);
}

void TrainView::ApplyShader(eShader shaderName)
{
	switch (shaderName)
	{
	case TrainView::NONE:
		glUseProgram(0);
		break;
	case TrainView::wood:
		glUseProgram(woodProgram);
		glUniform1f(glGetUniformLocation(woodProgram, "GrainSizeRecip"), 1);
		glUniform3f(glGetUniformLocation(woodProgram, "colorSpread"), 0.15, 0.075, 0);
		glUniform3f(glGetUniformLocation(woodProgram, "DarkColor"), 0.6, 0.3, 0.1);
		glUniform3f(glGetUniformLocation(woodProgram, "LightPosition"), 0, 0, 4);
		glUniform1f(glGetUniformLocation(woodProgram, "Scale"), 2);
		break;
	case TrainView::dimple:
		glUseProgram(dimpleProgram);
		glUniform3f(glGetUniformLocation(dimpleProgram, "LightPosition"), 0, 300, 500);
		glUniform1f(glGetUniformLocation(dimpleProgram, "Scale"), 1);
		break;
	case TrainView::kill:
		glUseProgram(killProgram);
		glUniform3f(glGetUniformLocation(killProgram, "LightPosition"), 0, 0, 3);
		break;
	case TrainView::sWater:
		glUseProgram(sWaterProgram);
		glUniform1f(glGetUniformLocation(sWaterProgram, "waveTime"), waveTime);
		glUniform1f(glGetUniformLocation(sWaterProgram, "waveWidth"), waveWidth);
		glUniform1f(glGetUniformLocation(sWaterProgram, "waveHeight"), waveHeight);
		glActiveTexture(GL_TEXTURE0);
		glUniform1i(glGetUniformLocation(sWaterProgram, "color_texture"), 0);
		glBindTexture(GL_TEXTURE_2D, sWaterTex[0]);
		break;
	case TrainView::Phong:
		glUseProgram(PhongProgram);
		//glUniform1i(glGetUniformLocation(PhongProgram, "numLights"), 7); //MAX 8 Lights
		break;
	default:
		break;
	}
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
