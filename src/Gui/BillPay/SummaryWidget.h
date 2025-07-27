#line 2 "src/Gui/BillPay/SummaryWidget.h"

#ifndef __GUI_BILLPAY_SUMMARYWIDGET_H___
#define __GUI_BILLPAY_SUMMARYWIDGET_H___

#include <Wt/WContainerWidget.h>
#include <Wt/WLabel.h>
#include <Wt/WTemplate.h>
#include <Wt/WText.h>
#include <Wt/WTable.h>

namespace GCW {
  namespace Gui {
    namespace BillPay {

/*!
** \brief Summary Widget
**
** Bill Pay Summary Widget
**

*/
class SummaryWidget
: public Wt::WContainerWidget
{
  public:

    SummaryWidget( );

    auto setMonth( int _month )-> void ;

  private:

    class Splits
    {
      public:

#ifdef NEVER
      typedef struct PAYMENT_S
      {
        int         day   ;
        std::string guid  ;
        std::string bank  ;
        std::string bill  ;
        GCW_NUMERIC value ;
      } Split_t;
#endif

        Splits( int _month );

        /*
        ** this returns all the guids of all the splits
        */
        auto splitGuids () const-> std::vector< std::string > ;

        /*
        ** return all the days represented by all the splits
        */
        auto days() const-> std::set< int > ;

        /*
        ** return a list of payments made on a day
        */
        auto dayPayments( int _day ) const-> std::vector< std::string > ;

        /*
        ** return all the pay-froms represented
        */
        auto payFroms() const-> std::set< std::string > ;

        /*
        ** return all the days represented by this one payFrom account
        */
        auto payFromDays( const std::string & _payFrom ) const-> std::set< int > ;

        /*
        ** return all the payment splits that were paid from this
        **  account and paid on this day
        */
        auto paymentSplits( const std::string & _payFrom, int _day ) const-> std::vector< std::string > ;

        int m_month = -1;
        std::vector< std::string > m_splitGuids;

    };

    int          m_month = -1      ;
    Wt::WText  * m_title = nullptr ;
    Wt::WTable * m_table = nullptr ;

}; // endclass SummaryWidget

    } // endnamespace BillPay {
  } // endnamespace Gui {
} // endnamespace GCW {

#endif // __GUI_BILLPAY_SUMMARYWIDGET_H___


