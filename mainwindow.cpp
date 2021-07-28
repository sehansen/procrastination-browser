
#include <QtWidgets>
#include <QtNetwork>
#include <QtWebKitWidgets>
#include "mainwindow.h"

MainWindow::MainWindow()
{
    QNetworkProxyFactory::setUseSystemConfiguration(true);

    view = new QWebView(this);
    view->load(QUrl("http://dr.dk"));
    connect(view, SIGNAL(loadFinished(bool)), SLOT(adjustLocation()));
    connect(view, SIGNAL(titleChanged(QString)), SLOT(adjustTitle()));
    connect(view, SIGNAL(loadProgress(int)), SLOT(setProgress()));
    connect(view, SIGNAL(loadFinished(bool)), SLOT(finishLoading(bool)));

    QWebPage *page = view->page();
    page->setLinkDelegationPolicy(QWebPage::DelegateAllLinks);
    connect(page, SIGNAL(linkClicked(QUrl)), SLOT(pageToQueue(QUrl)));

    locationEdit = new QLineEdit(this);
    locationEdit->setSizePolicy(QSizePolicy::Expanding, locationEdit->sizePolicy().verticalPolicy());
    connect(locationEdit, SIGNAL(returnPressed()), SLOT(changeLocation()));

    QToolBar *toolBar = addToolBar(tr("Navigation"));
    toolBar->addAction(view->pageAction(QWebPage::Back));
    toolBar->addAction(view->pageAction(QWebPage::Forward));
    toolBar->addAction(view->pageAction(QWebPage::Reload));
    toolBar->addAction(view->pageAction(QWebPage::Stop));
    toolBar->addWidget(locationEdit);

    queueMenu = menuBar()->addMenu(tr("&Queue"));
    queueMenu->addAction("Navigate breadth first", this, SLOT(breadthFirst()));
    queueMenu->addAction("Navigate depth first", this, SLOT(depthFirst()));
    queueMenu->addAction("Navigate randomly", this, SLOT(random()));
    queueMenu->actions().at(0)->setEnabled(false);
    queueMenu->actions().at(1)->setEnabled(false);
    queueMenu->actions().at(2)->setEnabled(false);

    setCentralWidget(view);
    setUnifiedTitleAndToolBarOnMac(true);
}

void MainWindow::adjustLocation()
{
    locationEdit->setText(view->url().toString());
}

void MainWindow::changeLocation()
{
    QUrl url = QUrl::fromUserInput(locationEdit->text());
    view->load(url);
    view->setFocus();
}

void MainWindow::adjustTitle()
{
    setWindowTitle(view->title());
}

void MainWindow::setProgress()
{
    adjustTitle();
}

void MainWindow::finishLoading(bool)
{
    adjustTitle();
}

void MainWindow::pageToQueue(QUrl target)
{
    qDebug() << target.toString();
    pipeline.enqueue(target);
    queueMenu->actions().at(0)->setEnabled(true);
    queueMenu->actions().at(1)->setEnabled(true);
    //takeAt()
    //dequeue()
}

void MainWindow::breadthFirst()
{
    view->load(pipeline.dequeue());
    if (pipeline.count() <= 0)
    {
        queueMenu->actions().at(0)->setEnabled(false);
        queueMenu->actions().at(1)->setEnabled(false);
    }
}


void MainWindow::depthFirst()
{
    view->load(pipeline.takeLast());
    if (pipeline.count() <= 0)
    {
        queueMenu->actions().at(0)->setEnabled(false);
        queueMenu->actions().at(1)->setEnabled(false);
    }
}


void MainWindow::random()
{
    view->load(pipeline[this->randInt(0,pipeline.length()-1)]);
    if (pipeline.count() <= 0)
    {
        queueMenu->actions().at(0)->setEnabled(false);
        queueMenu->actions().at(1)->setEnabled(false);
    }
}

int MainWindow::randInt(int low, int high)
{
    return qrand() % ((high + 1) - low) + low;
}

