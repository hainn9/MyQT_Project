//HaiNN9
#include "svgimage.h"
#include <QSvgRenderer>
#include <QFile>

SvgImage::SvgImage(QQuickItem *parent)
    : QQuickPaintedItem(parent)
{
    setFlag(ItemHasContents, true);
    setAcceptedMouseButtons(Qt::AllButtons);
    QFile file(":/test.svg");
    file.open(QIODevice::ReadOnly);
    svg.setContent(&file);

//    QDomElement docElem = svg.documentElement();

//    QDomNode n = docElem.firstChild();

//    QDomElement e = n.toElement(); // try to convert the node to an element.
//    if(!e.isNull()) {
//        qDebug() << qPrintable(e.tagName()) << endl; // the node really is an element.
//    }
//    QDomNode n_child = e.firstChild();
//    QDomElement e_child = n_child.toElement();
//    if (!e_child.isNull()) {
//        qDebug() << qPrintable(e_child.tagName()) << endl;
//        QDomAttr a = e_child.attributeNode("fill");
//        a.setValue("#1498CD");
//    }
//    QDomNode n2 = e.lastChild();
//    QDomElement e2 = n2.toElement();
//    qDebug()<<qPrintable(e2.tagName())<<endl;
//    QDomAttr a2 = e2.attributeNode("to");
//    qDebug()<<"to="<<a2.value();

//    n = n.nextSibling();
    m_renderer = new QSvgRenderer(svg.toByteArray());
}

void SvgImage::setColor(const QString &color)
{
    if (m_color != color) {
        m_color = color;
        emit colorChanged();
    }
}

void SvgImage::setScale(const QString scale)
{
    if (m_scale != scale) {
        m_scale = scale;
        emit scaleChanged();
    }
}

//void SvgImage::setSource(  const QString &source )
//{
//    m_Source = source;
//    qDebug()<<"m_source="<<m_Source;
//    QFile file(m_Source);
//    file.open(QIODevice::ReadOnly);
//    svgXML.setContent(&file);
//    QDomElement docElem = svg.documentElement();

//    QDomNode n = docElem.firstChild();

//    QDomElement e = n.toElement(); // try to convert the node to an element.
//    if(!e.isNull()) {
////        qDebug() << qPrintable(e.tagName()) << endl; // the node really is an element.
//    }
//    QDomNode n_child = e.firstChild();
//    QDomElement e_child = n_child.toElement();
//    if (!e_child.isNull()) {
////        qDebug() << qPrintable(e_child.tagName()) << endl;
//        QDomAttr a = e_child.attributeNode("fill");
//        a.setValue("#000000");
////        qDebug()<<"fill:"<<a.value() <<endl;
//    }

//    n = n.nextSibling();
//    m_renderer = new QSvgRenderer(svg.toByteArray());
//    connect(m_renderer, SIGNAL(repaintNeeded()), this, SLOT(update()));
//    emit sourceChanged();
//    update();
//}

void SvgImage::mousePressEvent(QMouseEvent *event)
{
    QQuickItem::mousePressEvent(event);
    QDomElement docElem = svg.documentElement();

    QDomNode n = docElem.firstChild();

    QDomElement e = n.toElement(); // try to convert the node to an element.
    if(!e.isNull()) {
        qDebug() << qPrintable(e.tagName()) << endl; // the node really is an element.
    }
    QDomNode n_child = e.firstChild();
    QDomElement e_child = n_child.toElement();
    if (!e_child.isNull()) {
        qDebug() << qPrintable(e_child.tagName()) << endl;
        QDomAttr a = e_child.attributeNode("fill");
        a.setValue("#1498CD");
    }
    QDomNode n2 = e.lastChild();
    QDomElement e2 = n2.toElement();
    qDebug()<<qPrintable(e2.tagName())<<endl;
    QDomAttr a2 = e2.attributeNode("to");
    a2.setValue(m_scale);
    n = n.nextSibling();
    m_renderer = new QSvgRenderer(svg.toByteArray());
    connect(m_renderer, SIGNAL(repaintNeeded()), this, SLOT(update()));
    update();
}

void SvgImage::changeAttributes(QString attName, QString attValue)
{
    QDomElement rootElem = svg.documentElement();

    QDomNode n = rootElem.firstChild();
    while(!n.isNull())
    {
        if(n.isElement())
        {
            QDomElement e = n.toElement();
            if(e.hasAttribute(attName)) {
                e.setAttribute(attName, attValue);
                qDebug()<<qPrintable(e.tagName())<<endl;
            }
            if(n.hasChildNodes())
                recursiveChangeAttributes(n.firstChild(), attName, attValue);
        }
        n = n.nextSibling();
    }
}

void SvgImage::recursiveChangeAttributes(QDomNode node, QString attName, QString attValue)
{
    QDomNode n = node;
    while(!n.isNull())
    {
        if(n.isElement())
        {
            QDomElement e = n.toElement();
            if(e.hasAttribute(attName))
                e.setAttribute(attName, attValue);

            if(n.hasChildNodes())
                recursiveChangeAttributes(n.firstChild(), attName, attValue);
        }
        n = n.nextSibling();
    }
}

void SvgImage::paint(QPainter *painter)
{
    m_renderer->setViewBox(QRect(10,9,100,100));
//    qDebug()<<m_renderer->animationDuration();
    m_renderer->render(painter);
}

