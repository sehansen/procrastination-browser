#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>

class QWebView;
QT_BEGIN_NAMESPACE
class QLineEdit;
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow();

protected slots:

    void adjustLocation();
    void changeLocation();
    void adjustTitle();
    void setProgress();
    void finishLoading(bool);
    void pageToQueue(QUrl target);

    void breadthFirst();

private:
    QWebView *view;
    QLineEdit *locationEdit;
    QQueue<QUrl> pipeline;
    QMenu *queueMenu;
};

#endif // MAINWINDOW_H
