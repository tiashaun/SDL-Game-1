#ifndef TILE_H
#define TILE_H


class Tile
{
    public:
        /** Default constructor */
        Tile();
        /** Default destructor */
        virtual ~Tile();
        /** Access m_iTileX
         * \return The current value of m_iTileX
         */
        int GetTileX() { return m_iTileX; }
        /** Set m_iTileX
         * \param val New value to set
         */
        void SetTileX(int val) { m_iTileX = val; }
        /** Access m_iTileY
         * \return The current value of m_iTileY
         */
        int GetTileY() { return m_iTileY; }
        /** Set m_iTileY
         * \param val New value to set
         */
        void SetTileY(int val) { m_iTileY = val; }
        /** Access m_iPosX
         * \return The current value of m_iPosX
         */
        int GetPosX() { return m_iPosX; }
        /** Set m_iPosX
         * \param val New value to set
         */
        void SetPosX(int val) { m_iPosX = val; }
        /** Access m_iPosY
         * \return The current value of m_iPosY
         */
        int GetPosY() { return m_iPosY; }
        /** Set m_iPosY
         * \param val New value to set
         */
        void SetPosY(int val) { m_iPosY = val; }
    protected:
    private:
        int m_iTileX; //!< Member variable "m_iTileX"
        int m_iTileY; //!< Member variable "m_iTileY"
        int m_iPosX; //!< Member variable "m_iPosX"
        int m_iPosY; //!< Member variable "m_iPosY"
};

#endif // TILE_H
