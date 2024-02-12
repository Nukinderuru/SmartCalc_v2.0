#include <QApplication>

#include "View/mainwindow.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  MainWindow w;
  w.setStyleSheet("background-color:black;");
  w.show();
  return a.exec();
}
