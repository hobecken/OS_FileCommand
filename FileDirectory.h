#pragma once
#include "cstdio"
#include "cstdlib"
#include "String"
#include "iostream"
#include "windows.h"
#include "windowsx.h"
#include "tchar.h"
#include "string"
#include <Windows.h>
using namespace std;

//用孩子-兄弟结点法表示文件目录树结构
typedef enum fileType

{

	file,

	folder

}FileType;

typedef struct FileNode
{
	int seniority; //孩子排行
	int level;
	string filename = "";
	string filepath = "";
	FileType type;

	struct FileNode* firstchild, * nextsibling, * parent;

}FileNode, * FileTree;

typedef struct QueNode
{
	FileTree value;
	struct QueNode* next;
}QueNode, *QueuePtr;

typedef struct {
	QueuePtr front;
	QueuePtr rear;
}LinkQueue;

//文件目录树类，包含生成树方法、进入上层目录方法、进入当前层任意文件方法、通过搜索进入任意层目录方法
//属性包括层数，上一层指针，树根节点
class FileDirectory {
private:
	FileTree T; //树根节点
	int layer_num; //层数
	
	int current_layer;
	FileTree previous_layer;
	void CreateTree(FileTree &);
	int GetDepth(FileTree &);
public:
	FileDirectory();

	FileTree GetRoot();
	int BackToPrevious();
	int GoToTargetFolder(/*文件号*/);
	int Traversal(FileTree);
	int Search(TCHAR);	//按文件名查找
	int Search(int);	//在当前目录下按文件号查找
};