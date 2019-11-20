#include "GlWidget.h"

GlWidget::GlWidget(TrackerManager* trackerManager, QWidget* parent)	: QOpenGLWidget(parent)
{

	// set background color to black
	clearColor = Qt::black;

	m_refTrackerManager = trackerManager;

}

GlWidget::~GlWidget()
{

	// set current opengl context active
	makeCurrent(); // called automatically by paintGL()

	// delete all meshes
	for (auto itMesh = m_meshPool.begin(); itMesh != m_meshPool.end(); itMesh++)
		delete *itMesh;

	// delete shader program
	delete m_shaderProgram_texture;

	// diable current opengl contex
	doneCurrent();

}

void GlWidget::initializeGL()
{

	// initialize opengl
	initializeOpenGLFunctions();

	// enable depth test and backface culling
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_MULTISAMPLE);

	// load meshes and shader program
	init();

}

void GlWidget::init()
{

	createShaderProgram();
	createMeshes();

}

void GlWidget::createMeshes()
{

	// create grid
	m_meshPool.push_back(new Primitive(Primitive::Plane, m_shaderProgram_texture, new QOpenGLTexture(QImage(QString(":/ressources/images/tex_grid_10x10.png"))), Vector3::zero(), Vector3(2.0f, 2.0f, 2.0f)));
	// create cube
	m_meshPool.push_back(new Primitive(Primitive::Cube, m_shaderProgram_confidence, new QOpenGLTexture(QImage(QString(":/ressources/images/tex_checker_01.png"))), Vector3(0.0f, 0.1f, 0.0f), Vector3(0.1f, 0.1f, 0.1f)));

}

void GlWidget::createShaderProgram()
{

	// create vertex shader
	QOpenGLShader * vshader = new QOpenGLShader(QOpenGLShader::Vertex, this);
	const char* vsrc;

	// create fragment shader
	QOpenGLShader* fshader = new QOpenGLShader(QOpenGLShader::Fragment, this);
	const char* fsrc;



	// ### TEXTURE SHADER PROGRAM ###

	// define vertex shader
	vsrc =
		"attribute highp vec4 vertex;\n"
		"attribute mediump vec4 texCoord;\n"
		"varying mediump vec4 texc;\n"
		"uniform mediump mat4 matrix;\n"
		"void main(void)\n"
		"{\n"
		"    gl_Position = matrix * vertex;\n"
		"    texc = texCoord;\n"
		"}\n";

	// define fragment shader
	fsrc =
		"uniform sampler2D texture;\n"
		"varying mediump vec4 texc;\n"
		"uniform mediump vec4 color;\n"
		"void main(void)\n"
		"{\n"
		"    gl_FragColor = texture2D(texture, texc.st) * color;\n"
		"}\n";

	// compile vertex shader
	vshader->compileSourceCode(vsrc);
	// compile fragment shader
	fshader->compileSourceCode(fsrc);

	// create texture shader program
	m_shaderProgram_texture = new QOpenGLShaderProgram;
	// add vertex and frament shader
	m_shaderProgram_texture->addShader(vshader);
	m_shaderProgram_texture->addShader(fshader);
	// bind vertex shader attribute to location / id
	m_shaderProgram_texture->bindAttributeLocation("vertex", 0);
	m_shaderProgram_texture->bindAttributeLocation("texCoord", 1);
	// link shaders to shader program
	m_shaderProgram_texture->link();



	// ### CONFIDENCE SHADER PROGRAM ###

	// define vertex shader
	vsrc =
		"attribute highp vec4 vertex;\n"
		"attribute mediump vec4 texCoord;\n"
		"varying mediump vec4 texc;\n"
		"uniform mediump mat4 matrix;\n"
		"void main(void)\n"
		"{\n"
		"    gl_Position = matrix * vertex;\n"
		"    texc = texCoord;\n"
		"}\n";

	// define fragment shader
	fsrc =
		"uniform sampler2D texture;\n"
		"varying mediump vec4 texc;\n"
		"uniform mediump vec4 color;\n"
		"void main(void)\n"
		"{\n"
		"    gl_FragColor = color;\n"
		"}\n";

	// compile vertex shader
	vshader->compileSourceCode(vsrc);
	// compile fragment shader
	fshader->compileSourceCode(fsrc);

	// create confidence shader program
	m_shaderProgram_confidence = new QOpenGLShaderProgram;
	// add vertex and frament shader
	m_shaderProgram_confidence->addShader(vshader);
	m_shaderProgram_confidence->addShader(fshader);
	// bind vertex shader attribute to location / id
	m_shaderProgram_confidence->bindAttributeLocation("vertex", 0);
	m_shaderProgram_confidence->bindAttributeLocation("texCoord", 1);
	// link shaders to shader program
	m_shaderProgram_confidence->link();

}

// render loop
void GlWidget::paintGL()
{

	// set background color
	glClearColor(clearColor.redF(), clearColor.greenF(), clearColor.blueF(), clearColor.alphaF());
	// clear color and depth buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// reset camera matrix
	m_camera.getMatrix()->setToIdentity();
	// set camera to perspective with current aspect ratio
	m_camera.getMatrix()->perspective(60.0f, ((float)this->width() / this->height()), 0.05f, 10.0f);
	// translate and rotate camera
	m_camera.translate(Vector3(0.0f, -0.5f, -2.0f));
	// rotate camera based on mouse movement
	m_camera.rotate();

	// mesh render loop
	for (auto itMesh = m_meshPool.begin(); itMesh != m_meshPool.end(); itMesh++)
	{

		// render mesh if active
		if((*itMesh)->isActive())
			renderMesh(*itMesh, Vector3::one());

	}

	// skeleton render loop

	//for (auto itTracker = m_refTrackerManager->getPoolTracker()->begin(); itTracker != m_refTrackerManager->getPoolTracker()->end(); itTracker++)
	//{		
	//	for (auto itSkeleton = itTracker->second->getSkeletonPool()->begin(); itSkeleton != itTracker->second->getSkeletonPool()->end(); itSkeleton++)
	//	{			
	//		for (auto itJoint = itSkeleton->second->m_joints.begin(); itJoint != itSkeleton->second->m_joints.end(); itJoint++)
	//		{

	//			itJoint->second.getJointPosition();
	//			itJoint->second.getJointRotation();

	//		}
	//	}
	//}
}

void GlWidget::renderMesh(Mesh* mesh, Vector3 color)
{

	// bind mesh vbo, texture and shader program
	mesh->bind(m_worldMatrix * *(m_camera.getMatrix()), color);

	// draw all faces with GL_TRIANGLE_FAN
	for(int faceIndex = 0; faceIndex < mesh->getFaceCount(); faceIndex++)
		glDrawArrays(GL_TRIANGLE_FAN, faceIndex * 4, 4);

	// release mesh vbo and texture
	mesh->release();

}

void GlWidget::resizeGL(int width, int height)
{

	// set viewport size based on opengl widget size
	glViewport(0, 0, width, height);

}

void GlWidget::mousePressEvent(QMouseEvent* event)
{

	lastPos = event->pos();

}

void GlWidget::mouseMoveEvent(QMouseEvent* event)
{

	// get x and y differance based on last mouse position
	int dx = event->x() - lastPos.x();
	int dy = event->y() - lastPos.y();

	// add difference to camera rotation if left mouse button is pressed
	if (event->buttons() & Qt::LeftButton)
		m_camera.addRotation(Vector3(dy, dx, 0));
		
	lastPos = event->pos();

	// update opengl
	update();

}

void GlWidget::mouseReleaseEvent(QMouseEvent* /* event */)
{

	emit clicked();

}