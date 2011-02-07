#include "Maps/Structure.h"

Structure::Structure(int imagesheetID, int imagesheetX, int imagesheetY, int posX, int posY)
{
    m_iImagesheetID = imagesheetID;
    m_iImagesheetX = imagesheetX;
    m_iImagesheetY = imagesheetY;
    m_iPosX = posX;
    m_iPosY = posY;
}

Structure::~Structure()
{
    //dtor
}

/** Access m_iPosX
         * \return The current value of m_iPosX
         */
int Structure::GetiPosX()
{
    return m_iPosX;
}
/** Set m_iPosX
 * \param val New value to set
 */
void Structure::SetiPosX(int val)
{
    m_iPosX = val;
}
/** Access m_iPosY
 * \return The current value of m_iPosY
 */
int Structure::GetiPosY()
{
    return m_iPosY;
}
/** Set m_iPosY
 * \param val New value to set
 */
void Structure::SetiPosY(int val)
{
    m_iPosY = val;
}
/** Access m_iImagesheetID
 * \return The current value of m_iImagesheetID
 */
int Structure::GetiImagesheetID()
{
    return m_iImagesheetID;
}
/** Set m_iImagesheetID
 * \param val New value to set
 */
void Structure::SetiImagesheetID(int val)
{
    m_iImagesheetID = val;
}
/** Access m_iImagesheetX
 * \return The current value of m_iImagesheetX
 */
int Structure::GetiImagesheetX()
{
    return m_iImagesheetX;
}
/** Set m_iImagesheetX
 * \param val New value to set
 */
void Structure::SetiImagesheetX(int val)
{
    m_iImagesheetX = val;
}
/** Access m_iImagesheetY
 * \return The current value of m_iImagesheetY
 */
int Structure::GetiImagesheetY()
{
    return m_iImagesheetY;
}
/** Set m_iImagesheetY
 * \param val New value to set
 */
void Structure::SetiImagesheetY(int val)
{
    m_iImagesheetY = val;
}
