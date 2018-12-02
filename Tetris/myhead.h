#include <iostream>
#include <string.h>
#include "const.h"

using namespace std;

class CTetris {
public:
    /*-----1.初始化和清理部分-----*/
    //构造函数
    CTetris(const char *szTemp);

    //拷贝构造函数
    CTetris(const CTetris& dup);

    //析构函数
    ~CTetris();

    //绘制界面
    void DrawUI();

    //打印界面
    void PrintUI();

    //显示
    void MovePostion(int x, int y);

    //右侧绘制
    void RightDraw();

    //方块绘制
    bool DrawTetris_L_A(int nMove);
    bool DrawTetris_L_B(int nMove);
    bool DrawTetris_Z_A(int nMove);
    bool DrawTetris_Z_B(int nMove);
    bool DrawTetris_T(int nMove);
    bool DrawTetris_I(int nMove);
    bool DrawTetris_Square(int nMove);

    /*-----2.功能部分-----*/

    //集成函数
    void Hub();

    //光标定位
    void DrawString(int x, int y, const char * szStr);

    //随机出现方块
    bool SrandTetris(int nMove, int m_type);

    //旋转方块
    void RotateTetris(char *block, int nMove);

    //判定游戏是否结束
    void GameOver();

    //左右移动、变形
    void MoveTetrisRL(char ch, char* TetrisTp, int nMove);

    //田字型方块的特殊处理
    void MoveSquareRL(char ch, char* TetrisTp, int nMove);

    //消行
    void DelLine(char* Map);

private:
    char* m_pszStart;
    int m_nMaxWidth = 12;    //围墙最大宽度
    int m_nMaxHeight = 21;   //围墙最大长度
    char* m_pszMap;     //绘制的图形
    int m_type;         //方块类型
    int m_GlobalX = 0;  //全局X偏移量
    int m_nScore = 0;   //计数
    int m_nRandProc;    //随机数
    int m_nRandNext;    //存放下一个随机数

    bool bFlag;
    char *mapsNest = new char[4 * 4] { 0 };
};