#ifndef CONTROL_H
#define CONTROL_H

#include <QGraphicsItem>
#include <QPainter>

class Control : public QGraphicsItem
{
public:
    Control();

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0) override;

    int type() const;
    enum {Type = UserType + 6};

};

#endif // CONTROL_H
