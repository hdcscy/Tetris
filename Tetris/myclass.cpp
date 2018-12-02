#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include "myhead.h"
#include <conio.h>
#include "const.h"

using namespace std;

//�Զ��幹�캯��
CTetris::CTetris(const char *szTemp) //szTemp�����ǳ�ʼ��ָ��
    :m_pszStart("start") {

    CONSOLE_CURSOR_INFO cci = { 1, 0 };
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cci);

    if (strcmp(m_pszStart, szTemp) != 0) {
        cout << "Parameter is error!" << endl;
        cout << "Please input \"start\"!" << endl;
    }

    int nFlag = 0;
    int nTemp = 0;

    srand((unsigned int)time(NULL));
    m_nRandNext = rand() % 7 + 1;
    m_nRandProc = m_nRandNext;

    DrawUI();

    while(1) {
        GameOver();
        nFlag = 0;
        m_GlobalX = 3;
        m_nRandNext = rand() % 7 + 1;
        bFlag = false;
        while (nFlag < m_nMaxHeight) {
            PrintUI();
            if (SrandTetris(nFlag, m_nRandProc)) {
            //if (DrawTetris_Square(nFlag)) {
                break;
            }

            nFlag++;
            
            //��ʱ
            for (int n = 0; n < 30000; n++) {
                if (_kbhit()) {
                    break;
                }
            }
        }
        
        m_nRandProc = m_nRandNext;
        DelLine(m_pszMap);
    }
}

//�������캯��
CTetris::CTetris(const CTetris& dup) {
    
}

//��������
CTetris::~CTetris() {
    //�ͷ���Դ
    delete(m_pszMap);
    cout << "Game models will close." << endl;
}

//���ƽ���
void CTetris::DrawUI() {
    //����Χǽ��0��1���
    m_pszMap = new char[m_nMaxWidth * m_nMaxHeight];

    for (int i = 0; i < m_nMaxHeight; i++) {
        for (int j = 0; j < m_nMaxWidth; j++) {
            if (j == 0 || j == m_nMaxWidth - 1 || i == m_nMaxHeight - 1) {
                m_pszMap[i * m_nMaxWidth + j] = 1;
            } else {
                m_pszMap[i * m_nMaxWidth + j] = 0;
            }
        }
    }
}

//��ʾ����
void CTetris::PrintUI() {
    //Χǽ�Ͳ��ݷ�����ʾ���
    for (int i = 0; i < m_nMaxHeight; i++) {
        for (int j = 0; j < m_nMaxWidth; j++) {
            if (m_pszMap[i * m_nMaxWidth + j] == 1) { 
                DrawString(j, i, "��");
            } else if (m_pszMap[i * m_nMaxWidth + j] == 0) {
                DrawString(j, i, "  ");
            }
        }
    }

    //������ʾ���
    MovePostion(14, 0);
    printf(" +----Score----+");
    MovePostion(14, 1);
    printf(" |             |");
    MovePostion(14, 2);
    printf(" |    %.5d    |", m_nScore);
    MovePostion(14, 3);
    printf(" |             |");
    MovePostion(14, 4);
    printf(" +-------------+");

    //������ʾ��飨���ڣ�
    MovePostion(14, 6);
    printf(" +-----Now-----+");
    MovePostion(14, 7);
    printf(" |             |");
    MovePostion(14, 8);
    printf(" |             |");
    MovePostion(14, 9);
    printf(" |             |");
    MovePostion(14, 10);
    printf(" |             |");
    MovePostion(14, 11);
    printf(" |             |");
    MovePostion(14, 12);
    printf(" +-------------+");

    //��һ��
    MovePostion(14, 14);
    printf(" +----Next.----+");
    MovePostion(14, 15);
    printf(" |             |");
    MovePostion(14, 16);
    printf(" |             |");
    MovePostion(14, 17);
    printf(" |             |");
    MovePostion(14, 18);
    printf(" |             |");
    MovePostion(14, 19);
    printf(" |             |");
    MovePostion(14, 20);
    printf(" +-------------+");
}

//���
void CTetris::MovePostion(int x, int y)
{
    HANDLE hWnd = GetStdHandle(STD_OUTPUT_HANDLE);
    int X = x;
    int Y = y;
    
    COORD pos = { 0 };
    pos.X = (short)(X * 2);
    pos.Y = (short)Y;
    SetConsoleCursorPosition(hWnd, pos);
}

//�����ַ���
void CTetris::DrawString(int x, int y, const char * szStr)
{
    HANDLE hWnd = GetStdHandle(STD_OUTPUT_HANDLE);
    MovePostion(x, y);
    printf(szStr);
    COORD pos = { 0 };
    pos.X = 0;
    pos.Y = 0;
    SetConsoleCursorPosition(hWnd, pos);
}

//�������
bool CTetris::SrandTetris(int nMove, int m_type) {
    bool bFlag = false;
    switch (m_type) {
        case 1:
            bFlag = DrawTetris_L_A(nMove);
            break;
        case 2:
            bFlag = DrawTetris_L_B(nMove);
            break;
        case 3:
            bFlag = DrawTetris_Z_A(nMove);
            break;
        case 4:
            bFlag = DrawTetris_Z_B(nMove);
            break;
        case 5:
            bFlag = DrawTetris_T(nMove);
            break;
        case 6:
            bFlag = DrawTetris_I(nMove);
            break;
        case 7:
            bFlag = DrawTetris_Square(nMove);
            break;
    }

    return bFlag;
}

//ͼ����ת
void CTetris::RotateTetris(char *block, int nMove) {
    //��ͼ��С
    int nMapSize = 4;
    char szAryTemp[4][4] = { 0 };

    //��ʱ�ռ�
    char *ary = (char *) new char[16]{ 0 };
    if (ary == NULL) {
        goto EXIT_PROC;
    }

    //����ת
    for (int i = 0; i < nMapSize; i++) {
        for (int j = 0; j < nMapSize; j++) {
            //˳ʱ����ת,�и����б仯
            ary[i * nMapSize + j] = block[j * nMapSize + (nMapSize - 1 - i)];
        }
    }

    //�ȴ������ά����
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            szAryTemp[i][j] = ary[i * 4 + j];
        }
    }
     
    //�ж��Ա��Ƿ������ת
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (szAryTemp[i][j] == 1) { //1
                int nX = i + nMove;
                int nY = j + 1 + m_GlobalX;
                char szFlag = m_pszMap[nX * m_nMaxWidth + nY];
                if (szFlag == 1) {
                    return;
                }
            }
        }
    }
    //��ֵ��block
    ::memcpy(block, ary, nMapSize * nMapSize);

EXIT_PROC:
    if (ary != NULL)
    {
        delete ary;
    }
    return;
}

//�����ͷ�������⴦��
void CTetris::MoveSquareRL(char ch, char* TetrisTp, int nMove) {
    char szAryTemp[4][4] = { 0 };
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            szAryTemp[i][j] = TetrisTp[i * 4 + j];
        }
    }

    if (_kbhit()) {
        ch = _getch();
    }

    if (ch == 'd') {
        m_GlobalX = m_GlobalX + 1;

        //�ж��Ƿ���ǽ���߷���
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (szAryTemp[i][j] == 1) { //1
                    int nX = i + nMove;
                    int nY = j + 1 + m_GlobalX;
                    char szFlag = m_pszMap[nX * m_nMaxWidth + nY];
                    if (szFlag == 1) {
                        m_GlobalX = m_GlobalX - 1;
                    }
                }
            }
        }
    }

    if (ch == 'a') {
        m_GlobalX = m_GlobalX - 1;

        //�ж��Ƿ���ǽ���߷���
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (szAryTemp[i][j] == 1) { //1
                    int nX = i + nMove;
                    int nY = j + 1 + m_GlobalX;
                    char szFlag = m_pszMap[nX * m_nMaxWidth + nY];
                    if (szFlag == 1) {
                        m_GlobalX = m_GlobalX + 1;
                    }
                }
            }
        }
    }
}

//�����ƶ�������
void CTetris::MoveTetrisRL(char ch, char* TetrisTp, int nMove) {
    char szAryTemp[4][4] = { 0 };
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            szAryTemp[i][j] = TetrisTp[i * 4 + j];
        }
    }

    if (_kbhit()) {
        ch = _getch();
    }

    if (ch == 'w') {
        RotateTetris((char*)TetrisTp, nMove);
    }

    if (ch == 'd') {
        m_GlobalX = m_GlobalX + 1;

        //�ж��Ƿ���ǽ���߷���
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (szAryTemp[i][j] == 1) { //1
                    int nX = i + nMove;
                    int nY = j + 1 + m_GlobalX;
                    char szFlag = m_pszMap[nX * m_nMaxWidth + nY];
                    if (szFlag == 1) {
                        m_GlobalX = m_GlobalX - 1;
                    }
                }
            }
        }
    }

    if (ch == 'a') {
        m_GlobalX = m_GlobalX - 1;

        //�ж��Ƿ���ǽ���߷���
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (szAryTemp[i][j] == 1) { //1
                    int nX = i + nMove;
                    int nY = j + 1 + m_GlobalX;
                    char szFlag = m_pszMap[nX * m_nMaxWidth + nY];
                    if (szFlag == 1) {
                        m_GlobalX = m_GlobalX + 1;
                    }
                }
            }
        }
    }
}

//��Ϸ�����ж�
void CTetris::GameOver() {
    int nCnt = 0;
    for (int i = 0; i < m_nMaxWidth; i++) {
        if (m_pszMap[i] == 1) {
            nCnt++;
        }
    }

    //�����⵽��һ�����ڴ��еġ�1������������2����֤�����
    if (nCnt > 2) {
        system("cls");
        printf("Game Over!");
        getch();
        exit(0);
    }
}

//����
void CTetris::DelLine(char* Map) {
    int nCnt = 0;
    char szAryTemp[21][12] = { 0 };
    char szStr[13] = "\x1\x1\x1\x1\x1\x1\x1\x1\x1\x1\x1\x1";
    char szTemp[13] = "";

    //����ͼ���ݴ�һά����ת���ɶ�ά����
    for (int i = 0; i < m_nMaxHeight; i++) {
        for (int j = 0; j < m_nMaxWidth; j++) {
            szAryTemp[i][j] = Map[i * m_nMaxWidth + j];
        }
    }

    for (int i = 0; i < m_nMaxHeight - 1; i++) {
        for (int j = 0; j < m_nMaxWidth; j++) {
            if (szAryTemp[i][j] == 1) {
                nCnt++;
            } else {
                nCnt--;
            }
        }
        if (nCnt == 12) {
            for (int k = i; k > 0; k--) {
                ::memcpy((char *)szAryTemp[k], (char *)szAryTemp[k - 1], m_nMaxWidth);
            }
            //���м���
            m_nScore++;
        }
        nCnt = 0;
    }

    ::memcpy(Map, (char *)szAryTemp, m_nMaxHeight * m_nMaxWidth);
}

//�Ҳ���ʾ
void CTetris::RightDraw() {
    //���ڵķ���
    char *maps = arys[m_nRandProc - 1];
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            MovePostion(17 + j, 8 + i);
            printf("  ");
        }
    }

    //ʹ��ʾ�ķ�����У����ڣ�
    int ci = 0;
    int cj = 0;
    int ti = 0;
    int tj = 0;
    bool bi = true;
    bool bj = true;

    for (int i = 0; i < 4; i++) {
        ci = 0;
        cj = 0;
        for (int j = 0; j < 4; j++) {
            if (maps[i * 4 + j] == 0 && bi) {
                ci++;
            } else {
                ci = 0;
                bi = false;
            }

            if (maps[j * 4 + i] == 0 && bj) {
                cj++;
            } else {
                cj = 0;
                bj = false;
            }
        }

        if (ci >= 4) {
            ti++;
            ci = 0;
        }

        if (cj >= 4) {
            tj++;
            cj = 0;
        }
    }

    for (int i = ti,y = 0; i < 4; i++,y++) {
        for (int j = tj,x = 0; j < 4; j++,x++) {
            if (maps[i * 4 + j] == 1) {
                MovePostion(17 + x, 8 + y);
                printf("��");
            }
        }
    }

    ci = 0;
    cj = 0;
    ti = 0;
    tj = 0;
    bi = true;
    bj = true;

    //��һ������
    //char *mapsNest = new char[4 * 4] { 0 };
    if (bFlag == false) {
        memcpy(mapsNest, arys[m_nRandNext - 1], 4 * 4);
        bFlag = true;
    }

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            MovePostion(17 + j, 16 + i);
            printf("  ");
        }
    }

    //ʹ������У���һ����
    for (int i = 0; i < 4; i++) {
        ci = 0;
        cj = 0;
        for (int j = 0; j < 4; j++) {
            if (mapsNest[i * 4 + j] == 0 && bi) {
                ci++;
            }
            else {
                ci = 0;
                bi = false;
            }

            if (mapsNest[j * 4 + i] == 0 && bj) {
                cj++;
            }
            else {
                cj = 0;
                bj = false;
            }
        }

        if (ci >= 4) {
            ti++;
            ci = 0;
        }

        if (cj >= 4) {
            tj++;
            cj = 0;
        }
    }

    for (int i = ti, y = 0; i < 4; i++, y++) {
        for (int j = tj, x = 0; j < 4; j++, x++) {
            if (mapsNest[i * 4 + j] == 1) {
                MovePostion(17 + x, 16 + y);
                printf("��");
            }
        }
    }

    if (bFlag == false && mapsNest != nullptr) {
        delete[] mapsNest;
    }
}