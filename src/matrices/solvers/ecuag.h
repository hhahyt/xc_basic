//----------------------------------------------------------------------------
//  xc_basic library; general purpose classes and functions.
//
//  Copyright (C)  Luis Claudio Pérez Tato
//
//  Este software es libre: usted puede redistribuirlo y/o modificarlo 
//  bajo los términos de la Licencia Pública General GNU publicada 
//  por la Fundación para el Software Libre, ya sea la versión 3 
//  de la Licencia, o (a su elección) cualquier versión posterior.
//
//  Este software se distribuye con la esperanza de que sea útil, pero 
//  SIN GARANTÍA ALGUNA; ni siquiera la garantía implícita 
//  MERCANTIL o de APTITUD PARA UN PROPÓSITO DETERMINADO. 
//  Consulte los detalles de la Licencia Pública General GNU para obtener 
//  una información más detallada. 
//
// Debería haber recibido una copia de la Licencia Pública General GNU 
// junto a este programa. 
// En caso contrario, consulte <http://www.gnu.org/licenses/>.
//----------------------------------------------------------------------------
//ecuag.h
//Procedimiento general para la soluciOn de un sistema de ecuaciones.

#ifndef ECUAG_H
#define ECUAG_H

#include "math.h"
#include "ZMatrix.h"
#include "matem.h"
#include "gj_aux.h"

template <class treal>
size_t pivote(const size_t &j)
  {
    size_t i,m= a.getNumberOfRows();
    treal rm,piv,r= 0;
    r=zero;piv=0;
    for(i=1;i<=m;i++)
      if (!In(fp,i))
        {
          rm= gj_abs(a(i,j));
          if(rm>r)
            {
              piv= i;
              r=rm;
            }
        }
    return piv;
  } //pivote

template <class treal>
void transformar(const size_t &l,const size_t &k)
  {
    size_t i,j;
    for(j=1;j<=n;j++)
      if( !In(cp,j) && (gj_abs(a(l,j))>zero) )
        {
          a(l,j)/=a(l,k);
          for(i=1;i<=m;i++)
            if(i!=l)
              a(i,j)-=a(i,k)*a(l,j);
        }
  }//transformar
template <class treal>
void resultados(void)
  {
    size_t i,j,l;
    holgura= n-1-rango;      (* holgura y variables libres *)
    for(i=1;i<=mmax;i++)
      for(j=1;j<=nmax;j++) x(i,j)=0.0;
    if(holgura>0)
      {
        i=0;
        for(j=1;j<=n-1;j++)
          if(!In(cp,j))
            {
              i++;
              libres[i]=j;
            }
      }
    for(j=1;j<= n-1;j++)         (* almacena solucion *)
      {
        l=pivot[j];i=1;
        if(In(cp,j)) x(1,j)= a(l,n);
        if(holgura>0)
          for(k=1;k<=n-1;k++)
            if(!In(cp,k))
              {
                i++;
                if(In(cp,j))
                  x(i,j)=-a[l,k];
                else
                  x(i,j)=1;
              }
      }
   }// resultados

template<class treal>
void resolver( const size_t &m,
               const szie_t &n,
               ZMatrix<treal> &a,
               int compatible)
  {
    size_t i,j,k,l,rmax,rango;
    //Dimensioning the matrix for the indices of the pivot.
    ZMatrix<treal>::size_type n= a.getNumberOfRows();
    ZMatrix<treal>::size_type *pivot= new ZMatrix<treal>::size_type[mmax];
    set_szt fp;
    set_szt cp;
    k=0;rango=0;         (* resolver *)
    if(m>n)
      rmax:=n;
    else
      rmax:=m;
    while( (rango<rmax) && (k<n) )
      {
        k++;
        l=pivote(k);
        if(l>0)
          {
            fp.insert(l);
            cp.insert(k);
            pivot[k]=l;
            rango++;
            if(k<n) transformar(l,k);
          }
      }
    compatible= !In(cp,n);
    if(compatible) resultados;
  }//resolver

template <class treal>
//! Pre-multiply by transpose.
void multrasp(void)
  {
    size_t i,j,k;
    for(i=1;i<=m;i++)
      for(j=1;j<=n;j++)
        {
          b(i,j)=0.0;
          for(k=1;k<=m;k++)
            b(i,j)+= a(k,i)*a(k,j);
        }
  }// multrasp

template <class treal>
treal errorcuad(void)
  {
    size_t i,j;
    treal s,ss;
    s:=0;
    for(i=1;i<=m;i++)
      {
        ss=a(i,n);
        for(j=1;j<=n-1;j++) ss-=a(i,j)*x(1,j);
        s+=sqr(ss);
      }
    return sqrt(s/m);
  }//errorcuad

template <class treal>
void ecuag(const size_t &m,
           const size_t &n,
           ZMatrix<treal> &a,
           ZMatrix<treal> &x,
           var libres:indices,
           int holgura,
           const treal &error,
           int &compatible)
// solucion general de un sistema de ecuaciones
//         m        = numero de ecuaciones
//         n        = numero de incognitas mas uno
//         a        = matrix of the coefficients
//                          termino independiente in column n
//         x        = solution matrix
//                        column 1 variables dependientes
//                               2 a holguras+1 independientes
//         libres   = indices de variables libres
//         holgura  = numero de variables libres
//           error  = si el sistema es incompatible,
//                             error cuadratico medio
  {
    int compa;
    ZMatrix<treal> b=a; //ecuag
    resolver(m,n,b,compatible);
    if(!compatible)
      {
        multrasp;
        resolver(n-1,n,b,compa);
        error=errorcuad;
      }
  }                  (* ecuag *)

template <class treal>
void salida(void)
  {
    size_t i,j,l;
    if(!compatible)
      {
        std::clog << " sistema incompatible " << std::endl;
        std::clog << " mejor aproximacion en media cuadratica " << std::endl;
        std::clog << std::endl;
      }
    std::cout << "         - 0- ";
    for(j=1;j<=holgura;j++)
      std::cout << "  -" << libres[j] << "-  ";
    std::cout << std::endln;
    for(j=1;j<=n;j++)
      {
        std::cout << " -" << j << "- ";
        for(i=1;i<=holgura+1;i++)
          std::cout << x[i,j];
        std::cout << std::endl;
      }
    if(!compatible)
      {
        std::clog << std::endl;
        std::clog << " error cuadratico medio = " << error;
        std::clog << std::endl;
      }
  }
#endif

