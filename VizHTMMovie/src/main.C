/*
 * main.C
 *
 *  Created on: Mar 11, 2016
 *      Author: mrilee
 */

#include <main.h>

//using namespace std;

int main(int argc, char *argv[]) {

	std::string mainName = executableName(argv[0]);
	std::cout << mainName << " starting." << std::endl;

	/**************** Start Graphics ****************/
	QWidget *window = SoQt::init(argv[0]);
	if (window == NULL) exit(1);

	SoSelection *selectionRoot = new SoSelection;
	selectionRoot->policy = SoSelection::SINGLE;

	SoSeparator *root = new SoSeparator;
	//	root->ref(); // TODO Figure out ->ref();

//	root->addChild(viz->makeRoot());

	selectionRoot->addChild(root);

	SoQtExaminerViewer *viewer = new SoQtExaminerViewer(window);
	viewer->setSceneGraph(selectionRoot);
	viewer->setTitle(mainName.c_str());
	viewer->show();

	SoQt::show(window);
	SoQt::mainLoop();

	delete viewer;

	std::cout << mainName << " done." << std::endl;

	return 0;
}
