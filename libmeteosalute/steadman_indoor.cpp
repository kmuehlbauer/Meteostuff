/***************************************************************************
 *   Copyright (C) 2012 by Graziano Giuliani                               *
 *   graziano.giuliani at poste.it                                         *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details. (see COPYING)            *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 *                                                                         *
 *   LIC: GPL                                                              *
 *                                                                         *
 ***************************************************************************/
// $Id: $

#include <meteosalute.h>
#include <cmath>

using namespace std;
using namespace Meteo;

float *Meteosalute::steadman_indoor(float *t, float *rh, float *p_hPa)
{ 
  if (vector_size <= 0) return 0;
  float *steadman_indoor = new float[vector_size];

  for (int i = 0; i < vector_size; i ++)
  {
    steadman_indoor[i] = 999.9;
    if (rh[i] > 100.1 || rh[i] < 0.0)
      continue;
    else if (t[i] > 100.0 || t[i] < -100.0)
      continue;
    else
    {
      float e = (rh[i]/100.0)*(6.105*exp((t[i]*17.27)/(237.7+t[i])));
      steadman_indoor[i] = -2.56+(0.89*t[i])+(0.382*e);  
    }
  }
  return steadman_indoor;
}

#ifdef TEST_ME

#include <iostream>

int main(int argc, char *argv[])
{
  const int V_SIZE = 1;
  Meteosalute m(V_SIZE);
  float t[V_SIZE] = { 30.0};
  float rh[V_SIZE] = { 75.0};
  float p_hPa[V_SIZE] = { 12.0};
  
  float *steadman_indoor = m.steadman_indoor(t, rh, p_hPa);

  float *res = steadman_indoor;
  for (int i = 0; i < V_SIZE; i ++)
  {
    std::cout << res[i] << std::endl;
  }
  return 0;
}

#endif
