#include "fboinsgrenderer.h"
#include "modelrenderer.h"

#include <QtGui/QOpenGLFramebufferObject>

#include <QtQuick/QQuickWindow>
#include <qsgsimpletexturenode.h>

class ModelInFboRenderer : public QQuickFramebufferObject::Renderer
{
public:
    ModelInFboRenderer()
    {
#if QT_VERSION < QT_VERSION_CHECK(5,6,0)
        model.initialize(ModelRenderer::MirrorYCoord);
#else
        model.initialize();
#endif
    }

    void render() Q_DECL_OVERRIDE {
        model.render();
        m_window->resetOpenGLState();
    }

    void synchronize(QQuickFramebufferObject *qfbitem) Q_DECL_OVERRIDE {
        m_window = qfbitem->window();
        FboInSGRenderer *item = static_cast<FboInSGRenderer *>(qfbitem);
        m_rotX = item->rotX();
        m_rotY = item->rotY();
        m_rotZ = item->rotZ();
        m_dX = item->dX();
        m_dY = item->dY();
        m_dZ = item->dZ();
        m_scale = item->scaleValue();
        model.setRotX(m_rotX);
        model.setRotY(m_rotY);
        model.setRotZ(m_rotZ);
        model.setDX(m_dX);
        model.setDY(m_dY);
        model.setDZ(m_dZ);
        model.setScaleValue(m_scale);
    }

    QOpenGLFramebufferObject *createFramebufferObject(const QSize &size) {
        QOpenGLFramebufferObjectFormat format;
        format.setAttachment(QOpenGLFramebufferObject::CombinedDepthStencil);
        format.setSamples(4);
        return new QOpenGLFramebufferObject(size, format);
    }

    ModelRenderer model;
private:
    QQuickWindow *m_window;
    qreal m_rotX, m_rotY, m_rotZ;
    qreal m_dX, m_dY, m_dZ;
    qreal m_scale;
    QString m_source;
};

FboInSGRenderer::FboInSGRenderer(QQuickItem *parent)
    : QQuickFramebufferObject(parent)
{
#if QT_VERSION >= QT_VERSION_CHECK(5,6,0)
    setMirrorVertically(true);
#endif
}

QQuickFramebufferObject::Renderer *FboInSGRenderer::createRenderer() const
{

    return new ModelInFboRenderer();
}

void FboInSGRenderer::setRotX(qreal r)
{
    if (r != m_rotX) {
        m_rotX = r;
        update();
    }
}

void FboInSGRenderer::setRotY(qreal r)
{
    if (r != m_rotY) {
        m_rotY = r;
        update();
    }
}

void FboInSGRenderer::setRotZ(qreal r)
{
    if (r != m_rotZ) {
        m_rotZ = r;
        update();
    }
}

void FboInSGRenderer::setDX(qreal d)
{
    if (d != m_dX) {
        m_dX = d;
        update();
    }
}

void FboInSGRenderer::setDY(qreal d)
{
    if (d != m_dY) {
        m_dY = d;
        update();
    }
}

void FboInSGRenderer::setDZ(qreal d)
{
    if (d != m_dZ) {
        m_dZ = d;
        update();
    }
}

void FboInSGRenderer::setScaleValue(qreal scale)
{
    if (scale != m_scale) {
        m_scale = scale;
        update();
    }
}

void FboInSGRenderer::setObjName(const QString &source)
{
    if (source != m_source) {
        m_source = source;
//        createRenderer();
        update();
    }
//    qDebug()<<"source ="<<source<<"m_source ="<<m_source;
}

//void FboInSGRenderer::setSourceObj(QString source)
//{
//    if (source != m_source) {
//        m_source = source;
//        update();
//    }
//    qDebug()<<"m_source qml = "<<m_source;
//}

