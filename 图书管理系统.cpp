#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct Book {
	string id;
	string name;
	string author;
	int stock;
};

vector<Book> bookList;

void addBook() {
	Book b;
	cout << "输入图书编号：";
	cin >> b.id;
	cout << "输入书名：";
	cin >> b.name;
	cout << "输入作者：";
	cin >> b.author;
	cout << "输入库存：";
	cin >> b.stock;
	bookList.push_back(b);
	cout << "添加成功！\n";
}

void showAll() {
	if(bookList.empty()){
		cout << "暂无图书\n";
		return;
	}
	cout << "编号\t书名\t作者\t库存\n";
	for(auto &b : bookList){
		cout << b.id << "\t" << b.name << "\t" << b.author << "\t" << b.stock << endl;
	}
}

void searchBook() {
	string key;
	cout << "输入要查询的书名：";
	cin >> key;
	bool find = false;
	for(auto &b : bookList){
		if(b.name == key){
			cout << "找到："<<b.id<<" "<<b.name<<" "<<b.author<<" 库存:"<<b.stock<<endl;
			find = true;
		}
	}
	if(!find) cout << "未找到\n";
}

void borrowBook() {
	string key;
	cout << "输入借阅图书编号：";
	cin >> key;
	for(auto &b : bookList){
		if(b.id == key){
			if(b.stock > 0){
				b.stock--;
				cout << "借阅成功\n";
				return;
			}else{
				cout << "库存不足\n";
				return;
			}
		}
	}
	cout << "没有这本书\n";
}

void returnBook() {
	string key;
	cout << "输入归还图书编号：";
	cin >> key;
	for(auto &b : bookList){
		if(b.id == key){
			b.stock++;
			cout << "归还成功\n";
			return;
		}
	}
	cout << "没有这本书\n";
}

int main() {
	int op;
	while(true){
		cout << "\n====图书管理系统====\n";
		cout << "1 添加图书\n2 显示全部\n3 查询图书\n4 借阅图书\n5 归还图书\n0 退出\n";
		cout << "请选择：";
		cin >> op;
		switch(op){
			case 1: addBook();break;
			case 2: showAll();break;
			case 3: searchBook();break;
			case 4: borrowBook();break;
			case 5: returnBook();break;
			case 0: cout << "退出程序\n";return 0;
			default: cout << "输入错误\n";
		}
	}
	return 0;
}

