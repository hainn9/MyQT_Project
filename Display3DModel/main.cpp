#include <QApplication>
//#include "openglwindow.h"
//#include "modelwindow_gl_2.h"
#include <QGuiApplication>
#include <QQuickView>
//#include "model3d.h"
#include "fboinsgrenderer.h"

int main(int argc, char *argv[])
{
    QString OpenGL_Model(":/object/ring.dae");
    QString OpenGLES_Model(":/object/ring.3ds");

    //Solution1:
//    QApplication a(argc, argv);

//    QSurfaceFormat format;
//    format.setDepthBufferSize(24);
//    QSurfaceFormat::setDefaultFormat(format);

//    ModelWindow_GL_2 *widget = new ModelWindow_GL_2(OpenGL_Model, ModelLoader::RelativePath);
//    widget->setGeometry(0,0, 700, 640);
//    widget->show();

    //Solution2:
//    QGuiApplication a(argc, argv);
//    qmlRegisterType<Model3D>("Model3DOpenGL", 1, 0, "Model3DOpenGL");
//    QQuickView viewer;
//    viewer.setResizeMode(QQuickView::SizeRootObjectToView);
//    viewer.setSource(QUrl("qrc:///main.qml"));
//    viewer.show();

    //Solution3:
    QGuiApplication a(argc, argv);

    qmlRegisterType<FboInSGRenderer>("SceneGraphRendering", 1, 0, "Renderer");

    QQuickView view;
    view.setResizeMode(QQuickView::SizeRootObjectToView);
    view.setSource(QUrl("qrc:///main.qml"));
//    view.setGeometry(0,0,1000,800);
    view.show();

    return a.exec();
}
