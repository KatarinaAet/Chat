#include "clickableqlabel.h"

ClickableQLabel::ClickableQLabel(const QString &text, QWidget *parent)
{
    setText(text);
}

ClickableQLabel::~ClickableQLabel()
{

}

void ClickableQLabel::mousePressEvent(QMouseEvent *event)
{
    emit clicked();
}
