#line 2 "src/Gui/BillPay/Item.h"

#ifndef __GCW_GUI_BILLPAYITEM_H___
#define __GCW_GUI_BILLPAYITEM_H___

#include "../../Dbo/Vars/Vars.h"

namespace GCW {
  namespace Gui {
    namespace BillPay {

/*!
** \brief Bill Pay Item
**
** This item contains all the bits of the bill-pay
**  tool.  This object is a controller for a single
**  bill-pay-item.  It is used to receive payments
**  and assist with the process of paying bills and
**  recording the confirmation codes and so on.
**
*/
class Item
{
  public:

    Item( GCW::Dbo::Vars::Item::Ptr _varItem ) ;

    /*!
    ** \brief Item GUID
    **
    */
    auto guid() const-> std::string ;

    /*!
    ** \brief Account GUID
    **
    ** This is the account that this bill-pay item is
    **  tied to.  When a payment is made, from some
    **  other account, it is posted to .this. account.
    **
    */
    auto accountGuid() const-> std::string ;

    /*!
    ** \brief Pay-From Account
    **
    ** This holds the GUID of the account that last made
    **  the payment.  This ID will get recalled on subsequent
    **  payments, to faciliate rapid payment processing
    **  functions.
    **
    */
    auto payFromGuid       () const-> std::string ;
    auto accountFullName   () const-> std::string ;
    auto dueDay            () const-> std::string ;
    auto minimum           () const-> std::string ;
    auto budget            () const-> std::string ;
    auto nickname          () const-> std::string ;
    auto group             () const-> std::string ;
    auto limit             () const-> std::string ;
    auto actual            () const-> std::string ;
    auto url               () const-> std::string ;
    auto ap                () const-> std::string ;
    auto isActive          () const-> std::string ;
    auto isVisible         () const-> std::string ;
    auto autoPay           () const-> std::string ;
    auto payNow            () const-> std::string ;
    auto last4             () const-> std::string ;
    auto note              () const-> std::string ;
    auto cb( int _index     ) const-> std::string ;

    auto set_accountGuid   ( const Wt::WString & _value )-> void ;
    auto set_dueDay        ( const Wt::WString & _value )-> void ;
    auto set_minimum       ( const Wt::WString & _value )-> void ;
    auto set_budget        ( const Wt::WString & _value )-> void ;
    auto set_nickname      ( const Wt::WString & _value )-> void ;
    auto set_group         ( const Wt::WString & _value )-> void ;
    auto set_limit         ( const Wt::WString & _value )-> void ;
    auto set_actual        ( const Wt::WString & _value )-> void ;
    auto set_url           ( const Wt::WString & _value )-> void ;
    auto set_ap            ( const Wt::WString & _value )-> void ;
    auto set_isActive      ( const Wt::WString & _value )-> void ;
    auto set_isVisible     ( const Wt::WString & _value )-> void ;
    auto set_autoPay       ( const Wt::WString & _value )-> void ;
    auto set_payNow        ( const Wt::WString & _value )-> void ;
    auto set_last4         ( const Wt::WString & _value )-> void ;
    auto set_note          ( const Wt::WString & _value )-> void ;
    auto set_cb( int _index, const Wt::WString & _value )-> void ;

    /*!
    ** \brief Sort Value
    **
    ** This produces a value suitable for sorting the model.
    **
    ** The model gets sorted on the 'group.dueDay' value.  This
    **  provides a nice group/sorted display of the bills-due view.
    **  All items that share the same group appear in the same area
    **  and subsequent items are sorted on the dueDay value.
    */
    auto sortValue() const -> float ;

    auto setVar( const std::string & _key, const Wt::WString & _value )-> void ;

    GCW::Dbo::Vars::Item::Ptr m_varItem ;

}; // endclass Item

    } // endnamespace BillPay {
  } // endnamespace Gui {
} // endnamespace GCW {

#endif // __GCW_GUI_BILLPAYITEM_H___



