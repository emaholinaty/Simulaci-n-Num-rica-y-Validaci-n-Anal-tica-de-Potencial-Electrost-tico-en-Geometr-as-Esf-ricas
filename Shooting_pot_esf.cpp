#include <iostream>
#include <cmath>
#include <iomanip>
#include <fstream>
using namespace std;

double f1 (double t, double y[]);
double f2 (double t, double y[]);
double (*Af[]) (double t, double y[])={f1, f2}; // array de punteros a funciones 
void RK4(double (*Af[])(double t, double y[]), double t0, double tf, double h, double y[], double yf, double &E, int flag, int n);
double solucion (double r);
int main()
{   
int n=2;// numero de ecuaciones de primer orden acopladas
double y[n];
double t0=5, tf=10, y0=110, yf=0, h=0.05, tolerancia=1e-8; // t0 -> R1=5cm, tf -> R2=10cm
double p0, p1, p2, E0, E1; // pendientes y errores, metodo de la secante
int flag=0;

cout << setprecision(15);
// Primer intento
p0=(yf-y0)/(tf-t0);// estimacion inicial para la pendiente en el extremo izquierdo
y[0]=y0; 
y[1]=p0;  // condiciones iniciales
RK4(Af,t0,tf,h,y,yf,E0,flag,n); // llamada a la funcion RK4
cout << "Pendiente =" << p0 << "  Error = " << E0 << endl;

// segundo intento 
if (p0*E0 < 0) { p1=p0*2.0;}
else { p1=p0/2.0;} // estimacion inicial para la pendiente en el extremo izquierdo
y[0]=y0; // condicion inicial en el extremo izquierdo
y[1]=p1; // condicion inicial para la pendiente
RK4(Af,t0,tf,h,y,yf,E1,flag,n); // llamada a la funcion RK4
cout << "Pendiente =" << p1 << "  Error = " << E1 << endl;

do 
{
p2=p1-E1*(p1-p0)/(E1-E0);
y[0]=y0; // condicion inicial en el extremo izquierdo
y[1]=p2; // condicion inicial para la pendiente
p0=p1;
p1=p2;
E0=E1;
RK4(Af,t0,tf,h,y,yf,E1,flag,n); // llamada a la funcion RK4
cout << "Pendiente =" << p2 << "  Error = " << E1 << endl;
} while (fabs(E1) > tolerancia); 
flag=1; // activamos flag=1 para grabar los datos
y[0]=y0; // condicion inicial en el extremo izquierdo
y[1]=p2; // condicion inicial para la pendiente
RK4(Af,t0,tf,h,y,yf,E1,flag,n); // llamada final a la funcion RK4
cout << " Grabamos la solucion final" << endl;
// al ser flag=1, se imprimen los resultados y se graba el fichero

// grabamos la solucion exacta en un fichero
  ofstream fsalida2("sexacta.dat", ios::out);
  if (!fsalida2)
    {cout << "No se puede abrir el archivo";
     system("PAUSE"); }
 for (double r=t0; r<tf+h; r=r+h)
 { fsalida2 << r << "    " << solucion(r) << endl; }
 
system("PAUSE");
return 0;
}

double f1(double t, double y[])
// t -> r
// y[0] = u, y[1]= du/dr
// f1=dy[0]/dt=y[1]
// y[0](r=5)=110
// f2=dy[1]/dr=-(2/r)*y[1]
// y[1] (r=10)=0 , segunda condicion de contorno
{ return y[1];}


double f2(double t, double y[])
// t -> r
// y[0] = u, y[1]= du/dr
// f1=dy[0]/dt=y[1]
// y[0](r=5)=110
// f2=dy[1]/dr=-(2/r)*y[1]
// y[1] (r=10)=0 , segunda condicion de contorno
{ return (-2*y[1]/t); }

void RK4(double (*Af[])(double t, double y[]), double t0, double tf, double h, double y[], double yf, double &E, int flag, int n)
{
  int j;
  double t=t0, k1[n], k2[n], k3[n], k4[n], yy[n];
  // Hay que abrir el flujo en la funcion
  ofstream fsalida("potencial.dat", ios::out);
  if (!fsalida)
    {cout << "No se puede abrir el archivo";
     system("PAUSE"); }
  if (flag==1) {
  cout << t;
  fsalida << t;
  for (j=0; j<n; j++) 
  { cout << "   " << y[j];
    fsalida << "   " << y[j]; }
  cout << endl;
  fsalida << endl; }
   do {
    for (j=0; j<n; j++)    { k1[j]=h*Af[j](t,y);}
    for (j=0; j<n; j++)    { yy[j]=y[j]+0.5*k1[j];}
    for (j=0; j<n; j++)    { k2[j]=h*Af[j](t+0.5*h,yy);}
    for (j=0; j<n; j++)    { yy[j]=y[j]+0.5*k2[j];}
    for (j=0; j<n; j++)    { k3[j]=h*Af[j](t+0.5*h,yy); }
    for (j=0; j<n; j++)    { yy[j]=y[j]+k3[j];}
    for (j=0; j<n; j++)    { k4[j]=h*Af[j](t+h,yy);}
    // nueva aproximación
    for (j=0; j<n; j++) 
    { y[j]=y[j] + (1.0/6.0)*(k1[j] + 2.0*k2[j] + 2.0*k3[j] + k4[j]);}
    t=t+h;
    if (flag==1) {
    cout << t;
    fsalida << t;
    for (j=0; j<n; j++) 
    { cout << "   " << y[j];
      fsalida << "   " << y[j];}
    cout << endl;
    fsalida << endl;}
    } while (t<=tf); 
    E=y[0]-yf;
    fsalida.close();
}

double solucion (double r)
{  return ((110.0*5.0/r)*(10.0-r)/(10.0-5.0));}
