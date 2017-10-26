#ifndef FBOINSGRENDERER_H
#define FBOINSGRENDERER_H

#include <QtQuick/QQuickFramebufferObject>
#include <QVector3D>
#include <QQuickItem>

class ModelRenderer;

class FboInSGRenderer : public QQuickFramebufferObject
{
    Q_OBJECT
    Q_PROPERTY(qreal rotX READ rotX WRITE setRotX)
    Q_PROPERTY(qreal rotY READ rotY WRITE setRotY)
    Q_PROPERTY(qreal rotZ READ rotZ WRITE setRotZ)
    Q_PROPERTY(qreal dX READ dX WRITE setDX)
    Q_PROPERTY(qreal dY READ dY WRITE setDY)
    Q_PROPERTY(qreal dZ READ dZ WRITE setDZ)
    Q_PROPERTY(qreal scaleValue READ scaleValue WRITE setScaleValue)
    Q_PROPERTY(QString objName READ objName WRITE setObjName)
public:
    explicit FboInSGRenderer(QQuickItem *parent = 0);
    Renderer *createRenderer() const;
    qreal rotX() const {return m_rotX;}
    void setRotX(qreal r);

    qreal rotY() const {return m_rotY;}
    void setRotY(qreal r);

    qreal rotZ() const {return m_rotZ;}
    void setRotZ(qreal r);

    qreal dX() const {return m_dX;}
    void setDX(qreal d);

    qreal dY() const {return m_dY;}
    void setDY(qreal d);

    qreal dZ() const {return m_dZ;}
    void setDZ(qreal d);

    qreal scaleValue() const {return m_scale; }
    void setScaleValue(qreal scale);

    QString objName() const {return m_source;}
    void setObjName(const QString &source);
//signals:
//    void rotXChanged();
//    void rotYChanged();
//    void rotZChanged();
//    void dXChanged();
//    void dYChanged();
//    void dZChanged();
//    void scaleValueChanged();
//    void sourceObjChanged();
private:
    qreal m_rotX, m_rotY, m_rotZ;
    qreal m_dX, m_dY, m_dZ;
    qreal m_scale;
    QString m_source;
};

#endif
