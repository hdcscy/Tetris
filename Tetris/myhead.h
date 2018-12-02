#include <iostream>
#include <string.h>
#include "const.h"

using namespace std;

class CTetris {
public:
    /*-----1.��ʼ����������-----*/
    //���캯��
    CTetris(const char *szTemp);

    //�������캯��
    CTetris(const CTetris& dup);

    //��������
    ~CTetris();

    //���ƽ���
    void DrawUI();

    //��ӡ����
    void PrintUI();

    //��ʾ
    void MovePostion(int x, int y);

    //�Ҳ����
    void RightDraw();

    //�������
    bool DrawTetris_L_A(int nMove);
    bool DrawTetris_L_B(int nMove);
    bool DrawTetris_Z_A(int nMove);
    bool DrawTetris_Z_B(int nMove);
    bool DrawTetris_T(int nMove);
    bool DrawTetris_I(int nMove);
    bool DrawTetris_Square(int nMove);

    /*-----2.���ܲ���-----*/

    //���ɺ���
    void Hub();

    //��궨λ
    void DrawString(int x, int y, const char * szStr);

    //������ַ���
    bool SrandTetris(int nMove, int m_type);

    //��ת����
    void RotateTetris(char *block, int nMove);

    //�ж���Ϸ�Ƿ����
    void GameOver();

    //�����ƶ�������
    void MoveTetrisRL(char ch, char* TetrisTp, int nMove);

    //�����ͷ�������⴦��
    void MoveSquareRL(char ch, char* TetrisTp, int nMove);

    //����
    void DelLine(char* Map);

private:
    char* m_pszStart;
    int m_nMaxWidth = 12;    //Χǽ�����
    int m_nMaxHeight = 21;   //Χǽ��󳤶�
    char* m_pszMap;     //���Ƶ�ͼ��
    int m_type;         //��������
    int m_GlobalX = 0;  //ȫ��Xƫ����
    int m_nScore = 0;   //����
    int m_nRandProc;    //�����
    int m_nRandNext;    //�����һ�������

    bool bFlag;
    char *mapsNest = new char[4 * 4] { 0 };
};