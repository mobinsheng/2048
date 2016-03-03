// 2048_a.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <time.h>

using namespace std;

#include "MIniFile.h"
#include "MAchive.h"

#define _TEST_																			// ���Ժ�

/*********************************************
*    �궨��                                                                 
*********************************************/
#define EXIT_PROMPT										("game over!")
#define INPUT_ERROR_PROMPT						("error input. please input 'a'[��] or 'w'[��] or 's'[��] or 'd'[��] or 'q'[exit]")
#define INPUT_PROMPT									("next step 'a'[��],'w'[��],'s'[��],'d'[��],'q'[exit] >>")

#define																QUIT ('q')

/*********************************************
*    �ƶ��ķ���                                                                  
*********************************************/
enum Orientation
{
	UP			= 'w',	// ����
	DOWN		= 's',		// ����
	LEFT			= 'a',		// ����
	RIGHT		= 'd'		// ����
};

/*********************************************
*    ������                                                                  
*********************************************/
class Util
{
public:
	
	static int GetNumLen(int d)						// ��ȡһ���޷������ĳ��ȣ�����3600�ĳ�����4
	{
		char buf[8] = {0};

		sprintf(buf,"%d",d);

		int len = 0;

		return strlen(buf);
	}

	static int GetRandomNum(int a,int b)		// ��ȡ����[a,b)�ڵ������
	{
		srand((unsigned)time(NULL)); 

		return rand()%(b-a)+a;
	}

	static char Drive()										// ��������
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
*    �����࣬һ���������λ����Ϣ����ֵ                                                                 
*********************************************/
struct Box 
{
	int x;				// ������
	int y;				// ������
	int data;		// ����

	Box()
	{
		x = -1;

		y = -1;

		data = 0;
	}
};

/*********************************************
*    ����һ����n*n�ķ������                                                                  
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

	void Init(int width,int heigh)														// ��ʼ��
	{
		Clean();																					// ���Ƚ�������

		SetHeight(heigh);																	// ���ø߶�

		SetWidth(width);																	// ���ÿ��

		m_Data = new vector<Box*>[heigh];									

		if (m_Data == NULL)
		{
			return;
		}

		for (int i = 0; i < m_nHeigth; ++i)											// �����ʼ��
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

		Box* pBox = GetRandomEmptyPosAndProduce2or4();			// ����һ������ķ��飬�÷����ֵ��2��4
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

	Box* GetRandomEmptyPosAndProduce2or4()							// �ڿյķ��飨��data=0�ķ��飩�������ȡһ����Ȼ�����һ��2��4
	{
		vector<Box*> line;																// ���ڴ�ſյķ���

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

		int num = Util::GetRandomNum(0,line.size());						// �ӿյķ����������ȡһ��

		Box* box = line[num];

		box->data = Produce2or4();

		return box;
	}

protected:
	
	void SetWidth(int w)																	// ���ÿ��
	{
		m_nWidth = w;
	}

	void SetHeight(int h)																	// ���ø߶�
	{
		m_nHeigth = h;
	}

	void Clean()																				// ����
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

	int Produce2or4()																	// ���ݸ��ʲ���2��4
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
*    ��Ϸ����                                                                  
*********************************************/
class My2048
{
public:
	static My2048* GetInstance()											// ��ȡ����
	{
		if (NULL == m_pInstance)
		{
			m_pInstance = new My2048();
		}

		return m_pInstance;
	}

	void Run()																			// ������Ϸ
	{
		ShowGrid();																	// ��ʾ��Ϸ

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
	
	char GetInput()																	// ��ȡ�û�����
	{
		string strInput = "";

		cin >> strInput;

		return strInput[strInput.size() - 1];
	}

	void Output(string str,bool bReturn = true)						// �����Ϣ
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

	void ShowGrid()																// ��ʾ��Ϸ
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

	bool CanMove()																// �ж��Ƿ�����ƶ�
	{
		for (int i = 0; i < m_Grid.GetHeight() ; ++i)					// ���Ȳ鿴������Ƿ���ֵΪ0�����ո��ӣ��ĸ��ӣ��������ô�����ƶ�
		{
			for (int j = 0; j < m_Grid.GetWidth() ; ++j)
			{
				if ( m_Grid.Get(i,j)->data  == 0)
				{
					return true;
				}
			}
		}

		for (int i = 0; i < m_Grid.GetHeight() ; ++i)					// ������ӵ�ֵ����Ϊ0�������еĸ��Ӷ��Ѿ���������ˣ�����ô�鿴���ڵĸ����Ƿ���Ժϲ���������Ժϲ�����ô��ʾ�������ƶ�
		{
			for (int j = 0; j < m_Grid.GetWidth() ; ++j)
			{
				if (i == 0 && j == 0)											// ���ϽǸ������⴦��
				{
					if (m_Grid.Get(i,j)->data == m_Grid.Get(i+1,j)->data ||
						m_Grid.Get(i,j)->data == m_Grid.Get(i,j+1)->data)
					{
						return true;
					}
					continue;
				}

				if (i == 0 && j == m_Grid.GetWidth() - 1)			// ���ϽǸ������⴦��
				{
					if (m_Grid.Get(i,j)->data == m_Grid.Get(i,j-1)->data ||
						m_Grid.Get(i,j)->data == m_Grid.Get(i+1,j)->data)
					{
						return true;
					}
					continue;
				}

				if (i == m_Grid.GetHeight() - 1 && j == 0)			//���½Ǹ������⴦��
				{
					if (m_Grid.Get(i,j)->data == m_Grid.Get(i-1,j)->data ||
						m_Grid.Get(i,j)->data == m_Grid.Get(i,j+1)->data)
					{
						return true;
					}
					continue;
				}

				if (i == m_Grid.GetHeight() - 1 && j == m_Grid.GetWidth() - 1) //���½Ǹ������⴦��
				{
					if (m_Grid.Get(i,j)->data == m_Grid.Get(i-1,j)->data ||
						m_Grid.Get(i,j)->data == m_Grid.Get(i,j-1)->data)
					{
						return true;
					}
					continue;
				}

				if (i ==0 )																					// ��һ�еĸ���
				{
					if (m_Grid.Get(i,j)->data == m_Grid.Get(i,j-1)->data ||
						m_Grid.Get(i,j)->data == m_Grid.Get(i,j+1)->data ||
						m_Grid.Get(i,j)->data == m_Grid.Get(i+1,j)->data)
					{
						return true;
					}
					continue;
				}

				if (j == 0)																					//��һ�и���														
				{
					if (m_Grid.Get(i,j)->data == m_Grid.Get(i-1,j)->data ||
						m_Grid.Get(i,j)->data == m_Grid.Get(i,j+1)->data ||
						m_Grid.Get(i,j)->data == m_Grid.Get(i+1,j)->data)
					{
						return true;
					}
					continue;
				}

				if (i ==m_Grid.GetHeight() - 1 )													//���һ�еĸ���
				{
					if (m_Grid.Get(i,j)->data == m_Grid.Get(i,j-1)->data ||
						m_Grid.Get(i,j)->data == m_Grid.Get(i,j+1)->data ||
						m_Grid.Get(i,j)->data == m_Grid.Get(i-1,j)->data)
					{
						return true;
					}
					continue;
				}

				if (j == m_Grid.GetWidth() - 1) // ���һ��
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

	void MoveLeft()																// �����ƶ�
	{
		bool bMove = false;														// �ж��Ƿ�����ƶ����ӣ����������ھ����Ƿ�����¸���

		for (int i = 0; i < m_Grid.GetHeight(); ++i)						// ���һ�е���ֵ��Ϊ0�ĸ���
		{
			vector<int> line;

			Box* box = 0;

			bool bFirstZero = false;												// ��һ���б�������һ������0

			for (int j = 0; j < m_Grid.GetWidth();++j)
			{
				box = m_Grid.Get(i,j);

				if (box->data != 0)
				{
					line.push_back(box->data);

					box->data = 0;

					if (bFirstZero)													// ���������֮���з���ĸ��ӣ���ô�����ƶ�
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
					line[k] = line[k] * 2;															// ���Ӻϲ�

					line[k + 1] = 0;

					m_nTotal += line[k];															// ��������

					bMove = true;																	// ���ӿ��Ժϲ�Ҳ��ʾ�����ƶ�
				}
			}

			int col = 0;

			for (int k = 0 ; k < line.size() ; ++k)
			{
				if (line[k]> 0)
				{
					m_Grid.Get(i,col)->data = line[k];										// ���ƶ�������֮��ĸ��Ӹ��ƻ�ԭ���ĸ�����

					col++;
				}
			}
		}

		if (bMove)
		{
			Box* box = m_Grid.GetRandomEmptyPosAndProduce2or4();	// ��������µĸ���
		}
	}

	
	void MoveRigth()																				// �����ƶ����߼�ͬ��
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

	void MoveUp()																							// �����ƶ����߼�ͬ��
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

	void MoveDown()																											// �����ƶ�
	{
		bool bMove = false;																									// �ж������Ƿ�����ƶ��������������ƶ���Ȼ�����һ��2��4��

		for (int j = 0; j< m_Grid.GetWidth(); ++j)																	
		{
			vector<int> line;																									// ���һ�е���ֵ��Ϊ0�ĸ���

			Box* box = 0;

			bool bFisrtZero = false;																							// ����һ�е�ʱ���ҵ��ĵ�һ��ֵΪ0�ĸ���

			for (int i = m_Grid.GetHeight() - 1; i >= 0 ;--i)														// �������Ͽ�ʼ����
			{
				box = m_Grid.Get(i,j);

				if (box->data != 0)
				{
					line.push_back(box->data);

					box->data = 0;

					if (bFisrtZero)																								// �������һ��0֮��������0�ĸ��ӣ���ô��ʾ�ǿ����ƶ���
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
					line[k] = line[k] * 2;																						// �����������������ͬ����ô�ϲ�

					line[k  - 1] = 0;

					m_nTotal += line[k];																						// �������

					bMove = true;																								// ���Ժϲ�Ҳ��ʾ�����ƶ�
				}
			}

			int row = m_Grid.GetHeight() - 1;

			for (int k = line.size() - 1 ; k >= 0 ; --k)
			{
				if (line[k]> 0)
				{
					m_Grid.Get(row,j)->data = line[k];																	// ����֮��Ľ�����Ƹ�����

					row--;
				}
			}
		}

		if (bMove)	
		{
			Box* box = m_Grid.GetRandomEmptyPosAndProduce2or4();								// �����¸���
		}
	}
private:

	Grid					m_Grid;																									// ��Ϸ���

	static My2048*	m_pInstance;																						// ��Ϸʵ��

	unsigned long	m_nTotal;																								// �ܷ�

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
