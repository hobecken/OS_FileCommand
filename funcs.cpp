#include "FileDirectory.h"

string getpath(FileTree t)
{
	return t->parent->filepath + "\\" + t->filename;
}

int InitQueue(LinkQueue  &Q)
{
	Q.front = Q.rear = new QueNode;
	if (!Q.front) exit(OVERFLOW);
	Q.front->next = NULL;
	return 1;
}

int EnQueue(LinkQueue& Q, FileTree e)
{
	QueuePtr p = new QueNode;
	if (!p) exit(OVERFLOW);
	p->value = e;
	p->next = NULL;
	Q.rear->next = p;
	Q.rear = p;
	return 1;
}

int DeQueue(LinkQueue& Q, FileTree& e)
{
	if (Q.front == Q.rear)return 0;
	QueuePtr p = new QueNode;
	p = Q.front->next;
	e = p->value;
	Q.front->next = p->next;
	if (Q.rear == p) Q.rear = Q.front;
	return 1;
}

FileTree FileDirectory::GetRoot()
{
	return this->T;
}

void FileDirectory::CreateTree(FileTree & parent_node)
{
	/*
	FileTree current_node = new FileNode;
	current_node->parent = parent_node;
	parent_node->firstchild = current_node;
	*/
	//已传入根节点和根目录地址，通过bfs构建孩子兄弟树
	WIN32_FIND_DATA lpfindfiledata;
	string source = "";
	

	//创建队列，存储本层节点
	LinkQueue Q;
	InitQueue(Q);
	
	//根节点入队
	EnQueue(Q, parent_node);

	while (Q.front != Q.rear)
	{
		//队列顶部节点出队
		FileTree p = new FileNode;

		DeQueue(Q, p);
		//p->firstchild = NULL;	//这行有问题，初始化节点的firstchild，如果不初始化会在getdepth中达到叶子节点时出错

		int loop_num = 0;
		FileTree sunxiaochuan = NULL;

		source = p->filepath + "//*.*";

		HANDLE hfind = FindFirstFile(source.c_str(), &lpfindfiledata);
		if (hfind != INVALID_HANDLE_VALUE)
		{
			while (FindNextFile(hfind, &lpfindfiledata) != 0)
			{
				if ((lpfindfiledata.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0) //是目录
				{
					if ((strcmp(lpfindfiledata.cFileName, ".") != 0) && (strcmp(lpfindfiledata.cFileName, "..") != 0))
					{
						FileTree q = new FileNode;
						
						loop_num++;
						if (loop_num == 1)
						{
							p->firstchild = q;
						}
						else {
							sunxiaochuan->nextsibling = q;
						}
						//为新节点指针赋值
						q->parent = p;
						q->level += q->parent->level;
						q->filename = lpfindfiledata.cFileName;
						q->filepath = getpath(q);
						q->firstchild = NULL; q->nextsibling = NULL;
						
						q->type = folder;
						q->seniority = loop_num++;
						sunxiaochuan = q;
						//新节点入队列
						EnQueue(Q, q);
						
						//cout << q->filename << endl;
					}
				}
			}
		}
		//p->firstchild = NULL;
	}

	
}

int FileDirectory::GetDepth(FileTree &t)
{
	if (!t)return 0;
	if (!t->firstchild)return 1;
	FileTree p;
	int ans = 0, depth = 0;
	p = t->firstchild;
	while (p)
	{
		depth = GetDepth(p);

		if (depth > ans)

			ans = depth;

		p = p->nextsibling;
	}
}

FileDirectory::FileDirectory()
{
	T = new FileNode;
	T->level = 1;
	T->parent = T;
	string szDir = "C:";
	T->filename = szDir;
	T->filepath = szDir;
	T->nextsibling = NULL;
	T->firstchild = NULL;
	T->type = folder;
	T->seniority = 1;

	current_layer = 1;
	cout << szDir << endl;
	
	CreateTree(T);
	
	layer_num = GetDepth(T);
}

int FileDirectory::Traversal(FileTree t)
{
	FileTree p = t->firstchild;
	while (p)
	{
		cout << p->filename << endl;
		p = p->nextsibling;
	}
	return 1;
}