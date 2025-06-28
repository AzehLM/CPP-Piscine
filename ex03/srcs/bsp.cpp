#include "Point.hpp"

bool bsp( Point const a, Point const b, Point const c, Point const point)
{
    // Calcul des différences nécessaires pour les coordonnées barycentriques
    Fixed s1 = c.getY() - a.getY();  // C.y - A.y
    Fixed s2 = c.getX() - a.getX();  // C.x - A.x
    Fixed s3 = b.getY() - a.getY();  // B.y - A.y
    Fixed s4 = point.getY() - a.getY();  // P.y - A.y

    Fixed denominator;

    // Calcul du dénominateur pour w1
	denominator = s3 * s2 - (b.getX() - a.getX()) * s1;

	// Vérifier si le triangle est dégénéré (aire nulle)
    if (denominator == Fixed(0))
    {
        // Triangle dégénéré - les trois points sont colinéaires
        return false;
    }

    // Calcul de w1 (première coordonnée barycentrique)
    Fixed w1 = (a.getX() * s1 + s4 * s2 - point.getX() * s1) / denominator;

    // Calcul de w2 (deuxième coordonnée barycentrique)
    Fixed w2;
    if (s1 == Fixed(0))
    {
        // Cas spécial : C.y == A.y (ligne horizontale)
        // Utiliser une formule alternative
        if (s2 == Fixed(0))
        {
            // A et C sont le même point - triangle dégénéré
            return false;
        }
        w2 = (point.getX() - a.getX() - w1 * (b.getX() - a.getX())) / s2;
    }
    else
        w2 = (s4 - w1 * s3) / s1;

    return (w1 > Fixed(0) && w2 > Fixed(0) && (w1 + w2) < Fixed(1));
}
