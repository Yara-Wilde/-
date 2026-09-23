#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QPushButton>
#include <QTextEdit>
#include <QVector>
#include <QString>

struct Book
{
    QString id;
    QString name;
    QString author;
    int stock;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);

private slots:
    void slotAddBook();
    void slotShowAll();
    void slotQueryBook();
    void slotBorrowBook();
    void slotReturnBook();

private:
    QVector<Book> bookList;
    QLineEdit *editId;
    QLineEdit *editName;
    QLineEdit *editAuthor;
    QLineEdit *editStock;
    QPushButton *btnAdd;
    QPushButton *btnShow;
    QPushButton *btnQuery;
    QPushButton *btnBorrow;
    QPushButton *btnReturn;
    QTextEdit *textOut;
};

#endif // MAINWINDOW_H
