#ifndef SVGIMAGE
#define SVGIMAGE

//HaiNN9
#include <QQuickPaintedItem>
#include <QPainter>
#include <QSvgRenderer>
#include <QDomDocument>

class SvgImage : public QQuickPaintedItem
{
    Q_OBJECT

//    Q_PROPERTY(QString source READ source WRITE setSource NOTIFY sourceChanged)
    Q_PROPERTY(QString color READ color WRITE setColor NOTIFY colorChanged)
    Q_PROPERTY(QString scale READ scale WRITE setScale NOTIFY scaleChanged)
public:
    SvgImage(QQuickItem *parent = 0);

    QSvgRenderer* m_renderer;

//    QString source() const { return m_Source; }

//    void setSource( const QString &source );

    QString scale() const { return m_scale;}
    void setScale(const QString scale);

    QString color() const { return m_color; }
    void setColor(const QString &color);

    void mousePressEvent(QMouseEvent *event);
    void changeAttributes(QString attName, QString attValue);
    void recursiveChangeAttributes(QDomNode node, QString attName, QString attValue);
private slots :
    void paint(QPainter *painter);

signals:
    void sourceChanged();
    void colorChanged();
    void scaleChanged();
private :
    QString m_Source;
    QString m_scale;
    QString m_color;
    QDomDocument svg;

};

#endif // SVGIMAGE

