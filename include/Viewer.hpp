// Viewer.hpp

#ifndef __VIEWER_INCLUDE__
#define __VIEWER_INCLUDE__

#include <iostream>
#include <thread>

#include <zed/utils/GlobalDefine.hpp>
#include <GL/glew.h>
#include <GL/glut.h>   /* OpenGL Utility Toolkit header */
#include <Eigen/Core>
#include <Eigen/Eigen>

#include "utils.hpp"
#include "Shader.hpp"
#include "CameraGL.hpp"
#include "Simple3DObject.hpp"
#include "PointCloud.hpp"

#define MOUSE_R_SENSITIVITY 0.015f
#define MOUSE_UZ_SENSITIVITY 0.75f
#define MOUSE_DZ_SENSITIVITY 1.25f
#define MOUSE_T_SENSITIVITY 0.1f
#define KEY_T_SENSITIVITY 0.1f

/*
 * This class manages the window, input events and Opengl rendering pipeline
 */
class Viewer {
public:
    Viewer(PointCloud& pointCloud, int argc, char **argv);
    ~Viewer();
    void destroy();
    bool isEnded();
	bool isInitialized();
private:
	/*
      Initialize OpenGL context and variables, and other Viewer's variables
	*/
    void initialize();
	/*
	  Rendering loop method called each frame by glutDisplayFunc
	*/
    void render();
	/*
	  Everything that needs to be updated before rendering must be done in this method
	*/
    void update();
	/*
	  Once everything is updated, every renderable objects must be drawn in this method
	*/
    void draw();
	/*
	  Clear and refresh inputs' data
	*/
    void clearInputs();

    static Viewer* currentInstance_;

    //! Glut Functions CALLBACKs
    static void drawCallback();
    static void mouseButtonCallback(int button, int state, int x, int y);
    static void mouseMotionCallback(int x, int y);
    static void reshapeCallback(int width, int height);
    static void keyPressedCallback(unsigned char c, int x, int y);
    static void keyReleasedCallback(unsigned char c, int x, int y);
    static void idle();

    std::thread* mainLoopThread_;

    bool ended_;

	int _argc;
	char** _argv;

    enum MOUSE_BUTTON {
        LEFT = 0,
        MIDDLE = 1,
        RIGHT = 2,
        WHEEL_UP = 3,
        WHEEL_DOWN = 4
    };

	enum KEY_STATE {
		UP = 'u',
		DOWN = 'd',
		FREE = 'f'
	};

    bool mouseButton_[3];
    int mouseWheelPosition_;
    int mouseCurrentPosition_[2];
    int mouseMotion_[2];
    int previousMouseMotion_[2];
	KEY_STATE keyStates_[256];

    Simple3DObject* axis_;
    PointCloud& pointCloud_;
    CameraGL* camera_;
    Shader* shader_;
    GLuint shMVPMatrixLoc_;

	bool initialized_;
};

#endif	/* __VIEWER_INCLUDE__ */