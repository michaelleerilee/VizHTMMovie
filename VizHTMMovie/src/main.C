/*
 * main.C
 *
 *  Created on: Mar 11, 2016
 *      Author: mrilee
 */

#include <main.h>

#ifdef TEST_OFFSCREEN_VIZ
#include <testOffScreenViz.h>
#endif

#include <OffScreenViz.h>

#include <Inventor/nodes/SoDirectionalLight.h>
#include <Inventor/nodes/SoCube.h>
#include <Inventor/nodes/SoRotationXYZ.h>

void plotConstraint(VizHTM *viz, SpatialConstraint sc) {
	viz->addConstraint(sc,1.0,0.5,1.0);
}

void tenDegreeGrid(VizHTM *viz) {
	float64 PI = atan2(0,-1);
	float64 k  = 2*PI/360.;

	float dLat = 10;
	float dLon = 10;
	for(float lat=-90; lat<=90; lat+= dLat) {
		for(float lon=0; lon<=360; lon+= dLon) {
			float r = 0.125+0.125*(1+cos(k*lon)); // r=0;
			float g = 0.125+0.125*(1+sin(k*lon)); // g=0;
			float b = 0.125+0.125*(1+sin(k*lat)); // b=0;
			viz->addLatLonBoxEdgesDegrees(
					lat + 0.25, lon + 0.25,
					lat + dLat - 0.25, lon + dLon - 0.25,
					r,g,b);
		}
	}
}


void loadScene(SoSeparator *root, SoSeparator *content, SbViewportRegion *vpRegion){

    SoDirectionalLight * light = new SoDirectionalLight;

    SbRotation cameraRotation = SbRotation::identity();
//    cameraRotation *= SbRotation(SbVec3f(0, 0, 1), M_PI/2.0);
//    cameraRotation *= SbRotation(SbVec3f(0, 0, 1), 0.4);
//
    SoPerspectiveCamera *perscam = new SoPerspectiveCamera;
    perscam->orientation.setValue(cameraRotation);
////    perscam->aspectRatio.setValue(270.0/480.0);
    perscam->position.setValue(0,0,8);
////    perscam->viewportMapping.setValue(SoCamera::CROP_VIEWPORT_LINE_FRAME);
    perscam->nearDistance = 0.1;
//
    root->addChild(light);
    root->addChild(perscam);

//    SoCube * cube = new SoCube;
//    root->addChild(cube);

    root->addChild(content);
    // make sure that the cube is visible
//    perscam->viewAll(root, *vpRegion);
}


//using namespace std;

int main(int argc, char *argv[]) {

	SoDB::init();

	std::string mainName = executableNameFromPathAsCString(argv[0]);
	std::cout << mainName << " starting." << std::endl;

	/* testOffScreen */
#ifdef TEST_OFFSCREEN_VIZ
	std::cout << mainName << " testOffScreenViz starting." << std::endl;
	testOffScreenViz::testOffScreenViz *testOffScreen
		= new testOffScreenViz::testOffScreenViz;
	delete testOffScreen;
	std::cout << mainName << " testOffScreenViz done. Exiting." << std::endl;
	return 0;
#endif

	/**************** Start Graphics ****************/
	std::cout << mainName << " graphics starting." << std::endl;

	QWidget *window = SoQt::init(argv[0]);
	if (window == NULL) exit(1);

	SoSelection *selectionRoot = new SoSelection;
	selectionRoot->policy = SoSelection::SINGLE;


	VizHTM *viz = new VizHTM(NARRAY_);
//	tenDegreeGrid(viz);
	viz->triaxis();

	SoSeparator *root = new SoSeparator;

	//	root->ref(); // TODO Figure out ->ref();

	SoRotationXYZ *rot = new SoRotationXYZ;
	rot->axis.setValue(SoRotationXYZ::X);
	rot->angle.setValue(0.0*0.25*M_PI);
	root->addChild(rot);

	root->addChild(viz->makeRoot());
	selectionRoot->addChild(root);

	OffScreenViz *offscreen = new OffScreenViz();
	offscreen->initImageDirectory("tmp/offscreen/"+formattedDateTime()+"/",4);
	offscreen->root = new SoSeparator;
	loadScene(offscreen->root,root,offscreen->vpRegion);
	offscreen->saveImage(1);

	SoQtExaminerViewer *viewer = new SoQtExaminerViewer(window);
	viewer->setSceneGraph(selectionRoot);
	viewer->setTitle(mainName.c_str());
	viewer->show();

	SoQt::show(window);
	SoQt::mainLoop();

	delete viewer;
	std::cout << mainName << " graphics done." << std::endl;

	std::cout << mainName << " exiting." << std::endl;

	return 0;
}
