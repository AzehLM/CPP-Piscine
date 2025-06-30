#include "Point.hpp"

bool bsp( Point const a, Point const b, Point const c, Point const point)
{
    /* Calcul des vecteurs */
    Fixed s1 = c.getY() - a.getY();
    Fixed s2 = c.getX() - a.getX();
    Fixed s3 = b.getY() - a.getY();
    Fixed s4 = point.getY() - a.getY();

    Fixed denominator;

    /* Calcul du dénominateur pour w1 -> si sa valeur est nulle on a un triangle dégénéré */
	denominator = s3 * s2 - (b.getX() - a.getX()) * s1;
    if (denominator == Fixed(0))
        return (false);

    /* Calcul de w1 (première coordonnée barycentrique) */
    Fixed w1 = (a.getX() * s1 + s4 * s2 - point.getX() * s1) / denominator;

    Fixed w2;
    if (s1 == Fixed(0))
    {
        if (s2 == Fixed(0))
            return (false);
        w2 = (point.getX() - a.getX() - w1 * (b.getX() - a.getX())) / s2;
    }
    else
        w2 = (s4 - w1 * s3) / s1;

    return (w1 > Fixed(0) && w2 > Fixed(0) && (w1 + w2) < Fixed(1));
}
