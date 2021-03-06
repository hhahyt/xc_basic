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
//ExprBase.h

#ifndef EXPRBASE_H
#define EXPRBASE_H

#include "ProtoExpr.h"

class ExprBase: public ProtoExpresion
  {
  protected:
    bool err_traduc; //!< Verdadero si se produce un error en la traducción.
  public:
    //! @brief Constructor por defecto.
    ExprBase(const bool &ET)
      : ProtoExpresion(), err_traduc(ET) {}
    //! @brief Devuelve verdadero si ha habido errores en la traducción.
    inline bool ErrorTraduccion(void) const
      { return err_traduc; }
  };

#endif













