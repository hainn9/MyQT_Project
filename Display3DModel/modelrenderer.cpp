#include "modelrenderer.h"
#include <limits>
#include <QOpenGLTexture>
#include <QColor>

ModelRenderer::ModelRenderer()
    :m_indexBuffer(QOpenGLBuffer::IndexBuffer)
    ,m_rotX(0.0)
    ,m_rotY(0.0)
    ,m_rotZ(0.0)
    ,m_dX(0.0)
    ,m_dY(0.0)
    ,m_dZ(0.0)
    ,m_scale(1.0)
    ,texture(0)
    ,m_coordMirror(DoNotMirror)
{

}

ModelRenderer::~ModelRenderer()
{

}

void ModelRenderer::render()
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

//    glEnable(GL_CULL_FACE);
//    glCullFace(GL_CCW);
    m_shaderProgram.bind();
    texture->bind();
    m_model.setToIdentity();
    m_model.translate(m_dX, m_dY, m_dZ);
//    m_model.translate(0.5f, 0.0f, 0.0f);
    m_model.rotate(m_rotX, 1.0f, 0.0f, 0.0f);
    m_model.rotate(m_rotY, 0.0f, 1.0f, 0.0f);
    m_model.rotate(m_rotZ, 0.0f, 0.0f, 1.0f);
//    m_model.translate(-0.5f, 0.0f, 0.0f);
    m_model.scale(m_scale);
    m_shaderProgram.setUniformValue("lightPosition", m_lightInfo.Position);
    m_shaderProgram.setUniformValue("lightIntensity", m_lightInfo.Intensity);
    m_shaderProgram.setUniformValue("qt_EyePosition", QVector3D(0,0,-1));
    m_shaderProgram.setUniformValue("lightDirection", QVector3D(0,0,1));
    m_shaderProgram.setUniformValue("light.position", QVector3D(0,0,-1));
    m_shaderProgram.setUniformValue("light.spot_direction", QVector3D(0,0,1));
    m_shaderProgram.setUniformValue("light.ambient", QColor(Qt::white));
    m_shaderProgram.setUniformValue("light.diffuse", QColor(Qt::white));
    m_shaderProgram.setUniformValue("light.specular", QColor(Qt::white));
    m_shaderProgram.setUniformValue("light.spot_cutoff", 40.0f);
    m_shaderProgram.setUniformValue("light.spot_exponent", 25.0f);
    m_shaderProgram.setUniformValue("texture", 0);
    m_vertexBuffer.bind();
    m_shaderProgram.enableAttributeArray(0);
    m_shaderProgram.setAttributeBuffer(0, GL_FLOAT, 0, 3);
    m_normalBuffer.bind();
    m_shaderProgram.enableAttributeArray(1);
    m_shaderProgram.setAttributeBuffer(1, GL_FLOAT, 0, 3);
//    qDebug()<<"texture buffer is created:"<<m_textureUVBuffer.isCreated();
//    if (m_textureUVBuffer.isCreated()) {
//        m_textureUVBuffer.bind();
//        m_shaderProgram.enableAttributeArray(2);
//        m_shaderProgram.setAttributeBuffer(2, GL_FLOAT, 0, 2);
//    }
    m_indexBuffer.bind();
    drawNode(m_rootNode.data(), QMatrix4x4());
//    glDisable(GL_CULL_FACE);
    m_indexBuffer.release();
//    m_index += 0.1f;
}

void ModelRenderer::drawNode(const Node *node, QMatrix4x4 objectMatrix)
{
//    qDebug()<<Q_FUNC_INFO<<"node size:"<<node->nodes.size();
    // Prepare matrices
//    switch (m_coordMirror) {
//    case ModelRenderer::DoNotMirror:
//        break;
//    case ModelRenderer::MirrorYCoord:
//        m_projection.scale(1.0, -1.0, 1.0);
//        break;
//    }

    objectMatrix *= node->transformation;
//    qDebug()<<"object matrix = "<<objectMatrix;
//    qDebug()<<"model matrix = "<<m_model;
//    qDebug()<<"view matrix = "<<m_view;
//    qDebug()<<"projection matrix = "<<m_projection;
    QMatrix4x4 modelMatrix = m_model * objectMatrix;
    QMatrix4x4 modelViewMatrix = m_view * modelMatrix;
    QMatrix3x3 normalMatrix = modelViewMatrix.normalMatrix();
    QMatrix4x4 mvp = m_projection * modelViewMatrix;
//    qDebug()<<"mvp matrix = "<<mvp;

    m_shaderProgram.setUniformValue( "MV", modelViewMatrix );// Transforming to eye space
    m_shaderProgram.setUniformValue( "N", normalMatrix );    // Transform normal to Eye space
    m_shaderProgram.setUniformValue( "MVP", mvp );           // Matrix for transforming to Clip space

    // Draw each mesh in this node
    for(int imm = 0; imm<node->meshes.size(); ++imm)
    {
//        qDebug()<<"m_materialInfo"<<m_materialInfo.Name<<m_materialInfo.textureName;
//        MaterialInfo mat = *node->meshes[imm]->material;
//        qDebug()<<"mesh material:"<<mat.Name<<mat.textureName;
        if(node->meshes[imm]->material->Name == QString("DefaultMaterial"))
            setMaterialUniforms(m_materialInfo);
        else
            setMaterialUniforms(*node->meshes[imm]->material);
//        qDebug()<<"Ka="<<node->meshes[imm]->material->Ambient.x()<<node->meshes[imm]->material->Ambient.y()<<node->meshes[imm]->material->Ambient.z();
//        qDebug()<<"Kd="<<node->meshes[imm]->material->Diffuse.x()<<node->meshes[imm]->material->Diffuse.y()<<node->meshes[imm]->material->Diffuse.z();
//        qDebug()<<"Ks="<<node->meshes[imm]->material->Specular.x()<<node->meshes[imm]->material->Specular.y()<<node->meshes[imm]->material->Specular.z();
        //Test propose - Start
        glDrawElements(GL_TRIANGLES, node->meshes[imm]->indexCount, GL_UNSIGNED_INT
                       , (const void*)(node->meshes[imm]->indexOffset * sizeof(unsigned int)));
        //Test propose - End
//        glDrawElements( GL_TRIANGLES, node->meshes[imm]->indexCount, GL_UNSIGNED_SHORT
//                        , (const void*)(node->meshes[imm]->indexOffset * sizeof(unsigned short)) );
    }

    // Recursively draw this nodes children nodes
    for(int inn = 0; inn<node->nodes.size(); ++inn)
    {
//        qDebug()<<"draw node %d"<<inn<<node->nodes[inn].name;
        drawNode(&node->nodes[inn], objectMatrix);
    }
}

void ModelRenderer::setMaterialUniforms(MaterialInfo &mater)
{
    m_shaderProgram.setUniformValue("Ka", mater.Ambient);
    m_shaderProgram.setUniformValue("Kd", mater.Diffuse);
    m_shaderProgram.setUniformValue("Ks", mater.Specular);
    m_shaderProgram.setUniformValue("shininess", mater.Shininess);
}

//struct VertexData
//{
//    QVector2D texCoord;
//};

void ModelRenderer::initialize(CoordMirror cm)
{
    initializeOpenGLFunctions();
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glEnable(GL_DEPTH_TEST);
//    glEnable(GL_CULL_FACE);
    QString vSrc = QString(":/spot_light.vert");
    QString fSrc = QString(":/spot_light.frag");
    m_coordMirror = cm;

    m_shaderProgram.addShaderFromSourceFile(QOpenGLShader::Vertex, vSrc.toUtf8());
    m_shaderProgram.addShaderFromSourceFile(QOpenGLShader::Fragment, fSrc.toUtf8());

    m_shaderProgram.link();
    m_vertPosLoc = m_shaderProgram.attributeLocation("vertexPosition");
    qDebug()<<"vertPosLoc ="<<m_vertPosLoc;
    m_vertNorLoc = m_shaderProgram.attributeLocation("vertexNormal");
    qDebug()<<"vertNorLoc ="<<m_vertNorLoc;
//    m_texCoordLoc = m_shaderProgram.attributeLocation("a_texcoord");
//    qDebug()<<"texCoordLoc ="<<m_texCoordLoc;

//    texture = new QOpenGLTexture(QImage(":/object/ringMaterial.png").mirrored());
//    texture->setMinificationFilter(QOpenGLTexture::Nearest);
//    texture->setMagnificationFilter(QOpenGLTexture::Linear);
//    texture->setWrapMode(QOpenGLTexture::Repeat);


    const QImage env_posx = QImage(":/object/NewTexture/env_ring_+x.png").mirrored().convertToFormat(QImage::Format_RGBA8888);
    const QImage env_posy = QImage(":/object/NewTexture/env_ring_+y.png").mirrored().convertToFormat(QImage::Format_RGBA8888);
    const QImage env_posz = QImage(":/object/NewTexture/env_ring_+z.png").mirrored().convertToFormat(QImage::Format_RGBA8888);
    const QImage env_negx = QImage(":/object/NewTexture/env_ring_-x.png").mirrored().convertToFormat(QImage::Format_RGBA8888);
    const QImage env_negy = QImage(":/object/NewTexture/env_ring_-y.png").mirrored().convertToFormat(QImage::Format_RGBA8888);
    const QImage env_negz = QImage(":/object/NewTexture/env_ring_-z.png").mirrored().convertToFormat(QImage::Format_RGBA8888);

//    const QImage env_posx = QImage(":/object/red.png").mirrored().convertToFormat(QImage::Format_RGBA8888);
//    const QImage env_posy = QImage(":/object/blue.png").mirrored().convertToFormat(QImage::Format_RGBA8888);
//    const QImage env_posz = QImage(":/object/white.png").mirrored().convertToFormat(QImage::Format_RGBA8888);
//    const QImage env_negx = QImage(":/object/yellow.png").mirrored().convertToFormat(QImage::Format_RGBA8888);
//    const QImage env_negy = QImage(":/object/purple.png").mirrored().convertToFormat(QImage::Format_RGBA8888);
//    const QImage env_negz = QImage(":/object/gray.png").mirrored().convertToFormat(QImage::Format_RGBA8888);

    texture = new QOpenGLTexture(QOpenGLTexture::TargetCubeMap);
    texture->create();
    texture->setSize(env_posx.width(), env_posx.height(), env_posx.depth());
    texture->setFormat(QOpenGLTexture::RGBA8_UNorm);
    texture->allocateStorage();
    texture->setData(0,0, QOpenGLTexture::CubeMapPositiveX,QOpenGLTexture::RGBA, QOpenGLTexture::UInt8, (const void *)env_posx.constBits(), 0);
    texture->setData(0,0, QOpenGLTexture::CubeMapPositiveY,QOpenGLTexture::RGBA, QOpenGLTexture::UInt8, (const void *)env_posy.constBits(), 0);
    texture->setData(0,0, QOpenGLTexture::CubeMapPositiveZ,QOpenGLTexture::RGBA, QOpenGLTexture::UInt8, (const void *)env_posz.constBits(), 0);
    texture->setData(0,0, QOpenGLTexture::CubeMapNegativeX,QOpenGLTexture::RGBA, QOpenGLTexture::UInt8, (const void *)env_negx.constBits(), 0);
    texture->setData(0,0, QOpenGLTexture::CubeMapNegativeY,QOpenGLTexture::RGBA, QOpenGLTexture::UInt8, (const void *)env_negy.constBits(), 0);
    texture->setData(0,0, QOpenGLTexture::CubeMapNegativeZ,QOpenGLTexture::RGBA, QOpenGLTexture::UInt8, (const void *)env_negz.constBits(), 0);
//    texture->setAutoMipMapGenerationEnabled(true);
    texture->generateMipMaps();
    texture->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
    texture->setMagnificationFilter(QOpenGLTexture::LinearMipMapLinear);
    texture->setWrapMode(QOpenGLTexture::ClampToEdge);

    glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);

    ModelLoader model;
//    qDebug()<<"m_source ="<<m_source;
    if(!model.Load(QString("/object/ring.3ds"), ModelLoader::RelativePath))
    {
        qDebug()<<"load failed";
        return;
    }



    QVector<float> *vertices;
    QVector<float> *normals;
    QVector<QVector<float> > *textureUV;
    QVector<unsigned int> *indices;

    model.getBufferData(&vertices, &normals, &indices);
    model.getTextureData(&textureUV, 0, 0);

    qDebug()<<"textureUV"<<textureUV<<"size"<<textureUV->size();
    qDebug()<<"vertices"<<vertices<<"size"<<vertices->size();

    // Create a buffer and copy the vertex data to it
    m_vertexBuffer.create();
    m_vertexBuffer.setUsagePattern( QOpenGLBuffer::StaticDraw );
    m_vertexBuffer.bind();
    m_vertexBuffer.allocate( &(*vertices)[0], vertices->size() * sizeof( float ) );
    qDebug()<<"size of vertices buffer ="<<m_vertexBuffer.size();

    // Create a buffer and copy the vertex data to it
    m_normalBuffer.create();
    m_normalBuffer.setUsagePattern( QOpenGLBuffer::StaticDraw );
    m_normalBuffer.bind();
    m_normalBuffer.allocate( &(*normals)[0], normals->size() * sizeof( float ) );
    qDebug()<<"size of normal buffer ="<<m_normalBuffer.size();

    if(textureUV != 0 && textureUV->size() != 0)
    {
        // Create a buffer and copy the vertex data to it
        m_textureUVBuffer.create();
        m_textureUVBuffer.setUsagePattern( QOpenGLBuffer::StaticDraw );
        m_textureUVBuffer.bind();
        int texSize = 0;
        for(int ii=0; ii<textureUV->size(); ++ii) {
            qDebug()<<"size0 ="<<textureUV->at(0).size();
//            for (int i=0; i<textureUV->at(0).size(); i++)
//                qDebug()<<textureUV->at(0).at(i);
            texSize += textureUV->at(ii).size();
        }
        m_textureUVBuffer.allocate( &(*textureUV)[0][0], texSize * sizeof( float ) );
        qDebug()<<"size of texture buffer ="<<m_textureUVBuffer.size();
    }

    // Create a buffer and copy the index data to it
    m_indexBuffer.create();
    m_indexBuffer.setUsagePattern( QOpenGLBuffer::StaticDraw );
    m_indexBuffer.bind();
    //Test propose - Start
    m_indexBuffer.allocate(&(*indices)[0], indices->size()*sizeof(unsigned int));
    //Test propose - End
//    QVector<unsigned short> shortindices;
//    shortindices.resize(indices->size());
//    std::copy(indices->begin(), indices->end(), shortindices.begin());
//    m_indexBuffer.allocate( &(shortindices)[0], shortindices.size() * sizeof( unsigned short ) );
//    qDebug()<<"size of indices buffer ="<<m_indexBuffer.size();

    m_rootNode = model.getNodeData();
    m_vertexBuffer.release();
    m_normalBuffer.release();
    m_indexBuffer.release();
    m_view.setToIdentity();
    m_view.lookAt(
                QVector3D(0.0f, 0.0f, 1.2f),    // Camera Position
                QVector3D(0.0f, 0.0f, 0.0f),    // Point camera looks towards
                QVector3D(0.0f, 1.0f, 0.0f));   // Up vector
//    qDebug()<<"view matrix = "<<m_view;

//    float aspect = 16.0f/9.0f;
    m_projection.setToIdentity();
//    m_projection.perspective(60.0f,aspect,0.01f,1000.0f);
    m_projection.ortho(-0.875f, 0.875f, -0.8f, 0.8f, 0.3f, 1000.0f);

    switch (cm) {
    case ModelRenderer::DoNotMirror:
        break;
    case ModelRenderer::MirrorYCoord:
        m_projection.scale(1.0, -1.0, 1.0);
        break;
    }



//    qDebug()<<"projection matrix = "<<m_projection;
    m_lightInfo.Position = QVector4D( 0.0f, 2.0f, 1.0f, 0.0f );
    m_lightInfo.Intensity = QVector3D( 1.0f, 1.0f, 1.0f);

    m_materialInfo.Ambient = QVector3D( 1.0f, 0.2f, 0.05f );
    m_materialInfo.Diffuse = QVector3D( 0.3f, 0.5f, 0.3f );
    m_materialInfo.Specular = QVector3D( 0.8f, 0.8f, 0.8f );
    m_materialInfo.Shininess = 50.0f;
//    m_index = 0;

//    VertexData vert[] = {{QVector2D(0.0f, 0.0f)},
//                         {QVector2D(1.0f, 0.0f)},
//                         {QVector2D(0.0f, 1.0f)},
//                         {QVector2D(1.0f, 1.0f)}};
}

