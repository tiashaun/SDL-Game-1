#ifndef STRUCTURE_H
#define STRUCTURE_H


class Structure
{
    public:
        /** Default constructor */
        Structure(int imagesheetID, int imagesheetX, int imagesheetY, int posX, int posY);
        /** Default destructor */
        virtual ~Structure();

        int GetiPosX();
        void SetiPosX(int val);

        int GetiPosY();
        void SetiPosY(int val);

        int GetiImagesheetID();
        void SetiImagesheetID(int val);

        int GetiImagesheetX();
        void SetiImagesheetX(int val);

        int GetiImagesheetY();
        void SetiImagesheetY(int val);
    protected:
    private:
        int m_iPosX; //!< Member variable "m_iPosX"
        int m_iPosY; //!< Member variable "m_iPosY"
        int m_iImagesheetID; //!< Member variable "m_iImagesheetID"
        int m_iImagesheetX; //!< Member variable "m_iImagesheetX"
        int m_iImagesheetY; //!< Member variable "m_iImagesheetY"
};

#endif // STRUCTURE_H
