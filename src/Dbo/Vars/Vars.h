#line 2 "src/Dbo/Vars.h"

#ifndef __DBO_VARS_H___
#define __DBO_VARS_H___

#include "../BaseItem.h"
#include "Var.h"

/*
** Predefine the class that fixin to come up.
**
*/
namespace GCW {
  namespace Dbo {
    namespace Vars {
      class Item;
    }
  }
}

/*
** Now we can start building our class!
**
*/
namespace GCW {
  namespace Dbo {
    namespace Vars {

/*!
** \brief Variables Item Class
**
**
*/
class Item
: public GCW::Dbo::BaseItem< Item >
{
  public:

    const std::string & keyField () const { return m_keyField ; }
    const std::string & cfyField () const { return m_cfyField ; }
    const std::string & varField () const { return m_varField ; }

    void setKeyField( const std::string & _value ) { m_keyField = _value; }
    void setCfyField( const std::string & _value ) { m_cfyField = _value; }
    void setVarField( const std::string & _value ) { m_varField = _value; }

          std::string getVarString( const std::string & _field ) const;
          int         getVarInt( const std::string & _field ) const;
    void              setVar( const std::string & _field, const char *        _value );
    void              setVar( const std::string & _field, const Wt::WString & _value );
    void              setVar( const std::string & _field, const std::string & _value );
    void              setVar( const std::string & _field, int _value );

    template< class Action > void persist( Action & action )
    {
      Wt::Dbo::field( action, m_keyField , GCW::Dbo::Var::Field:: keyField, 32 );
      Wt::Dbo::field( action, m_cfyField , GCW::Dbo::Var::Field:: cfyField, 32 );
      Wt::Dbo::field( action, m_varField , GCW::Dbo::Var::Field:: varField     );
    }

  private:

    std::string m_keyField ;
    std::string m_cfyField ;
    std::string m_varField ;

}; // endclass Item

auto get( const std::string & _keyValue, const std::string & _cfyValue = "*", bool _add = true )-> GCW::Dbo::Vars::Item::Ptr ;
auto getByCfy( const std::string & _cfyValue )-> GCW::Dbo::Vars::Item::Vector ;

extern const char * s_tableName;

    } // endnamespace Vars {
  } // endnamespace Dbo {
} // endnamespace GCW {

#endif // end#ifndef __VARS_H___

