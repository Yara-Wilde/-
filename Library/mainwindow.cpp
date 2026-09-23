#include "mainwindow.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("图书管理系统");
    resize(650,450);
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);
    QHBoxLayout *lay1 = new QHBoxLayout();
    lay1->addWidget(new QLabel("编号："));
    editId = new QLineEdit();
    lay1->addWidget(editId);

    lay1->addWidget(new QLabel("书名："));
    editName = new QLineEdit();
    lay1->addWidget(editName);

    lay1->addWidget(new QLabel("作者："));
    editAuthor = new QLineEdit();
    lay1->addWidget(editAuthor);

    lay1->addWidget(new QLabel("库存："));
    editStock = new QLineEdit();
    lay1->addWidget(editStock);
    mainLayout->addLayout(lay1);

    QHBoxLayout *lay2 = new QHBoxLayout();
    btnAdd = new QPushButton("添加图书");
    btnShow = new QPushButton("展示全部");
    btnQuery = new QPushButton("书名查询");
    btnBorrow = new QPushButton("借阅图书");
    btnReturn = new QPushButton("归还图书");
    lay2->addWidget(btnAdd);
    lay2->addWidget(btnShow);
    lay2->addWidget(btnQuery);
    lay2->addWidget(btnBorrow);
    lay2->addWidget(btnReturn);
    mainLayout->addLayout(lay2);

    textOut = new QTextEdit();
    textOut->setReadOnly(true);
    mainLayout->addWidget(textOut);

    connect(btnAdd,SIGNAL(clicked()),this,SLOT(slotAddBook()));
    connect(btnShow,SIGNAL(clicked()),this,SLOT(slotShowAll()));
    connect(btnQuery,SIGNAL(clicked()),this,SLOT(slotQueryBook()));
    connect(btnBorrow,SIGNAL(clicked()),this,SLOT(slotBorrowBook()));
    connect(btnReturn,SIGNAL(clicked()),this,SLOT(slotReturnBook()));
}

void MainWindow::slotAddBook()
{
    Book b;
    b.id = editId->text().trimmed();
    b.name = editName->text().trimmed();
    b.author = editAuthor->text().trimmed();
    QString sStr = editStock->text().trimmed();
    bool ok;
    b.stock = sStr.toInt(&ok);
    if(!ok || b.id.isEmpty() || b.name.isEmpty())
    {
        textOut->append("【错误】信息不全或者库存不是数字！");
        return;
    }
    bookList.append(b);
    textOut->append(QString("✅添加成功：%1 | %2 | %3，库存：%4").arg(b.id).arg(b.name).arg(b.author).arg(b.stock));
    editId->clear();
    editName->clear();
    editAuthor->clear();
    editStock->clear();
}

void MainWindow::slotShowAll()
{
    textOut->append("\n----------全部图书列表----------");
    if(bookList.empty())
    {
        textOut->append("暂无图书数据");
        return;
    }
    for(int i=0;i<bookList.size();i++)
    {
        Book b = bookList[i];
        textOut->append(QString("编号:%1,书名:%2,作者:%3,库存:%4").arg(b.id).arg(b.name).arg(b.author).arg(b.stock));
    }
}

void MainWindow::slotQueryBook()
{
    QString key = editName->text().trimmed();
    if(key.isEmpty())
    {
        textOut->append("\n【提示】请输入要查询的书名！");
        return;
    }
    bool find = false;
    for(int i=0;i<bookList.size();i++)
    {
        if(bookList[i].name == key)
        {
            Book b = bookList[i];
            textOut->append(QString("\n🔍查询结果：编号:%1,书名:%2,作者:%3,库存:%4").arg(b.id).arg(b.name).arg(b.author).arg(b.stock));
            find=true;
        }
    }
    if(!find)
        textOut->append("\n未找到该图书！");
}

void MainWindow::slotBorrowBook()
{
    QString bid = editId->text().trimmed();
    if(bid.isEmpty())
    {
        textOut->append("\n【提示】输入图书编号进行借阅");
        return;
    }
    for(int i=0;i<bookList.size();i++)
    {
        if(bookList[i].id == bid)
        {
            if(bookList[i].stock <= 0)
            {
                textOut->append("\n❌借阅失败：库存为0！");
                return;
            }
            bookList[i].stock --;
            textOut->append(QString("\n📖借阅成功！编号%1，当前库存：%2").arg(bookList[i].id).arg(bookList[i].stock));
            return;
        }
    }
    textOut->append("\n没有找到该编号图书");
}

void MainWindow::slotReturnBook()
{
    QString bid = editId->text().trimmed();
    if(bid.isEmpty())
    {
        textOut->append("\n【提示】输入图书编号归还");
        return;
    }
    for(int i=0;i<bookList.size();i++)
    {
        if(bookList[i].id == bid)
        {
            bookList[i].stock++;
            textOut->append(QString("\n📥归还成功！编号%1，当前库存：%2").arg(bookList[i].id).arg(bookList[i].stock));
            return;
        }
    }
    textOut->append("\n没有找到该编号图书");
}
