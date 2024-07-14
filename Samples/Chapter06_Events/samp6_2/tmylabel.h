#ifndef TMYLABEL_H
#define TMYLABEL_H

#include <QLabel>
#include <QObject>
#include <QEvent>

class TMyLabel : public QLabel
{
    Q_OBJECT
public:
    TMyLabel(QWidget *parent = nullptr);
signals:
    void doubleClicked();

    // QWidget interface
protected:
    virtual void mouseDoubleClickEvent(QMouseEvent *event) override;

    // QObject interface
public:
    virtual bool event(QEvent *event) override;
};

#endif // TMYLABEL_H
