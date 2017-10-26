#ifndef MODELRENDERER
#define MODELRENDERER

#include <QOpenGLShaderProgram>
#include <QOpenGLFunctions>
#include <QMatrix4x4>
#include "modelloader.h"
#include <QOpenGLBuffer>
#include <QOpenGLTexture>

class ModelRenderer:public QOpenGLFunctions
{
public:
    ModelRenderer();
    ~ModelRenderer();

    enum CoordMirror {
        DoNotMirror,
        MirrorYCoord
    };

    void render();
    void initialize(CoordMirror cm = DoNotMirror);

    void setRotX(qreal r) {m_rotX = r;}
    void setRotY(qreal r) {m_rotY = r;}
    void setRotZ(qreal r) {m_rotZ = r;}
    void setDX(qreal d) {m_dX = d;}
    void setDY(qreal d) {m_dY = d;}
    void setDZ(qreal d) {m_dZ = d;}
    void setScaleValue(qreal scale) {m_scale = scale;}
    void setObjName(QString &source) {m_source = source;}

//    void createShaderProgram();
//    void createBuffers();
//    void setupLightingAndMatrices();

private:
    void drawNode(const Node *node, QMatrix4x4 objectMatrix);
    void setMaterialUniforms(MaterialInfo &mater);
    QOpenGLShaderProgram m_shaderProgram;
    int m_vertPosLoc;
    int m_vertNorLoc;
    int m_texCoordLoc;
    QOpenGLBuffer m_vertexBuffer;
    QOpenGLBuffer m_normalBuffer;
    QOpenGLBuffer m_textureUVBuffer;
    QOpenGLBuffer m_indexBuffer;
    QSharedPointer<Node> m_rootNode;
    QMatrix4x4 m_projection, m_view, m_model;
    LightInfo m_lightInfo;
    MaterialInfo m_materialInfo;
    qreal m_rotX, m_rotY, m_rotZ;
    qreal m_dX, m_dY, m_dZ;
    qreal m_scale;
    QString m_source;
    QOpenGLTexture *texture;
    CoordMirror m_coordMirror;
};


#endif // MODELRENDERER

