#include <iostream>
#include <QGuiApplication>
#include <QResource>
#include <QQuickView>
#include <QQmlEngine>
#include "PreviewController.h"
#include "SineSource.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QResource::registerResource("FMAnalysisData.rcc");

    qmlRegisterType<synth::PreviewController>("Synth", 1, 0, "PreviewController");
    qmlRegisterType<synth::SineSource>("Synth", 1, 0, "SineSource");

    QQuickView view;
    view.connect(view.engine(), &QQmlEngine::quit, &app, &QCoreApplication::quit);
    view.setSource(QUrl("qrc:/qml/MainWindow.qml"));
    if (view.status() == QQuickView::Error)
        return -1;
    view.setResizeMode(QQuickView::SizeRootObjectToView);
    view.show();

    return app.exec();
}
