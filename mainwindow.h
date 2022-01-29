#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>
#include <QWebSettings>

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
    void disableDequeue();

    void breadthFirst();
    void depthFirst();
    void random();

private:
    QWebView *view;
    QWebSettings *settings;
    QLineEdit *locationEdit;
    QQueue<QUrl> pipeline;
    QToolBar *toolBar;
    QMenu *queueMenu;
    int randInt(int low, int high);
    void navigate(QUrl url);
};

#endif // MAINWINDOW_H
