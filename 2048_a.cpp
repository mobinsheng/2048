// 2048_a.cpp : 定义控制台应用程序的入口点。
//

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <time.h>

using namespace std;

#include "MIniFile.h"
#include "MAchive.h"

#define _TEST_																			// 测试宏

/*********************************************
*    宏定义                                                                 
*********************************************/
#define EXIT_PROMPT										("game over!")
#define INPUT_ERROR_PROMPT						("error input. please input 'a'[←] or 'w'[↑] or 's'[↓] or 'd'[→] or 'q'[exit]")
#define INPUT_PROMPT									("next step 'a'[←],'w'[↑],'s'[↓],'d'[→],'q'[exit] >>")

#define																QUIT ('q')

/*********************************************
*    移动的方向                                                                  
*********************************************/
enum Orientation
{
	UP			= 'w',	// 向上
	DOWN		= 's',		// 向下
	LEFT			= 'a',		// 向左
	RIGHT		= 'd'		// 向右
};

/*********************************************
*    工具类                                                                  
*********************************************/
class Util
{
public:
	
	static int GetNumLen(int d)						// 获取一个无符号数的长度，例如3600的长度是4
	{
		char buf[8] = {0};

		sprintf(buf,"%d",d);

		int len = 0;

		return strlen(buf);
	}

	static int GetRandomNum(int a,int b)		// 获取区间[a,b)内的随机数
	{
		srand((unsigned)time(NULL)); 

		return rand()%(b-a)+a;
	}

	static char Drive()										// 驱动测试
	{
		static unsigned long count= 0;

		int leftcount = count % 4;

		++count;

		switch(leftcount)
		{
		case 0:
			return UP;
			break;
		case 1:
			return DOWN;
			break;
		case 2:
			return LEFT;
			break;
		case 3:
			return RIGHT;
			break;
		}
	}
};


/*********************************************
*    方块类，一个方块存有位置信息和数值                                                                 
*********************************************/
struct Box 
{
	int x;				// 横坐标
	int y;				// 纵坐标
	int data;		// 数据

	Box()
	{
		x = -1;

		y = -1;

		data = 0;
	}
};

/*********************************************
*    网格，一般由n*n的方块组成                                                                  
*********************************************/
class Grid
{
public:

	typedef vector<Box*>::iterator Iter;

	Grid()
	{
		m_nWidth = 0;

		m_nHeigth = 0;

		m_Data = 0;
	}

	virtual ~Grid()
	{
		Clean();
	}

	void Init(int width,int heigh)														// 初始化
	{
		Clean();																					// 首先进行清理

		SetHeight(heigh);																	// 设置高度

		SetWidth(width);																	// 设置宽度

		m_Data = new vector<Box*>[heigh];									

		if (m_Data == NULL)
		{
			return;
		}

		for (int i = 0; i < m_nHeigth; ++i)											// 方块初始化
		{
			for (int j = 0 ; j < m_nWidth; ++j)
			{
				Box* box = new Box();

				box->x = i;

				box->y = j;

				box->data = 0;

				m_Data[i].push_back(box);
			}
		}

		Box* pBox = GetRandomEmptyPosAndProduce2or4();			// 产生一个随机的方块，该方块的值是2或4
	}

	int GetWidth()
	{
		return m_nWidth;
	}

	int GetHeight()
	{
		return m_nHeigth;
	}

	Box* Get(int i,int j)
	{
		if (!m_Data)
		{
			return 0;
		}

		return m_Data[i][j];
	}

	Box* GetRandomEmptyPosAndProduce2or4()							// 在空的方块（即data=0的方块）中随机抽取一个，然后产生一个2或4
	{
		vector<Box*> line;																// 用于存放空的方块

		for (int i = 0; i < m_nHeigth; ++i)
		{
			for (int j = 0; j < m_nWidth; ++j)
			{
				if (m_Data[i][j]->data == 0)
				{
					line.push_back(m_Data[i][j]);
				}
			}
		}

		int num = Util::GetRandomNum(0,line.size());						// 从空的方块中随机抽取一个

		Box* box = line[num];

		box->data = Produce2or4();

		return box;
	}

protected:
	
	void SetWidth(int w)																	// 设置宽度
	{
		m_nWidth = w;
	}

	void SetHeight(int h)																	// 设置高度
	{
		m_nHeigth = h;
	}

	void Clean()																				// 清理
	{
		if (!m_Data)
		{
			return;
		}

		for (int i = 0; i < m_nHeigth; ++i)
		{
			for (Iter it = m_Data[i].begin(); it != m_Data[i].end(); ++it)
			{
				Box* box = *it;

				delete box;
			}
		}

		delete[] m_Data;

		m_Data = 0;

		m_nHeigth = 0;

		m_nWidth = 0;
	}

	int Produce2or4()																	// 根据概率产生2或4
	{
		int num = Util::GetRandomNum(0,100);

		if (num < 90)
		{
			return 2;
		}
		else
		{
			return 4;
		}
	}

private:
	int m_nWidth;

	int m_nHeigth;

	vector<Box*>* m_Data;
};

/*********************************************
*    游戏主类                                                                  
*********************************************/
class My2048
{
public:
	static My2048* GetInstance()											// 获取单例
	{
		if (NULL == m_pInstance)
		{
			m_pInstance = new My2048();
		}

		return m_pInstance;
	}

	void Run()																			// 运行游戏
	{
		ShowGrid();																	// 显示游戏

		char chInput = 0;

		while(chInput != QUIT && CanMove())
		{
			Output(INPUT_PROMPT);

#ifdef _TEST_
			chInput = Util::Drive();
#else
			chInput = GetInput();
#endif
			switch(chInput)
			{
			case UP:
				MoveUp();
				ShowGrid();
				break;
			case LEFT:
				MoveLeft();
				ShowGrid();
				break;
			case DOWN:
				MoveDown();
				ShowGrid();
				break;
			case RIGHT:
				MoveRigth();
				ShowGrid();
				break;
			default:
				Output(INPUT_ERROR_PROMPT);
				break;
			}
		}
	}

protected:
	
	char GetInput()																	// 获取用户输入
	{
		string strInput = "";

		cin >> strInput;

		return strInput[strInput.size() - 1];
	}

	void Output(string str,bool bReturn = true)						// 输出信息
	{
		if (bReturn == true)
		{
			cout<< str<<endl;
		}
		else
		{
			cout<< str;
		}
	}

	void ShowGrid()																// 显示游戏
	{
		cout<<"Total:"<<m_nTotal<<endl;

		for (int i = 0; i < m_Grid.GetWidth(); ++i)
		{
			cout<<"-------------------------------------"<<endl;

			string strRow = "|";

			int emptyspace = 8;

			for (int j = 0; j < m_Grid.GetHeight(); ++j)
			{
				Box* box = NULL;

				box = m_Grid.Get(i,j);

				if (box->data != 0)
				{
					int data = box->data;

					int datalen = Util::GetNumLen(data);

					string strFormat = "";

					for (int x=0; x < (emptyspace - datalen) / 2; ++x)
					{
						strFormat += " ";
					}

					strFormat += "%d";

					for (int x=0; x < emptyspace - datalen - (emptyspace - datalen) / 2; ++x)
					{
						strFormat += " ";
					}

					char buf[64] = {0};

					sprintf(buf,strFormat.c_str(),box->data);

					strRow += buf;
				}
				else
				{
					strRow += "        ";
				}

				strRow += "|";
			}

			cout<<strRow<<endl;
		}

		cout<<"-------------------------------------"<<endl;
	}

	bool CanMove()																// 判断是否可以移动
	{
		for (int i = 0; i < m_Grid.GetHeight() ; ++i)					// 首先查看表格中是否还是值为0（即空格子）的格子，如果有那么可以移动
		{
			for (int j = 0; j < m_Grid.GetWidth() ; ++j)
			{
				if ( m_Grid.Get(i,j)->data  == 0)
				{
					return true;
				}
			}
		}

		for (int i = 0; i < m_Grid.GetHeight() ; ++i)					// 如果格子的值都不为0（即所有的格子都已经被填充满了），那么查看相邻的格子是否可以合并，如果可以合并，那么表示还可以移动
		{
			for (int j = 0; j < m_Grid.GetWidth() ; ++j)
			{
				if (i == 0 && j == 0)											// 左上角格子特殊处理
				{
					if (m_Grid.Get(i,j)->data == m_Grid.Get(i+1,j)->data ||
						m_Grid.Get(i,j)->data == m_Grid.Get(i,j+1)->data)
					{
						return true;
					}
					continue;
				}

				if (i == 0 && j == m_Grid.GetWidth() - 1)			// 右上角格子特殊处理
				{
					if (m_Grid.Get(i,j)->data == m_Grid.Get(i,j-1)->data ||
						m_Grid.Get(i,j)->data == m_Grid.Get(i+1,j)->data)
					{
						return true;
					}
					continue;
				}

				if (i == m_Grid.GetHeight() - 1 && j == 0)			//左下角格子特殊处理
				{
					if (m_Grid.Get(i,j)->data == m_Grid.Get(i-1,j)->data ||
						m_Grid.Get(i,j)->data == m_Grid.Get(i,j+1)->data)
					{
						return true;
					}
					continue;
				}

				if (i == m_Grid.GetHeight() - 1 && j == m_Grid.GetWidth() - 1) //右下角格子特殊处理
				{
					if (m_Grid.Get(i,j)->data == m_Grid.Get(i-1,j)->data ||
						m_Grid.Get(i,j)->data == m_Grid.Get(i,j-1)->data)
					{
						return true;
					}
					continue;
				}

				if (i ==0 )																					// 第一行的格子
				{
					if (m_Grid.Get(i,j)->data == m_Grid.Get(i,j-1)->data ||
						m_Grid.Get(i,j)->data == m_Grid.Get(i,j+1)->data ||
						m_Grid.Get(i,j)->data == m_Grid.Get(i+1,j)->data)
					{
						return true;
					}
					continue;
				}

				if (j == 0)																					//第一列格子														
				{
					if (m_Grid.Get(i,j)->data == m_Grid.Get(i-1,j)->data ||
						m_Grid.Get(i,j)->data == m_Grid.Get(i,j+1)->data ||
						m_Grid.Get(i,j)->data == m_Grid.Get(i+1,j)->data)
					{
						return true;
					}
					continue;
				}

				if (i ==m_Grid.GetHeight() - 1 )													//最后一行的格子
				{
					if (m_Grid.Get(i,j)->data == m_Grid.Get(i,j-1)->data ||
						m_Grid.Get(i,j)->data == m_Grid.Get(i,j+1)->data ||
						m_Grid.Get(i,j)->data == m_Grid.Get(i-1,j)->data)
					{
						return true;
					}
					continue;
				}

				if (j == m_Grid.GetWidth() - 1) // 最后一列
				{
					if (m_Grid.Get(i,j)->data == m_Grid.Get(i-1,j)->data ||
						m_Grid.Get(i,j)->data == m_Grid.Get(i+1,j)->data ||
						m_Grid.Get(i,j)->data == m_Grid.Get(i,j-1)->data)
					{
						return true;
					}
					continue;
				}

				if (m_Grid.Get(i-1,j)->data == m_Grid.Get(i,j)->data ||
					m_Grid.Get(i,j-1)->data == m_Grid.Get(i,j)->data ||
					m_Grid.Get(i,j+1)->data == m_Grid.Get(i,j)->data ||
					m_Grid.Get(i+1,j)->data == m_Grid.Get(i,j)->data 
					)
				{
					return true;
				}
			}
		}

		Output(EXIT_PROMPT);

		return false;
	}

	void MoveLeft()																// 向左移动
	{
		bool bMove = false;														// 判断是否可以移动格子，此条件用于决定是否产生新格子

		for (int i = 0; i < m_Grid.GetHeight(); ++i)						// 存放一行当中值不为0的格子
		{
			vector<int> line;

			Box* box = 0;

			bool bFirstZero = false;												// 在一行中遍历，第一次遇到0

			for (int j = 0; j < m_Grid.GetWidth();++j)
			{
				box = m_Grid.Get(i,j);

				if (box->data != 0)
				{
					line.push_back(box->data);

					box->data = 0;

					if (bFirstZero)													// 如果遇到零之后还有非零的格子，那么可以移动
					{
						bMove = true;
					}
				}
				else
				{
					bFirstZero = true;
				}
			}

			if (line.size() == 0)
			{
				continue;
			}

			for (int k = 0 ; k < line.size() - 1; ++k)
			{
				if ( (line[k]> 0) && (line[k] == line[k + 1]))
				{
					line[k] = line[k] * 2;															// 格子合并

					line[k + 1] = 0;

					m_nTotal += line[k];															// 分数计算

					bMove = true;																	// 格子可以合并也表示可以移动
				}
			}

			int col = 0;

			for (int k = 0 ; k < line.size() ; ++k)
			{
				if (line[k]> 0)
				{
					m_Grid.Get(i,col)->data = line[k];										// 将移动、计算之后的格子复制回原来的格子中

					col++;
				}
			}
		}

		if (bMove)
		{
			Box* box = m_Grid.GetRandomEmptyPosAndProduce2or4();	// 随机产生新的格子
		}
	}

	
	void MoveRigth()																				// 向右移动，逻辑同上
	{
		bool bMove = false;

		for (int i = 0; i < m_Grid.GetHeight(); ++i)
		{
			//list<int> tmplist;

			vector<int> line;

			Box* box = 0;

			bool bFirstZero = false;

			for (int j = m_Grid.GetWidth() - 1; j  >= 0;--j)
			{
				box = m_Grid.Get(i,j);

				if (box->data != 0)
				{
					line.push_back(box->data);

					box->data = 0;

					if (bFirstZero)
					{
						bMove = true;
					}
				}
				else
				{
					bFirstZero = true;
				}
			}

			if (line.size() == 0)
			{
				continue;
			}

			reverse(line.begin(),line.end());

			for (int k = line.size() -1 ; k > 0; --k)
			{
				if ( (line[k]> 0) && (line[k] == line[k - 1]))
				{
					line[k] = line[k] * 2;

					line[k  - 1] = 0;

					m_nTotal += line[k];

					bMove = true;
				}
			}

			int col = m_Grid.GetWidth() - 1;

			for (int k = line.size() - 1 ; k >= 0 ; --k)
			{
				if (line[k]> 0)
				{
					m_Grid.Get(i,col)->data = line[k];

					col--;
				}
			}
		}

		if (bMove)
		{
			Box* box = m_Grid.GetRandomEmptyPosAndProduce2or4();
		}
	}

	void MoveUp()																							// 向上移动，逻辑同上
	{
		bool bMove = false;

		for (int j = 0; j< m_Grid.GetWidth(); ++j)
		{
			vector<int> line;

			Box* box = 0;

			bool bFirstZero = false;

			for (int i = 0; i < m_Grid.GetHeight();++i)
			{
				box = m_Grid.Get(i,j);

				if (box->data != 0)
				{
					line.push_back(box->data);

					box->data = 0;

					if (bFirstZero)
					{
						bMove = true;
					}
				}
				else
				{
					bFirstZero = true;
				}
			}

			if (line.size() == 0)
			{
				continue;
			}

			for (int k = 0 ; k < line.size() -1; ++k)
			{
				if ( (line[k]> 0) && (line[k] == line[k + 1]))
				{
					line[k] = line[k] * 2;

					line[k  + 1] = 0;

					m_nTotal += line[k];

					bMove = true;
				}
			}

			int row = 0;

			for (int k = 0 ; k < line.size()  ; ++k)
			{
				if (line[k]> 0)
				{
					m_Grid.Get(row,j)->data = line[k];

					row++;
				}
			}
		}

		if (bMove)
		{
			Box* box = m_Grid.GetRandomEmptyPosAndProduce2or4();
		}
	}

	void MoveDown()																											// 向下移动
	{
		bool bMove = false;																									// 判断向下是否可以移动（即可以往左移动，然后产生一个2或4）

		for (int j = 0; j< m_Grid.GetWidth(); ++j)																	
		{
			vector<int> line;																									// 存放一列当中值不为0的格子

			Box* box = 0;

			bool bFisrtZero = false;																							// 遍历一列的时候找到的第一个值为0的格子

			for (int i = m_Grid.GetHeight() - 1; i >= 0 ;--i)														// 从下往上开始查找
			{
				box = m_Grid.Get(i,j);

				if (box->data != 0)
				{
					line.push_back(box->data);

					box->data = 0;

					if (bFisrtZero)																								// 如果遇到一个0之后还遇到非0的格子，那么表示是可以移动的
					{
						bMove = true;
					}
				}
				else
				{
					bFisrtZero = true;
				}
			}

			if (line.size() == 0)
			{
				continue;
			}

			reverse(line.begin(),line.end());

			for (int k = line.size() -1 ; k > 0; --k)
			{
				if ( (line[k]> 0) && (line[k] == line[k - 1]))
				{
					line[k] = line[k] * 2;																						// 相邻两个格子如果相同，那么合并

					line[k  - 1] = 0;

					m_nTotal += line[k];																						// 计算分数

					bMove = true;																								// 可以合并也表示可以移动
				}
			}

			int row = m_Grid.GetHeight() - 1;

			for (int k = line.size() - 1 ; k >= 0 ; --k)
			{
				if (line[k]> 0)
				{
					m_Grid.Get(row,j)->data = line[k];																	// 计算之后的结果复制给格子

					row--;
				}
			}
		}

		if (bMove)	
		{
			Box* box = m_Grid.GetRandomEmptyPosAndProduce2or4();								// 产生新格子
		}
	}
private:

	Grid					m_Grid;																									// 游戏表格

	static My2048*	m_pInstance;																						// 游戏实例

	unsigned long	m_nTotal;																								// 总分

	My2048(int m = 4,int n = 4)
	{
		m_nTotal = 0;

		m_Grid.Init(m,n);
	}
};

My2048* My2048::m_pInstance = 0;


#include "../libHead/TemplateArray.h"

int main(int argc, char* argv[])
{
	getchar();

	MBS::TemplateArray<int> X;
	return 0;
}
