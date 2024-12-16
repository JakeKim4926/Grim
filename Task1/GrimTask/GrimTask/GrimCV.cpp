#include "pch.h"
#include "GrimCV.h"


C_GrimCV::C_GrimCV()
{
    m_nRadius = 0;
}

C_GrimCV::~C_GrimCV()
{
}


BOOL C_GrimCV::DrawCircle(unsigned char* pucImg, int nPitch, int nImageWidth, int nImageHeight)
{
	srand(GetTickCount());

    int nX = m_sCoordinate.m_nX1;
    int nY = m_sCoordinate.m_nY1;
    int nRadius;

    // get circle
    do {
        nRadius = rand() % (std::min(nImageWidth, nImageHeight) / 2);
    } while (nX - nRadius < 0 || nX + nRadius >= nImageWidth ||
                nY - nRadius < 0 || nY + nRadius >= nImageHeight);

    m_nRadius = nRadius;

    // draw circle
    for (int y = 0; y < nImageHeight; y++) {
        for (int x = 0; x < nImageWidth; x++) {
            if ((x - nX) * (x - nX) + (y - nY) * (y - nY) <= nRadius * nRadius) {
                pucImg[y * nPitch + x] = COLOR_WHITE;
            }
        }
    }

    return TRUE;
}

BOOL C_GrimCV::Action(unsigned char* pucImg, int nPitch, int nImageWidth, int nImageHeight)
{
    bool bDown = false;
    bool bRight = false;
    bool bXEqual = false;
    bool bYEqual = false;

    if (m_sCoordinate.m_nX1 < m_sCoordinate.m_nX2)    bRight = true;
    if (m_sCoordinate.m_nY1 < m_sCoordinate.m_nY2)    bDown = true;
    if (m_sCoordinate.m_nX1 == m_sCoordinate.m_nX2)   bXEqual = true;
    if (m_sCoordinate.m_nY1 == m_sCoordinate.m_nY2)   bYEqual = true;
    
    BOOL bMoveX = TRUE;
    BOOL bMoveY = TRUE;

    if (!bXEqual) {
        if (!bRight)  bMoveX = ShiftImageLeft();
        else          bMoveX = ShiftImageRight(nImageWidth);
    }
    
    if (!bYEqual) {
        if (!bDown)  bMoveY = ShiftImageUp();
        else         bMoveY = ShiftImageDown(nImageHeight);
    }

    int nX = m_sCoordinate.m_nX1;
    int nY = m_sCoordinate.m_nY1;

    // draw circle
    for (int y = 0; y < nImageHeight; y++) {
        for (int x = 0; x < nImageWidth; x++) {
            if ((x - nX) * (x - nX) + (y - nY) * (y - nY) <= m_nRadius * m_nRadius) {
                pucImg[y * nPitch + x] = COLOR_WHITE;
            } else {
                pucImg[y * nPitch + x] = COLOR_GRAY;
            }
        }
    }

    //if (!bMoveX)    AfxMessageBox(_T("범위를 초과하였거나 목표 X 좌표에 도달하였습니다"));
    //if (!bMoveY)    AfxMessageBox(_T("범위를 초과하였거나 목표 Y 좌표에 도달하였습니다"));

    if (!bMoveX && !bMoveY)
        return FALSE;

    return TRUE;
}

BOOL C_GrimCV::OpenImage()
{
	return 0;
}

BOOL C_GrimCV::DetectCircle()
{
	return 0;
}

BOOL C_GrimCV::ShiftImageUp()
{
    if (m_sCoordinate.m_nY1 - MOVE_VALUE <= m_sCoordinate.m_nY2) {
        m_sCoordinate.m_nY1 = m_sCoordinate.m_nY2;
        return FALSE;
    } else {
        if (m_sCoordinate.m_nY1 - MOVE_VALUE - m_nRadius < 0) {
            m_sCoordinate.m_nY1 = m_nRadius;
            return FALSE;
        } else {
            m_sCoordinate.m_nY1 -= MOVE_VALUE;
        }

    }

    return TRUE;
}

BOOL C_GrimCV::ShiftImageDown(int nHeight)
{
    if (m_sCoordinate.m_nY1 + MOVE_VALUE >= m_sCoordinate.m_nY2) {
        m_sCoordinate.m_nY1 = m_sCoordinate.m_nY2;
        return FALSE;
    } else {
        if (m_sCoordinate.m_nY1 + MOVE_VALUE + m_nRadius >= nHeight) {
            m_sCoordinate.m_nY1 = nHeight - m_nRadius - 1;
            return FALSE;
        }
        else {
            m_sCoordinate.m_nY1 += MOVE_VALUE;
        }

    }

    return TRUE;
}

BOOL C_GrimCV::ShiftImageLeft()
{
    if (m_sCoordinate.m_nX1 - MOVE_VALUE <= m_sCoordinate.m_nX2) {
        m_sCoordinate.m_nX1 = m_sCoordinate.m_nX2;
        return FALSE;
    } else {
        if (m_sCoordinate.m_nX1 - MOVE_VALUE - m_nRadius < 0) {
            m_sCoordinate.m_nX1 = m_nRadius;
            return FALSE;
        } else {
            m_sCoordinate.m_nX1 -= MOVE_VALUE;
        }

    }

    return TRUE;
}

BOOL C_GrimCV::ShiftImageRight(int nWidth)
{
    if (m_sCoordinate.m_nX1 + MOVE_VALUE >= m_sCoordinate.m_nX2) {
        m_sCoordinate.m_nX1 = m_sCoordinate.m_nX2;
        return FALSE;
    } else {
        if (m_sCoordinate.m_nX1 + MOVE_VALUE + m_nRadius >= nWidth) {
            m_sCoordinate.m_nX1 = nWidth - m_nRadius - 1;
            return FALSE;
        }
        else {
            m_sCoordinate.m_nX1 += MOVE_VALUE;
        }

    }

    return TRUE;
}

void C_GrimCV::setCoordinate(int nX1, int nY1, int nX2, int nY2)
{
    m_sCoordinate.setCoordinate(nX1, nY1, nX2, nY2);
}

S_Coordinate C_GrimCV::getCoordinate()
{
    return m_sCoordinate;
}

int C_GrimCV::getRadius()
{
    return m_nRadius;
}
