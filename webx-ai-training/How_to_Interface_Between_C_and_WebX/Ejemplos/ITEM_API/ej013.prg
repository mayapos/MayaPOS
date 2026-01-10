//------------------------------------------------------------------------------
// Ejercicio uso de metodos en C. Ejecutar metodos PRG desde C
// ej013.prg
//------------------------------------------------------------------------------

#include "HBClass.ch"

PROCEDURE main

   LOCAL oModel := TMiModelo():new( "Manu", "Exposito", 57, 1200 )

   oModel:verDatosModelo()

   cambiaDatosEnC( oModel )
   oModel:verDatosModelo()

   cambiaDatosEnCPar( oModel, "Gerogina", "Gamero", 33, 4523.65 )
   oModel:verDatosModelo()

RETURN

//------------------------------------------------------------------------------

CREATE CLASS TMiModelo

   HIDDEN:
   DATA cNombre
   DATA cApellido
   DATA nEdad
   DATA nSueldo

   EXPORTED:
   CONSTRUCTOR new( cNombre, cApellido, nEdad, nSueldo )
   METHOD cambiaDatos( cNombre, cApellido, nEdad, nSueldo )
   METHOD isMayorEdad()
   METHOD guardaModelo()
   METHOD leeModelo()
   METHOD verDatosModelo()

   // Metodos SET / GET
   METHOD getNombre()
   METHOD setNombre( cNombre )
   METHOD getApellido()
   METHOD setApellido( cApellido )
   METHOD getEdad()
   METHOD setEdad( nEdad )
   METHOD getSueldo()
   METHOD setSueldo( nSueldo )

END CLASS

//------------------------------------------------------------------------------

METHOD new( cNombre, cApellido, nEdad, nSueldo ) CLASS TMiModelo

   ::cambiaDatos( cNombre, cApellido, nEdad, nSueldo )

RETURN self

//------------------------------------------------------------------------------

METHOD cambiaDatos( cNombre, cApellido, nEdad, nSueldo ) CLASS TMiModelo

   IF ValType( cNombre ) == 'C'
      ::cNombre := cNombre
   ENDIF

   IF ValType( cApellido ) == 'C'
      ::cApellido := cApellido
   ENDIF

   IF ValType( nEdad ) == 'N'
      ::nEdad := nEdad
   ENDIF

   IF ValType( nSueldo ) == 'N'
      ::nSueldo := nSueldo
   ENDIF

return self

//------------------------------------------------------------------------------

METHOD isMayorEdad() CLASS TMiModelo
RETURN ::nEdad >= 18

//------------------------------------------------------------------------------

METHOD guardaModelo() CLASS TMiModelo

   LOCAL lRet := .F.

   Alert( "Aqui se persiste el modelo" )

RETURN lRet

//------------------------------------------------------------------------------

METHOD leeModelo() CLASS TMiModelo

   LOCAL lRet := .F.

   Alert( "Aqui se carga el modelo desde el DataSet" )

RETURN lRet

//------------------------------------------------------------------------------

METHOD verDatosModelo() CLASS TMiModelo

   Alert( "INFORMACION;-----------;" + ";" + ;
          "Nombre...: " + ::getNombre() + ";" + ;
          "Apellido.: " + ::getApellido() + ";" + ;
          "Edad.....: " + hb_ntos( ::getEdad() ) + ";" + ;
          "Sueldo...: " + hb_ntos( ::getSueldo() ) )

RETURN self

//------------------------------------------------------------------------------
// Metodos SET / GET

METHOD getNombre() CLASS TMiModelo
RETURN ::cNombre

//------------------------------------------------------------------------------

METHOD setNombre( cNombre ) CLASS TMiModelo

   IF ValType( cNombre ) == 'C' .AND. !Empty( cNombre )
      ::cNombre := cNombre
   ENDIF

RETURN self

//------------------------------------------------------------------------------

METHOD getApellido() CLASS TMiModelo
RETURN ::cApellido

//------------------------------------------------------------------------------

METHOD setApellido( cApellido ) CLASS TMiModelo

   IF ValType( cApellido ) == 'C' .AND. !Empty( cApellido )
      ::cApellido := cApellido
   ENDIF

RETURN self

//------------------------------------------------------------------------------

METHOD getEdad() CLASS TMiModelo
RETURN ::nEdad

//------------------------------------------------------------------------------

METHOD setEdad( nEdad ) CLASS TMiModelo

   IF ValType( nEdad ) == 'N' .AND. edad > 0
      ::nEdad := nEdad
   ENDIF

RETURN self

//------------------------------------------------------------------------------

METHOD getSueldo() CLASS TMiModelo
RETURN ::nSueldo

//------------------------------------------------------------------------------

METHOD setSueldo( nSueldo ) CLASS TMiModelo

   IF ValType( nSueldo ) == 'N' .AND. nSueldo > 0
      ::nSueldo := nSueldo
   ENDIF

RETURN self

//------------------------------------------------------------------------------
