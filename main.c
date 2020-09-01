
#include <mlx.h>
#include <stdlib.h>
#include <math.h>
double InnerProduct(double *a, double *b)
{
    return (a[0] * b[0] + a[1] * b[1] + a[2] * b[2]);
}

int main()
{
    int width = 500;
    int height = 500;
    double PL[3] = {0, 800, -600.0};
    double Pv[3] = {width/2, height/2, -600.0}; //position of camera
    double Pc[3] = {width/2, height/2, 600.6}; //the center of camera
    double R = 400.5;
    double P[3]; //intersection of sphere and sight
    double n[3]; // normal vector of intersection
    double v[3]; //sight vector
    double vL[3]; //ray vector
    double t; // the solution of vector equation
    double cosA;
    double cosr; 
    double vR[3]; // vector of reflected ray
    double Pvc[3];
    double ld;
    void *mlx;
    void *mlx_win;
    mlx = mlx_init();
    mlx_win = mlx_new_window(mlx,width,height,"42madrid");
    int i, j,k;

    i = 0;
    double A,B,C,D;
    while(i < width)// i ,j means each pixel
    {
        j = 0;
        while (j < height)
        {
            v[0] = i - Pv[0];
            v[1] = j - Pv[1];
            v[2] = 0 - Pv[2];
            k = 0;
            while (k < 3)
            {
                Pvc[k] = Pv[k] - Pc[k];
                k++;
            }
            A = InnerProduct(v, v);
            B = InnerProduct(Pvc, v);
            C = InnerProduct(Pvc, Pvc) - R * R;
            D = (B * B) - (A * C);
            if (D >= 0) //sight hit the sphere
            {
                t = (- B - sqrt(D))/A;
                k = 0;
                while (k < 3)
                {
                    P[k] = Pv[k] + v[k]*t;//get intersection points
                    n[k] = P[k] - Pc[k];//normal vector on intersection points
                    vL[k] = P[k] - PL[k];//ray vector
                    k++;
                }
                cosA = -InnerProduct(vL, n) / sqrt(InnerProduct(vL, vL) * InnerProduct(n, n));
                if (cosA >= 0)
                {
                    mlx_pixel_put(mlx,mlx_win,i,j, 0xff0000 * cos(cosA));
                }
                else
                {
                    mlx_pixel_put(mlx,mlx_win,i,j, 0);
                }
            }
            else
            {
                mlx_pixel_put(mlx,mlx_win,i,j,127);
            }
            j++;
        }
        i++;
    }
    mlx_loop(mlx);
}