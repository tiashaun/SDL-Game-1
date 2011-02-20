#ifndef TILESET_H
#define TILESET_H

#include <string>

class Tileset
{
    public:
        /** Default constructor */
        Tileset();
        /** Default destructor */
        virtual ~Tileset();
        /** Access m_sName
         * \return The current value of m_sName
         */
        std::string GetName() { return m_sName; }
        /** Set m_sName
         * \param val New value to set
         */
        void SetName(std::string val) { m_sName = val; }
        /** Access m_sImage
         * \return The current value of m_sImage
         */
        std::string GetImage() { return m_sImage; }
        /** Set m_sImage
         * \param val New value to set
         */
        void SetImage(std::string val) { m_sImage = val; }
        /** Access m_iTileWidth
         * \return The current value of m_iTileWidth
         */
        int Getm_iTileWidth() { return m_iTileWidth; }
        /** Set m_iTileWidth
         * \param val New value to set
         */
        void Setm_iTileWidth(int val) { m_iTileWidth = val; }
        /** Access m_iTileHeight
         * \return The current value of m_iTileHeight
         */
        int Getm_iTileHeight() { return m_iTileHeight; }
        /** Set m_iTileHeight
         * \param val New value to set
         */
        void Setm_iTileHeight(int val) { m_iTileHeight = val; }
    protected:
    private:
        std::string m_sName; //!< Member variable "m_sName"
        std::string m_sImage; //!< Member variable "m_sImage"
        int m_iTileWidth; //!< Member variable "m_iTileWidth"
        int m_iTileHeight; //!< Member variable "m_iTileHeight"
};

#endif // TILESET_H
