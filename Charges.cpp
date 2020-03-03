#include "Complex.h"
#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <time.h> 
#include <fstream>

using namespace std;


main()
{
    double x1,x2,y1,y2;
    x1 = 0.0;
    y1 = 0.0;
    x2 = 10.0;
    y2 = 0.01;
    double vx1,vx2,vy1,vy2;
    vx1 = 7.0;
    vy1 = 0.0;
    vx2 = -7.0;
    vy2 = 0.0;
    double t;
    double inter = 0.00001;
    
    double c = 20; // Speed of Light!!
    
    ofstream r1,r2,v1,v2,e,rel;
    r1.open ("Position_Charge_1.dat");
    r2.open ("Position_Charge_2.dat");
    
    rel.open("Relative_Position_Charges.dat");
    
    v1.open ("Velocity_Charge_1.dat");
    v2.open ("Velocity_Charge_2.dat");
    
    e.open ("Energy.dat");
    
    int cont = 0;
    
    for (t=0.0;t<1.6;t+=inter)
    {
        
	double gamma = ( 1.0 ) - ( ( vx1 * vx2 ) + ( vy1 * vy2 ) ) / ( c * c ) ;
        double dist = sqrt( ( ( x1 - x2 ) * ( x1 - x2 ) ) + ( ( y1 - y2 ) * ( y1 - y2 ) ) );
        double energy = 0.5*(vx1*vx1 + vx2*vx2 + vy1*vy1 + vy2*vy2) + ( log(dist) * gamma  );
        
	
        if (!(cont%100)) 
        {
        
        r1 << x1 << " " << y1 << "\n";
        r2 << x2 << " " << y2 << "\n";
        rel << x2 - x1 << " " << y2 - y1 << "\n";
        
        v1 << t << " " << sqrt((vx1*vx1)+(vy1*vy1)) << "\n";
        v2 << t << " " << sqrt((vx2*vx2)+(vy2*vy2)) << "\n";
        
        e << t << " " << energy << "\n";
        
        }
        
        
        //double gamma = ( 1.0 ) - ( ( vx1 * vx2 ) + ( vy1 * vy2 ) ) / ( c * c ) ;
	//double gamma1 = 1.0 / sqrt(( 1.0 ) - ( ( vx1 * vx1 ) + ( vy1 * vy1 ) ) / ( c * c )) ;
	//double gamma2 = 1.0 / sqrt(( 1.0 ) - ( ( vx2 * vx2 ) + ( vy2 * vy2 ) ) / ( c * c )) ;
	double dot1 = ( vx1 * ( x1 - x2 ) ) + ( vy1 * ( y1 - y2 ) );
        double dot2 = ( vx2 * ( x2 - x1 ) ) + ( vy2 * ( y2 - y1 ) );
        double prefactor = ( inter ) / ( dist * dist );
	
        // Only Electric Interaction
        /*
        vx1 = vx1 + ((inter) * ( x2 - x1 ) / (dist * dist ));
        vy1 = vy1 + ((inter) * ( y2 - y1 ) / (dist * dist ));  
        vx2 = vx2 + ((inter) * ( x1 - x2 ) / (dist * dist ));
        vy2 = vy2 + ((inter) * ( y1 - y2 ) / (dist * dist ));  
        */
            
        // Both Magnetic and Electric Interaction
        
        vx1 = vx1 + ( ( prefactor ) * ( ( ( x2 - x1 ) * gamma ) + ( ( vx2 * dot1 ) / ( c * c ) ) ) );
        vy1 = vy1 + ( ( prefactor ) * ( ( ( y2 - y1 ) * gamma ) + ( ( vy2 * dot1 ) / ( c * c ) ) ) );
        vx2 = vx2 + ( ( prefactor ) * ( ( ( x1 - x2 ) * gamma ) + ( ( vx1 * dot2 ) / ( c * c ) ) ) );
        vy2 = vy2 + ( ( prefactor ) * ( ( ( y1 - y2 ) * gamma ) + ( ( vy1 * dot2 ) / ( c * c ) ) ) );
        
        
	
	// Position Update 
	
        x1 = x1 + ( ( inter ) * vx1 );
        x2 = x2 + ( ( inter ) * vx2 );
        y1 = y1 + ( ( inter ) * vy1 );
        y2 = y2 + ( ( inter ) * vy2 );
        
        cont++;
        
        
        
    }
    
    r1.close();
    r2.close();
    v1.close();
    v2.close();
    e.close();
     
    
    
    
    
    
    
}




