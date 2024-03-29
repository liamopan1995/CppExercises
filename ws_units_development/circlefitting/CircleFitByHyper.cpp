
#include "circle.h"
#include "data.h"
#include "Utilities.cpp"
#include <Eigen/Dense>
Circle CircleFitByHyper (Data& data)
/*  
      Circle fit to a given set of data points (in 2D)
      
      This is an algebraic fit based on the journal article
     
      A. Al-Sharadqah and N. Chernov, "Error analysis for circle fitting algorithms",
      Electronic Journal of Statistics, Vol. 3, pages 886-911, (2009)
      
      It is an algebraic circle fit with "hyperaccuracy" (with zero essential bias). 
      The term "hyperaccuracy" first appeared in papers by Kenichi Kanatani around 2006
		
      Input:  data     - the class of data (contains the given points):
		
	      data.n   - the number of data points
	      data.X[] - the array of X-coordinates
	      data.Y[] - the array of Y-coordinates
     
     Output:	       
               circle - parameters of the fitting circle:
		        
	       circle.Px - the X-coordinate of the center of the fitting circle
	       circle.Py - the Y-coordinate of the center of the fitting circle
 	       circle.r - the radius of the fitting circle
 	       circle.s - the root mean square error (the estimate of sigma)
 	       circle.j - the total number of iterations

     This method combines the Pratt and Taubin fits to eliminate the essential bias.
        
     It works well whether data points are sampled along an entire circle or
     along a small arc. 
     
     Its statistical accuracy is theoretically higher than that of the Pratt fit 
     and Taubin fit, but practically they all return almost identical circles
     (unlike the Kasa fit that may be grossly inaccurate). 
     
     It provides a very good initial guess for a subsequent geometric fit. 
     
       Nikolai Chernov  (September 2012)

*/
{
    int i,iter,IterMAX=99;

    reals Xi,Yi,Zi;
    reals Mz,Mxy,Mxx,Myy,Mxz,Myz,Mzz,Cov_xy,Var_z;
    reals A0,A1,A2,A22;
    reals Dy,xnew,x,ynew,y;
    reals DET,Xcenter,Ycenter;
    
    Circle circle;

    data.means();   // Compute x- and y- sample means (via a function in the class "data") 

//     computing moments 

    Mxx=Myy=Mxy=Mxz=Myz=Mzz=0.;

    for (i=0; i<data.n; i++)
    {
        Xi = data.X[i] - data.meanX;   //  centered x-coordinates
        Yi = data.Y[i] - data.meanY;   //  centered y-coordinates
        Zi = Xi*Xi + Yi*Yi;

        Mxy += Xi*Yi;
        Mxx += Xi*Xi;
        Myy += Yi*Yi;
        Mxz += Xi*Zi;
        Myz += Yi*Zi;
        Mzz += Zi*Zi;
    }
    Mxx /= data.n;
    Myy /= data.n;
    Mxy /= data.n;
    Mxz /= data.n;
    Myz /= data.n;
    Mzz /= data.n;

//    computing the coefficients of the characteristic polynomial

    Mz = Mxx + Myy;
    Cov_xy = Mxx*Myy - Mxy*Mxy;
    Var_z = Mzz - Mz*Mz;

    A2 = Four*Cov_xy - Three*Mz*Mz - Mzz;
    A1 = Var_z*Mz + Four*Cov_xy*Mz - Mxz*Mxz - Myz*Myz;
    A0 = Mxz*(Mxz*Myy - Myz*Mxy) + Myz*(Myz*Mxx - Mxz*Mxy) - Var_z*Cov_xy;
    A22 = A2 + A2;

//    finding the root of the characteristic polynomial
//    using Newton's method starting at x=0  
//     (it is guaranteed to converge to the right root)

	for (x=0.,y=A0,iter=0; iter<IterMAX; iter++)  // usually, 4-6 iterations are enough
    {
        Dy = A1 + x*(A22 + 16.*x*x);
        xnew = x - y/Dy;
        if ((xnew == x)||(!isfinite(xnew))) break;
        ynew = A0 + xnew*(A1 + xnew*(A2 + Four*xnew*xnew));
        if (abs(ynew)>=abs(y))  break;
        x = xnew;  y = ynew;
    }

//    computing paramters of the fitting circle

    DET = x*x - x*Mz + Cov_xy;
    Xcenter = (Mxz*(Myy - x) - Myz*Mxy)/DET/Two;
    Ycenter = (Myz*(Mxx - x) - Mxz*Mxy)/DET/Two;

//       assembling the output

    circle.Px = Xcenter + data.meanX;
    circle.Py = Ycenter + data.meanY;
    circle.r = sqrt(Xcenter*Xcenter + Ycenter*Ycenter + Mz - x - x);
    circle.s = Sigma(data,circle);
    circle.i = 0;
    circle.j = iter;  //  return the number of iterations, too
    
    return circle;
}





Circle CircleFitByHyper_vectorized (Eigen::MatrixXf P)


{
    int i,iter,IterMAX=99;

    float Mz,Mxy,Mxx,Myy,Mxz,Myz,Mzz,Cov_xy,Var_z;
    float A0,A1,A2,A22;
    float Dy,xnew,x,ynew,y;
    float DET,Xcenter,Ycenter;
    
    Circle circle;

    Eigen::VectorXf Xi(P.rows()) ;
    Eigen::VectorXf Yi(P.rows()) ;
    Eigen::VectorXf Zi(P.rows()) ;

    Eigen::Vector3f P_mean = P.colwise().mean();  // shape <3,1>

    //P.colwise() -= P_mean; wrong!
    P.rowwise() -= P_mean.transpose(); // Centerize along the row axis   <n,3 > - <3,1>.Transpose

    Xi = P.col(0);
    Yi = P.col(1);
    Zi = P.leftCols<2>().array().square().rowwise().sum();


    Mxy = Xi.dot(Yi) /P.rows();
    Mxx = Xi.dot(Xi) /P.rows();
    Myy = Yi.dot(Yi) /P.rows();
    Mxz = Xi.dot(Zi) /P.rows();
    Myz = Yi.dot(Zi) /P.rows();
    Mzz = Zi.dot(Zi) /P.rows();

//    computing the coefficients of the characteristic polynomial

    Mz = Mxx + Myy;
    Cov_xy = Mxx*Myy - Mxy*Mxy;
    Var_z = Mzz - Mz*Mz;

    A2 = Four*Cov_xy - Three*Mz*Mz - Mzz;
    A1 = Var_z*Mz + Four*Cov_xy*Mz - Mxz*Mxz - Myz*Myz;
    A0 = Mxz*(Mxz*Myy - Myz*Mxy) + Myz*(Myz*Mxx - Mxz*Mxy) - Var_z*Cov_xy;
    A22 = A2 + A2;

//    finding the root of the characteristic polynomial
//    using Newton's method starting at x=0  
//     (it is guaranteed to converge to the right root)

	for (x=0.,y=A0,iter=0; iter<IterMAX; iter++)  // usually, 4-6 iterations are enough
    {
        Dy = A1 + x*(A22 + 16.*x*x);
        xnew = x - y/Dy;
        if ((xnew == x)||(!isfinite(xnew))) break;
        ynew = A0 + xnew*(A1 + xnew*(A2 + Four*xnew*xnew));
        if (abs(ynew)>=abs(y))  break;
        x = xnew;  y = ynew;
    }

//    computing paramters of the fitting circle

    DET = x*x - x*Mz + Cov_xy;
    Xcenter = (Mxz*(Myy - x) - Myz*Mxy)/DET/Two;
    Ycenter = (Myz*(Mxx - x) - Mxz*Mxy)/DET/Two;

//       assembling the output

    circle.Px = Xcenter + P_mean(0);
    circle.Py = Ycenter + P_mean(1);
    circle.r = sqrt(Xcenter*Xcenter + Ycenter*Ycenter + Mz - x - x);
    // circle.s = Sigma(data,circle);
    // circle.i = 0;
    // circle.j = iter;  //  return the number of iterations, too
    
    return circle;
}
