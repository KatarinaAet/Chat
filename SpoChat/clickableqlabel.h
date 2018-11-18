#ifndef CLICKABLEQLABEL_H
#define CLICKABLEQLABEL_H
#include <QLabel>


class ClickableQLabel:public QLabel
{
    Q_OBJECT
public:
    explicit ClickableQLabel( const QString& text ="", QWidget * parent = 0 );
       ~ClickableQLabel();
signals:
    void clicked();
protected:
      void mousePressEvent ( QMouseEvent * event ) ;
};

#endif // CLICKABLEQLABEL_H
