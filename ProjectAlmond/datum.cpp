#include "datum.h"

Datum::Datum()
    :_dan(-1),_mesec(-1),_godina(-1)
{}

/**
    Konstruktor preko stringa.
    Racuna se da se u unosu preko GUI-a vrsi provera formata datuma!
    Ukoliko je uneti string prazan, datum se inicijalizuje vrednoscu koja ukazuje na njegovu "nepoznatost"
    **/
Datum::Datum(const std::string &s)
{
    if(s.empty()){PostaviNepoznat();}
    else{

        if (!KorektanDatum(s))
            throw "Nije korektan datum dat stringom, formiranje datuma neuspesno!";

        /* s = dd.mm.gggg. ili mm.gggg. ili gggg. */
        int dan,mesec,godina;
        if (s.size() == 11)
        {
            dan = atoi( s.substr(0, 2).c_str() );
            mesec = atoi( s.substr(3, 2).c_str() );
            godina = atoi( s.substr(6, 4).c_str() );
        }

        else if (s.size() == 8)
        {
            dan = 0;
            mesec = atoi( s.substr(0, 2).c_str() );
            godina = atoi( s.substr(3, 4).c_str() );
        }

        else    if (s.size() == 5)
        {
            dan = 0;
            mesec = 0;
            godina = atoi( s.substr(0, 4).c_str() );
        }
        else
            throw "Inicjalizacija datuma nije uspela!";
        _dan=dan;
        _mesec=mesec;
        _godina=godina;
    }
}
bool Datum::NepoznatDatum()const
{
    return _dan==-1&&_mesec==-1&&_godina==-1;
}


bool Datum::PrestupnaGodina(int godina)
{
    return (godina % 4 == 0 && godina % 100 != 0)
            || godina % 400 == 0;
}


bool Datum::KorektanDatum(const std::string & s)
{
    int dan, mesec, godina;

    if (s.size() == 11)
    {
        dan = atoi( s.substr(0, 2).c_str() );
        mesec = atoi( s.substr(3, 2).c_str() );
        godina = atoi( s.substr(6, 4).c_str() );
    }

    else if (s.size() == 8)
    {
        dan = 0;
        mesec = atoi( s.substr(0, 2).c_str() );
        godina = atoi( s.substr(3, 4).c_str() );
    }

    else    if (s.size() == 5)
    {
        dan = 0;
        mesec = 0;
        godina = atoi( s.substr(0, 4).c_str() );
    }
    else
        return false;


    if (dan < 0 || mesec < 0 || godina < 0)
        return false;

    switch (mesec)
    {
    case 0:
        return dan == 0;
    case 1:
    case 3:
    case 5:
    case 7:
    case 8:
    case 10:
    case 12:
        return dan <= 31;
    case 4:
    case 6:
    case 9:
    case 11:
        return dan <= 30;
    case 2:
        if (PrestupnaGodina(godina))
            return dan <= 29;
        else
            return dan <= 28;
    default:
        return false;
    }


}

bool Datum::Rodjendan(const Datum & danas) const
{
    if (_mesec == 0 || _dan == 0)
        return false;

    if (_mesec == danas._mesec && _dan == danas._dan)
        return true;
    if (_mesec == 2 && _dan == 29
            && !PrestupnaGodina(danas._godina)
            && danas._dan == 1 && danas._mesec == 3)
        return true;
    return false;
}


std::ostream & operator<<(std::ostream & ostr, const Datum & d)
{
    if (d.NepoznatDatum())
    {
        ostr << "--.--.----.";
        return ostr;
    }

    if (d._dan > 0)
    {
        //if (d._dan < 10)
            //ostr << 0;
        ostr << std::setfill('0') << std::setw(2) << d._dan << '.';
    }
    if (d._mesec > 0)
    {
        //if (d._mesec < 10)
        //    ostr << 0;
        ostr << std::setfill('0') << std::setw(2) << d._mesec << '.';
    }
    ostr << d._godina << '.';
    return ostr;
}

void Datum::PostaviNepoznat()
{
    _dan=-1;
    _mesec=-1;
    _godina=-1;
}

bool Datum::operator <(const Datum& datum) const
{
    if (this->_godina < datum._godina)
        return true;
    if (this->_godina > datum._godina)
        return false;
    if (this->_mesec < datum._mesec)
        return true;
    if (this->_mesec > datum._mesec)
        return false;
    if (this->_dan > datum._mesec)
        return true;
    return false;
}

bool Datum::operator >(const Datum& datum) const
{
    return datum < *this;
}

bool Datum::operator ==(const Datum& datum) const
{
    return datum._godina == this->_godina &&
            datum._mesec == this->_mesec &&
            datum._dan == this->_dan;
}

bool Datum::operator !=(const Datum& datum) const
{
    return !(*this == datum);
}

bool Datum::operator >=(const Datum& datum) const
{
    return !(*this < datum);
}

bool Datum::operator <=(const Datum& datum) const
{
    return !(*this > datum);
}
